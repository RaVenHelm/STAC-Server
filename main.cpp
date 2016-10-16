// Copyright 2016 T.C. Enders

#include <iostream>

#include <boost/filesystem.hpp>

#include "TcpServer.hpp"
#include "TcpConnection.hpp"
#include "DBConfig.hpp"

using stac::tcpip::TcpServer;
using stac::tcpip::TcpConnection;

int main() {
  try {
    boost::filesystem::path path{ "stac.conf" };
    auto abs_path = boost::filesystem::absolute(path);
    auto conf = stac::config::load_db_config_from_file(abs_path.generic_string());
    
    // listens on localhost
    TcpServer<TcpConnection> server{ conf };
    server.run(1025);
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
