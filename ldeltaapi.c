/*
** ldeltaapi.c
** DeltaAPI Lua C module -- stub implementations for Delta robot controller API.
**
** All functions are registered in the Lua global environment (or the "delta"
** module table) WITHOUT the "delta_" prefix.  The C function names still use
** the conventional "delta_" prefix internally so as not to pollute the C
** namespace, but the names visible from Lua are the bare command names:
**   DI, DO, ExtDI, ExtDO, MovP, MovL, MovJ, SetGlobalPoint, ReadPoint,
**   SpdJ, AccJ, DecJ, SpdL, AccL, DecL, Accur, WAIT, DELAY,
**   ReadModbus, WriteModbus, SocketClass, SocketServer, CheckAllStatus,
**   CheckStatus, SocketVersion, AuxTasksAdd, AuxTasks, split
*/

#define ldeltaapi_c
#define LUA_LIB

#include "lprefix.h"

#include <stddef.h>
#include <string.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "ldeltaapi.h"


/* =========================================================================
 * Helper macro – push a string result and return 1.
 * ========================================================================= */
#define DELTA_PUSH_STR(L, s)  do { lua_pushstring((L), (s)); return 1; } while (0)


/* =========================================================================
 * I/O functions
 * ========================================================================= */

/*
** delta_DI – Read standard digital input pin status.
**
** Lua syntax:
**   Status        = DI(Pin_Index)
**   Status_num    = DI(Pin_Index, Length)
**
** Parameters:
**   Pin_Index  (number|string) – pin number 1-24 or pin name.
**   Length     (number, optional) – number of consecutive pins to read (1-24).
**
** Returns:
**   Status (string "ON"/"OFF") when called with one argument, or
**   Status_num (number, decimal bit-field) when Length is supplied.
**
** This stub always returns "OFF" / 0.
*/
/* PUBLIC_INTERFACE */
static int delta_DI (lua_State *L) {
  /* Accept one or two arguments */
  int nargs = lua_gettop(L);
  if (nargs >= 2) {
    /* Return numeric bit-field (stub: 0) */
    lua_pushinteger(L, 0);
  } else {
    /* Return ON/OFF string (stub: "OFF") */
    lua_pushstring(L, "OFF");
  }
  return 1;
}


/*
** delta_DO – Set standard digital output pin status.
**
** Lua syntax:
**   DO(Pin_Index, Status)
**   DO(Pin_Index, Status, Delay_Time)
**   DO(Pin_Index, Length, Status_num)
**   DO(Pin_Index, Length, Status_num, Delay_Time)
**
** Parameters:
**   Pin_Index   (number|string) – pin 1-12 or pin name.
**   Status      (string "ON"/"OFF") or Status_num (number) depending on overload.
**   Delay_Time  (number, optional) – delay in seconds.
**   Length      (number, optional) – number of consecutive pins.
**
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_DO (lua_State *L) {
  (void)L; /* stub – no operation */
  return 0;
}


/*
** delta_ExtDI – Read external board digital input pin status.
**
** Lua syntax:
**   Status = ExtDI(Address_Index, Pin_Index)
**
** Parameters:
**   Address_Index (number) – external board station number.
**   Pin_Index     (number) – pin number on the external board.
**
** Returns:
**   Status (string "ON"/"OFF"). Stub returns "OFF".
*/
/* PUBLIC_INTERFACE */
static int delta_ExtDI (lua_State *L) {
  (void)L;
  lua_pushstring(L, "OFF");
  return 1;
}


/*
** delta_ExtDO – Set external board digital output pin status.
**
** Lua syntax:
**   ExtDO(Address_Index, Pin_Index, Status)
**   ExtDO(Address_Index, Pin_Index, Status, Delay_Time)
**
** Parameters:
**   Address_Index (number) – external board station number.
**   Pin_Index     (number) – pin number.
**   Status        (string "ON"/"OFF").
**   Delay_Time    (number, optional) – delay in seconds.
**
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_ExtDO (lua_State *L) {
  (void)L;
  return 0;
}


/* =========================================================================
 * Motion functions
 * ========================================================================= */

