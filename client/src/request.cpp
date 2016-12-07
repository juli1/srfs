#include <iostream>

#include "debug.hpp"
#include "request.hpp"

Request::Request (std::string server, int port, std::string file) : m_server(server), m_port(port), m_file(file)
{
}

srfs_error_t Request::perform ()
{
	debug ("perform a generic request", SEVERITY_INFO);
	return no_error;
}




ReadRequest::ReadRequest (std::string server, int port, std::string file, int size) : Request (server,port,file), m_size(size)
{
}

srfs_error_t ReadRequest::perform ()
{
	debug ("perform a read request", SEVERITY_INFO);
	return no_error;
}



