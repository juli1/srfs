#include <iostream>

#include "debug.hpp"


using std::endl;
using std::cerr;


void debugfunc (std::string msg, severity_t sev  __attribute__((unused)), std::string filename, int line)
{
	cerr << "[" << filename << ":"<< line << "] "  << msg << endl;
}