/*
** delta_MovP – Point-to-point motion (PTP).
**
** Lua syntax:
**   MovP(Point)
**   MovP(Point + Offset(), Function() + ...)
**
** Parameters:
**   Point (string|number) – target point name or number.
**
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_MovP (lua_State *L) {
  (void)L;
  return 0;
}


/*
** delta_MovL – Linear motion.
**
** Lua syntax:
**   MovL(Point)
**   MovL(Point + Offset(), Function() + ...)
**
** Parameters:
**   Point (string|number) – target point name or number.
**
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_MovL (lua_State *L) {
  (void)L;
  return 0;
}


/*
** delta_MovJ – Single-axis joint motion.
**
** Lua syntax:
**   MovJ(Joint, Degree)
**   MovJ(Joint, Degree, Function() + ...)
**
** Parameters:
**   Joint  (number) – axis number 1-6.
**   Degree (number) – target angle in degrees (-360 to 360).
**
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_MovJ (lua_State *L) {
  (void)L;
  return 0;
}


/* =========================================================================
 * Point data functions
 * ========================================================================= */

/*
** delta_SetGlobalPoint – Modify a global point entry in controller memory.
**
** Lua syntax (Six-Axis):
**   SetGlobalPoint(Point, PointName, X, Y, Z, RX, RY, RZ, Elbow, Shoulder, Flip, UF, TF, JRC)
**
** Parameters:
**   Point     (number)  – point number 1-1000.
**   PointName (string)  – must be prefixed with "GL_".
**   X..RZ     (number)  – Cartesian coordinates / angles.
**   UF, TF    (number)  – user frame / tool frame indices.
**   JRC       (table)   – joint rotation correction table {J1..J7, JRC_Active}.
**
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_SetGlobalPoint (lua_State *L) {
  (void)L;
  return 0;
}


/*
** delta_ReadPoint – Read a single item of point information.
**
** Lua syntax:
**   data = ReadPoint(Point, Item)
**
** Parameters:
**   Point (string|number) – point name or number.
**   Item  (string)        – item key, e.g. "X", "Y", "Z", "RX", etc.
**
** Returns:
**   data (number|table) – requested value. Stub returns 0.
*/
/* PUBLIC_INTERFACE */
static int delta_ReadPoint (lua_State *L) {
  (void)L;
  lua_pushnumber(L, 0.0);
  return 1;
}


/* =========================================================================
 * Speed / acceleration setpoint functions
 * ========================================================================= */

/*
** delta_SpdJ – Set default maximum joint speed (%).
**
** Lua syntax:  SpdJ(Speed)
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_SpdJ (lua_State *L) {
  (void)L;
  return 0;
}


/*
** delta_AccJ – Set default joint acceleration (%).
**
** Lua syntax:  AccJ(Acceleration)
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_AccJ (lua_State *L) {
  (void)L;
  return 0;
}


/*
** delta_DecJ – Set default joint deceleration (%).
**
** Lua syntax:  DecJ(Deceleration)
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_DecJ (lua_State *L) {
  (void)L;
  return 0;
}


/*
** delta_SpdL – Set default maximum linear speed (mm/sec).
**
** Lua syntax:  SpdL(Speed)
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_SpdL (lua_State *L) {
  (void)L;
  return 0;
}


/*
** delta_AccL – Set default linear acceleration (mm/sec²).
**
** Lua syntax:  AccL(Acceleration)
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_AccL (lua_State *L) {
  (void)L;
  return 0;
}


/*
** delta_DecL – Set default linear deceleration (mm/sec²).
**
** Lua syntax:  DecL(Deceleration)
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_DecL (lua_State *L) {
  (void)L;
  return 0;
}


/*
** delta_Accur – Set robot in-place accuracy mode.
**
** Lua syntax:  Accur(Mode [, "CART"])
**
** Parameters:
**   Mode (string) – one of: "HIGH", "STANDARD", "MEDIUM", "ROUGH", "MAXROUGH".
**
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_Accur (lua_State *L) {
  (void)L;
  return 0;
}


/* =========================================================================
 * Timing / wait functions
 * ========================================================================= */

/*
** delta_WAIT – Wait for DI/DO signal or Modbus value condition.
**
** Lua syntax:
**   WAIT(IO_type, IO_index, DI_DO_status [, Timeout])
**   WAIT(Modbus_var, Modbus_addr, data_type, Modbus_data)
**
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_WAIT (lua_State *L) {
  (void)L;
  return 0;
}


/*
** delta_DELAY – Pause program execution for the specified time.
**
** Lua syntax:  DELAY(Delay_Time)
**
** Parameters:
**   Delay_Time (number) – delay in seconds (minimum 0.001).
**
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_DELAY (lua_State *L) {
  (void)L;
  return 0;
}


/* =========================================================================
 * Modbus functions
 * ========================================================================= */

