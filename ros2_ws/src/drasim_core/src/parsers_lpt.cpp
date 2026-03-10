#include "drasim_core/parsers.hpp"
#include <fstream>
#include <iostream>
namespace drasim_core{
bool parse_lpt(const std::string&fp){std::ifstream f(fp,std::ios::binary);if(!f.is_open()){std::cerr<<"[core] no LPT.bin\n";return true;}std::cout<<"[core] LPT.bin stub: "<<fp<<"\n";return true;}
}//ns
