#ifndef __REPLY_H__
#define __REPLY_H__

#include <cstring>
#include "error.h"

typedef enum replytypet
{
   ok,
   open_ok,
   open_ko,
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

   void set_type (reply_type_t t)
   {
      this->type = t;
   }

   srfs_error_t set_data (char* d, uint32_t s)
   {
      if (s > maxlength)
      {
         return toobig;
      }

      std::memcpy (this->data, d, s);

      return no_error; 
   }

   void set_handle (int h)
   {
      this->handle = h;
   }

   srfs_error_t serialize (char* c, uint32_t& s)
   {
      switch (this->type)
      {
         case open_ok:
         {
            std::memcpy (c, "open ok\n", 6);
            s = 6;
            break;
         }

         case open_ko:
         {
            std::memcpy (c, "open ko\n", 6);
            s = 6;

            break;
         }
         default:
         {
            return no_error;
         }
      }
      return no_error;
   }

private:
   reply_type_t type;
   char data[maxlength];
   uint32_t datasize;
   int handle;
};

#endif