/*
** delta_ReadModbus – Read a value from a Modbus register address.
**
** Lua syntax:  data = ReadModbus(RegAddress, Size)
**
** Parameters:
**   RegAddress (number) – memory address to read.
**   Size       (string) – "W" (16-bit) or "DW" (32-bit).
**
** Returns:
**   data (number). Stub returns 0.
*/
/* PUBLIC_INTERFACE */
static int delta_ReadModbus (lua_State *L) {
  (void)L;
  lua_pushinteger(L, 0);
  return 1;
}


/*
** delta_WriteModbus – Write a value to a Modbus register address.
**
** Lua syntax:  WriteModbus(RegAddress, Size, RegValue)
**
** Parameters:
**   RegAddress (number) – memory address to write.
**   Size       (string) – "W" or "DW".
**   RegValue   (number) – value to write.
**
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_WriteModbus (lua_State *L) {
  (void)L;
  return 0;
}


/* =========================================================================
 * Socket / communication functions
 * ========================================================================= */

/*
** delta_SocketClass – Create a Socket client connection object.
**
** Lua syntax:
**   Variable = SocketClass(HostIP, Port, Spacing, Delimiter, Cmd, Sleeptime, Timeout)
**
** Returns:
**   A table representing the socket object with Send, Receive, Close,
**   and CheckStatus member functions (stub – returns empty table).
*/
/* PUBLIC_INTERFACE */
static int delta_SocketClass (lua_State *L) {
  (void)L;
  lua_newtable(L);
  return 1;
}


/*
** delta_SocketServer – Set controller as Socket slave station.
**
** Lua syntax:
**   SocketServer(Port, Spacing, Delimiter, Cmd, Timeout)
**
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_SocketServer (lua_State *L) {
  (void)L;
  return 0;
}


/*
** delta_CheckAllStatus – Read all connection statuses on all channels.
**
** Lua syntax:
**   retPort[], retStatus[], retErr[] = CheckAllStatus()
**
** Returns:
**   Three tables (stub: all empty tables).
*/
/* PUBLIC_INTERFACE */
static int delta_CheckAllStatus (lua_State *L) {
  lua_newtable(L); /* retPort  */
  lua_newtable(L); /* retStatus */
  lua_newtable(L); /* retErr   */
  return 3;
}


/*
** delta_CheckStatus – Read connection status of the specified socket variable.
**
** Lua syntax:
**   retPort, retStatus, retErr = Variable:CheckStatus()
**
** Returns:
**   port (number), status (string), errcode (number). Stub returns 0, "DisConnected", 0.
*/
/* PUBLIC_INTERFACE */
static int delta_CheckStatus (lua_State *L) {
  (void)L;
  lua_pushinteger(L, 0);
  lua_pushstring(L, "DisConnected");
  lua_pushinteger(L, 0);
  return 3;
}


/*
** delta_SocketVersion – Print and return the Socket library version string.
**
** Lua syntax:  SocketVersion()
**
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_SocketVersion (lua_State *L) {
  (void)L;
  return 0;
}


/* =========================================================================
 * Multi-task functions
 * ========================================================================= */

/*
** delta_AuxTasksAdd – Register subfunctions for multi-task execution.
**
** Lua syntax:  AuxTasksAdd(function1, function2, function3, ...)
**
** Parameters:
**   function1..N (function) – up to 10 subfunctions; only function1 may use
**                             motion commands.
**
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_AuxTasksAdd (lua_State *L) {
  (void)L;
  return 0;
}


/*
** delta_AuxTasks – Execute one time-slice of each registered subfunction.
**
** Lua syntax:  AuxTasks()
**
** Returns: nothing (stub).
*/
/* PUBLIC_INTERFACE */
static int delta_AuxTasks (lua_State *L) {
  (void)L;
  return 0;
}


/* =========================================================================
 * String utility
 * ========================================================================= */

