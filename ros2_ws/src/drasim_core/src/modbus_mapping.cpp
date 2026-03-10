// drasim_core/src/modbus_mapping.cpp
// ModbusMapping — address-range validation helpers.
// With dictionary-based MemoryImage storage, address-to-index translation is
// no longer required.  Callers use the raw Modbus address directly.
#include "drasim_core/modbus_mapping.hpp"

namespace drasim_core
{

// PUBLIC_INTERFACE
bool ModbusMapping::is_dio_range(uint32_t address)
{
  return address >= DIO_BASE && address <= DIO_END;
}

// PUBLIC_INTERFACE
bool ModbusMapping::is_app_range(uint32_t address)
{
  return address >= APP_BASE && address <= APP_END;
}

// PUBLIC_INTERFACE
bool ModbusMapping::is_valid(uint32_t address)
{
  return is_dio_range(address) || is_app_range(address);
}

}  // namespace drasim_core
