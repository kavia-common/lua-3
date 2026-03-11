// drasim_lua/src/delta_api_bindings.cpp
// C++ implementations of Delta Robot Language API exposed to Lua.
// Modbus register access now uses the dictionary-backed MemoryImage:
// raw Modbus addresses are passed directly — no index translation required.
//
// Coroutine-based AuxTasks implementation:
//   - AuxTasksAdd(fn1, fn2, ...) creates a Lua coroutine per function via lua_newthread
//     and stores a registry reference to keep it alive.
//   - AuxTasks() round-robins across coroutines and resumes one step via lua_resume.
//   - DELAY/WAIT are implemented as yieldable primitives: they yield back to the host
//     scheduler so long-running tasks can be time-sliced without blocking.
//
// This version also provides:
//   - ON / OFF global constants (string "ON" / "OFF")
//   - SocketClass constructor + :Send() / :Receive() / :Close() methods
//     with simulated handshake responses to prevent infinite loops
//   - Point-offset arithmetic: X(), Y(), Z(), RX(), RY(), RZ()
//     returning userdata that support __add and __tostring metamethods
//   - DO() single-argument read-back (returns "ON"/"OFF")
//   - Improved ExtDI / ExtDO with state memory (simulated "ON" by default)
//   - HomeAuto() stub
//   - Improved WAIT supporting ExtDI table-index form
#include "drasim_lua/delta_api_bindings.hpp"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
}

#include <drasim_core/memory_image.hpp>
#include <drasim_core/io_mapping.hpp>
#include <drasim_core/modbus_mapping.hpp>

#include <chrono>
#include <cstddef>
#include <iostream>
#include <map>
#include <mutex>
#include <new>
#include <string>
#include <thread>
#include <vector>

