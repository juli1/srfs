#include <iostream>

#include "debug.hpp"

using namespace std;


void debugfunc (std::string msg, severity_t sev, std::string filename, int line)
{
	cout << "[" << filename << ":"<< line << "] "  << msg << endl;
}

