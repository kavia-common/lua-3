// drasim_robot_emulator/src/robot_emulator_node_main.cpp
// Main entrypoint for the DRASim robot emulator ROS2 node.
// Spins a RobotEmulatorNode that provides 6-axis motion emulation via
// MovJ, MovL, MovP services and publishes /drasim/motion_state.

#include "drasim_robot_emulator/robot_emulator_node.hpp"
#include <rclcpp/rclcpp.hpp>

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<drasim_robot_emulator::RobotEmulatorNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
