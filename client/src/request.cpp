#include <iostream>

#include "debug.hpp"
#include "error.hpp"
#include "request.hpp"

Request::Request ()
{
}

srfs_error_t Request::perform ()
{
	debug ("perform a generic request", SEVERITY_INFO);
	return no_error;
}

ReadRequest::ReadRequest ()
{
}

srfs_error_t ReadRequest::perform ()
{
	debug ("perform a read request", SEVERITY_INFO);
	return no_error;
}