namespace drasim_lua
{

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------
static bool status_to_bool(const char * s) { return s && std::string(s) == "ON"; }
static void push_on_off(lua_State * L, bool v) { lua_pushstring(L, v ? "ON" : "OFF"); }

// We encode DELAY/WAIT yields as a single yielded number: seconds to sleep.
// AuxTasks() reads this and stores it in per-task wakeup times.
static constexpr int LUA_YIELD_RETCOUNT = 1;

static double now_seconds_monotonic()
{
  using clock = std::chrono::steady_clock;
  const auto tp = clock::now().time_since_epoch();
  return std::chrono::duration<double>(tp).count();
}

// ---------------------------------------------------------------------------
// ExtDI / ExtDO in-process state (addr -> pin -> bool)
// ---------------------------------------------------------------------------
static std::mutex ext_io_mutex;
static std::map<int, std::map<int, bool>> ext_di_state;
static std::map<int, std::map<int, bool>> ext_do_state;

// ---------------------------------------------------------------------------
// Robot Control
// ---------------------------------------------------------------------------

// PUBLIC_INTERFACE
/// RobotServoOn() - Activate all-axis servo motors.
/// Must be called before any motion command.
static int l_RobotServoOn(lua_State * L)
{
  (void)L;
  std::cout << "[DeltaAPI] RobotServoOn: all-axis servo motors activated.\n";
  return 0;
}

// PUBLIC_INTERFACE
/// RobotServoOff() - Deactivate all-axis servo motors.
static int l_RobotServoOff(lua_State * L)
{
  (void)L;
  std::cout << "[DeltaAPI] RobotServoOff: all-axis servo motors deactivated.\n";
  return 0;
}

// PUBLIC_INTERFACE
/// MotionStop([Mode]) - Decelerate and stop ongoing robot motion.
/// Mode: omitted = current decel; "FBK" = stop at current speed, reset position error.
static int l_MotionStop(lua_State * L)
{
  const char * mode = luaL_optstring(L, 1, "");
  if (mode && std::string(mode) == "FBK") {
    std::cout << "[DeltaAPI] MotionStop(\"FBK\"): stop at current speed, reset position error.\n";
  } else {
    std::cout << "[DeltaAPI] MotionStop(): decelerating to stop.\n";
  }
  return 0;
}

// PUBLIC_INTERFACE
/// HomeAuto() - Automatic homing sequence (stub).
static int l_HomeAuto(lua_State * L)
{
  (void)L;
  std::cout << "[DeltaAPI] HomeAuto: automatic homing (simulated).\n";
  return 0;
}

// ---------------------------------------------------------------------------
// I/O
// ---------------------------------------------------------------------------

// PUBLIC_INTERFACE
/// DI(pin [,length]) -> "ON"/"OFF" | bitmask
/// Reads digital input pin state(s).
static int l_DI(lua_State * L)
{
  auto & mem     = drasim_core::MemoryImage::instance();
  auto & mapping = drasim_core::IOMapping::instance();
  std::size_t pin = 0;
  if (lua_isstring(L, 1) && !lua_isnumber(L, 1)) {
    pin = mapping.resolve_di(lua_tostring(L, 1));
  } else {
    pin = (std::size_t)luaL_checkinteger(L, 1);
  }
  int length = (int)luaL_optinteger(L, 2, 1);
  if (length == 1) { push_on_off(L, mem.get_di(pin)); return 1; }
  lua_pushinteger(L, (lua_Integer)mem.get_di_block(pin, (std::size_t)length));
  return 1;
}

// PUBLIC_INTERFACE
/// DO(pin) -> "ON"/"OFF"  (read-back form)
/// DO(pin, status [, delay])  (set form)
/// DO(pin, length, bitmask [, delay])  (block set form)
static int l_DO(lua_State * L)
{
  auto & mem     = drasim_core::MemoryImage::instance();
  auto & mapping = drasim_core::IOMapping::instance();
  std::size_t pin = 0;
  if (lua_isstring(L, 1) && !lua_isnumber(L, 1)) {
    pin = mapping.resolve_do(lua_tostring(L, 1));
  } else {
    pin = (std::size_t)luaL_checkinteger(L, 1);
  }

  // Read-only form: DO(pin) -> "ON"/"OFF"
  if (lua_gettop(L) == 1) {
    push_on_off(L, mem.get_do(pin));
    return 1;
  }

  if (lua_isstring(L, 2)) {
    bool s = status_to_bool(lua_tostring(L, 2));
    mem.set_do(pin, s);
    double d = luaL_optnumber(L, 3, 0.0);
    if (d > 0.0) {
      std::thread([pin, d, s] {
        std::this_thread::sleep_for(std::chrono::duration<double>(d));
        drasim_core::MemoryImage::instance().set_do(pin, !s);
      }).detach();
    }
  } else {
    int len       = (int)luaL_checkinteger(L, 2);
    uint32_t mask = (uint32_t)luaL_checkinteger(L, 3);
    double d      = luaL_optnumber(L, 4, 0.0);
    for (int i = 0; i < len; ++i) {
      mem.set_do(pin + (std::size_t)i, (mask & (1u << i)) != 0);
    }
    if (d > 0.0) {
      std::thread([pin, len, mask, d] {
        std::this_thread::sleep_for(std::chrono::duration<double>(d));
        auto & m = drasim_core::MemoryImage::instance();
        for (int i = 0; i < len; ++i) {
          m.set_do(pin + (std::size_t)i, (mask & (1u << i)) == 0);
        }
      }).detach();
    }
  }
  return 0;
}

// PUBLIC_INTERFACE
/// ExtDI(addr, pin) -> "ON"/"OFF"
/// Simulated: returns "ON" by default (ready state) to avoid infinite WAIT loops.
/// Reflects state driven by ExtDO for same addr/pin.
static int l_ExtDI(lua_State * L)
{
  int addr = (int)luaL_checkinteger(L, 1);
  int pin  = (int)luaL_checkinteger(L, 2);
  std::lock_guard<std::mutex> lk(ext_io_mutex);
  // Check if this addr/pin was explicitly set
  auto a_it = ext_di_state.find(addr);
  if (a_it != ext_di_state.end()) {
    auto p_it = a_it->second.find(pin);
    if (p_it != a_it->second.end()) {
      push_on_off(L, p_it->second);
      return 1;
    }
  }
  // Default: "ON" (simulated ready state)
  push_on_off(L, true);
  return 1;
}

// PUBLIC_INTERFACE
/// ExtDO(addr, pin, status [, delay])
/// Sets external digital output and feeds back to ExtDI for simulation.
static int l_ExtDO(lua_State * L)
{
  int addr        = (int)luaL_checkinteger(L, 1);
  int pin         = (int)luaL_checkinteger(L, 2);
  const char * st = luaL_checkstring(L, 3);
  bool val        = status_to_bool(st);
  {
    std::lock_guard<std::mutex> lk(ext_io_mutex);
    ext_do_state[addr][pin] = val;
    // Feedback loop: ExtDI reflects the driven state for simulation
    ext_di_state[addr][pin] = val;
  }
  std::cout << "[DeltaAPI] ExtDO addr=" << addr << " pin=" << pin << " " << st << "\n";
  return 0;
}

// ---------------------------------------------------------------------------
// ReadModbus / WriteModbus
// ---------------------------------------------------------------------------

// PUBLIC_INTERFACE
/// ReadModbus(address, size) -> integer
/// Reads from the dictionary-backed MemoryImage at the given raw Modbus address.
static int l_ReadModbus(lua_State * L)
{
  uint32_t addr   = (uint32_t)luaL_checkinteger(L, 1);
  const char * sz = luaL_checkstring(L, 2);
  auto & mem      = drasim_core::MemoryImage::instance();

  if (!drasim_core::ModbusMapping::is_valid(addr)) {
    lua_pushinteger(L, 0);
    return 1;
  }

  int32_t v = (std::string(sz) == "DW")
    ? mem.read_dword(addr)
    : static_cast<int32_t>(mem.read_word(addr));
  lua_pushinteger(L, (lua_Integer)v);
  return 1;
}

// PUBLIC_INTERFACE
/// WriteModbus(address, size, value)
/// Writes to the dictionary-backed MemoryImage at the given raw Modbus address.
static int l_WriteModbus(lua_State * L)
{
  uint32_t addr   = (uint32_t)luaL_checkinteger(L, 1);
  const char * sz = luaL_checkstring(L, 2);
  int32_t value   = (int32_t)luaL_checkinteger(L, 3);

  if (!drasim_core::ModbusMapping::is_valid(addr)) { return 0; }

  auto & mem = drasim_core::MemoryImage::instance();
  if (std::string(sz) == "DW") {
    mem.write_dword(addr, value);
  } else {
    mem.write_word(addr, static_cast<int16_t>(value));
  }
  return 0;
}

// ---------------------------------------------------------------------------
// Point-offset system
//
// Delta robot motion commands accept expressions like:
//   MovP("Fix1" + Z(80) + RX(-180))
//
// We model this with a Lua userdata "PointExpr" that holds a base point name
// and a list of axis offsets. The __add metamethod combines them.
// Strings lack __add normally but since PointExpr is right operand, its
// __add is tried when the left operand (string) has no __add.
// ---------------------------------------------------------------------------
static const char * POINT_EXPR_MT = "DeltaAPI.PointExpr";

struct PointExpr {
  std::string base;  // point name (or empty for pure-offset)
  double x{0.0}, y{0.0}, z{0.0};
  double rx{0.0}, ry{0.0}, rz{0.0};
};

/// Push a new PointExpr userdata on the stack.
static PointExpr * push_point_expr(lua_State * L)
{
  auto * pe = static_cast<PointExpr *>(lua_newuserdata(L, sizeof(PointExpr)));
  new (pe) PointExpr{};
  luaL_getmetatable(L, POINT_EXPR_MT);
  lua_setmetatable(L, -2);
  return pe;
}

/// __tostring metamethod: returns base name.
static int pe_tostring(lua_State * L)
{
  auto * pe = static_cast<PointExpr *>(luaL_checkudata(L, 1, POINT_EXPR_MT));
  lua_pushstring(L, pe->base.c_str());
  return 1;
}

/// __add metamethod: handles string+PointExpr, PointExpr+PointExpr, PointExpr+string.
static int pe_add(lua_State * L)
{
  PointExpr lhs{}, rhs{};

  // Parse left operand
  if (luaL_testudata(L, 1, POINT_EXPR_MT)) {
    lhs = *static_cast<PointExpr *>(lua_touserdata(L, 1));
  } else if (lua_isstring(L, 1)) {
    lhs.base = lua_tostring(L, 1);
  }

  // Parse right operand
  if (luaL_testudata(L, 2, POINT_EXPR_MT)) {
    rhs = *static_cast<PointExpr *>(lua_touserdata(L, 2));
  } else if (lua_isstring(L, 2)) {
    rhs.base = lua_tostring(L, 2);
  }

  // Merge: use the non-empty base name
  PointExpr * res = push_point_expr(L);
  res->base = lhs.base.empty() ? rhs.base : lhs.base;
  res->x  = lhs.x  + rhs.x;
  res->y  = lhs.y  + rhs.y;
  res->z  = lhs.z  + rhs.z;
  res->rx = lhs.rx + rhs.rx;
  res->ry = lhs.ry + rhs.ry;
  res->rz = lhs.rz + rhs.rz;
  return 1;
}

/// __gc metamethod for PointExpr.
static int pe_gc(lua_State * L)
{
  auto * pe = static_cast<PointExpr *>(luaL_checkudata(L, 1, POINT_EXPR_MT));
  pe->~PointExpr();
  return 0;
}

/// Extract point name from stack position (string or PointExpr).
static std::string point_name(lua_State * L, int idx)
{
  if (luaL_testudata(L, idx, POINT_EXPR_MT)) {
    return static_cast<PointExpr *>(lua_touserdata(L, idx))->base;
  }
  if (lua_isstring(L, idx)) { return lua_tostring(L, idx); }
  if (lua_isinteger(L, idx)) { return std::to_string((int)lua_tointeger(L, idx)); }
  return "<unknown>";
}

/// Register the PointExpr metatable.
static void register_point_expr_mt(lua_State * L)
{
  luaL_newmetatable(L, POINT_EXPR_MT);

  lua_pushcfunction(L, pe_add);
  lua_setfield(L, -2, "__add");

  lua_pushcfunction(L, pe_tostring);
  lua_setfield(L, -2, "__tostring");

  lua_pushcfunction(L, pe_gc);
  lua_setfield(L, -2, "__gc");

  // __index = self (so methods on instances survive)
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");

  lua_pop(L, 1);
}

/// Offset constructor: X(n), Y(n), Z(n), RX(n), RY(n), RZ(n)
/// Each returns a PointExpr userdata with only that offset field set.
#define MAKE_OFFSET_FN(fname, field) \
  static int l_##fname(lua_State * L) { \
    double v = luaL_checknumber(L, 1); \
    PointExpr * pe = push_point_expr(L); \
    pe->field = v; \
    return 1; \
  }

