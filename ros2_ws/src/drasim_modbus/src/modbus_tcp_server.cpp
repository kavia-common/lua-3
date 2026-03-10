// drasim_modbus/src/modbus_tcp_server.cpp
// Minimal Modbus/TCP server skeleton bound to MemoryImage.
#include "drasim_modbus/modbus_tcp_server.hpp"
#include <drasim_core/memory_image.hpp>
#include <drasim_core/modbus_mapping.hpp>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <stdexcept>

namespace drasim_modbus
{

static constexpr uint8_t FC_RH = 0x03;  // Read Holding Registers
static constexpr uint8_t FC_WS = 0x06;  // Write Single Register
static constexpr uint8_t FC_WM = 0x10;  // Write Multiple Registers
static constexpr std::size_t MBAP_SZ = 6;
static constexpr std::size_t MAX_PDU = 253;

ModbusTcpServer::ModbusTcpServer(const std::string & h, uint16_t p)
: host_(h), port_(p) {}

void ModbusTcpServer::start()
{
  if (running_.load()) { return; }
  server_fd_ = ::socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd_ < 0) { throw std::runtime_error("[Modbus] socket() failed"); }
  int opt = 1;
  ::setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  sockaddr_in a{};
  a.sin_family = AF_INET;
  a.sin_port   = htons(port_);
  ::inet_pton(AF_INET, host_.c_str(), &a.sin_addr);
  if (::bind(server_fd_, (sockaddr *)&a, sizeof(a)) < 0) {
    ::close(server_fd_);
    throw std::runtime_error("[Modbus] bind() failed");
  }
  if (::listen(server_fd_, 5) < 0) {
    ::close(server_fd_);
    throw std::runtime_error("[Modbus] listen() failed");
  }
  running_.store(true);
  server_thread_ = std::thread([this] { accept_loop(); });
  std::cout << "[Modbus] Listening on " << host_ << ":" << port_ << "\n";
}

void ModbusTcpServer::stop()
{
  running_.store(false);
  if (server_fd_ >= 0) { ::shutdown(server_fd_, SHUT_RDWR); ::close(server_fd_); server_fd_ = -1; }
  if (server_thread_.joinable()) { server_thread_.join(); }
}

void ModbusTcpServer::accept_loop()
{
  while (running_.load()) {
    sockaddr_in ca{};
    socklen_t l = sizeof(ca);
    int cfd = ::accept(server_fd_, (sockaddr *)&ca, &l);
    if (cfd < 0) { if (running_.load()) { std::cerr << "[Modbus] accept err\n"; } break; }
    std::thread([this, cfd] { handle_client(cfd); }).detach();
  }
}

void ModbusTcpServer::handle_client(int fd)
{
  uint8_t buf[MBAP_SZ + MAX_PDU];
  uint8_t resp[MBAP_SZ + MAX_PDU];
  while (running_.load()) {
    if (::recv(fd, buf, MBAP_SZ, MSG_WAITALL) != (ssize_t)MBAP_SZ) { break; }
    uint16_t txid = (uint16_t)((buf[0] << 8) | buf[1]);
    uint16_t pl   = (uint16_t)((buf[4] << 8) | buf[5]);
    if (!pl || pl > MAX_PDU + 1) { break; }
    if (::recv(fd, buf + MBAP_SZ, pl, MSG_WAITALL) != (ssize_t)pl) { break; }
    std::size_t rl = 0;
    process_pdu(buf + MBAP_SZ, pl, resp + MBAP_SZ, rl, txid, buf[MBAP_SZ - 1]);
    resp[0] = (txid >> 8) & 0xFF; resp[1] = txid & 0xFF;
    resp[2] = 0; resp[3] = 0;
    resp[4] = (rl >> 8) & 0xFF; resp[5] = rl & 0xFF;
    ::send(fd, resp, MBAP_SZ + rl, 0);
  }
  ::close(fd);
}

void ModbusTcpServer::process_pdu(
  const uint8_t * pdu, std::size_t,
  uint8_t * resp, std::size_t & rl,
  uint16_t, uint16_t)
{
  auto & mem = drasim_core::MemoryImage::instance();
  uint8_t fc = pdu[0];
  if (fc == FC_RH) {
    uint16_t st  = (uint16_t)((pdu[1] << 8) | pdu[2]);
    uint16_t qty = (uint16_t)((pdu[3] << 8) | pdu[4]);
    resp[0] = fc; resp[1] = (uint8_t)(qty * 2);
    for (uint16_t i = 0; i < qty; ++i) {
      auto idx = drasim_core::ModbusMapping::to_register_index(st + i);
      int16_t v = (idx != SIZE_MAX) ? mem.read_word((uint32_t)idx) : 0;
      resp[2 + i * 2]     = (uint8_t)((v >> 8) & 0xFF);
      resp[2 + i * 2 + 1] = (uint8_t)(v & 0xFF);
    }
    rl = 2 + (std::size_t)(qty * 2);
  } else if (fc == FC_WS) {
    uint16_t ad = (uint16_t)((pdu[1] << 8) | pdu[2]);
    int16_t v   = (int16_t)((pdu[3] << 8) | pdu[4]);
    auto idx = drasim_core::ModbusMapping::to_register_index(ad);
    if (idx != SIZE_MAX) { mem.write_word((uint32_t)idx, v); }
    std::memcpy(resp, pdu, 5); rl = 5;
  } else if (fc == FC_WM) {
    uint16_t st  = (uint16_t)((pdu[1] << 8) | pdu[2]);
    uint16_t qty = (uint16_t)((pdu[3] << 8) | pdu[4]);
    for (uint16_t i = 0; i < qty; ++i) {
      int16_t v = (int16_t)((pdu[6 + i * 2] << 8) | pdu[6 + i * 2 + 1]);
      auto idx  = drasim_core::ModbusMapping::to_register_index(st + i);
      if (idx != SIZE_MAX) { mem.write_word((uint32_t)idx, v); }
    }
    resp[0] = fc; resp[1] = pdu[1]; resp[2] = pdu[2];
    resp[3] = pdu[3]; resp[4] = pdu[4]; rl = 5;
  } else {
    resp[0] = (uint8_t)(fc | 0x80); resp[1] = 0x01; rl = 2;
  }
}

}  // namespace drasim_modbus
