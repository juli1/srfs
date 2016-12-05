#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE client
#include <boost/test/unit_test.hpp>

#include "client.hpp"
#include "request.hpp"
#include "reply.hpp"
 
 
BOOST_AUTO_TEST_CASE(check_readrequest)
{
	request r;

	BOOST_CHECK (read_request ("b", r) == invalid_request);
	BOOST_CHECK (read_request ("open bla", r) == no_error);
}
