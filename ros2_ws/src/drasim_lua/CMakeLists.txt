cmake_minimum_required(VERSION 3.8)
project(drasim_lua)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(drasim_interfaces REQUIRED)
find_package(drasim_core REQUIRED)

# Lua 5.4 sources are two directories above the workspace root (lua-3/)
set(LUA_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../..")

add_library(lua54_static STATIC
  ${LUA_SRC_DIR}/lapi.c
  ${LUA_SRC_DIR}/lauxlib.c
  ${LUA_SRC_DIR}/lbaselib.c
  ${LUA_SRC_DIR}/lcode.c
  ${LUA_SRC_DIR}/lcorolib.c
  ${LUA_SRC_DIR}/lctype.c
  ${LUA_SRC_DIR}/ldblib.c
  ${LUA_SRC_DIR}/ldebug.c
  ${LUA_SRC_DIR}/ldeltaapi.c
  ${LUA_SRC_DIR}/ldo.c
  ${LUA_SRC_DIR}/ldump.c
  ${LUA_SRC_DIR}/lfunc.c
  ${LUA_SRC_DIR}/lgc.c
  ${LUA_SRC_DIR}/linit.c
  ${LUA_SRC_DIR}/liolib.c
  ${LUA_SRC_DIR}/llex.c
  ${LUA_SRC_DIR}/lmathlib.c
  ${LUA_SRC_DIR}/lmem.c
  ${LUA_SRC_DIR}/loadlib.c
  ${LUA_SRC_DIR}/lobject.c
  ${LUA_SRC_DIR}/lopcodes.c
  ${LUA_SRC_DIR}/loslib.c
  ${LUA_SRC_DIR}/lparser.c
  ${LUA_SRC_DIR}/lstate.c
  ${LUA_SRC_DIR}/lstring.c
  ${LUA_SRC_DIR}/lstrlib.c
  ${LUA_SRC_DIR}/ltable.c
  ${LUA_SRC_DIR}/ltablib.c
  ${LUA_SRC_DIR}/ltm.c
  ${LUA_SRC_DIR}/lundump.c
  ${LUA_SRC_DIR}/lutf8lib.c
  ${LUA_SRC_DIR}/lvm.c
  ${LUA_SRC_DIR}/lzio.c
)

target_include_directories(lua54_static PUBLIC
  $<BUILD_INTERFACE:${LUA_SRC_DIR}>
)
target_compile_options(lua54_static PRIVATE -w)
target_link_libraries(lua54_static dl m)

add_executable(lua_node
  src/lua_node_main.cpp
  src/lua_node.cpp
  src/delta_api_bindings.cpp
)

target_include_directories(lua_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${LUA_SRC_DIR}
)

target_link_libraries(lua_node lua54_static)

ament_target_dependencies(lua_node
  rclcpp
  drasim_interfaces
  drasim_core
)

install(TARGETS lua_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
