/*
** ldeltaapi.h
** DeltaAPI Lua C module -- ROS2-backed simulator for Modbus, DI/DO, MovP
*/
#ifndef ldeltaapi_h
#define ldeltaapi_h
#include "lua.h"
#define LUA_DELTAAPI_LIBNAME "delta"
/* PUBLIC_INTERFACE */
LUAMOD_API int luaopen_deltaapi(lua_State *L);
#endif
