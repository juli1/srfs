#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>


#include "debug.hpp"
#include "request.hpp"

using boost::asio::ip::tcp;


Request::Request (std::string server, int port, std::string file) : m_server(server), m_port(port), m_file(file)
{
}

srfs_error_t Request::perform ()
{
	debug ("perform a generic request", SEVERITY_INFO);
	return no_error;
}

Request::~Request ()
{
}




ReadRequest::ReadRequest (std::string server, int port, std::string file, int size) : Request (server,port,file), m_size(size)
{
}

srfs_error_t ReadRequest::perform ()
{
	debug ("perform a read request", SEVERITY_INFO);

	std::string msg;
   boost::system::error_code error;
	size_t len; 

   boost::asio::io_service io_svc;
   tcp::resolver resolver (io_svc);
   tcp::resolver::query query( tcp::v4(), this->m_server, "4444");
   tcp::resolver::iterator iterator = resolver.resolve (query);
   tcp::socket s (io_svc);
   boost::asio::connect (s, iterator);

	msg = "open " + this->m_file ;

	debug ("sending" + msg, SEVERITY_INFO);

   s.write_some (boost::asio::buffer (msg, msg.length()), error);
	char buf[1025];

   len = s.read_some (boost::asio::buffer (buf, 1024), error);
	buf[len] = '\0';
	std::string reply(buf);

	debug ("reply is " + reply, SEVERITY_INFO);
	reply.erase (0, 3);

	debug ("handle" + reply, SEVERITY_INFO);

   do
	{
		msg = "read " + reply + " 1024\n";
   	s.write_some (boost::asio::buffer (msg, msg.length()), error);

		len = s.read_some (boost::asio::buffer (buf, 1024), error);
		buf[len] = '\0';
		std::string content(buf);
		std::cout << content;

	}
	while (len == 1024);

	return no_error;
}

ReadRequest::~ReadRequest ()
{
}




