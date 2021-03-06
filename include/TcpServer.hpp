#pragma once

#include <algorithm>
#include <thread>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include "TcpConnection.hpp"
#include "DBConfig.hpp"
#include "DBI.hpp"

using boost::asio::ip::tcp;
using stac::config::DBConfig;
using stac::config::connection_string;
using stac::db::DBI;
using stac::db::print_sql_error;

namespace stac {
namespace tcpip {

template <typename ConnectionHandler>
class TcpServer
{
  using shared_handler_t = boost::shared_ptr<ConnectionHandler>;

  unsigned short m_port = 0;
  unsigned m_thread_count = 1;
  std::vector<std::thread> m_thread_pool;
  boost::asio::io_service m_service;
  tcp::acceptor m_acceptor;
  boost::asio::signal_set m_signals;
  std::shared_ptr<DBI> m_dbi;
public:
  TcpServer() = delete;

  TcpServer(TcpServer const &) = delete;

  TcpServer &operator=(TcpServer const &) = delete;

  TcpServer(DBConfig const& conf, unsigned thread_count = 1)
    : m_thread_count(thread_count),
      m_service(),
      m_acceptor(m_service),
      m_signals(m_service),
      m_dbi(std::make_shared<DBI>(connection_string(conf), conf.username, conf.password, conf.schema))
  {
    std::cout << "DB connection made, starting server...\n";
    this->m_signals.add(SIGINT);
    this->m_signals.add(SIGTERM);
#if defined(SIGQUIT)
    this->m_signals.add(SIGQUIT);
#endif
    handle_await_stop();
  }

  void run(unsigned short port)
  {
    auto handler = boost::make_shared<ConnectionHandler>(m_service, m_dbi);

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
    m_acceptor.open(endpoint.protocol());
    m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    m_acceptor.bind(endpoint);
    m_acceptor.listen();

    std::cout << "Server is now listening on port " << port << '\n';
    m_acceptor.async_accept(handler->socket(),
        [=](boost::system::error_code ec)
        {
          handle_accept(handler, ec);
        });
    for(unsigned i = 0; i < m_thread_count; ++i)
    {
      m_thread_pool.emplace_back( [=]{ m_service.run(); } );
    }
    std::for_each(m_thread_pool.begin(), m_thread_pool.end(), [](auto& t){ t.join(); });
  }

private:
  void handle_await_stop()
  {
    m_signals.async_wait(
      [this](auto const& err, auto sigNum)
      {
        std::cerr << "Signal Received: " << sigNum << ". Message: " << err.message() << '\n';
        m_acceptor.close();
      });
  }

  void handle_accept(shared_handler_t handler, boost::system::error_code const& error_code)
  {
    if(error_code) return;

    std::cout << "Handling new connection...\n";
    handler->start();

    auto new_handler = boost::make_shared<ConnectionHandler>(m_service, m_dbi);

    m_acceptor.async_accept(new_handler->socket(),
        [=](boost::system::error_code ec)
        {
          handle_accept(new_handler, ec);
        });
  }
};
} // tcpip
} // stac
