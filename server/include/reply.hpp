#ifndef __REPLY_H__
#define __REPLY_H__

#include <cstdint>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"


typedef enum replytypet
{
   ok,
   open_ok,
   open_ko,
   read_ok,
   read_ko,
   close_ok,
   close_ko,
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

   srfs_error_t serialize (char* c, uint32_t& s);

   char* get_buffer ()
   {
      return this->data;
   }

   int get_buffer_size ()
   {
      return this->datasize;
   }

   void set_buffer_size (const int s)
   {
      this->datasize = s;
   }


private:
   reply_type_t type;
   char data[maxlength];
   uint32_t datasize;
   int handle;
};

#endif

