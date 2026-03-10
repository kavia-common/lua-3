// drasim_modbus/src/modbus_node.cpp
// ModbusNode — ROS2 service node that exposes ReadModbus / WriteModbus services.
// Register access uses the dictionary-backed MemoryImage: raw Modbus addresses
// are passed directly to read_word / write_word / read_dword / write_dword.
// Lambdas use explicit types required by ROS2 Jazzy's create_service API.
#include "drasim_modbus/modbus_node.hpp"
#include <drasim_core/memory_image.hpp>
#include <drasim_core/modbus_mapping.hpp>
#include <stdexcept>
#include <string>

namespace drasim_modbus
{

ModbusNode::ModbusNode(const rclcpp::NodeOptions & o)
: rclcpp::Node("drasim_modbus_node", o)
{
  this->declare_parameter<std::string>("modbus_host", "0.0.0.0");
  this->declare_parameter<int>("modbus_port", 1502);
  std::string host = this->get_parameter("modbus_host").as_string();
  int port         = this->get_parameter("modbus_port").as_int();
  RCLCPP_INFO(this->get_logger(), "Starting Modbus/TCP on %s:%d", host.c_str(), port);

  tcp_ = std::make_unique<ModbusTcpServer>(host, (uint16_t)port);
  try { tcp_->start(); } catch (const std::exception & e) {
    RCLCPP_ERROR(this->get_logger(), "TCP failed: %s", e.what());
  }

  ep_ = this->create_publisher<drasim_interfaces::msg::ModbusRegister>(
    "/drasim/modbus_event", rclcpp::QoS(10));

  // Use explicit shared_ptr types — required by ROS2 Jazzy's create_service.
  rs_ = this->create_service<drasim_interfaces::srv::ReadModbus>(
    "/drasim/read_modbus",
    [this](std::shared_ptr<drasim_interfaces::srv::ReadModbus::Request> q,
           std::shared_ptr<drasim_interfaces::srv::ReadModbus::Response> r)
    { handle_read(q, r); });

  ws_ = this->create_service<drasim_interfaces::srv::WriteModbus>(
    "/drasim/write_modbus",
    [this](std::shared_ptr<drasim_interfaces::srv::WriteModbus::Request> q,
           std::shared_ptr<drasim_interfaces::srv::WriteModbus::Response> r)
    { handle_write(q, r); });
}

ModbusNode::~ModbusNode()
{
  if (tcp_ && tcp_->is_running()) { tcp_->stop(); }
}

void ModbusNode::handle_read(
  std::shared_ptr<drasim_interfaces::srv::ReadModbus::Request> req,
  std::shared_ptr<drasim_interfaces::srv::ReadModbus::Response> res)
{
  uint32_t addr = req->reg_address;

  // Validate that the address falls within a supported Modbus range.
  if (!drasim_core::ModbusMapping::is_valid(addr)) {
    res->success = false;
    res->message = "Invalid address: 0x" + std::to_string(addr);
    return;
  }

  auto & mem = drasim_core::MemoryImage::instance();

  if (req->size == "DW") {
    if (addr % 2 != 0) {
      res->success = false;
      res->message = "DW read requires an even Modbus address";
      return;
    }
    // Pass the raw Modbus address — MemoryImage now handles dictionary lookup.
    res->value = mem.read_dword(addr);
  } else {
    res->value = static_cast<int32_t>(mem.read_word(addr));
  }

  res->success = true;
  res->message = "OK";
}

void ModbusNode::handle_write(
  std::shared_ptr<drasim_interfaces::srv::WriteModbus::Request> req,
  std::shared_ptr<drasim_interfaces::srv::WriteModbus::Response> res)
{
  uint32_t addr = req->reg_address;

  // Validate that the address falls within a supported Modbus range.
  if (!drasim_core::ModbusMapping::is_valid(addr)) {
    res->success = false;
    res->message = "Invalid address: 0x" + std::to_string(addr);
    return;
  }

  auto & mem = drasim_core::MemoryImage::instance();

  if (req->size == "DW") {
    if (addr % 2 != 0) {
      res->success = false;
      res->message = "DW write requires an even Modbus address";
      return;
    }
    // Pass the raw Modbus address — MemoryImage now handles dictionary lookup.
    mem.write_dword(addr, req->reg_value);
  } else {
    mem.write_word(addr, static_cast<int16_t>(req->reg_value));
  }

  // Publish a change notification event on the Modbus event topic.
  drasim_interfaces::msg::ModbusRegister ev;
  ev.stamp     = this->now();
  ev.address   = addr;
  ev.data_type = req->size;
  ev.value     = req->reg_value;
  ep_->publish(ev);

  res->success = true;
  res->message = "OK";
}

}  // namespace drasim_modbus
