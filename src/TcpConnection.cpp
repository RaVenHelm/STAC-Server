#include <iterator>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string/trim_all.hpp>

#include "TcpConnection.hpp"
#include "RequestMessage.hpp"

using stac::tcpip::TcpConnection;

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
  try
  {
    RequestMessage message{packet_string};
    message.perform_action([&](auto const& type, auto const& values){
    (void)type;
    std::cout << "Values received: " << values.size() << '\n';
    if(type == RequestType::logout)
    {
      m_is_primed_for_logout = true;
    }
    });
  }
  catch(std::exception& err)
  {
    std::cerr << err.what() << '\n';
    return;
  }

  if(m_is_primed_for_logout)
  {
    send("LOGO");
    return;
  }
  send(packet_string);
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
  if(error)
  {
    std::cerr << "Error during write: " << error.message() << '\n';
    stop(error);
    return;
  }

  if(m_is_primed_for_logout)
  {
    std::cout << "Logging out user: [FILL IN LATER]\n";
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
