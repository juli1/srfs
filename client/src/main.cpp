#include <iostream>
#include <boost/program_options.hpp>

#include "request.hpp"

namespace po = boost::program_options;

using std::cout;
using std::endl;

void print_help (std::string& binary, po::options_description& desc)
{
	cout << desc << endl;
	cout << "read a file: " << binary << " --operation read --file myfile --size 1024 --server localhost --port 4444" << " - read 1024 bytes from the remote file myfile" << endl;
	cout << "write a file: " << binary << " --operation write --file myfile --size 2 --server localhost --port 4444" << " - write 2 bytes to the remote file myfile from the standard input" << endl;
}

void check_arguments (std::string& binary, po::variables_map& vm, po::options_description& desc)
{

   if (vm.count("help"))
	{
		print_help (binary, desc);
		exit (EXIT_SUCCESS);
	}

   if (
			vm.count("server") == 0 ||
			vm.count("operation") == 0 ||
			vm.count("port") == 0
		)
	{
		print_help (binary, desc);
		exit (EXIT_FAILURE);
	}

	std::string operation = vm["operation"].as<std::string>();
	
	if (operation == "read")
	{
		if (
			vm.count("file") == 0 ||
			vm.count("size") == 0
			)
		{
			print_help (binary, desc);
			exit (EXIT_FAILURE);
		}
	}

}


int main (int ac, char* av[])
{
   po::options_description desc("Available options");

   desc.add_options()
      ("help", "print help message")
      ("operation", po::value<std::string>(), "requested operation: read/write/list")
      ("size", po::value<int>(), "size to read/write")
      ("server", po::value<std::string>(), "server to connect to")
      ("port", po::value<int>(), "remote port")
      ("file", po::value<std::string>(), "file to read/write from/to")
      ;

	std::string binary = av[0];
   po::variables_map vm;
   po::store(po::parse_command_line(ac, av, desc), vm);
   po::notify(vm);

	check_arguments (binary, vm, desc);


	std::string operation = vm["operation"].as<std::string>();
	std::string server = vm["server"].as<std::string>();
	int port = vm["port"].as<int>();


	if (operation == "read")
	{
		std::string file = vm["file"].as<std::string>();
		int size = vm["size"].as<int>();
		ReadRequest request(server, port, file, size);
	}

}
