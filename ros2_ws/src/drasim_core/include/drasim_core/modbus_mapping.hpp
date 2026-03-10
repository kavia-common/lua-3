#ifndef DRASIM_CORE__MODBUS_MAPPING_HPP_
#define DRASIM_CORE__MODBUS_MAPPING_HPP_
#include <cstdint>
#include <cstddef>
#include <climits>
namespace drasim_core {
/** Modbus address validation and MemoryImage index conversion. */
class ModbusMapping {
public:
  static constexpr uint32_t DIO_BASE = 0x1000u;
  static constexpr uint32_t DIO_END  = 0x1FFFu;
  static constexpr uint32_t APP_BASE = 0x3000u;
  static constexpr uint32_t APP_END  = 0x3FFFu;
  static bool is_dio_range(uint32_t address);
  static bool is_app_range(uint32_t address);
  static bool is_valid(uint32_t address);
  static std::size_t to_register_index(uint32_t address);
};
}  // namespace drasim_core
#endif  // DRASIM_CORE__MODBUS_MAPPING_HPP_