MAKE_OFFSET_FN(X,  x)
MAKE_OFFSET_FN(Y,  y)
MAKE_OFFSET_FN(Z,  z)
MAKE_OFFSET_FN(RX, rx)
MAKE_OFFSET_FN(RY, ry)
MAKE_OFFSET_FN(RZ, rz)

// ---------------------------------------------------------------------------
// Motion commands — accept string or PointExpr as first arg
// ---------------------------------------------------------------------------

// PUBLIC_INTERFACE
/// MovJ(joint, degree [, SPD(n)]) - Move single joint to target angle.
static int l_MovJ(lua_State * L)
{
  int joint  = (int)luaL_checkinteger(L, 1);
  double deg = luaL_checknumber(L, 2);
  std::cout << "[DeltaAPI] MovJ joint=" << joint << " deg=" << deg << "\n";
  return 0;
}

// PUBLIC_INTERFACE
/// MovL(point [+ offsets]) - Linear move to named point with optional offsets.
static int l_MovL(lua_State * L)
{
  std::string p = point_name(L, 1);
  std::cout << "[DeltaAPI] MovL point=" << p << "\n";
  return 0;
}

// PUBLIC_INTERFACE
/// MovP(point [+ offsets]) - PTP move to named point with optional offsets.
static int l_MovP(lua_State * L)
{
  std::string p = point_name(L, 1);
  std::cout << "[DeltaAPI] MovP point=" << p << "\n";
  return 0;
}

