#include <string>
#include <iterator>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/algorithm/string/trim_all.hpp>

#include "TcpConnection.hpp"
#include "RequestMessage.hpp"
#include "ResponseBuilder.hpp"

using stac::tcpip::TcpConnection;
using stac::core::ResponseBuilder;

void TcpConnection::start()
{
  read_from_socket();
}

void TcpConnection::stop()
{
  std::cout << "Clean shutting down of connection\n";
  auto ignored_code = boost::system::error_code{};
  m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_code);
}

void TcpConnection::stop(boost::system::error_code &error_code)
{
  std::cout << "Shutting down connection. Reason: " << error_code.message() << '\n';
  m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error_code);
}

void TcpConnection::read_from_socket()
{
  // Blocking call that registers a callback to boost::asio when a read happens
  m_socket.async_receive(boost::asio::buffer(m_in_packet, 4096),
                         [self = shared_from_this()](boost::system::error_code ec, size_t sz) {
                           self->read_complete(ec, sz);
                         });
}

void TcpConnection::read_complete(boost::system::error_code &error, size_t bytes_transferred)
{
  // Check for any error values
  // Most common will be EOF and connection reset
  if (error.value() != 0)
  {
    stop(error);
    return;
  }

  // More of a sanity check for empty sends
  if (bytes_transferred == 0)
  {
    stop();
    return;
  }

  // Only copies the amount of bytes transferred to the strings
  auto iter = m_in_packet.begin();
  std::string packet_string{iter, iter + bytes_transferred};

  // Turning this on for diagnostics
  // TODO: Remove this later
  std::cout << std::boolalpha;

  // Work to do after reading
  // Timestamp on request
  auto now = boost::posix_time::microsec_clock::local_time();
  std::cout << '[' << now << "]\n";

  // Get size and remote IP of socket
  m_remote_ip = m_socket.remote_endpoint().address().to_string();
  std::cout << "Message recieved from: " << m_remote_ip << '\n';
  std::cout << "Message size: " << bytes_transferred << '\n';
  std::cout << packet_string << '\n';

  // Trimming the front/back of the string for sanity reasons
  boost::trim_all(packet_string);

  ResponseBuilder builder{};
  std::string out_response{};
  try
  {
    RequestMessage message{packet_string};
    auto type = message.type();
    auto values = message.values();
    std::cout << "Values received: " << values.size() << '\n';

    if (type == RequestType::heartbeat)
    {
      out_response = builder.heartbeat_response();
    }

    if (type == RequestType::invalid)
    {
      m_is_primed_for_shutdown = true;
      out_response = builder.invalid_request(packet_string);
    }

    if (type == RequestType::logout)
    {
      m_is_primed_for_shutdown = true;
      out_response = builder.logout_reponse(true);
    }

    if (type == RequestType::login)
    {
      if (m_is_logged_in)
      {
        out_response = builder.error_response("Already logged in, killing connection");
        m_is_primed_for_shutdown = true;
      }
      else
      {
        auto command = values[0];
        auto uname = values[1];
        auto password = values[2];
        auto is_success = false;

        // Check for LOGA or LOGU
        if (command == "LOGA")
        {
          std::cout << "Logging in ADMIN..." << uname << '\n';
          auto res = m_dbi->LoginAdmin(uname, password);
          is_success = res == 0;

          // also set if the connection is for a admin
          m_is_admin_session = true;

          if (is_success)
          {
            m_is_logged_in = true;
            m_username = uname;
            m_id = m_dbi->GetAdminIdFromName(uname);
          }
          std::cout << "Login status: " << is_success << '\n';
          out_response = builder.login_response(is_success);
        }

        if (command == "LOGU")
        {
          std::cout << "Logging in USER... " << uname << '\n';
          auto res = m_dbi->LoginUser(uname, password);
          is_success = res == 0;

          if (is_success)
          {
            m_is_logged_in = true;
            m_username = uname;
            m_id = m_dbi->GetUserIdFromName(uname);
          }
          std::cout << "Login status: " << is_success << '\n';
          out_response = builder.login_response(is_success);
        }
      }
    }

    if (type == RequestType::register_req)
    {
      if (m_is_logged_in)
      {
        out_response = builder.error_response("Already logged in, killing connection");
        m_is_primed_for_shutdown = true;
      }
      else
      {
        auto command = values[0];
        auto uname = values[1];
        auto password = values[2];
        auto fname = values[3];
        auto lname = values[4];

        auto is_success = false;

        if (command == "REGA")
        {
          std::cout << "About to register ADMIN...\n";
          auto res = m_dbi->RegisterAdmin(fname, lname, uname, password);

          // set is admin
          m_is_admin_session = true;
          is_success = res == 0;

          if (is_success)
          {
            m_is_logged_in = true;
            m_username = uname;
            m_id = m_dbi->GetAdminIdFromName(uname);
          }
          std::cout << "Registration status: " << is_success << '\n';
          out_response = builder.register_response(is_success);
        }

        if (command == "REGU")
        {
          std::cout << "About to register USER...\n";
          auto res = m_dbi->RegisterUser(fname, lname, uname, password);
          is_success = res == 0;

          if (is_success)
          {
            m_is_logged_in = true;
            m_username = uname;
            m_id = m_dbi->GetUserIdFromName(uname);
          }
          std::cout << "Registration status: " << is_success << '\n';
          out_response = builder.register_response(is_success);
        }
      }
    }

    if (type == RequestType::class_view)
    {
      if (m_is_logged_in)
      {
        auto cid_str = values[1];
        auto cid = std::stoi(cid_str.c_str(), nullptr, 10);
        auto is_success = false;
        std::cout << cid << '\n';
        auto res = m_dbi->SelectClassDetails(cid);
        if(res) {
          is_success = true;
        }

        out_response = builder.class_view_response(is_success, res);
      }
      else
      {
        out_response = builder.error_response("No user logged in!");
      }
    }

    if (type == RequestType::class_search)
    {
      if (m_is_logged_in)
      {
        auto command = values[0];
        auto clsname = values[1];
        auto cid = values[2];
        auto is_success = false;
        auto res = m_dbi->SelectClassID(clsname, cid);
        is_success = res.size() > 0;

        out_response = builder.class_search_response(is_success, res);
      }
      else
      {
        out_response = builder.error_response("No user logged in!");
      }
    }

    if (type == RequestType::class_create)
    {
      if (m_is_admin_session = true && m_is_logged_in)
      {
        auto command = values[0];
        auto clsname = values[1];
        auto instit = values[2];
        auto start_date = values[3];
        auto end_date = values[4];
        auto ip_address = values[5];
        auto dow_time = values[6];
        auto is_success = false;
        std::cout << clsname << " " << m_id << " " << instit << " " << start_date << " " << end_date << " " << ip_address << " " << dow_time << '\n';
        // This result is the class ID inserted into the database
        auto res = m_dbi->CreateClass(clsname, m_id, instit, start_date, end_date, ip_address, dow_time);
        is_success = res > 0;

        out_response = builder.create_class_response(is_success, res);
      }
      else
      {
        out_response = builder.error_response("No user logged in or the user is not an admin!");
      }
    }
  }
  catch (std::exception &err)
  {
    auto err_message = err.what();
    std::cerr << "Error occurred during processing request: " << err_message << '\n';
    m_is_primed_for_shutdown = true;
    out_response = builder.error_response(err_message);
  }

  send(out_response);
}

void TcpConnection::write_to_socket()
{
  boost::asio::async_write(m_socket,
                           boost::asio::buffer(m_out_packet, m_out_packet.size()),
                           m_write_strand.wrap(
                               [self = shared_from_this()](boost::system::error_code code, size_t sz) {
                                 self->write_complete(code, sz);
                               }));
}

void TcpConnection::write_complete(boost::system::error_code &error, size_t /*bytes_transferred*/)
{
  // Check for any issues writing
  // Usually the client will close the connection early
  if (error.value() != 0)
  {
    std::cerr << "Error during write: " << error.message() << '\n';
    stop(error);
    return;
  }

  if (m_is_primed_for_shutdown)
  {
    stop();
    return;
  }

  m_out_packet.clear();
  read_from_socket();
}

void TcpConnection::send(std::string msg)
{
  std::cout << "Sending message: " << msg << '\n';
  std::copy(msg.begin(), msg.end(), std::back_inserter(m_out_packet));
  m_out_packet.push_back('\n');
  write_to_socket();
}
