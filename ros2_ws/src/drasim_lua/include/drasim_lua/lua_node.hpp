#ifndef DRASIM_LUA__LUA_NODE_HPP_
#define DRASIM_LUA__LUA_NODE_HPP_

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <rclcpp/rclcpp.hpp>
#include <string>
#include <memory>

namespace drasim_lua
{

/**
 * @brief LuaNode — embeds Lua 5.4 with Delta API bindings.
 *
 * Parameter: script_path (string) — path to Lua script to run on startup.
 */
class LuaNode : public rclcpp::Node
{
public:
  // PUBLIC_INTERFACE
  explicit LuaNode(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());
  // PUBLIC_INTERFACE
  ~LuaNode() override;

  // PUBLIC_INTERFACE
  /** @brief Run a Lua script file. Returns true on success. */
  bool run_script(const std::string & filepath);

  // PUBLIC_INTERFACE
  /** @brief Run a Lua code string. Returns true on success. */
  bool run_string(const std::string & code);

  // PUBLIC_INTERFACE
  /** @brief Access the underlying Lua state. */
  lua_State * lua_state() const { return L_; }

private:
  void init_lua();
  lua_State * L_{nullptr};
};

}  // namespace drasim_lua

#endif  // DRASIM_LUA__LUA_NODE_HPP_
