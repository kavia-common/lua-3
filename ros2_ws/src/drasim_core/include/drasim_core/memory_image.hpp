#ifndef DRASIM_CORE__MEMORY_IMAGE_HPP_
#define DRASIM_CORE__MEMORY_IMAGE_HPP_

#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_map>

namespace drasim_core
{

/**
 * @brief MemoryImage — thread-safe single source of truth for all IO and Modbus registers.
 *
 * Modbus register storage is dictionary-based: an unordered_map keyed by the
 * raw Modbus address (uint32_t).  Valid address ranges are:
 *   0x1000 – 0x1FFF : DI/DO mirror registers
 *   0x3000 – 0x3FFF : General-purpose application registers
 *
 * read_word / write_word / read_dword / write_dword all accept the Modbus
 * address directly – no external index translation is required.
 */
class MemoryImage
{
public:
  static constexpr std::size_t DI_COUNT = 24;
  static constexpr std::size_t DO_COUNT = 12;

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
  /**
   * @brief Read a 16-bit Modbus register.
   * @param address  Raw Modbus address (e.g. 0x1000 – 0x3FFF).
   * @return Stored value, or 0 if the address has never been written.
   */
  int16_t read_word(uint32_t address) const;

  // PUBLIC_INTERFACE
  /**
   * @brief Write a 16-bit Modbus register.
   * @param address  Raw Modbus address.
   * @param value    Value to store.
   */
  void write_word(uint32_t address, int16_t value);

  // PUBLIC_INTERFACE
  /**
   * @brief Read a 32-bit Modbus register pair (address must be even).
   * Low word is at @p address, high word at @p address+1.
   * @param address  Raw Modbus base address (must be even).
   * @return 32-bit signed value, or 0 on alignment error.
   */
  int32_t read_dword(uint32_t address) const;

  // PUBLIC_INTERFACE
  /**
   * @brief Write a 32-bit Modbus register pair (address must be even).
   * Low word is stored at @p address, high word at @p address+1.
   * @param address  Raw Modbus base address (must be even).
   * @param value    32-bit signed value to store.
   */
  void write_dword(uint32_t address, int32_t value);

  // PUBLIC_INTERFACE
  /**
   * @brief Return a snapshot copy of the entire register map.
   * Useful for diagnostic / serialisation purposes.
   */
  std::unordered_map<uint32_t, int16_t> snapshot_registers() const;

private:
  MemoryImage() = default;
  MemoryImage(const MemoryImage &) = delete;
  MemoryImage & operator=(const MemoryImage &) = delete;

  mutable std::mutex mutex_;
  bool di_pins_[DI_COUNT]{};
  bool do_pins_[DO_COUNT]{};
  /// Register store: key = Modbus address, value = 16-bit register value.
  std::unordered_map<uint32_t, int16_t> registers_;
};

}  // namespace drasim_core

#endif  // DRASIM_CORE__MEMORY_IMAGE_HPP_
