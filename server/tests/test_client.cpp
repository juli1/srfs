#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE client
#include <boost/test/unit_test.hpp>

#include "client.hpp"
 
 
BOOST_AUTO_TEST_CASE(checkclient)
{
	BOOST_CHECK (1 == 1);
}