// ---------------------------------------------------------------------------
// Yielding primitives
// ---------------------------------------------------------------------------

// PUBLIC_INTERFACE
/// DELAY(seconds) - Yield for the specified number of seconds (cooperative scheduling).
static int l_DELAY(lua_State * L)
{
  const double s = luaL_checknumber(L, 1);
  // Yield to scheduler; AuxTasks() will resume this coroutine after s seconds.
  lua_pushnumber(L, s > 0.0 ? s : 0.0);
  return lua_yield(L, LUA_YIELD_RETCOUNT);
}

static int l_SpdJ(lua_State * L)
{
  std::cout << "[DeltaAPI] SpdJ=" << luaL_checknumber(L, 1) << "%\n";
  return 0;
}
static int l_AccJ(lua_State * L)
{
  std::cout << "[DeltaAPI] AccJ=" << luaL_checknumber(L, 1) << "%\n";
  return 0;
}
static int l_DecJ(lua_State * L)
{
  std::cout << "[DeltaAPI] DecJ=" << luaL_checknumber(L, 1) << "%\n";
  return 0;
}
static int l_SpdL(lua_State * L)
{
  std::cout << "[DeltaAPI] SpdL=" << luaL_checknumber(L, 1) << "mm/s\n";
  return 0;
}
static int l_AccL(lua_State * L)
{
  std::cout << "[DeltaAPI] AccL=" << luaL_checknumber(L, 1) << "mm/s2\n";
  return 0;
}
static int l_DecL(lua_State * L)
{
  std::cout << "[DeltaAPI] DecL=" << luaL_checknumber(L, 1) << "mm/s2\n";
  return 0;
}
static int l_Accur(lua_State * L)
{
  std::cout << "[DeltaAPI] Accur=" << luaL_checkstring(L, 1) << "\n";
  return 0;
}

static int l_SetGlobalPoint(lua_State * L)
{
  int pt          = (int)luaL_checkinteger(L, 1);
  const char * nm = luaL_checkstring(L, 2);
  double x        = luaL_optnumber(L, 3, 0.0);
  double y        = luaL_optnumber(L, 4, 0.0);
  double z        = luaL_optnumber(L, 5, 0.0);
  std::cout << "[DeltaAPI] SetGlobalPoint pt=" << pt << " name=" << nm
            << " X=" << x << " Y=" << y << " Z=" << z << "\n";
  return 0;
}

static int l_ReadPoint(lua_State * L)
{
  const char * pt = luaL_checkstring(L, 1);
  const char * it = luaL_checkstring(L, 2);
  std::cout << "[DeltaAPI] ReadPoint pt=" << pt << " item=" << it << "\n";
  // Return 0.0 for all coordinate queries (simulation)
  lua_pushnumber(L, 0.0);
  return 1;
}

// ---------------------------------------------------------------------------
// WAIT — supports:
//   WAIT(DI/DO, pin, "ON"/"OFF" [, timeout_ms])
//   WAIT(ExtDI, {addr, pin}, "ON"/"OFF" [, timeout_ms])
//   WAIT(DI, {p1,p2,...}, "ON"/"OFF" [, timeout_ms])
//
// Coroutine version: yields with a small slice so callers spinning in loops
// can be time-sliced. In this simulation we generally satisfy immediately,
// but we still yield once to enable cooperative scheduling and avoid blocking.
// ---------------------------------------------------------------------------

