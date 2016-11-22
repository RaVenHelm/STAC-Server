// Copyright 2016 T.C. Enders

#include <iostream>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include "TcpServer.hpp"
#include "TcpConnection.hpp"
#include "DBConfig.hpp"

using stac::tcpip::TcpServer;
using stac::tcpip::TcpConnection;

namespace options = boost::program_options;
int main(int argc, char *argv[]) {
  options::options_description desc{"STAC command line configuration options"};

  try {
    unsigned int thread_count{1};
    unsigned short port{1025};
    std::string conf_name{"stac.conf"};

    desc.add_options()
      ("help,h", "Get help")
      ("thread-count", options::value<unsigned int>(&thread_count)->default_value(1))
      ("conf-name,c", options::value<std::string>(&conf_name)->default_value(std::string{"stac.conf"}))
      ("port,p", options::value<unsigned short>(&port)->default_value(1025))
    ;

    options::variables_map vm{};
    options::store(options::parse_command_line(argc, argv, desc), vm);
    options::notify(vm);

    if(vm.count("help")) {
      std::cout << "Program Options:\n";
      std::cout << desc << '\n';
      return 0;
    }

    boost::filesystem::path path{ conf_name.c_str() };
    auto abs_path = boost::filesystem::absolute(path);
    auto conf = stac::config::load_db_config_from_file(abs_path.generic_string());

    // listens on localhost
    TcpServer<TcpConnection> server{ conf, thread_count };
    server.run(port);
  }
  catch (options::error& opt_err)
  {
    std::cerr << opt_err.what() << '\n';
    std::cerr << desc << '\n';
    return 2;
  }
  catch (std::exception& ex)
  {
    std::cerr << ex.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Uncaught error!\n";
  }

  return 0;
}
