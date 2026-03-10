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
 * Available globals: DI, DO, ExtDI, ExtDO, ReadModbus, WriteModbus,
 *   MovJ, MovL, MovP, DELAY, SpdJ, AccJ, DecJ, SpdL, AccL, DecL,
 *   Accur, SetGlobalPoint, ReadPoint, WAIT, AuxTasksAdd, AuxTasks, split.
 */
void register_delta_api(lua_State * L);

}  // namespace drasim_lua

#endif  // DRASIM_LUA__DELTA_API_BINDINGS_HPP_
