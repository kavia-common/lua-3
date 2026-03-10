#include "drasim_core/memory_image.hpp"
#include <cstddef>
namespace drasim_core {
MemoryImage& MemoryImage::instance(){static MemoryImage i;return i;}
bool MemoryImage::get_di(std::size_t p)const{if(p<1||p>DI_COUNT)return false;std::lock_guard<std::mutex>l(mutex_);return di_pins_[p-1];}
void MemoryImage::set_di(std::size_t p,bool s){if(p<1||p>DI_COUNT)return;std::lock_guard<std::mutex>l(mutex_);di_pins_[p-1]=s;}
uint32_t MemoryImage::get_di_block(std::size_t sp,std::size_t n)const{uint32_t r=0;std::lock_guard<std::mutex>l(mutex_);for(std::size_t i=0;i<n;++i){std::size_t pin=sp+i;if(pin<1||pin>DI_COUNT)break;if(di_pins_[pin-1])r|=(1u<<i);}return r;}
bool MemoryImage::get_do(std::size_t p)const{if(p<1||p>DO_COUNT)return false;std::lock_guard<std::mutex>l(mutex_);return do_pins_[p-1];}
void MemoryImage::set_do(std::size_t p,bool s){if(p<1||p>DO_COUNT)return;std::lock_guard<std::mutex>l(mutex_);do_pins_[p-1]=s;}
uint32_t MemoryImage::get_do_block(std::size_t sp,std::size_t n)const{uint32_t r=0;std::lock_guard<std::mutex>l(mutex_);for(std::size_t i=0;i<n;++i){std::size_t pin=sp+i;if(pin<1||pin>DO_COUNT)break;if(do_pins_[pin-1])r|=(1u<<i);}return r;}
int16_t MemoryImage::read_word(uint32_t idx)const{if(idx>=REG_COUNT)return 0;std::lock_guard<std::mutex>l(mutex_);return registers_[idx];}
void MemoryImage::write_word(uint32_t idx,int16_t v){if(idx>=REG_COUNT)return;std::lock_guard<std::mutex>l(mutex_);registers_[idx]=v;}
int32_t MemoryImage::read_dword(uint32_t idx)const{if(idx%2!=0||idx+1>=REG_COUNT)return 0;std::lock_guard<std::mutex>l(mutex_);return static_cast<int32_t>((static_cast<uint16_t>(registers_[idx+1])<<16u)|static_cast<uint16_t>(registers_[idx]));}
void MemoryImage::write_dword(uint32_t idx,int32_t v){if(idx%2!=0||idx+1>=REG_COUNT)return;std::lock_guard<std::mutex>l(mutex_);registers_[idx]=static_cast<int16_t>(v&0xFFFF);registers_[idx+1]=static_cast<int16_t>((v>>16)&0xFFFF);}
}//ns
