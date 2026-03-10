#pragma once
#include <atomic>
#include <cstdint>
#include <string>
#include <thread>
namespace drasim_modbus {
class ModbusTcpServer {
public:
  explicit ModbusTcpServer(const std::string&host="0.0.0.0",uint16_t port=1502);
  void start();
  void stop();
  bool is_running()const{return running_.load();}
private:
  void accept_loop();
  void handle_client(int fd);
  void process_pdu(const uint8_t*pdu,std::size_t len,uint8_t*resp,std::size_t&rlen,uint16_t txid,uint16_t uid);
  std::string host_;uint16_t port_;int server_fd_{-1};
  std::atomic<bool>running_{false};std::thread server_thread_;
};
}
