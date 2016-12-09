#include <iostream>

#include "debug.hpp"
#include "filehandle.hpp"

using namespace std;
using std::ostream;

ostream& operator<< (ostream& stream, const filehandle& fh) {
   stream << "filehandle offset=" << fh.offset << std::endl;
   return stream;
}

filehandle::filehandle ()
{
}

filehandle::filehandle(std::string p) : path(p)
{
	offset = 0;
	internal.open (p);
}

std::string filehandle::getPath ()
{
	return this->path;
}

srfs_error_t filehandle::set_path (std::string p)
{
	this->path = p;
	this->offset = 0;
	internal.open (p, ios::in |  ios::out);

	if (internal.is_open ())
	{
		return no_error;
	}
	else
	{
		return not_available;
	}
}

int filehandle::read_data (char* data, int size)
{
	char c;
	char* ptr;
	int readsize;

	readsize = 0;
	ptr = data;

	while ( (readsize < size) && (!internal.eof()) )
	{
		internal.get(c);
		*ptr = c;
		ptr++;
		readsize++;
	}

	return readsize;
}


filehandle::~filehandle ()
{
	debug ("[filehandle] closing file through destructor", SEVERITY_DEBUG);

	if (internal.is_open ())
	{
		internal.close();
	}
}


