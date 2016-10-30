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
  boost::asio::io_service& m_service; // master service that ultimately deals with IO
  tcp::socket m_socket; // TCP/IP Socket abstraction
  boost::asio::strand m_write_strand; // used for protecting two threads writing to the socket at the same time
  std::shared_ptr<stac::db::DBI> m_dbi; // essentially a handle to the DB interface
                                        // doubt we'll need syncronization, but here is where that'd go
  std::array<char, 4096> m_in_packet; // input character buffer, could maybe change the size later
  std::vector<char> m_out_packet; // output character buffer
  
  // Flags for state of the connection
  // If we get too many, we'd need to use a bitset
  // but that will be a lot of extra work
  bool m_is_primed_for_shutdown = false;
  bool m_is_admin_session = false;
  bool m_is_logged_in = false;

  std::string m_remote_ip{};

  // Username and id for the session
  std::string m_username{};
  int m_id = -1;

public:
  // Each connection will need a IO service and DB handle in order to function correctly
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

  // Startup and shutdown methods
  void start();
  void stop();
  void stop(boost::system::error_code& errorCode);

  // Needed for async_accept
  boost::asio::ip::tcp::socket& socket()
  {
    return m_socket;
  }

  
private:
  // Prepares the message to be written to the socket
  void send(std::string msg);

  // Register the callback to the boost::asio service for reading
  void read_from_socket();

  // Register the callback to the boost::asio service for reading
  void write_to_socket();

  // Essentially, these get called by the lambda expression
  // makes it a bit cleaner than having huge lambdas
  // Also silences some compiler warnings about recursion
  void read_complete(boost::system::error_code& error, size_t bytes_transferred);
  void write_complete(boost::system::error_code& error, size_t bytes_transferred);
}; // TcpConnection
} // tcpip
} // stac
