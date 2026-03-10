#ifndef DRASIM_CORE__MODBUS_MAPPING_HPP_
#define DRASIM_CORE__MODBUS_MAPPING_HPP_

#include <cstdint>

namespace drasim_core
{

/**
 * @brief ModbusMapping — address-range validator for the dictionary-backed MemoryImage.
 *
 * With dictionary-based register storage, callers pass raw Modbus addresses
 * directly to MemoryImage::read_word / write_word / read_dword / write_dword.
 * This class provides helpers to validate that an address falls within a known,
 * supported range before making those calls.
 *
 * Valid address ranges:
 *   DIO_BASE (0x1000) – DIO_END  (0x1FFF) : DI/DO mirror registers
 *   APP_BASE (0x3000) – APP_END  (0x3FFF) : General-purpose application registers
 */
class ModbusMapping
{
public:
  /// Base / end of the DI-DO mirror register block.
  static constexpr uint32_t DIO_BASE = 0x1000u;
  static constexpr uint32_t DIO_END  = 0x1FFFu;

  /// Base / end of the general-purpose application register block.
  static constexpr uint32_t APP_BASE = 0x3000u;
  static constexpr uint32_t APP_END  = 0x3FFFu;

  // PUBLIC_INTERFACE
  /** @brief Return true if @p address falls in the DI/DO mirror range. */
  static bool is_dio_range(uint32_t address);

  // PUBLIC_INTERFACE
  /** @brief Return true if @p address falls in the application register range. */
  static bool is_app_range(uint32_t address);

  // PUBLIC_INTERFACE
  /** @brief Return true if @p address is within any supported Modbus range. */
  static bool is_valid(uint32_t address);
};

}  // namespace drasim_core

#endif  // DRASIM_CORE__MODBUS_MAPPING_HPP_
