#include <iostream>

#include "server.hpp"
#include "client.hpp"
#include "console.hpp"

static void console_command (const std::string& command)
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
void console_loop ()
{
   while (1)
   {
      cout << "[srfs] ";
      std::string incoming;
      cin >> incoming;

      if (cin.eof())
      {
         server* s = server::getInstance ();
         s->shutdown ();
         exit (EXIT_SUCCESS);
      }

      cout << "command " << incoming << endl;
      console_command (incoming);
   }
}

