#include <iterator>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string/trim_all.hpp>

#include "TcpConnection.hpp"
#include "RequestMessage.hpp"
#include "ResponseBuilder.hpp"

using stac::tcpip::TcpConnection;
using stac::core::ResponseBuilder;

void TcpConnection::start() {
  read_from_socket();
}

void TcpConnection::stop() {
  std::cout << "Clean shutting down of connection\n";
  auto ignored_code = boost::system::error_code();
  m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_code);
}

void TcpConnection::stop(boost::system::error_code& error_code) {
  std::cout << "Shutting down connection. Reason: " << error_code.message() << '\n';
  m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error_code);
}

void TcpConnection::read_from_socket() {
  // Note, we may want to change this later as it's easy to overflow
  m_socket.async_receive(boost::asio::buffer(m_in_packet, 4096),
  [self = shared_from_this()](boost::system::error_code ec, size_t sz)
  {
    self->read_complete(ec, sz);
  });
}

void TcpConnection::read_complete(boost::system::error_code &error, size_t bytes_transferred)
{
  if (error.value() != 0)
  {
    stop(error);
    return;
  }

  if (bytes_transferred == 0)
  {
    stop();
    return;
  }

  auto&& iter = m_in_packet.begin();
  std::string packet_string { iter, iter + bytes_transferred };

  // Work to do after reading
  auto now = boost::posix_time::microsec_clock::local_time();
  std::cout << '[' << now << "]\n";
  std::cout << "Message recieved from: " << m_socket.remote_endpoint().address().to_string() << '\n';
  std::cout << "Message size: " << bytes_transferred << '\n';
  std::cout << packet_string << '\n';
  boost::trim_all(packet_string);
  ResponseBuilder builder{};
  std::string out_response{};
  try
  {
    RequestMessage message{packet_string};
    auto type = message.type();
    auto values = message.values();
    std::cout << "Values received: " << values.size() << '\n';
    
    if(type == RequestType::heartbeat)
    {
      return;
    }

    if(type == RequestType::invalid)
    {
      m_is_primed_for_shutdown = true;
      out_response = builder.invalid_request(packet_string);
    }

    if(type == RequestType::logout)
    {
      m_is_primed_for_shutdown = true;
      out_response = builder.logout_reponse(true);
    }

    if(type == RequestType::login_req)
    {
      auto command = values[0];
      auto uname = values[1];
      auto password = values[2];
      auto is_success = false;

      // Check for LOGA or LOGU
      if(command == "LOGA")
      {
        auto res = m_dbi->LoginAdmin(uname, password);
        is_success = res == 0;
        // also set if the connection is for a admin
        m_is_admin_session = true;
      }

      if(command == "LOGU")
      {
        auto res = m_dbi->LoginUser(uname, password);
        is_success = res == 0;
      }

      out_response = builder.login_response(is_success);
    }

    if(type == RequestType::register_req)
    {
      // fname lname uname password
      auto command     = values[0];
      auto uname       = values[1];
      auto password    = values[2];
      auto fname       = values[3];
      auto lname       = values[4];

      auto is_success = false;

      if(command == "REGA")
      {
        auto res = m_dbi->RegisterAdmin(fname, lname, uname, password);
        // set is admin
        m_is_admin_session = true;
        is_success = res == 0;
      }

      if(command == "REGU")
      {
        auto res = m_dbi->RegisterUser(fname, lname, uname, password);
        is_success = res == 0;
      }

      out_response = builder.register_response(is_success);
    }
  }
  catch(std::exception& err)
  {
    auto err_message = err.what();
    std::cerr << "Error occurred during processing request: " << err_message << '\n';
    m_is_primed_for_shutdown = true;
    out_response = builder.error_response(err_message);
    return;
  }

  send(out_response);
}

void TcpConnection::write_to_socket() {
  boost::asio::async_write(m_socket,
    boost::asio::buffer(m_out_packet, m_out_packet.size()),
    m_write_strand.wrap(
      [self = shared_from_this()](boost::system::error_code code, size_t sz)
  {
    self->write_complete(code, sz);
  }));
}

void TcpConnection::write_complete(boost::system::error_code& error, size_t /*bytes_transferred*/)
{
  if(error.value() != 0)
  {
    std::cerr << "Error during write: " << error.message() << '\n';
    stop(error);
    return;
  }

  if(m_is_primed_for_shutdown)
  {
    stop();
    return;
  }

  m_out_packet.clear();
  read_from_socket();
}

void TcpConnection::send(std::string msg)
{
  std::copy(std::begin(msg), std::end(msg), std::back_inserter(m_out_packet));
  write_to_socket();
}
