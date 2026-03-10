// drasim_modbus/src/modbus_node.cpp
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

  rs_ = this->create_service<drasim_interfaces::srv::ReadModbus>(
    "/drasim/read_modbus",
    [this](auto q, auto r) { handle_read(q, r); });

  ws_ = this->create_service<drasim_interfaces::srv::WriteModbus>(
    "/drasim/write_modbus",
    [this](auto q, auto r) { handle_write(q, r); });
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
  if (!drasim_core::ModbusMapping::is_valid(addr)) {
    res->success = false; res->message = "Invalid address"; return;
  }
  auto idx = drasim_core::ModbusMapping::to_register_index(addr);
  auto & mem = drasim_core::MemoryImage::instance();
  if (req->size == "DW") {
    if (addr % 2 != 0) { res->success = false; res->message = "DW needs even addr"; return; }
    res->value = mem.read_dword((uint32_t)idx);
  } else {
    res->value = mem.read_word((uint32_t)idx);
  }
  res->success = true; res->message = "OK";
}

void ModbusNode::handle_write(
  std::shared_ptr<drasim_interfaces::srv::WriteModbus::Request> req,
  std::shared_ptr<drasim_interfaces::srv::WriteModbus::Response> res)
{
  uint32_t addr = req->reg_address;
  if (!drasim_core::ModbusMapping::is_valid(addr)) {
    res->success = false; res->message = "Invalid address"; return;
  }
  auto idx = drasim_core::ModbusMapping::to_register_index(addr);
  auto & mem = drasim_core::MemoryImage::instance();
  if (req->size == "DW") {
    if (addr % 2 != 0) { res->success = false; res->message = "DW needs even addr"; return; }
    mem.write_dword((uint32_t)idx, req->reg_value);
  } else {
    mem.write_word((uint32_t)idx, (int16_t)req->reg_value);
  }
  drasim_interfaces::msg::ModbusRegister ev;
  ev.stamp = this->now(); ev.address = addr;
  ev.data_type = req->size; ev.value = req->reg_value;
  ep_->publish(ev);
  res->success = true; res->message = "OK";
}

}  // namespace drasim_modbus
