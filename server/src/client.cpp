#include <thread>
#include <chrono>
#include <iostream>

#include "request.h"
#include "client.h"

using std::endl;
using std::cout;

#define MAX_LENGTH 1024

error_t read_request (std::string str, client* c, request_t& request)
{
   /*
    * We assume that is the request is less than 10
    * chars, this is not valid.
    */
   if (str.size () < 10)
   {
      return invalid_request;
   }
   return 0;
}

void handle_client (client* c)
{
   char data_[MAX_LENGTH];

   cout << "starting client" << endl;
   while (1)
   {
      boost::system::error_code error;

      while (1)
      {
         size_t len = c->get_socket().read_some (boost::asio::buffer (data_, MAX_LENGTH), error);

         if (! error)
         {
            c->get_socket().write_some (boost::asio::buffer (data_, len), error);
         }
      }

   }
}

