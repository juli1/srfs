#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include <chrono>
#include <list>
#include <thread>
#include <boost/asio.hpp>

#include "client.hpp"

using boost::asio::ip::tcp;

class server;

class server
{

	static server* m_instance;

	public:
	server(boost::asio::io_service& io_service, short port);


	static server* getInstance ()
	{
   	return static_cast<server*>(server::m_instance);
	}

	void removeClient (client* c);

	void shutdown ();

	std::list<client*>& getClients();

	void start();

	private:
	tcp::acceptor acceptor_;
	tcp::socket socket_;
	std::list<client*> clients;
};


#endif