// PUBLIC_INTERFACE
/// WAIT(io_type, pin_or_table, status [, timeout_ms])
/// Cooperative wait: yields back to scheduler to time-slice long-running scripts.
/// In simulation, conditions are generally satisfied immediately (ExtDI always ON).
static int l_WAIT(lua_State * L)
{
  if (!lua_isstring(L, 1)) { return 0; }
  std::string io_type = lua_tostring(L, 1);

  // In the real controller, WAIT blocks until condition or timeout.
  // Here we emulate "non-blocking" by yielding briefly; scripts that call WAIT
  // inside loops will give time back to AuxTasks.
  // Use ~15ms slice like Delta docs mention.
  lua_pushnumber(L, 0.015);
  return lua_yield(L, LUA_YIELD_RETCOUNT);
}

// ---------------------------------------------------------------------------
// AuxTasksAdd / AuxTasks  — coroutine-based cooperative multi-task scheduler
//
// Design
// ------
//  AuxTasksAdd(fn1, fn2, ...) creates a Lua thread (coroutine) for each fn.
//  The function is moved onto the thread's stack and resumed once to start.
//
//  DELAY/WAIT yield a single numeric return: seconds to sleep.
//  AuxTasks() stores per-thread wakeup time and only resumes runnable threads.
//
//  This structure allows a long-running fn containing `while true do ... end`
//  to still make progress if it calls DELAY/WAIT (or any other yielding API).
// ---------------------------------------------------------------------------

static constexpr int MAX_AUX_TASKS = 10;

struct AuxTask
{
  lua_State * thread{nullptr}; // coroutine
  int thread_ref{LUA_NOREF};   // registry ref holding the coroutine object alive
  bool alive{false};           // still runnable? (not completed)
  double wake_at{0.0};         // monotonic seconds; runnable when now >= wake_at
};

static AuxTask aux_tasks[MAX_AUX_TASKS];
static int aux_task_count = 0;
static int aux_task_index = 0;
static bool aux_tasks_initialized = false;

static void reset_aux_tasks(lua_State * L)
{
  for (int i = 0; i < MAX_AUX_TASKS; ++i) {
    if (aux_tasks[i].thread_ref != LUA_NOREF && aux_tasks[i].thread_ref != LUA_REFNIL) {
      luaL_unref(L, LUA_REGISTRYINDEX, aux_tasks[i].thread_ref);
    }
    aux_tasks[i] = AuxTask{};
  }
  aux_task_count = 0;
  aux_task_index = 0;
  aux_tasks_initialized = false;
}

// Parse yielded sleep seconds from thread stack (top), defaulting to 0.
static double parse_yield_sleep_seconds(lua_State * thread)
{
  if (lua_gettop(thread) >= 1 && lua_isnumber(thread, -1)) {
    const double s = lua_tonumber(thread, -1);
    lua_settop(thread, 0); // clear yielded values
    return (s > 0.0) ? s : 0.0;
  }
  lua_settop(thread, 0);
  return 0.0;
}

// PUBLIC_INTERFACE
/**
 * @brief AuxTasksAdd(fn1 [, fn2, ...]) — register Lua functions for coroutine time-slicing.
 *
 * Each argument must be a Lua function. For each function, we create a coroutine
 * via lua_newthread(), store a registry reference to keep it alive, move the
 * function onto the coroutine stack, and mark it runnable.
 *
 * Calling AuxTasksAdd again replaces the previously registered set.
 *
 * @param L Active Lua main state.
 * @return 0
 */
static int l_AuxTasksAdd(lua_State * L)
{
  const int n_args = lua_gettop(L);

  reset_aux_tasks(L);

  int n = n_args;
  if (n > MAX_AUX_TASKS) {
    std::cerr << "[DeltaAPI] AuxTasksAdd: " << n << " functions given; "
              << "only first " << MAX_AUX_TASKS << " will be used.\n";
    n = MAX_AUX_TASKS;
  }

  for (int i = 1; i <= n; ++i) {
    if (!lua_isfunction(L, i)) {
      std::cerr << "[DeltaAPI] AuxTasksAdd: argument " << i
                << " is not a function (type=" << lua_typename(L, lua_type(L, i))
                << "); skipping.\n";
      continue;
    }

    // Create coroutine; pushes thread object onto main stack.
    lua_State * T = lua_newthread(L);

    // Store registry ref to keep coroutine alive (pops thread object).
    const int tref = luaL_ref(L, LUA_REGISTRYINDEX);

    // Move function onto the coroutine's stack (as its entry function).
    lua_pushvalue(L, i);
    lua_xmove(L, T, 1);

    AuxTask & task = aux_tasks[aux_task_count];
    task.thread = T;
    task.thread_ref = tref;
    task.alive = true;
    task.wake_at = 0.0;

    ++aux_task_count;
  }

  aux_task_index = 0;
  aux_tasks_initialized = true;

  std::cout << "[DeltaAPI] AuxTasksAdd: registered " << aux_task_count
            << " coroutine task(s).\n";
  return 0;
}

