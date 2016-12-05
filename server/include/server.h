#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include <chrono>
#include <list>
#include <thread>
#include <boost/asio.hpp>

#include "client.h"

using boost::asio::ip::tcp;

class server;

class server
{

   static server* m_instance;

   public:
      server(boost::asio::io_service& io_service, short port)
         : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
         socket_(io_service)
      {
         server::m_instance = this;
      }
   
      
   static server* getInstance ()
   {
      return static_cast<server*>(server::m_instance);
   }

   void removeClient (client* c);

   void shutdown ();

   list<client*>& getClients() { return this->clients;}


   void start();

   private:
      tcp::acceptor acceptor_;
      tcp::socket socket_;
      list<client*> clients;
};


#endif

