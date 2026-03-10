#ifndef DRASIM_CORE__PARSERS_HPP_
#define DRASIM_CORE__PARSERS_HPP_
#include <string>
namespace drasim_core {
// PUBLIC_INTERFACE
bool parse_dio(const std::string & filepath);
// PUBLIC_INTERFACE
bool parse_lpt(const std::string & filepath);
}  // namespace drasim_core
#endif  // DRASIM_CORE__PARSERS_HPP_
