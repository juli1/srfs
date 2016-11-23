#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <boost/asio.hpp>

#include "error.h"


using std::move;
using boost::asio::ip::tcp;

class client
{
   public:
      client (tcp::socket s) : socket(std::move(s)) {};
      tcp::socket& get_socket () {return socket;}

   private:
      tcp::socket socket;
};

void handle_client (client* c);

error_t read_request (std::string request, client* c);

#endif

