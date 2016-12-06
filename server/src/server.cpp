#include <iostream>

#include "debug.hpp"
#include "server.hpp"
#include "client.hpp"
#include "console.hpp"

using std::cin;
using std::cout;
using std::endl;

// Need to initialize the static member
server *server::m_instance = nullptr;

// shut down the server
// close all connections and free allocated
// resources
void server::shutdown ()
{
   debug ("Shutdown server", SEVERITY_LOGGING);

   for (client* c : clients)
   {
      this->removeClient (c);
   }
}

void server::removeClient (client* c)
{
   if (c == nullptr)
   {
      return;
   }

   clients.remove (c);
   c->shutdown(); // close sockets and free client resource
}

void server::start()
{

   std::thread thr_mgmt(console_loop);
   thr_mgmt.detach();

   while (1)
   {
      debug ("new client", SEVERITY_LOGGING);
      acceptor_.accept(socket_);

      client* newclient = new client(std::move(socket_));
      clients.push_back (newclient);

      std::thread t(handle_client, newclient);
      t.detach();
   }
}

server::server(boost::asio::io_service& io_service, short port)
   : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
   socket_(io_service)
{
   server::m_instance = this;
}



list<client*>& server::getClients()
{
   return this->clients;
}




