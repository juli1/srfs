#ifndef __FILEHANDLE_H__
#define __FILEHANDLE_H__

#include <iostream>

using std::ostream;

class filehandle
{
public:
   filehandle ()
   {
   }

   filehandle(std::string p) : path(p)
   {
      offset = 0;
   }

   void setPath (std::string p)
   {
      this->path = p;
      this->offset = 0;
   }

   friend ostream& operator<< (ostream& stream, const filehandle& fh);

private:
   std::string path;
   uint32_t offset;

};

#endif

