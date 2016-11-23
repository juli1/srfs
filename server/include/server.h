#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include <chrono>
#include <thread>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class server
{
   public:
      server(boost::asio::io_service& io_service, short port)
         : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
         socket_(io_service)
   {
   }

   void start();

   private:
      tcp::acceptor acceptor_;
      tcp::socket socket_;
};

#endif

