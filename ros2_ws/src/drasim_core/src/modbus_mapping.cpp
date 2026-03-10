#include "drasim_core/modbus_mapping.hpp"
#include <climits>
namespace drasim_core{
bool ModbusMapping::is_dio_range(uint32_t a){return a>=DIO_BASE&&a<=DIO_END;}
bool ModbusMapping::is_app_range(uint32_t a){return a>=APP_BASE&&a<=APP_END;}
bool ModbusMapping::is_valid(uint32_t a){return is_dio_range(a)||is_app_range(a);}
std::size_t ModbusMapping::to_register_index(uint32_t a){if(is_dio_range(a))return static_cast<std::size_t>(a-DIO_BASE);if(is_app_range(a))return static_cast<std::size_t>(0x1000u+(a-APP_BASE));return SIZE_MAX;}
}//ns
