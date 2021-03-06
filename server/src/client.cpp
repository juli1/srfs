#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>

#include "debug.hpp"
#include "request.hpp"
#include "reply.hpp"
#include "client.hpp"
#include "server.hpp"

#define MAX_LENGTH 1024

srfs_error_t client::close_handle (int handle)
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


srfs_error_t client::get_unused_handle (int& handle)
{
   for (size_t i = 0 ; i < maxhandles ; i++)
   {
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


client::client (tcp::socket s) : socket(std::move(s)), handles(), thread (nullptr)
{
}

void client::setThread (std::thread* t)
{
   this->thread = t;
}

tcp::socket& client::get_socket ()
{
   return socket;
}


std::array<filehandle*,100> client::getHandles()
{
   return this->handles;
}

filehandle* client::get_handle(size_t n)
{
   return handles[n];
}



void client::shutdown ()
{
   /*
   if (this->thread != nullptr)
   {
      delete (this->thread);
   }
   */
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
      debug ("cannot set path", SEVERITY_DEBUG);
      delete (fh);
      handles[handle] = nullptr;
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
      filehandle* handle = c->get_handle (req.get_handle());

      // make sure we have a valid handle, will segfault otherwise
      if (handle == nullptr)
      {
         return invalid_request;
      }

      int final_size = handle->read_data (rep.get_buffer(), req.get_size());
      rep.set_type (read_ok);
      rep.set_buffer_size (final_size);
      return no_error;
   }

   if (req.getType() == closefile)
   {
      debug ("close file for handle ", SEVERITY_DEBUG);
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

srfs_error_t read_request (std::string str, request& request)
{
   debug ("reading the request, got: " + str , SEVERITY_DEBUG);
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

      request.setType (openfile);
      std::string filename = str.substr (5, str.size() - 5);

	   debug ("opening file " + filename, SEVERITY_INFO);
      /*
       * Here, we need to protect the filename. it can be ../../../
       */
      request.setPath (filename);
      return no_error;
   }

   if (str.substr (0, 4) == "read")
   {
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

   while (1)
   {
      boost::system::error_code error;
      request req;
      reply rep;
      srfs_error_t err;

      while (1)
      {
         c->get_socket().read_some (boost::asio::buffer (data_, MAX_LENGTH), error);

         if (error)
         {
            continue;
         }

         err = read_request (data_, req);

         if (err != no_error)
         {
            continue;
         }

         if (req.getType() == quit)
         {
            server* s = server::getInstance();
            s->removeClient (c);
            return; 
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

