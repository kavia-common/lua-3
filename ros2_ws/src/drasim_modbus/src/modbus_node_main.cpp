// drasim_modbus/src/modbus_node_main.cpp
// Main entrypoint for the DRASim Modbus/TCP ROS2 node.
// Spins a ModbusNode that provides ReadModbus and WriteModbus ROS2 services
// and exposes a Modbus/TCP server for external clients.

#include "drasim_modbus/modbus_node.hpp"
#include <rclcpp/rclcpp.hpp>

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<drasim_modbus::ModbusNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
