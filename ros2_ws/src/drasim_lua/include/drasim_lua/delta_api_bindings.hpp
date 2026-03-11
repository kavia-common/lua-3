#ifndef DRASIM_LUA__DELTA_API_BINDINGS_HPP_
#define DRASIM_LUA__DELTA_API_BINDINGS_HPP_

extern "C" {
#include "lua.h"
}

namespace drasim_lua
{

// PUBLIC_INTERFACE
/**
 * @brief Register all Delta API global Lua functions into the given state.
 *
 * Available globals after registration:
 *
 *   Robot control:
 *     RobotServoOn()          — activate all-axis servo motors
 *     RobotServoOff()         — deactivate all-axis servo motors
 *     MotionStop([mode])      — stop motion; mode "FBK" resets position error
 *     HomeAuto()              — automatic homing (simulated)
 *
 *   I/O:
 *     DI(pin[,len])           — read digital input: "ON"/"OFF" or bitmask
 *     DO(pin)                 — read digital output state: "ON"/"OFF"
 *     DO(pin, status[, delay])— set digital output
 *     ExtDI(addr, pin)        — read external digital input (simulated "ON")
 *     ExtDO(addr, pin, status)— set external digital output
 *     ReadModbus(addr, size)  — read Modbus register ("W" or "DW")
 *     WriteModbus(addr,size,v)— write Modbus register
 *
 *   Motion:
 *     MovJ(joint, deg)        — joint move to angle
 *     MovL(point[+offsets])   — linear move to point
 *     MovP(point[+offsets])   — PTP move to point
 *
 *   Cooperative yielding primitives (coroutine-based scheduling):
 *     DELAY(sec)              — yields for sec seconds (does not block OS thread)
 *     WAIT(...)               — yields briefly to allow time-slicing while "waiting"
 *
 *   Speed/Accuracy:
 *     SpdJ(%), AccJ(%), DecJ(%), SpdL(mm/s), AccL(mm/s2), DecL(mm/s2)
 *     Accur(mode)             — set in-place accuracy (HIGH/ROUGH/etc.)
 *
 *   Point management:
 *     SetGlobalPoint(n, name, x,y,z,...)
 *     ReadPoint(name, item)   — read X/Y/Z/RX/RY/RZ of a named point
 *
 *   Point offset constructors (return PointExpr userdata for + arithmetic):
 *     X(n), Y(n), Z(n), RX(n), RY(n), RZ(n)
 *     Usage: MovP("Fix1" + Z(80) + RX(-180))
 *
 *   Synchronization:
 *     WAIT(io_type, pin, status[, timeout_ms])
 *     WAIT(ExtDI, {addr,pin}, status[, timeout_ms])
 *
 *   Multi-task (coroutine scheduler):
 *     AuxTasksAdd(fn1, fn2, ...)  — creates one coroutine per function
 *     AuxTasks()                 — resumes one runnable coroutine round-robin
 *
 *   Utility:
 *     split(str, pat)         — split string by delimiter, return table
 *
 *   Socket (free protocol communication):
 *     SocketClass(host, port, spacing, delimiter, cmd, sleeptime, timeout)
 *       -> socket userdata with methods:
 *          :Send(cmd)         — transmit data
 *          :Receive()         — receive data as table (or nil if none)
 *          :Close()           — close connection
 *          :CheckStatus()     — returns port, status, err_code
 *     CheckAllStatus()        — returns retPort[], retStatus[], retErr[]
 *     SocketVersion()         — print socket library version
 *
 *   Constants:
 *     ON                      — string constant "ON"
 *     OFF                     — string constant "OFF"
 *
 * @param L  Active Lua state.
 */
void register_delta_api(lua_State * L);

}  // namespace drasim_lua

#endif  // DRASIM_LUA__DELTA_API_BINDINGS_HPP_
