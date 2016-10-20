#include "RequestMessage.hpp"

#include <iostream>
#include <sstream>
#include <exception>

auto match_string(std::string const& request)
{
  static const std::regex login_regex{ "^(LOGA|LOGU)\\s+\"([A-z]+)\"\\s+\"(.+)\"\\s*$" };
  static const std::regex register_regex{ "^(REGA|REGU)\\s+\"([A-z]+)\"\\s+\"(.+)\"\\s+\"([A-z]+)\"\\s+\"([A-z]+)\"\\s*$" };
  static const std::regex heartbeat_regex{ "^(HRBT)$" };
  static const std::regex logout_regex{ "^(LOGO)$" };

  auto matches = std::smatch{};

  if(std::regex_match(request, matches, heartbeat_regex))
  {
    return std::make_tuple(true, RequestType::heartbeat, matches);
  }

  if(std::regex_match(request, matches, login_regex))
  {
    return std::make_tuple(true, RequestType::login_req, matches);
  }
  
  if(std::regex_match(request, matches, register_regex))
  {
    return std::make_tuple(true, RequestType::register_req, matches);
  }
  
  if(std::regex_match(request, matches, logout_regex))
  {
    return std::make_tuple(true, RequestType::logout, matches);
  }
  
  return std::make_tuple(false, RequestType::invalid, matches);
}

RequestMessage::RequestMessage(std::string message)
{
  auto result = match_string(message);
  auto success = std::get<bool>(result);
  auto type   = std::get<RequestType>(result);
  m_request = type;
  if(!success)
  {
    std::cerr << "Cannot parse message: " << message << '\n';
    m_values = {};
  }
  else
  {
    auto matches = std::get<std::smatch>(result);
    auto values = std::vector<std::string>{};
    for(unsigned i = 1; i < matches.size(); ++i)
    {
      std::cout << "Submatch: " << matches[i].str() << '\n';
      values.push_back(matches[i].str());
    }
    m_values = values;
  }
}
