#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>

#include "request.h"
#include "reply.h"
#include "client.h"
#include "server.h"

using std::endl;
using std::cout;

#define MAX_LENGTH 1024

void client::shutdown ()
{
   if (this->get_socket().is_open())
   {
      this->get_socket().close();
   }
}

srfs_error_t client::openfile (std::string filename, int& handle)
{

   if (this->get_unused_handle (handle) != no_error)
   {
      return (not_available);
   }

   filehandle* fh = this->get_handle (handle);

   if (fh == NULL)
   {
      return (not_available);
   }

   /**
    * Cannot open the path, so, let's remove the filehandle
    */
   if (fh->set_path (filename) != no_error)
   {
      free (fh);
      return (not_available);
   }

   return no_error;
}

srfs_error_t process_request (client* c, request& req, reply& rep)
{
   if (req.getType() == openfile)
   {
      int handle;
      if (c->openfile (req.getPath(), handle) == no_error)
      {
         cout << "Handle=" << handle << endl;
         rep.set_type (open_ok);
         rep.set_handle (handle);
      }
      else
      {
         rep.set_type (open_ko);
      }
      return no_error;
   }

   if (req.getType() == readfile)
   {
      cout << "reading file for handle " << req.get_handle() << " and size " << req.get_size() << endl;
      filehandle* handle = c->get_handle (req.get_handle());

      // make sure we have a valid handle, will segfault otherwise
      if (handle == nullptr)
      {
         return invalid_request;
      }

      int final_size = handle->read_data (rep.get_buffer(), req.get_size());
      cout << "final size="<< final_size << endl;
      rep.set_type (read_ok);
      rep.set_buffer_size (final_size);
      return no_error;
   }

   if (req.getType() == closefile)
   {
      cout << "close file for handle " << req.get_handle() << endl;
      if (c->close_handle (req.get_handle()) == no_error)
      {
         rep.set_type (close_ok);
      }
      else
      {
         rep.set_type (close_ko);
      }

      return no_error;
   }

   return not_available;
}

srfs_error_t read_request (std::string str, client* c, request& request)
{
   cout << "reading the request, got: " << str << endl;
   /*
    * We assume that is the request is less than 4
    * chars, this is not valid. We need at least
    * 4 chars for the command request (open/close/read/write).
    */
   if (str.size () < 4)
   {
      return invalid_request;
   }

   if (str.substr (0, 4) == "open")
   {
      cout << "opening a file" << endl;

      request.setType (openfile);
      std::string filename = str.substr (5, str.size() - 7);
      /*
       * Here, we need to protect the filename. it can be ../../../
       */
      request.setPath (filename);
      return no_error;
   }

   if (str.substr (0, 4) == "read")
   {
      cout << "reading a file" << endl;

      request.setType (readfile);
      str.erase (0, 5);

      int pos = str.find (" ");
      std::string handle_str = str.substr(0, pos);
      int handle = atoi (handle_str.c_str());

      str.erase (0, pos + 1);
      int size = atoi (str.c_str());

      request.set_size (size);
      request.set_handle (handle);
      return no_error;
   }

   if (str.substr (0, 5) == "close")
   {
      cout << "closing a file" << endl;

      request.setType (closefile);
      str.erase (0, 6);

      int pos = str.find (" ");
      std::string handle_str = str.substr(0, pos);
      int handle = atoi (handle_str.c_str());

      request.set_handle (handle);
      return no_error;
   }

   if (str.substr (0, 4) == "quit")
   {
      cout << "quit" << endl;

      request.setType (quit);
      return no_error;
   }


   return invalid_request;
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

         if (req.getType() == quit)
         {
            cout << "Leaving client" << endl;

            server* s = server::getInstance();
            s->removeClient (c);
            cout << "Client closed" << endl;
            return; 
         }

         process_request (c, req, rep);

         if (err != no_error)
         {
            continue;
         }

         rep.serialize (serialized, serialized_size);

//         cout << "serialized size="<<serialized_size << endl;

         c->get_socket().write_some (boost::asio::buffer (serialized, serialized_size), error);

      }

   }
}

