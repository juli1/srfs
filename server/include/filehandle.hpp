#ifndef __FILEHANDLE_H__
#define __FILEHANDLE_H__

#include <iostream>
#include <fstream>

#include "error.h"

using std::ostream;

typedef enum filehandlestatus
{
   active = 0,
   inactive = 1
} filehandle_status_t;

class filehandle
{
public:
   filehandle ();

   filehandle(std::string p);

   std::string getPath ();

   srfs_error_t set_path (std::string p);

   int read_data (char* data, int size);

   friend ostream& operator<< (ostream& stream, const filehandle& fh);

   ~filehandle ();

private:
   std::ifstream internal;
   std::string path;
   uint32_t offset;

};

#endif

