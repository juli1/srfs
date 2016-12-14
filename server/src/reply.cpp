#include "reply.hpp"
#include "debug.hpp"

#include <iostream>

srfs_error_t reply::serialize (char* c, uint32_t& s)
{
	memset (c, '\0', 1024);

	switch (this->type)
	{
		case open_ok:
			{
				std::string intstr = std::to_string (this->handle);
				const char* cstr = intstr.c_str();
				int intstrlen = std::strlen (cstr);
				std::memset (c, '\0', 1024);
				std::strcpy (c + 3, cstr);
				std::memcpy (c, "OK ", 3);
				c[3+intstrlen] = '\n';
				c[3+intstrlen + 1] = '\0';
				s = 4 + intstrlen;
				return no_error;
				break;
			}

		case close_ok:
			{
				std::memcpy (c, "OK\n", 3);
				s = 3;
				return no_error;
				break;
			}

		case open_ko:
		case close_ko:
			{
				std::memcpy (c, "KO\n", 3);
				s = 3;
				return no_error;
				break;
			}

		case read_ok:
			{
				//debug (std::string(this->datasize), SEVERITY_DEBUG);
				memcpy (c, this->data, this->datasize);
				s = this->datasize;
				return no_error;

				break;
			}


		default:
			{
				std::memcpy (c, "ERROR\n", 6);
				s = 6;
				return no_error;
			}
	}
	return no_error;
}


