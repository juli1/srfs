#ifndef __FILEHANDLE_H__
#define __FILEHANDLE_H__

#include <iostream>
#include <fstream>

#include "error.h"

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

   std::string getPath ()
   {
      return this->path;
   }

   srfs_error_t set_path (std::string p)
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

   int read_data (char* data, int size)
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

   friend ostream& operator<< (ostream& stream, const filehandle& fh);

   ~filehandle ()
   {
      cout << "[filehandle] closing file through destructor" << endl;

      if (internal.is_open ())
      {
         internal.close();
      }
   }

private:
   std::ifstream internal;
   std::string path;
   uint32_t offset;

};

#endif

