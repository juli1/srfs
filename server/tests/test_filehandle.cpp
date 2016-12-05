#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE filehandle
#include <boost/test/unit_test.hpp>

#include "client.hpp"
#include "filehandle.hpp"
 
 
BOOST_AUTO_TEST_CASE(checkfilehandle)
{
	BOOST_CHECK (1 == 1);
}
