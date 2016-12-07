#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#include <string>

enum severity_t
{
	SEVERITY_INFO,
	SEVERITY_LOGGING,
	SEVERITY_WARNING,
	SEVERITY_ERROR
};

void debugfunc (std::string msg, severity_t severity, std::string filename, int line);

#define debug(x,y) debugfunc(x,y,__FILE__,__LINE__)


#endif

