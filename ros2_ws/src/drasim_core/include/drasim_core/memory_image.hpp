#ifndef DRASIM_CORE__MEMORY_IMAGE_HPP_
#define DRASIM_CORE__MEMORY_IMAGE_HPP_

#include <array>
#include <cstdint>
#include <mutex>
#include <string>

namespace drasim_core
{

/**
 * @brief MemoryImage — thread-safe single source of truth for all IO and Modbus registers.
 *
 * Modbus address space:
 *   0x1000 – 0x1FFF : DI/DO mirror registers
 *   0x3000 – 0x3FFF : General-purpose application registers
 */
class MemoryImage
{
public:
  static constexpr std::size_t DI_COUNT  = 24;
  static constexpr std::size_t DO_COUNT  = 12;
  static constexpr std::size_t REG_COUNT = 4096;

  // PUBLIC_INTERFACE
  /** @brief Singleton accessor. */
  static MemoryImage & instance();

  // PUBLIC_INTERFACE
  /** @brief Read a single DI pin state (1-based, 1-24). */
  bool get_di(std::size_t pin) const;

  // PUBLIC_INTERFACE
  /** @brief Set a single DI pin (1-based). */
  void set_di(std::size_t pin, bool state);

  // PUBLIC_INTERFACE
  /** @brief Read a block of DI pins as LSB-first bitmask. */
  uint32_t get_di_block(std::size_t start_pin, std::size_t length) const;

  // PUBLIC_INTERFACE
  /** @brief Read a single DO pin state (1-based, 1-12). */
  bool get_do(std::size_t pin) const;

  // PUBLIC_INTERFACE
  /** @brief Set a single DO pin (1-based). */
  void set_do(std::size_t pin, bool state);

  // PUBLIC_INTERFACE
  /** @brief Read a block of DO pins as LSB-first bitmask. */
  uint32_t get_do_block(std::size_t start_pin, std::size_t length) const;

  // PUBLIC_INTERFACE
  /** @brief Read a 16-bit Modbus register. */
  int16_t read_word(uint32_t index) const;

  // PUBLIC_INTERFACE
  /** @brief Write a 16-bit Modbus register. */
  void write_word(uint32_t index, int16_t value);

  // PUBLIC_INTERFACE
  /** @brief Read a 32-bit Modbus register pair (address must be even). */
  int32_t read_dword(uint32_t index) const;

  // PUBLIC_INTERFACE
  /** @brief Write a 32-bit Modbus register pair (address must be even). */
  void write_dword(uint32_t index, int32_t value);

  // PUBLIC_INTERFACE
  /** @brief Const pointer to raw 16-bit register array. */
  const int16_t * raw_registers() const { return registers_.data(); }

  // PUBLIC_INTERFACE
  /** @brief Mutable pointer to raw 16-bit register array. */
  int16_t * raw_registers_mutable() { return registers_.data(); }

private:
  MemoryImage() = default;
  MemoryImage(const MemoryImage &) = delete;
  MemoryImage & operator=(const MemoryImage &) = delete;

  mutable std::mutex mutex_;
  std::array<bool, DI_COUNT>     di_pins_{};
  std::array<bool, DO_COUNT>     do_pins_{};
  std::array<int16_t, REG_COUNT> registers_{};
};

}  // namespace drasim_core

#endif  // DRASIM_CORE__MEMORY_IMAGE_HPP_
