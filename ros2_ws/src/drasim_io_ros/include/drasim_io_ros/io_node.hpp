#pragma once
#include <rclcpp/rclcpp.hpp>
#include <drasim_interfaces/msg/digital_io.hpp>
#include <drasim_interfaces/srv/set_do.hpp>
#include <drasim_interfaces/srv/get_di.hpp>
namespace drasim_io_ros {
class IONode : public rclcpp::Node {
public:
  explicit IONode(const rclcpp::NodeOptions&o=rclcpp::NodeOptions());
private:
  void publish_io_state();
  void handle_set_do(std::shared_ptr<drasim_interfaces::srv::SetDO::Request>,std::shared_ptr<drasim_interfaces::srv::SetDO::Response>);
  void handle_get_di(std::shared_ptr<drasim_interfaces::srv::GetDI::Request>,std::shared_ptr<drasim_interfaces::srv::GetDI::Response>);
  rclcpp::Publisher<drasim_interfaces::msg::DigitalIO>::SharedPtr io_pub_;
  rclcpp::Service<drasim_interfaces::srv::SetDO>::SharedPtr set_do_srv_;
  rclcpp::Service<drasim_interfaces::srv::GetDI>::SharedPtr get_di_srv_;
  rclcpp::TimerBase::SharedPtr timer_;
};
}
