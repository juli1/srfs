#ifndef __REQUEST_HPP__
#define __REQUEST_HPP__

class Request
{
public:
	Request();
	virtual srfs_error_t perform();
};

class ReadRequest : public Request
{
public:
	ReadRequest();
	virtual srfs_error_t perform();
};


#endif

