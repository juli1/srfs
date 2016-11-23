#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <stddef.h>

using std::size_t;

typedef enum requestt
{
   openfile = 1,
   closefile = 2,
   readfile = 3,
   invalid = -1
}request_t;

class request
{
public:
   // Constructors
   request() : type(invalid)
   {
      offset = 0; 
      size = 0;
   }

   request (request_t t, size_t o, size_t s) :  type(t), path("")
   {
      offset = o;
      size = s;
   }

   request (request_t t, std::string p) :  type(t), path (p)
   {
      offset = 0;
      size = 0;
   };

   void setPath (std::string p) {this->path = p;}

private:
   request_t type;
   std::string path;
   size_t size;
   size_t offset;
};

#endif

