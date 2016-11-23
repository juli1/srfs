
#include <server.h>
#include <client.h>
#include <iostream>

using std::cout;
using std::endl;

void server::start()
{
   while (1)
   {
      cout << "new client" << endl;
      acceptor_.accept(socket_);
      client* newclient = new client(std::move(socket_));
      std::thread t(handle_client, newclient);
      t.detach();
   }
}



