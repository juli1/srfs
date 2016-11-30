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
}request_type_t;

class request
{
public:
   // Constructors
   request() : type(invalid)
   {
      offset = 0; 
      size = 0;
   }

   request (request_type_t t, size_t o, size_t s) :  type(t), path("")
   {
      offset = o;
      size = s;
   }

   request (request_type_t t, std::string p) :  type(t), path (p)
   {
      offset = 0;
      size = 0;
   };

   void setPath (std::string p) {this->path = p;}
   void setType (request_type_t t) {this->type = t;}
   request_type_t getType() {return this->type;}
   std::string getPath() {return this->path;}

private:
   request_type_t type;
   std::string path;
   size_t size;
   size_t offset;
};

#endif

