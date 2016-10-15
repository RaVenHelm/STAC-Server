// Copyright 2016 T.C. Enders

#include <iostream>

#include "TcpServer.hpp"
#include "TcpConnection.hpp"

using stac::tcpip::TcpServer;
using stac::tcpip::TcpConnection;

int main() {
  try {
    // listens on localhost
    TcpServer<TcpConnection> server{ 1 };
    server.run(1025);
  } catch (std::exception& ex) {
    std::cerr << ex.what() << '\n';
    return 1;
  } catch (...) {
		std::cerr << "Uncaught error!\n";
	}
  return 0;
}
