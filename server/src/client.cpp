#include <thread>
#include <chrono>
#include <iostream>

#include "request.h"
#include "reply.h"
#include "client.h"

using std::endl;
using std::cout;

#define MAX_LENGTH 1024

srfs_error_t process_request (client* c, request& req, reply& rep)
{
   return no_error;
}

srfs_error_t read_request (std::string str, client* c, request& request)
{
   cout << "reading the request" << endl;
   /*
    * We assume that is the request is less than 10
    * chars, this is not valid.
    */
   if (str.size () < 10)
   {
      return invalid_request;
   }

   if (str.substr (0, 4) == "open")
   {
      cout << "opening a file" << endl;

      request.setType (openfile);
      std::string filename = str.substr (5, str.size() - 5);
      /*
       * Here, we need to protect the filename. it can be ../../../
       */

      cout << "filename" << filename << endl;
   }
   return no_error;
}

void handle_client (client* c)
{
   char data_[MAX_LENGTH];
   char serialized[MAX_LENGTH];
   uint32_t serialized_size;

   cout << "starting client" << endl;
   while (1)
   {
      boost::system::error_code error;
      request req;
      reply rep;
      srfs_error_t err;

      while (1)
      {
         size_t len = c->get_socket().read_some (boost::asio::buffer (data_, MAX_LENGTH), error);

         if (error)
         {
            continue;
         }

         err = read_request (data_, c, req);

         if (err != no_error)
         {
            continue;
         }

         process_request (c, req, rep);

         if (err != no_error)
         {
            continue;
         }

         rep.serialize (serialized, serialized_size);

         c->get_socket().write_some (boost::asio::buffer (serialized, serialized_size), error);

      }

   }
}

