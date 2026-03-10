// drasim_robot_emulator/src/robot_emulator_node.cpp
// RobotEmulatorNode — exposes MotionEngine via ROS2 services (MovJ, MovL, MovP)
// and publishes motion state at a configurable rate.
// Lambdas use explicit types required by ROS2 Jazzy's create_service API.
#include "drasim_robot_emulator/robot_emulator_node.hpp"
#include <array>
#include <chrono>

using namespace std::chrono_literals;

namespace drasim_robot_emulator
{

RobotEmulatorNode::RobotEmulatorNode(const rclcpp::NodeOptions & options)
: rclcpp::Node("drasim_robot_emulator_node", options)
{
  this->declare_parameter<int>("publish_rate_hz", 20);
  int rate_hz = this->get_parameter("publish_rate_hz").as_int();
  RCLCPP_INFO(this->get_logger(), "Starting DRASim Robot Emulator at %d Hz", rate_hz);

  state_pub_ = this->create_publisher<drasim_interfaces::msg::MotionState>(
    "/drasim/motion_state", rclcpp::QoS(10));

  // Use explicit shared_ptr types — required by ROS2 Jazzy's create_service.
  mov_j_srv_ = this->create_service<drasim_interfaces::srv::MovJ>(
    "/drasim/mov_j",
    [this](std::shared_ptr<drasim_interfaces::srv::MovJ::Request> q,
           std::shared_ptr<drasim_interfaces::srv::MovJ::Response> r)
    { handle_mov_j(q, r); });

  mov_l_srv_ = this->create_service<drasim_interfaces::srv::MovL>(
    "/drasim/mov_l",
    [this](std::shared_ptr<drasim_interfaces::srv::MovL::Request> q,
           std::shared_ptr<drasim_interfaces::srv::MovL::Response> r)
    { handle_mov_l(q, r); });

  mov_p_srv_ = this->create_service<drasim_interfaces::srv::MovP>(
    "/drasim/mov_p",
    [this](std::shared_ptr<drasim_interfaces::srv::MovP::Request> q,
           std::shared_ptr<drasim_interfaces::srv::MovP::Response> r)
    { handle_mov_p(q, r); });

  auto period = std::chrono::milliseconds(1000 / rate_hz);
  timer_ = this->create_wall_timer(period, [this] { publish_motion_state(); });
}

void RobotEmulatorNode::publish_motion_state()
{
  drasim_interfaces::msg::MotionState msg;
  msg.stamp = this->now();
  auto joints = engine_.get_joint_angles();
  for (int i = 0; i < MotionEngine::NUM_JOINTS; ++i) { msg.joint_angles[i] = joints[i]; }
  auto pose = engine_.get_cartesian_pose();
  for (int i = 0; i < 6; ++i) { msg.cartesian_pose[i] = pose[i]; }
  msg.status     = engine_.get_status_string();
  msg.speed_pct  = 10.0;
  msg.tool_frame = 0;
  msg.user_frame = 0;
  state_pub_->publish(msg);
}

void RobotEmulatorNode::handle_mov_j(
  std::shared_ptr<drasim_interfaces::srv::MovJ::Request> req,
  std::shared_ptr<drasim_interfaces::srv::MovJ::Response> res)
{
  RCLCPP_INFO(this->get_logger(), "MovJ joint=%d deg=%.2f", req->joint, req->degree);
  bool ok = engine_.mov_j(req->joint, req->degree,
    req->speed_pct > 0.0 ? req->speed_pct : 10.0,
    req->acc_pct   > 0.0 ? req->acc_pct   : 10.0,
    req->dec_pct   > 0.0 ? req->dec_pct   : 10.0);
  res->success = ok;
  res->message = ok ? "OK" : "Invalid joint";
}

void RobotEmulatorNode::handle_mov_l(
  std::shared_ptr<drasim_interfaces::srv::MovL::Request> req,
  std::shared_ptr<drasim_interfaces::srv::MovL::Response> res)
{
  RCLCPP_INFO(this->get_logger(), "MovL point=%s spd=%.1fmm/s",
    req->point.c_str(), req->speed_mms);
  std::array<double, 6> offset{};
  for (int i = 0; i < 6; ++i) { offset[i] = req->offset[i]; }
  bool ok = engine_.mov_l(req->point, offset,
    req->speed_mms > 0.0 ? req->speed_mms : 100.0,
    req->acc_mms2  > 0.0 ? req->acc_mms2  : 10.0,
    req->dec_mms2  > 0.0 ? req->dec_mms2  : 10.0,
    req->use_pass);
  res->success = ok;
  res->message = ok ? "OK" : "Motion error";
}

void RobotEmulatorNode::handle_mov_p(
  std::shared_ptr<drasim_interfaces::srv::MovP::Request> req,
  std::shared_ptr<drasim_interfaces::srv::MovP::Response> res)
{
  RCLCPP_INFO(this->get_logger(), "MovP point=%s spd=%.1f%%",
    req->point.c_str(), req->speed_pct);
  std::array<double, 6> offset{};
  for (int i = 0; i < 6; ++i) { offset[i] = req->offset[i]; }
  bool ok = engine_.mov_p(req->point, offset,
    req->speed_pct > 0.0 ? req->speed_pct : 10.0,
    req->acc_pct   > 0.0 ? req->acc_pct   : 10.0,
    req->dec_pct   > 0.0 ? req->dec_pct   : 10.0,
    req->use_pass);
  res->success = ok;
  res->message = ok ? "OK" : "Motion error";
}

}  // namespace drasim_robot_emulator
