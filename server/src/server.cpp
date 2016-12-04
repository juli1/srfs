
#include <server.h>
#include <client.h>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// Need to initialize the static member
server *server::m_instance = nullptr;

void management_command (std::string& command)
{
   if (command == "quit")
   {
      server* s = server::getInstance();
      s->shutdown();

      exit (EXIT_SUCCESS);
   }

   if (command == "ls")
   {
      server* s = server::getInstance();
      list<client*>& clients = s->getClients();
      int i = 0;
      for (client* c : clients)
      {
         cout << "client" << i << " active" << endl;

         int fileno = 0;

         for (filehandle* fh : c->getHandles())
         {
            if (fh != nullptr)
            {
               cout << "  -> filehandle" << fileno << " open ; path=" << fh->getPath() << endl;
            }
            fileno++;
         }
         i++;
      }
      return;
   }

   if (command.substr(0,4) == "kill")
   {
      std::string clientIdString;
      cin >> clientIdString;
      int clientId = atoi (clientIdString.c_str());

      cout << "killing client" << clientId << endl;

      server* s = server::getInstance();
      list<client*>& clients = s->getClients();

      // this is bad code, should use random access such as []
      int i = 0;

      client* toremove;

      toremove = NULL;
      
      for (client* c : clients)
      {
         if (i == clientId)
         {
            cout << "Killing client" << i  << endl;
            toremove = c;
         }
         i++;
      }

      if (toremove != NULL)
      {
         s->removeClient (toremove);
      }

      return;
   }


}

// This is the entry point for the thread that reads
// the standard input and manage the server
void server_management ()
{
   while (1)
   {
      cout << "[srfs] ";
      std::string incoming;
      cin >> incoming;
      cout << "command " << incoming << endl;
      management_command (incoming);
   }
}


void server::shutdown ()
{
   cout << "Shutdown server" << endl;
}

void server::removeClient (client* c)
{
   clients.remove (c);
   c->shutdown();
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
      clients.push_back (newclient);

      std::thread t(handle_client, newclient);
      t.detach();
   }
}



