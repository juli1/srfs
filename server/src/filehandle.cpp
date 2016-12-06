#include <iostream>

#include "filehandle.hpp"

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

	//cout << "open the path|" << p << "|" << endl;

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
		cout << "read char" << c << endl;
		ptr++;
		readsize++;
	}

	cout << "read data " << data << endl;

	return readsize;
}


filehandle::~filehandle ()
{
	cout << "[filehandle] closing file through destructor" << endl;

	if (internal.is_open ())
	{
		internal.close();
	}
}


