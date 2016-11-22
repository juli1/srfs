#include <thread>
#include <chrono>

#include "client.h"

void handle_client (client* client)
{
   while (1)
   {
      boost::system::error_code ignored_error;
      std::string message = "hello\n";
      boost::asio::write(client->get_socket(), boost::asio::buffer(message), ignored_error);
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   }
}

client::client (tcp::socket& s)
{
   this->socket = &s; 
   this->thread = new std::thread(handle_client, this);
}
