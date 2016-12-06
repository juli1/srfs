#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE client
#include <boost/test/unit_test.hpp>

#include "client.hpp"
#include "request.hpp"
#include "reply.hpp"
 
 
BOOST_AUTO_TEST_CASE(check_readrequest)
{
	request r;

	BOOST_CHECK (read_request ("aaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbb", r) == invalid_request);

	BOOST_CHECK (read_request ("b", r) == invalid_request);

	BOOST_CHECK (read_request ("open bla", r) == no_error);
	BOOST_CHECK (r.getType() == openfile);

	BOOST_CHECK (read_request ("close 0", r) == no_error);
	BOOST_CHECK (r.getType() == closefile);

	BOOST_CHECK (read_request ("read 0 100", r) == no_error);
	BOOST_CHECK (r.getType() == readfile);
}
