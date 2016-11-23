#ifndef __REPLY_H__
#define __REPLY_H__

#include <cstring>
#include "error.h"

typedef enum replytypet
{
   ok,
   error,
}reply_type_t;

class reply
{
public:
   static const uint32_t maxlength = 1024;

   reply ()
   {
      type = error;
      datasize = 0;
   };

   srfs_error_t setData (char* d, uint32_t s)
   {
      if (s > maxlength)
      {
         return toobig;
      }

      std::memcpy (this->data, d, s);

      return no_error; 
   }

   srfs_error_t serialize (char* c, uint32_t& s)
   {
      std::memcpy (c, "hello\n", 6);
      s = 6;
      return no_error;
   }

private:
   reply_type_t type;
   char data[maxlength];
   uint32_t datasize;
};

#endif

