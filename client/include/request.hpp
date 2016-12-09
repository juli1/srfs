#ifndef __REQUEST_HPP__
#define __REQUEST_HPP__

#include "error.hpp"

class Request
{
public:
	Request(std::string server, int port, std::string file);
	virtual srfs_error_t perform();
	virtual ~Request();

protected:
	std::string m_server;
	int m_port;
	std::string m_file;
};

class ReadRequest : public Request
{
public:
	ReadRequest (std::string server, int port, std::string file, int size);
	virtual srfs_error_t perform();
	virtual ~ReadRequest();
private:
	int m_size;
};


#endif

