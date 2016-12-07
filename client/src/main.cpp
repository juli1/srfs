#include <iostream>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

using std::cout;
using std::endl;

int main (int ac, char* av[])
{
   po::options_description desc("Available options");
   desc.add_options()
      ("help", "print help message")
      ("operation", po::value<std::string>(), "requested operation: read/write/list")
      ("size", po::value<int>(), "size to read/write")
      ("file", po::value<std::string>(), "file to read/write from/to")
      ;

   po::variables_map vm;
   po::store(po::parse_command_line(ac, av, desc), vm);
   po::notify(vm);    

   if (vm.count("help")) {
      cout << desc << endl;
		cout << "read a file: " << av[0] << " --operation read --file myfile --size 1024" << " - read 1024 bytes from the remote file myfile" << endl;
		cout << "write a file: " << av[0] << " --operation write --file myfile --size 2" << " - write 2 bytes to the remote file myfile from the standard input" << endl;
      return 1;
   }

}
