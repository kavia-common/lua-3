// drasim_lua/src/lua_node_main.cpp
// Main entrypoint for the DRASim Lua scripting ROS2 node.
// Spins a LuaNode that embeds Lua 5.4 and exposes the Delta robot API
// via ROS2 service calls from Lua scripts.

#include "drasim_lua/lua_node.hpp"
#include <rclcpp/rclcpp.hpp>

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<drasim_lua::LuaNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
