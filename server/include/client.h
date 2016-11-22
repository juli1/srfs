#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class client
{
public:
   client (tcp::socket& s);
   tcp::socket& get_socket () {return *(this->socket);}

private:
   tcp::socket* socket;
   std::thread* thread;

};

#endif

