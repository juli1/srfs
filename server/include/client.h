#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <ctime>
#include <iostream>
#include <string>
#include <array>
#include <thread>
#include <cstdint>
#include <cstring>
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

      client (tcp::socket s) : socket(std::move(s)), handles()
      {
         
      }

      tcp::socket& get_socket () {return socket;}

      filehandle& getHandle(size_t n)
      {
         return handles[n];
      }

      size_t getUnusedHandle ()
      {
         for (size_t i = 0 ; i < maxhandles ; i++)
         {
            cout << "handle at " << std::to_string(i) << "->" << handles[i] << endl;
         }
         return 0;
      }


   private:
      tcp::socket socket;
      std::array<filehandle,100> handles;
};

void handle_client (client* c);

srfs_error_t read_request (std::string str, client* c, request& request);


srfs_error_t process_request (client* c, request& req, reply& rep);

#endif

