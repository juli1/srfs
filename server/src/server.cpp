
#include <server.h>
#include <client.h>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// Need to initialize the static member
server *server::m_instance = 0;

void management_command (std::string& command)
{
   if (command == "quit")
   {
      server* s = server::getInstance();
      s->shutdown();

      exit (EXIT_SUCCESS);
   }
}

// This is the entry point for the thread that reads
// the standard input and manage the server
void server_management ()
{
   while (1)
   {
      cout << "[srfs] $";
      std::string incoming;
      cin >> incoming;
      cout << "received " << incoming << endl;
      management_command (incoming);
   }
}

void server::shutdown ()
{
   cout << "Shutdown server" << endl;
}

void server::start()
{

   std::thread thr_mgmt(server_management);
   thr_mgmt.detach();

   while (1)
   {
      cout << "new client" << endl;
      acceptor_.accept(socket_);
      client* newclient = new client(std::move(socket_));
      std::thread t(handle_client, newclient);
      t.detach();
   }
}



