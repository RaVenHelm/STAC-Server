#include "RequestMessage.hpp"

#include <iostream>

std::tuple<bool, RequestType, std::smatch> match_string(std::string const& request)
{
  static const std::regex login_admin{ "^(LOGA)\\s+\"([A-z]+)\"\\s+\"(.+)\"\\s+$" };
  static const std::regex login_user{ "^(LOGU)\\s+\"([A-z]+)\"\\s+\"(.+)\"\\s+$" };
  static const std::regex register_admin{ "^(REGA)\\s+\"([A-z]+)\"\\s+\"(.+)\"\\s+\"([A-z]+)\"\\s+\"([A-z]+)\"\\s+$" };
  static const std::regex register_user{ "^(REGU)\\s+\"([A-z]+)\"\\s+\"(.+)\"\\s+\"([A-z]+)\"\\s+\"([A-z]+)\"\\s+$" };
  static const std::regex logout{"^(LOGO)$"};

  auto matches = std::smatch{};

  if(std::regex_match(request, matches, login_admin))
  {
    return std::make_tuple(true, RequestType::login_admin, matches);
  }
  else if(std::regex_match(request, matches, login_user))
  {
  return std::make_tuple(true, RequestType::login_user, matches);
  }
  else if(std::regex_match(request, matches, register_admin))
  {
    return std::make_tuple(true, RequestType::register_admin, matches);
  }
  else if(std::regex_match(request, matches, register_user))
  {
    return std::make_tuple(true, RequestType::register_user, matches);
  }
  else if(std::regex_match(request, matches, logout))
  {
    return std::make_tuple(true, RequestType::logout, matches);
  }
  else
  {
    return std::make_tuple(false, RequestType::invalid, matches);
  }
}

RequestMessage::RequestMessage(std::string message)
{
  auto result = match_string(message);
  if(!std::get<bool>(result))
  {
    std::cerr << "Cannot parse message: " << message << '\n';
  }
  else
  {
    m_request = std::get<RequestType>(result);
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
