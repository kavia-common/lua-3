#include "drasim_core/io_mapping.hpp"
#include <stdexcept>
namespace drasim_core{
IOMapping& IOMapping::instance(){static IOMapping i;return i;}
void IOMapping::add_di(const std::string&n,std::size_t p){if(n.empty()||n.size()>16)throw std::invalid_argument("name");di_map_[n]=p;}
void IOMapping::add_do(const std::string&n,std::size_t p){if(n.empty()||n.size()>16)throw std::invalid_argument("name");do_map_[n]=p;}
std::size_t IOMapping::resolve_di(const std::string&s)const{try{std::size_t p=std::stoul(s);if(p>=1&&p<=24)return p;}catch(...){}auto it=di_map_.find(s);return it!=di_map_.end()?it->second:0u;}
std::size_t IOMapping::resolve_do(const std::string&s)const{try{std::size_t p=std::stoul(s);if(p>=1&&p<=12)return p;}catch(...){}auto it=do_map_.find(s);return it!=do_map_.end()?it->second:0u;}
}//ns
