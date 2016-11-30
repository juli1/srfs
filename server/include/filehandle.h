#ifndef __FILEHANDLE_H__
#define __FILEHANDLE_H__

#include <iostream>
#include <fstream>

using std::ostream;
using namespace std;

typedef enum filehandlestatus
{
   active = 0,
   inactive = 1
} filehandle_status_t;

class filehandle
{
public:
   filehandle ()
   {
   }

   filehandle(std::string p) : path(p)
   {
      offset = 0;
      internal.open (p);
   }

   void set_path (std::string p)
   {
      this->path = p;
      this->offset = 0;
      internal.open (p);
   }

   friend ostream& operator<< (ostream& stream, const filehandle& fh);

private:
   std::fstream internal;
   std::string path;
   uint32_t offset;

};

#endif

