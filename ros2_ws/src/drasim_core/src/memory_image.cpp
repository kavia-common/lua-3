// drasim_core/src/memory_image.cpp
// Thread-safe MemoryImage implementation backed by a dictionary (unordered_map)
// keyed by raw Modbus address.
#include "drasim_core/memory_image.hpp"

#include <cstddef>

namespace drasim_core
{

// PUBLIC_INTERFACE
MemoryImage & MemoryImage::instance()
{
  static MemoryImage inst;
  return inst;
}

// ---------------------------------------------------------------------------
// Digital Input helpers
// ---------------------------------------------------------------------------

// PUBLIC_INTERFACE
bool MemoryImage::get_di(std::size_t pin) const
{
  if (pin < 1 || pin > DI_COUNT) { return false; }
  std::lock_guard<std::mutex> lk(mutex_);
  return di_pins_[pin - 1];
}

// PUBLIC_INTERFACE
void MemoryImage::set_di(std::size_t pin, bool state)
{
  if (pin < 1 || pin > DI_COUNT) { return; }
  std::lock_guard<std::mutex> lk(mutex_);
  di_pins_[pin - 1] = state;
}

// PUBLIC_INTERFACE
uint32_t MemoryImage::get_di_block(std::size_t start_pin, std::size_t length) const
{
  uint32_t result = 0;
  std::lock_guard<std::mutex> lk(mutex_);
  for (std::size_t i = 0; i < length; ++i) {
    std::size_t pin = start_pin + i;
    if (pin < 1 || pin > DI_COUNT) { break; }
    if (di_pins_[pin - 1]) { result |= (1u << i); }
  }
  return result;
}

// ---------------------------------------------------------------------------
// Digital Output helpers
// ---------------------------------------------------------------------------

// PUBLIC_INTERFACE
bool MemoryImage::get_do(std::size_t pin) const
{
  if (pin < 1 || pin > DO_COUNT) { return false; }
  std::lock_guard<std::mutex> lk(mutex_);
  return do_pins_[pin - 1];
}

// PUBLIC_INTERFACE
void MemoryImage::set_do(std::size_t pin, bool state)
{
  if (pin < 1 || pin > DO_COUNT) { return; }
  std::lock_guard<std::mutex> lk(mutex_);
  do_pins_[pin - 1] = state;
}

// PUBLIC_INTERFACE
uint32_t MemoryImage::get_do_block(std::size_t start_pin, std::size_t length) const
{
  uint32_t result = 0;
  std::lock_guard<std::mutex> lk(mutex_);
  for (std::size_t i = 0; i < length; ++i) {
    std::size_t pin = start_pin + i;
    if (pin < 1 || pin > DO_COUNT) { break; }
    if (do_pins_[pin - 1]) { result |= (1u << i); }
  }
  return result;
}

// ---------------------------------------------------------------------------
// Modbus register access — dictionary (map) keyed by Modbus address
// ---------------------------------------------------------------------------

// PUBLIC_INTERFACE
int16_t MemoryImage::read_word(uint32_t address) const
{
  std::lock_guard<std::mutex> lk(mutex_);
  auto it = registers_.find(address);
  return (it != registers_.end()) ? it->second : static_cast<int16_t>(0);
}

// PUBLIC_INTERFACE
void MemoryImage::write_word(uint32_t address, int16_t value)
{
  std::lock_guard<std::mutex> lk(mutex_);
  registers_[address] = value;
}

// PUBLIC_INTERFACE
int32_t MemoryImage::read_dword(uint32_t address) const
{
  if (address % 2 != 0) { return 0; }
  std::lock_guard<std::mutex> lk(mutex_);
  // Low word at address, high word at address + 1
  auto lo_it = registers_.find(address);
  auto hi_it = registers_.find(address + 1);
  uint16_t lo = (lo_it != registers_.end()) ? static_cast<uint16_t>(lo_it->second) : 0u;
  uint16_t hi = (hi_it != registers_.end()) ? static_cast<uint16_t>(hi_it->second) : 0u;
  return static_cast<int32_t>((static_cast<uint32_t>(hi) << 16u) | static_cast<uint32_t>(lo));
}

// PUBLIC_INTERFACE
void MemoryImage::write_dword(uint32_t address, int32_t value)
{
  if (address % 2 != 0) { return; }
  std::lock_guard<std::mutex> lk(mutex_);
  registers_[address]     = static_cast<int16_t>(value & 0xFFFF);
  registers_[address + 1] = static_cast<int16_t>((value >> 16) & 0xFFFF);
}

// PUBLIC_INTERFACE
std::unordered_map<uint32_t, int16_t> MemoryImage::snapshot_registers() const
{
  std::lock_guard<std::mutex> lk(mutex_);
  return registers_;
}

}  // namespace drasim_core
