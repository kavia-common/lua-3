#ifndef DRASIM_CORE__IO_MAPPING_HPP_
#define DRASIM_CORE__IO_MAPPING_HPP_
#include <cstddef>
#include <string>
#include <unordered_map>
namespace drasim_core {
/** Translates named IO pins to 1-based numeric indices. */
class IOMapping {
public:
  static IOMapping & instance();
  void add_di(const std::string & name, std::size_t pin);
  void add_do(const std::string & name, std::size_t pin);
  std::size_t resolve_di(const std::string & pin_index) const;
  std::size_t resolve_do(const std::string & pin_index) const;
private:
  IOMapping() = default;
  std::unordered_map<std::string, std::size_t> di_map_;
  std::unordered_map<std::string, std::size_t> do_map_;
};
}  // namespace drasim_core
#endif  // DRASIM_CORE__IO_MAPPING_HPP_
