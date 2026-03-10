#include "drasim_core/parsers.hpp"
#include "drasim_core/io_mapping.hpp"
#include <fstream>
#include <iostream>
namespace drasim_core{
bool parse_dio(const std::string&fp){std::ifstream f(fp);if(!f.is_open()){std::cerr<<"[core] no UserIO.dio\n";return true;}std::string tok;while(f>>tok){std::string n;std::size_t p=0;if(tok=="DI"||tok=="DO"){f>>n>>p;if(tok=="DI")IOMapping::instance().add_di(n,p);else IOMapping::instance().add_do(n,p);}}std::cout<<"[core] loaded "<<fp<<"\n";return true;}
}//ns