// PUBLIC_INTERFACE
/**
 * @brief AuxTasks() — resume one runnable coroutine in round-robin order.
 *
 * Resumes at most one coroutine per call. If the coroutine yields with a numeric
 * value, it is interpreted as sleep seconds and the coroutine will not be
 * resumed again until that time elapses.
 *
 * If all tasks are sleeping, AuxTasks() will sleep briefly (~1ms) to avoid
 * busy-spinning.
 *
 * @param L Active Lua main state.
 * @return 0
 */
static int l_AuxTasks(lua_State * L)
{
  if (!aux_tasks_initialized || aux_task_count <= 0) {
    std::this_thread::sleep_for(std::chrono::milliseconds(15));
    return 0;
  }

  const double now = now_seconds_monotonic();

  // Find one runnable task (not finished and not sleeping) in RR order.
  int tried = 0;
  int selected = -1;
  for (; tried < aux_task_count; ++tried) {
    const int idx = (aux_task_index + tried) % aux_task_count;
    AuxTask & task = aux_tasks[idx];
    if (!task.alive || task.thread == nullptr) {
      continue;
    }
    if (now >= task.wake_at) {
      selected = idx;
      break;
    }
  }

  // Advance RR pointer for next invocation (even if no runnable task found).
  aux_task_index = (aux_task_index + 1) % aux_task_count;

  if (selected < 0) {
    // All alive tasks are sleeping; back off a bit.
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    return 0;
  }

  AuxTask & task = aux_tasks[selected];
  lua_State * T = task.thread;

  // Resume coroutine with 0 args.
  int nres = 0;
  const int rc = lua_resume(T, L, 0, &nres);

  if (rc == LUA_YIELD) {
    // Interpret yielded value as sleep seconds (optional).
    const double sleep_s = parse_yield_sleep_seconds(T);
    task.wake_at = now_seconds_monotonic() + sleep_s;
  } else if (rc == LUA_OK) {
    // Finished; mark dead.
    task.alive = false;
    task.wake_at = 0.0;
    lua_settop(T, 0);
  } else {
    // Error: lua_resume leaves error message on T stack.
    const char * err = lua_tostring(T, -1);
    std::cerr << "[DeltaAPI] AuxTasks: error in task " << selected
              << ": " << (err ? err : "(unknown error)") << "\n";
    lua_settop(T, 0);
    task.alive = false;
  }

  return 0;
}

// ---------------------------------------------------------------------------
// split(str, pat) -> table
// ---------------------------------------------------------------------------

// PUBLIC_INTERFACE
/// split(str, pat) - Split string by delimiter, return array table.
static int l_split(lua_State * L)
{
  std::string str = luaL_checkstring(L, 1);
  std::string pat = luaL_checkstring(L, 2);
  lua_newtable(L);
  int tbl_idx = 1;
  std::size_t pos = 0, found;
  while ((found = str.find(pat, pos)) != std::string::npos) {
    lua_pushstring(L, str.substr(pos, found - pos).c_str());
    lua_rawseti(L, -2, tbl_idx++);
    pos = found + pat.size();
  }
  lua_pushstring(L, str.substr(pos).c_str());
  lua_rawseti(L, -2, tbl_idx);
  return 1;
}

// ---------------------------------------------------------------------------
// SocketClass implementation
//
// The Delta robot controller uses a Lua userdata class (SocketClass) that
// maintains a TCP connection to external devices. In this simulation we
// stub the networking; Receive() returns pre-programmed handshake strings
// so that the main.txt handshake loops exit normally:
//
//   tcp5    (port 2005)  -> first Receive returns {"IOT"}
//   RBSocket01 (port 2000) -> first Receive returns {"01_R"}
//   SocketTest3 (port 2003) -> Receive returns {"01_P"}, {"02_P"}, {"03_P"}
//   SocketTest4 (port 2004) -> Receive returns {"01_P"}
//   All other sockets    -> Receive returns nil
// ---------------------------------------------------------------------------
static const char * SOCKET_MT = "DeltaAPI.SocketClass";

struct SocketObj {
  std::string  host;
  int          port{0};
  std::string  spacing;
  std::string  delimiter;
  double       sleeptime{0.1};
  double       timeout{10.0};
  bool         closed{false};
  int          recv_count{0};
  std::vector<std::string> handshake_responses;
};

