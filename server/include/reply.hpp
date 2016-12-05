#ifndef __REPLY_H__
#define __REPLY_H__

#include <cstring>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"

using std::endl;
using std::cout;

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

   srfs_error_t serialize (char* c, uint32_t& s)
   {
      memset (c, '\0', 1024);

      switch (this->type)
      {
         case open_ok:
         {
            std::string intstr = std::to_string (this->handle);
            const char* cstr = intstr.c_str();
            int intstrlen = std::strlen (cstr);
            std::memset (c, '\0', 1024);
            std::strcpy (c + 3, cstr);
            std::memcpy (c, "OK ", 3);
            c[3+intstrlen] = '\n';
            c[3+intstrlen + 1] = '\0';
            s = 4 + intstrlen;
            return no_error;
            break;
         }

         case close_ok:
         {
            std::memcpy (c, "OK\n", 3);
            s = 3;
            return no_error;
            break;
         }

         case open_ko:
         case close_ko:
         {
            std::memcpy (c, "KO\n", 3);
            s = 3;
            return no_error;
            break;
         }

         case read_ok:
         {
            cout << "read_ok datasize=" << this->datasize << "data=" << this->data << endl;
            std::string intstr = std::to_string (this->datasize);
            uint32_t slen = intstr.length();
            memcpy (c, intstr.c_str(), slen);
            memcpy (c + slen, this->data, this->datasize);
            s = slen + this->datasize;
            cout << "s="<< s;
            return no_error;

            break;
         }


         default:
         {
            std::memcpy (c, "ERROR\n", 6);
            s = 6;
            return no_error;
         }
      }
      return no_error;
   }

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

