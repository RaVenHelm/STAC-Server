#include "RequestMessage.hpp"

#include <iostream>
#include <sstream>
#include <exception>

// TODO: Maybe make this a private static member function (?)
// See standards/requirements document for message specification
auto match_string(std::string const& request)
{
  // The "\s*"'s' at the end for random whitespace characters that may come from
  // Programs like netcat or Java
  // TODO: Refactor into a std::map<RequestType, std::regex> ?
  // Probably would also 
  static const std::regex login_regex{ "^(LOGA|LOGU)\\s\"([A-z0-9]+)\"\\s\"([^\"]+)\"\\s*$" };
  static const std::regex register_regex{ "^(REGA|REGU)\\s\"([A-z0-9]+)\"\\s\"([^\"]+)\"\\s\"([^0-9\"]+)\"\\s\"([^0-9\"]+)\"\\s*$" };
  static const std::regex heartbeat_regex{ "^(HRBT)\\s*$" };
  static const std::regex logout_regex{ "^(LOGO)$\\s*" };

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
  // TODO: Refactor: maybe add a member variable to the class
  // for the whole result object
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

    // TODO: Refactor: use iterators/std::copy
    for(unsigned i = 1; i < matches.size(); ++i)
    {
      std::cout << "Submatch: " << matches[i].str() << '\n';
      values.push_back(matches[i].str());
    }
    m_values = values;
  }
}