// PUBLIC_INTERFACE
/// SocketClass(host, port, spacing, delimiter, cmd, sleeptime, timeout) -> socket userdata
/// Creates a simulated socket connection. Receive() returns pre-programmed handshake strings.
static int l_SocketClass(lua_State * L)
{
  const char * host = luaL_checkstring(L, 1);
  int port          = (int)luaL_checkinteger(L, 2);

  // arg 3: spacing  (nil or string)
  std::string spacing = ",";
  if (lua_isstring(L, 3) && !lua_isnil(L, 3)) {
    spacing = lua_tostring(L, 3);
  }

  // arg 4: delimiter (nil or string)
  std::string delimiter = "\r\n";
  if (lua_isstring(L, 4) && !lua_isnil(L, 4)) {
    delimiter = lua_tostring(L, 4);
  }

  // arg 5: cmd (ignored in simulation)
  // arg 6: sleeptime
  double sleeptime = lua_isnumber(L, 6) ? lua_tonumber(L, 6) : 0.1;
  // arg 7: timeout
  double timeout   = lua_isnumber(L, 7) ? lua_tonumber(L, 7) : 10.0;

  auto * sock = static_cast<SocketObj *>(lua_newuserdata(L, sizeof(SocketObj)));
  new (sock) SocketObj{};
  sock->host      = host;
  sock->port      = port;
  sock->spacing   = spacing;
  sock->delimiter = delimiter;
  sock->sleeptime = sleeptime;
  sock->timeout   = timeout;
  sock->recv_count = 0;

  // Pre-program port-specific handshake responses
  if (port == 2005) {
    // tcp5: main.txt waits for data5 == "IOT"
    sock->handshake_responses = {"IOT"};
  } else if (port == 2000 || port == 2001) {
    // RBSocket01: main.txt waits for CMD == "01_R" or "01_R,01_R"
    sock->handshake_responses = {"01_R"};
  } else if (port == 2003) {
    // SocketTest3: camera results — return pass for all fixtures
    sock->handshake_responses = {"01_P", "02_P", "03_P"};
  } else if (port == 2004) {
    // SocketTest4: VB test results — return pass
    sock->handshake_responses = {"01_P"};
  } else {
    sock->handshake_responses = {};
  }

  luaL_getmetatable(L, SOCKET_MT);
  lua_setmetatable(L, -2);

  std::cout << "[DeltaAPI] SocketClass: host=" << host << " port=" << port
            << " (simulated, " << sock->handshake_responses.size()
            << " handshake responses)\n";
  return 1;
}

// PUBLIC_INTERFACE
/// sock:Send(cmd) - Transmit data to the remote host (logged, not actually sent).
static int l_Socket_Send(lua_State * L)
{
  auto * sock = static_cast<SocketObj *>(luaL_checkudata(L, 1, SOCKET_MT));
  if (sock->closed) { return 0; }
  std::string cmd;
  if (lua_isstring(L, 2)) {
    cmd = lua_tostring(L, 2);
  } else if (lua_isnumber(L, 2)) {
    cmd = std::to_string((int)lua_tonumber(L, 2));
  }
  std::cout << "[DeltaAPI] Socket(port=" << sock->port << "):Send(\"" << cmd << "\")\n";
  return 0;
}

// PUBLIC_INTERFACE
/// sock:Receive() -> table or nil
/// Returns the next pre-programmed handshake response as a 1-element table.
/// Returns nil once all handshake responses have been consumed.
static int l_Socket_Receive(lua_State * L)
{
  auto * sock = static_cast<SocketObj *>(luaL_checkudata(L, 1, SOCKET_MT));
  if (sock->closed) { lua_pushnil(L); return 1; }

  int idx = sock->recv_count;
  if (idx < (int)sock->handshake_responses.size()) {
    const std::string & resp = sock->handshake_responses[idx];
    sock->recv_count++;
    lua_newtable(L);
    lua_pushstring(L, resp.c_str());
    lua_rawseti(L, -2, 1);
    std::cout << "[DeltaAPI] Socket(port=" << sock->port
              << "):Receive() -> \"" << resp << "\"\n";
    return 1;
  }

  // No more handshake data — return nil to signal no data
  lua_pushnil(L);
  return 1;
}

// PUBLIC_INTERFACE
/// sock:Close() - Close the simulated socket connection.
static int l_Socket_Close(lua_State * L)
{
  auto * sock = static_cast<SocketObj *>(luaL_checkudata(L, 1, SOCKET_MT));
  sock->closed = true;
  std::cout << "[DeltaAPI] Socket(port=" << sock->port << "):Close()\n";
  return 0;
}

// PUBLIC_INTERFACE
/// sock:CheckStatus() -> port, status_string, err_code
static int l_Socket_CheckStatus(lua_State * L)
{
  auto * sock = static_cast<SocketObj *>(luaL_checkudata(L, 1, SOCKET_MT));
  lua_pushinteger(L, sock->port);
  lua_pushstring(L, sock->closed ? "DisConnected" : "Connected");
  lua_pushinteger(L, 0);
  return 3;
}

/// __gc metamethod: destroy SocketObj.
static int l_Socket_gc(lua_State * L)
{
  auto * sock = static_cast<SocketObj *>(luaL_checkudata(L, 1, SOCKET_MT));
  sock->~SocketObj();
  return 0;
}

