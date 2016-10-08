#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <future>
#include <array>
#include <vector>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "Worker.hpp"

using boost::asio::ip::tcp;

namespace stac {
namespace tcpip {

class TcpConnection;

class TcpConnection
    : public boost::enable_shared_from_this<TcpConnection>
{

  boost::asio::io_service& m_service;
  tcp::socket m_socket;
  boost::asio::strand m_write_strand;
  std::array<char, 4096> m_in_packet;
  std::vector<char> m_out_packet;
public:
  TcpConnection(boost::asio::io_service& service)
    : m_service(service),
      m_socket(service),
      m_write_strand(service)
  {

  }
  void start();
  void stop();
  void stop(boost::system::error_code& errorCode);

  boost::asio::ip::tcp::socket& socket()
  {
    return m_socket;
  }

  void send(std::string msg);
private:
  void read_from_socket();
  void write_to_socket();

  void read_complete(boost::system::error_code const& error, size_t bytes_transferred);
  void write_complete(boost::system::error_code const& error, size_t bytes_transferred);
}; // TcpConnection
} // tcpip
} // stac
