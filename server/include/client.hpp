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

#include "error.h"
#include "reply.hpp"
#include "request.hpp"
#include "filehandle.hpp"


using std::move;
using std::cout;
using std::endl;
using boost::asio::ip::tcp;

class client
{
   public:
      static const size_t maxhandles = 100;

      void shutdown ();

      client (tcp::socket s);

      tcp::socket& get_socket ();

      filehandle* get_handle(size_t n);

      std::array<filehandle*,100> getHandles();

      srfs_error_t openfile (std::string filename, int& handle);

      srfs_error_t close_handle (int handle);

      srfs_error_t get_unused_handle (int& handle);

      void setThread (std::thread* t);

   private:
      tcp::socket socket;
      std::array<filehandle*,100> handles;
      std::thread* thread;
};


void handle_client (client* c);

srfs_error_t read_request (std::string str, request& request);


srfs_error_t process_request (client* c, request& req, reply& rep);

#endif