/// Register the SocketClass userdata metatable.
static void register_socket_mt(lua_State * L)
{
  luaL_newmetatable(L, SOCKET_MT);

  // Methods table stored in __index
  lua_newtable(L);
  lua_pushcfunction(L, l_Socket_Send);        lua_setfield(L, -2, "Send");
  lua_pushcfunction(L, l_Socket_Receive);     lua_setfield(L, -2, "Receive");
  lua_pushcfunction(L, l_Socket_Close);       lua_setfield(L, -2, "Close");
  lua_pushcfunction(L, l_Socket_CheckStatus); lua_setfield(L, -2, "CheckStatus");
  lua_setfield(L, -2, "__index");

  lua_pushcfunction(L, l_Socket_gc);
  lua_setfield(L, -2, "__gc");

  lua_pop(L, 1);
}

// ---------------------------------------------------------------------------
// CheckAllStatus / SocketVersion
// ---------------------------------------------------------------------------

// PUBLIC_INTERFACE
/// CheckAllStatus() -> retPort[], retStatus[], retErr[]
/// Returns empty tables in simulation (no real connections).
static int l_CheckAllStatus(lua_State * L)
{
  (void)L;
  lua_newtable(L);
  lua_newtable(L);
  lua_newtable(L);
  return 3;
}

// PUBLIC_INTERFACE
/// SocketVersion() - Print the simulated socket library version.
static int l_SocketVersion(lua_State * L)
{
  (void)L;
  std::cout << "[DeltaAPI] SocketVersion: drasim_lua simulated v1.0\n";
  return 0;
}

// ---------------------------------------------------------------------------
// Function registration table
// ---------------------------------------------------------------------------
static const luaL_Reg delta_api_funcs[] = {
  /* Robot Control */
  {"RobotServoOn",   l_RobotServoOn},
  {"RobotServoOff",  l_RobotServoOff},
  {"MotionStop",     l_MotionStop},
  {"HomeAuto",       l_HomeAuto},
  /* I/O */
  {"DI",             l_DI},
  {"DO",             l_DO},
  {"ExtDI",          l_ExtDI},
  {"ExtDO",          l_ExtDO},
  {"ReadModbus",     l_ReadModbus},
  {"WriteModbus",    l_WriteModbus},
  /* Motion */
  {"MovJ",           l_MovJ},
  {"MovL",           l_MovL},
  {"MovP",           l_MovP},
  {"DELAY",          l_DELAY},
  /* Speed / Accuracy */
  {"SpdJ",           l_SpdJ},
  {"AccJ",           l_AccJ},
  {"DecJ",           l_DecJ},
  {"SpdL",           l_SpdL},
  {"AccL",           l_AccL},
  {"DecL",           l_DecL},
  {"Accur",          l_Accur},
  /* Point management */
  {"SetGlobalPoint", l_SetGlobalPoint},
  {"ReadPoint",      l_ReadPoint},
  /* Point offset constructors: X/Y/Z/RX/RY/RZ return PointExpr userdata */
  {"X",              l_X},
  {"Y",              l_Y},
  {"Z",              l_Z},
  {"RX",             l_RX},
  {"RY",             l_RY},
  {"RZ",             l_RZ},
  /* Synchronization */
  {"WAIT",           l_WAIT},
  /* Multi-task */
  {"AuxTasksAdd",    l_AuxTasksAdd},
  {"AuxTasks",       l_AuxTasks},
  /* Utility */
  {"split",          l_split},
  /* Socket */
  {"SocketClass",    l_SocketClass},
  {"CheckAllStatus", l_CheckAllStatus},
  {"SocketVersion",  l_SocketVersion},
  {nullptr, nullptr}
};

// PUBLIC_INTERFACE
/**
 * @brief Register all Delta API functions as Lua globals in the given state.
 *
 * Registers every C function from delta_api_funcs as a Lua global, plus:
 *   - ON / OFF string constants ("ON" / "OFF") for DI/DO comparisons
 *   - PointExpr metatable for point-offset arithmetic (X+Y+Z+RX+RY+RZ)
 *   - SocketClass userdata metatable with Send/Receive/Close/CheckStatus
 *
 * @param L  Active Lua state.
 */
void register_delta_api(lua_State * L)
{
  // Initialise aux-task scheduler state (idempotent on repeated calls)
  reset_aux_tasks(L);

  // Register metatables
  register_point_expr_mt(L);
  register_socket_mt(L);

  // Register all C functions as Lua globals
  for (const luaL_Reg * fn = delta_api_funcs; fn->name; ++fn) {
    lua_pushcfunction(L, fn->func);
    lua_setglobal(L, fn->name);
  }

  // ON / OFF string constants — scripts use: if DI(14) == ON then ...
  lua_pushstring(L, "ON");
  lua_setglobal(L, "ON");
  lua_pushstring(L, "OFF");
  lua_setglobal(L, "OFF");

  std::cout << "[DeltaAPI] Delta API bindings registered "
               "(coroutine AuxTasks, yielding DELAY/WAIT, SocketClass, ON/OFF, offsets, HomeAuto).\n";
}

}  // namespace drasim_lua
