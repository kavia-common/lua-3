// drasim_lua/src/delta_api_bindings.cpp
// C++ implementations of Delta Robot Language API exposed to Lua.
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
#include <string>
#include <thread>

namespace drasim_lua
{

static bool status_to_bool(const char * s) { return s && std::string(s) == "ON"; }
static void push_on_off(lua_State * L, bool v) { lua_pushstring(L, v ? "ON" : "OFF"); }

// DI(pin [,length]) -> "ON"/"OFF" | bitmask
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

// DO(pin, status [,delay]) or DO(pin, length, bitmask [,delay])
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
    int len = (int)luaL_checkinteger(L, 2);
    uint32_t mask = (uint32_t)luaL_checkinteger(L, 3);
    double d = luaL_optnumber(L, 4, 0.0);
    for (int i = 0; i < len; ++i) {
      mem.set_do(pin + (std::size_t)i, (mask & (1u << i)) != 0);
    }
    if (d > 0.0) {
      std::thread([pin, len, mask, d] {
        std::this_thread::sleep_for(std::chrono::duration<double>(d));
        auto & m = drasim_core::MemoryImage::instance();
        for (int i = 0; i < len; ++i) { m.set_do(pin + (std::size_t)i, (mask & (1u << i)) == 0); }
      }).detach();
    }
  }
  return 0;
}

static int l_ExtDI(lua_State * L) { (void)L; std::cerr << "[DeltaAPI] ExtDI: stub\n"; push_on_off(L, false); return 1; }
static int l_ExtDO(lua_State * L) { (void)L; std::cerr << "[DeltaAPI] ExtDO: stub\n"; return 0; }

static int l_ReadModbus(lua_State * L)
{
  uint32_t addr   = (uint32_t)luaL_checkinteger(L, 1);
  const char * sz = luaL_checkstring(L, 2);
  auto idx = drasim_core::ModbusMapping::to_register_index(addr);
  if (idx == SIZE_MAX) { lua_pushinteger(L, 0); return 1; }
  auto & mem = drasim_core::MemoryImage::instance();
  int32_t v = (std::string(sz) == "DW")
    ? mem.read_dword((uint32_t)idx)
    : (int32_t)mem.read_word((uint32_t)idx);
  lua_pushinteger(L, (lua_Integer)v);
  return 1;
}

static int l_WriteModbus(lua_State * L)
{
  uint32_t addr   = (uint32_t)luaL_checkinteger(L, 1);
  const char * sz = luaL_checkstring(L, 2);
  int32_t value   = (int32_t)luaL_checkinteger(L, 3);
  auto idx = drasim_core::ModbusMapping::to_register_index(addr);
  if (idx == SIZE_MAX) { return 0; }
  auto & mem = drasim_core::MemoryImage::instance();
  if (std::string(sz) == "DW") { mem.write_dword((uint32_t)idx, value); }
  else { mem.write_word((uint32_t)idx, (int16_t)value); }
  return 0;
}

static int l_MovJ(lua_State * L)
{
  int joint = (int)luaL_checkinteger(L, 1); double deg = luaL_checknumber(L, 2);
  double spd = luaL_optnumber(L, 3, 10.0);
  std::cout << "[DeltaAPI] MovJ joint=" << joint << " deg=" << deg << " spd=" << spd << "%\n";
  return 0;
}
static int l_MovL(lua_State * L)
{
  const char * p = luaL_checkstring(L, 1); double spd = luaL_optnumber(L, 2, 100.0);
  std::cout << "[DeltaAPI] MovL point=" << p << " spd=" << spd << "mm/s\n";
  return 0;
}
static int l_MovP(lua_State * L)
{
  const char * p = luaL_checkstring(L, 1); double spd = luaL_optnumber(L, 2, 10.0);
  std::cout << "[DeltaAPI] MovP point=" << p << " spd=" << spd << "%\n";
  return 0;
}
static int l_DELAY(lua_State * L)
{
  double s = luaL_checknumber(L, 1);
  if (s > 0.0) { std::this_thread::sleep_for(std::chrono::duration<double>(s)); }
  return 0;
}
static int l_SpdJ(lua_State * L) { std::cout << "[DeltaAPI] SpdJ=" << luaL_checknumber(L,1) << "%\n"; return 0; }
static int l_AccJ(lua_State * L) { std::cout << "[DeltaAPI] AccJ=" << luaL_checknumber(L,1) << "%\n"; return 0; }
static int l_DecJ(lua_State * L) { std::cout << "[DeltaAPI] DecJ=" << luaL_checknumber(L,1) << "%\n"; return 0; }
static int l_SpdL(lua_State * L) { std::cout << "[DeltaAPI] SpdL=" << luaL_checknumber(L,1) << "mm/s\n"; return 0; }
static int l_AccL(lua_State * L) { std::cout << "[DeltaAPI] AccL=" << luaL_checknumber(L,1) << "\n"; return 0; }
static int l_DecL(lua_State * L) { std::cout << "[DeltaAPI] DecL=" << luaL_checknumber(L,1) << "\n"; return 0; }
static int l_Accur(lua_State * L) { std::cout << "[DeltaAPI] Accur=" << luaL_checkstring(L,1) << "\n"; return 0; }

