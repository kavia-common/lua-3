#pragma once
#include "drasim_modbus/modbus_tcp_server.hpp"
#include <rclcpp/rclcpp.hpp>
#include <drasim_interfaces/srv/read_modbus.hpp>
#include <drasim_interfaces/srv/write_modbus.hpp>
#include <drasim_interfaces/msg/modbus_register.hpp>
#include <memory>
namespace drasim_modbus {
class ModbusNode : public rclcpp::Node {
public:
  explicit ModbusNode(const rclcpp::NodeOptions&o=rclcpp::NodeOptions());
  ~ModbusNode()override;
private:
  void handle_read(std::shared_ptr<drasim_interfaces::srv::ReadModbus::Request>,std::shared_ptr<drasim_interfaces::srv::ReadModbus::Response>);
  void handle_write(std::shared_ptr<drasim_interfaces::srv::WriteModbus::Request>,std::shared_ptr<drasim_interfaces::srv::WriteModbus::Response>);
  std::unique_ptr<ModbusTcpServer>tcp_;
  rclcpp::Service<drasim_interfaces::srv::ReadModbus>::SharedPtr rs_;
  rclcpp::Service<drasim_interfaces::srv::WriteModbus>::SharedPtr ws_;
  rclcpp::Publisher<drasim_interfaces::msg::ModbusRegister>::SharedPtr ep_;
};
}
