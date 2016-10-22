#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <array>
#include <vector>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "DBI.hpp"

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
  std::shared_ptr<stac::db::DBI> m_dbi;
  std::array<char, 4096> m_in_packet;
  std::vector<char> m_out_packet;
  bool m_is_primed_for_shutdown = false;
  bool m_is_admin_session = false;
  bool m_is_logged_in = false;
public:
  TcpConnection(boost::asio::io_service& service, std::shared_ptr<stac::db::DBI> dbi)
    : m_service(service),
      m_socket(service),
      m_write_strand(service),
      m_dbi(dbi),
      m_in_packet(),
      m_out_packet(),
      m_is_primed_for_shutdown(false)
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

  void read_complete(boost::system::error_code& error, size_t bytes_transferred);
  void write_complete(boost::system::error_code& error, size_t bytes_transferred);
}; // TcpConnection
} // tcpip
} // stac
