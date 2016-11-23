#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <boost/asio.hpp>

#include "reply.h"
#include "request.h"
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

srfs_error_t read_request (std::string str, client* c, request& request);


srfs_error_t process_request (client* c, request& req, reply& rep);

#endif