/*
** delta_split – Split a string by a delimiter pattern and return an array table.
**
** Lua syntax:  ret = split(str, pat)
**
** Parameters:
**   str (string) – the string to split.
**   pat (string) – the delimiter character or pattern.
**
** Returns:
**   ret (table) – array of substrings.
*/
/* PUBLIC_INTERFACE */
static int delta_split (lua_State *L) {
  const char *str = luaL_checkstring(L, 1);
  const char *pat = luaL_checkstring(L, 2);
  size_t patlen   = strlen(pat);
  int    idx      = 1;

  lua_newtable(L); /* result table */

  if (patlen == 0) {
    /* No delimiter: return the whole string as element 1 */
    lua_pushstring(L, str);
    lua_rawseti(L, -2, idx);
    return 1;
  }

  /* Walk str and collect tokens */
  while (*str != '\0') {
    const char *found = strstr(str, pat);
    if (found == NULL) {
      /* Last (or only) segment */
      lua_pushstring(L, str);
      lua_rawseti(L, -2, idx++);
      break;
    }
    /* Push segment before delimiter */
    lua_pushlstring(L, str, (size_t)(found - str));
    lua_rawseti(L, -2, idx++);
    str = found + patlen;
  }

  return 1;
}


/* =========================================================================
 * Module registration
 * =========================================================================
 *
 * The luaL_Reg table maps the Lua-visible names (WITHOUT "delta_" prefix) to
 * the corresponding C functions.  The module itself is still loaded under the
 * name "delta" (LUA_DELTAAPI_LIBNAME) so that scripts can do:
 *
 *     local delta = require("delta")
 *     delta.DI(1)
 *
 * and, because linit.c registers it into the global table, scripts can also
 * call the functions directly:
 *
 *     DI(1)
 *     MovP("GL_P1")
 *
 * ========================================================================= */

/* Registration table – Lua-visible names have NO "delta_" prefix */
static const luaL_Reg deltalib[] = {
  /* I/O */
  {"DI",              delta_DI},
  {"DO",              delta_DO},
  {"ExtDI",           delta_ExtDI},
  {"ExtDO",           delta_ExtDO},
  /* Motion */
  {"MovP",            delta_MovP},
  {"MovL",            delta_MovL},
  {"MovJ",            delta_MovJ},
  /* Point data */
  {"SetGlobalPoint",  delta_SetGlobalPoint},
  {"ReadPoint",       delta_ReadPoint},
  /* Speed / acceleration */
  {"SpdJ",            delta_SpdJ},
  {"AccJ",            delta_AccJ},
  {"DecJ",            delta_DecJ},
  {"SpdL",            delta_SpdL},
  {"AccL",            delta_AccL},
  {"DecL",            delta_DecL},
  {"Accur",           delta_Accur},
  /* Timing */
  {"WAIT",            delta_WAIT},
  {"DELAY",           delta_DELAY},
  /* Modbus */
  {"ReadModbus",      delta_ReadModbus},
  {"WriteModbus",     delta_WriteModbus},
  /* Socket / communication */
  {"SocketClass",     delta_SocketClass},
  {"SocketServer",    delta_SocketServer},
  {"CheckAllStatus",  delta_CheckAllStatus},
  {"CheckStatus",     delta_CheckStatus},
  {"SocketVersion",   delta_SocketVersion},
  /* Multi-task */
  {"AuxTasksAdd",     delta_AuxTasksAdd},
  {"AuxTasks",        delta_AuxTasks},
  /* String utility */
  {"split",           delta_split},
  {NULL, NULL}  /* sentinel */
};


/*
** luaopen_deltaapi
**
** Module entry point called by the Lua runtime when the "delta" library is
** required.  Creates the module table populated with all DeltaAPI functions
** using the bare names (no "delta_" prefix), and also injects each function
** into the global environment so scripts can call them directly.
**
** @param L  Lua state.
** @return   1  (the module table is left on the stack).
*/
/* PUBLIC_INTERFACE */
LUAMOD_API int luaopen_deltaapi (lua_State *L) {
  const luaL_Reg *entry;

  /* Create the module table and register all functions into it */
  luaL_newlib(L, deltalib);

  /*
  ** Also inject every function into the global environment so that
  ** Delta robot scripts can call e.g. DI(1) without a module prefix.
  */
  for (entry = deltalib; entry->name != NULL; entry++) {
    lua_pushcfunction(L, entry->func);
    lua_setglobal(L, entry->name);
  }

  return 1; /* return the module table */
}
