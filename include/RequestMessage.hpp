#pragma once

#include <vector>
#include <regex>
#include <string>
#include <utility>

#include <boost/optional.hpp>

enum class RequestType
{
  login,
  register_req, // register is a reserved keyword
  logout,
  class_create,
  class_view,
  class_search,
  heartbeat,
  enroll,
  drop,
  class_list,
  enroll_list,
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

  auto type() const { return m_request; }
  auto values() const { return m_values; }
};
