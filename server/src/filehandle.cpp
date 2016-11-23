#include <filehandle.h>
#include <iostream>

using std::ostream;

ostream& operator<< (ostream& stream, const filehandle& fh) {
   stream << "filehandle offset=" << fh.offset << std::endl;
   return stream;
}
