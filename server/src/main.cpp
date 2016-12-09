#include <ctime>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <debug.hpp>
#include <boost/program_options.hpp>
#include <boost/asio.hpp>

#include "client.hpp"
#include "server.hpp"

namespace po = boost::program_options;

using std::thread;
using boost::asio::ip::tcp;

std::string basedir;

void print_help (std::string& binary, po::options_description& desc)
{
	cout << desc << endl;
	cout << "read a file: " << binary << " --operation read --file myfile --server localhost --port 4444" << " - read 1024 bytes from the remote file myfile" << endl;
	cout << "write a file: " << binary << " --operation write --file myfile --server localhost --port 4444" << " - write 2 bytes to the remote file myfile from the standard input" << endl;
}


int main(int ac, char* av[])
{
   debug ("starting server", SEVERITY_INFO);

   po::options_description desc("Available options");

   desc.add_options()
      ("help", "print help message")
      ("basedir", po::value<std::string>(), "directory to serve")
      ("port", po::value<int>(), "port to listen to")
      ;

	std::string binary = av[0];
   po::variables_map vm;
   po::store(po::parse_command_line(ac, av, desc), vm);
   po::notify(vm);

   if (vm.count("port") == 0)
   {
      print_help (binary, desc);
      exit (EXIT_FAILURE);
   }

   if (vm.count("basedir") == 0)
   {
      print_help (binary, desc);
      exit (EXIT_FAILURE);
   }

	basedir = vm["basedir"].as<std::string>();
	int port = vm["port"].as<int>();


   try
   {
      boost::asio::io_service io_service;

      server s(io_service, port);
      s.start();

      io_service.run();
   }
   catch (std::exception& e)
   {
      std::cerr << e.what() << std::endl;
   }

   exit (EXIT_SUCCESS);
}
