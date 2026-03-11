// drasim_lua/src/lua_node.cpp
#include "drasim_lua/lua_node.hpp"
#include "drasim_lua/delta_api_bindings.hpp"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
}

#include <iostream>
#include <stdexcept>

namespace drasim_lua
{

LuaNode::LuaNode(const rclcpp::NodeOptions & options)
: rclcpp::Node("drasim_lua_node", options)
{
  this->declare_parameter<std::string>("script_path", "");
  init_lua();
  std::string script = this->get_parameter("script_path").as_string();
  if (!script.empty()) {
    RCLCPP_INFO(this->get_logger(), "Running Lua script: %s", script.c_str());
    if (!run_script(script)) {
      RCLCPP_ERROR(this->get_logger(), "Lua script execution failed.");
    }
  } else {
    RCLCPP_INFO(this->get_logger(), "No script_path set. Lua interpreter ready.");
  }
}

LuaNode::~LuaNode()
{
  if (L_) { lua_close(L_); L_ = nullptr; }
}

void LuaNode::init_lua()
{
  L_ = luaL_newstate();
  if (!L_) { throw std::runtime_error("[LuaNode] Failed to create Lua state"); }
  luaL_openlibs(L_);
  register_delta_api(L_);
  RCLCPP_DEBUG(this->get_logger(), "Lua 5.4 state initialised with Delta API bindings");
}

bool LuaNode::run_script(const std::string & filepath)
{
  if (luaL_loadfile(L_, filepath.c_str()) != LUA_OK) {
    std::cerr << "[LuaNode] Load error: " << lua_tostring(L_, -1) << "\n";
    lua_pop(L_, 1); return false;
  }
  if (lua_pcall(L_, 0, LUA_MULTRET, 0) != LUA_OK) {
    std::cerr << "[LuaNode] Runtime error: " << lua_tostring(L_, -1) << "\n";
    lua_pop(L_, 1); return false;
  }
  return true;
}

bool LuaNode::run_string(const std::string & code)
{
  if (luaL_loadstring(L_, code.c_str()) != LUA_OK) {
    std::cerr << "[LuaNode] Load error: " << lua_tostring(L_, -1) << "\n";
    lua_pop(L_, 1); return false;
  }
  if (lua_pcall(L_, 0, LUA_MULTRET, 0) != LUA_OK) {
    std::cerr << "[LuaNode] Runtime error: " << lua_tostring(L_, -1) << "\n";
    lua_pop(L_, 1); return false;
  }
  return true;
}

}  // namespace drasim_lua
