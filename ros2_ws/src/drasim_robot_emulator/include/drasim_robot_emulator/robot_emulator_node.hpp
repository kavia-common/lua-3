#ifndef DRASIM_ROBOT_EMULATOR__ROBOT_EMULATOR_NODE_HPP_
#define DRASIM_ROBOT_EMULATOR__ROBOT_EMULATOR_NODE_HPP_

#include "drasim_robot_emulator/motion_engine.hpp"
#include <rclcpp/rclcpp.hpp>
#include <drasim_interfaces/msg/motion_state.hpp>
#include <drasim_interfaces/srv/mov_j.hpp>
#include <drasim_interfaces/srv/mov_l.hpp>
#include <drasim_interfaces/srv/mov_p.hpp>
#include <memory>

namespace drasim_robot_emulator
{

/**
 * @brief RobotEmulatorNode — exposes MotionEngine via ROS2 services.
 *
 * Published: /drasim/motion_state  [drasim_interfaces/msg/MotionState] @ 20 Hz
 * Services:  /drasim/mov_j, /drasim/mov_l, /drasim/mov_p
 */
class RobotEmulatorNode : public rclcpp::Node
{
public:
  // PUBLIC_INTERFACE
  explicit RobotEmulatorNode(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());

private:
  void publish_motion_state();
  void handle_mov_j(std::shared_ptr<drasim_interfaces::srv::MovJ::Request>,
                    std::shared_ptr<drasim_interfaces::srv::MovJ::Response>);
  void handle_mov_l(std::shared_ptr<drasim_interfaces::srv::MovL::Request>,
                    std::shared_ptr<drasim_interfaces::srv::MovL::Response>);
  void handle_mov_p(std::shared_ptr<drasim_interfaces::srv::MovP::Request>,
                    std::shared_ptr<drasim_interfaces::srv::MovP::Response>);

  MotionEngine engine_;
  rclcpp::Publisher<drasim_interfaces::msg::MotionState>::SharedPtr state_pub_;
  rclcpp::Service<drasim_interfaces::srv::MovJ>::SharedPtr mov_j_srv_;
  rclcpp::Service<drasim_interfaces::srv::MovL>::SharedPtr mov_l_srv_;
  rclcpp::Service<drasim_interfaces::srv::MovP>::SharedPtr mov_p_srv_;
  rclcpp::TimerBase::SharedPtr timer_;
};

}  // namespace drasim_robot_emulator

#endif  // DRASIM_ROBOT_EMULATOR__ROBOT_EMULATOR_NODE_HPP_
