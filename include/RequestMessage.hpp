#pragma once

#include <vector>
#include <regex>
#include <string>
#include <utility>

#include <boost/optional.hpp>

enum class RequestType
{
  login_req,
  register_req,
  logout,
  invalid
};

auto match_string(std::string const& request);

class RequestMessage
{
  RequestType m_request;
  std::vector<std::string> m_values;
public:
  explicit RequestMessage(std::string message);
  RequestMessage() = delete;
  RequestMessage(RequestMessage const&) = delete;
  RequestMessage& operator=(RequestMessage const&) = delete;

  template <typename Action>
  void perform_action(Action action)
  {
    action(m_request, m_values);
  }
};
