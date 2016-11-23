#include <thread>
#include <chrono>
#include <iostream>
#include "client.h"

using std::endl;
using std::cout;

#define MAX_LENGTH 1024

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

