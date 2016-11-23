#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <chrono>
#include <thread>

#include <client.h>
#include <server.h>


using std::cout;
using std::endl;
using std::thread;
using boost::asio::ip::tcp;

int main()
{
   cout << "starting" << endl;
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