static int l_SetGlobalPoint(lua_State * L)
{
  int pt = (int)luaL_checkinteger(L, 1);
  const char * nm = luaL_checkstring(L, 2);
  double x = luaL_optnumber(L,3,0.0), y = luaL_optnumber(L,4,0.0), z = luaL_optnumber(L,5,0.0);
  std::cout << "[DeltaAPI] SetGlobalPoint pt=" << pt << " name=" << nm
            << " X=" << x << " Y=" << y << " Z=" << z << "\n";
  return 0;
}

static int l_ReadPoint(lua_State * L)
{
  const char * pt = luaL_checkstring(L,1); const char * it = luaL_checkstring(L,2);
  std::cout << "[DeltaAPI] ReadPoint pt=" << pt << " item=" << it << "\n";
  lua_pushnumber(L, 0.0); return 1;
}

static int l_WAIT(lua_State * L)
{
  if (lua_isstring(L, 1)) {
    std::string io_type = lua_tostring(L, 1);
    if (io_type == "DI" || io_type == "DO") {
      int pin = (int)luaL_checkinteger(L, 2);
      bool target = status_to_bool(luaL_checkstring(L, 3));
      double tms = luaL_optnumber(L, 4, -1.0);
      auto start = std::chrono::steady_clock::now();
      while (true) {
        bool cur = (io_type == "DI")
          ? drasim_core::MemoryImage::instance().get_di((std::size_t)pin)
          : drasim_core::MemoryImage::instance().get_do((std::size_t)pin);
        if (cur == target) { break; }
        if (tms > 0.0) {
          auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start).count();
          if (ms >= (long)tms) { break; }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
    }
  }
  return 0;
}

static int l_AuxTasksAdd(lua_State * L)
{
  std::cout << "[DeltaAPI] AuxTasksAdd: " << lua_gettop(L) << " funcs (stub)\n";
  return 0;
}
static int l_AuxTasks(lua_State * L) { (void)L; std::this_thread::sleep_for(std::chrono::milliseconds(15)); return 0; }

static int l_split(lua_State * L)
{
  std::string str = luaL_checkstring(L, 1);
  std::string pat = luaL_checkstring(L, 2);
  lua_newtable(L);
  int idx = 1; std::size_t pos = 0, found;
  while ((found = str.find(pat, pos)) != std::string::npos) {
    lua_pushstring(L, str.substr(pos, found - pos).c_str());
    lua_rawseti(L, -2, idx++);
    pos = found + pat.size();
  }
  lua_pushstring(L, str.substr(pos).c_str());
  lua_rawseti(L, -2, idx);
  return 1;
}

static const luaL_Reg delta_api_funcs[] = {
  {"DI",l_DI},{"DO",l_DO},{"ExtDI",l_ExtDI},{"ExtDO",l_ExtDO},
  {"ReadModbus",l_ReadModbus},{"WriteModbus",l_WriteModbus},
  {"MovJ",l_MovJ},{"MovL",l_MovL},{"MovP",l_MovP},
  {"DELAY",l_DELAY},{"SpdJ",l_SpdJ},{"AccJ",l_AccJ},{"DecJ",l_DecJ},
  {"SpdL",l_SpdL},{"AccL",l_AccL},{"DecL",l_DecL},{"Accur",l_Accur},
  {"SetGlobalPoint",l_SetGlobalPoint},{"ReadPoint",l_ReadPoint},
  {"WAIT",l_WAIT},{"AuxTasksAdd",l_AuxTasksAdd},{"AuxTasks",l_AuxTasks},
  {"split",l_split},{nullptr,nullptr}
};

// PUBLIC_INTERFACE
void register_delta_api(lua_State * L)
{
  for (const luaL_Reg * fn = delta_api_funcs; fn->name; ++fn) {
    lua_pushcfunction(L, fn->func);
    lua_setglobal(L, fn->name);
  }
  std::cout << "[DeltaAPI] Delta API bindings registered.\n";
}

}  // namespace drasim_lua
