#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <chrono>
#include <thread>
#include <debug.hpp>

#include "client.hpp"
#include "server.hpp"


using std::thread;
using boost::asio::ip::tcp;


int main()
{
   debug ("starting", SEVERITY_INFO);
   try
   {
      boost::asio::io_service io_service;

      server s(io_service, 4444);
      s.start();

      io_service.run();
   }
   catch (std::exception& e)
   {
      std::cerr << e.what() << std::endl;
   }

   return 0;
}
