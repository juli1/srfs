#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <ctime>
#include <iostream>
#include <string>
#include <array>
#include <thread>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <boost/asio.hpp>

#include "reply.h"
#include "request.h"
#include "error.h"
#include "filehandle.h"


using std::move;
using std::cout;
using std::endl;
using boost::asio::ip::tcp;

class client
{
   public:
      static const size_t maxhandles = 100;

      void shutdown ();

      client (tcp::socket s) : socket(std::move(s)), handles()
      {
         
      }

      tcp::socket& get_socket () {return socket;}

      filehandle* get_handle(size_t n)
      {
         return handles[n];
      }

      std::array<filehandle*,100> getHandles() {return this->handles;}

      srfs_error_t openfile (std::string filename, int& handle);

      srfs_error_t close_handle (int handle)
      {
         filehandle* h = this->handles[handle];

         if (h == nullptr)
         {
            return invalid_request;
         }

         delete (h);

         this->handles[handle] = NULL;
         return no_error;
      }


      srfs_error_t get_unused_handle (int& handle)
      {
         for (size_t i = 0 ; i < maxhandles ; i++)
         {
//            cout << "handle at " << std::to_string(i) << "->" << handles[i] << endl;

            if (handles[i] == NULL)
            {
               filehandle* new_handle = new filehandle();
               handles[i] = new_handle;
               handle = i;
               return no_error;
            }
         }
         return not_found;
      }


   private:
      tcp::socket socket;
      std::array<filehandle*,100> handles;
};

void handle_client (client* c);

srfs_error_t read_request (std::string str, client* c, request& request);


srfs_error_t process_request (client* c, request& req, reply& rep);

#endif

