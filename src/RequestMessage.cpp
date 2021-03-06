#include "RequestMessage.hpp"

#include <map>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>

#include "Utility.hpp"

// The "\s*"'s' at the end for random whitespace characters that may come from
// Programs like netcat or Java
static const std::map<RequestType, std::regex> regex_map = {
  {RequestType::login, std::regex{"^(LOGA|LOGU)\\s\"([A-z0-9]+)\"\\s\"([^\"]+)\"\\s*$"}},
  {RequestType::logout, std::regex{"^(LOGO)\\s*$"}},
  {RequestType::heartbeat, std::regex{"^(HRBT)\\s*$"}},
  {RequestType::register_req, std::regex{"^(REGA|REGU)\\s\"([A-z0-9]+)\"\\s\"([^\"]+)\"\\s\"([^0-9\"]+)\"\\s\"([^0-9\"]+)\"\\s*$"}},
  {RequestType::class_search, std::regex{"^(CSRC)\\s\"([^\"]*)?\"\\s\"([^\"]*)?\"\\s*$"}},
  {RequestType::class_view, std::regex{"^(CDTL)\\s\"([0-9]+)\"\\s*$"}},
  {RequestType::class_create, std::regex{ "^(CRCR)\\s\"([^\"]+)\"\\s\"([^\"]+)\"\\s\"(\\d{2}-\\d{2}-\\d{4})\"\\s\"(\\d{2}-\\d{2}-\\d{4})\"\\s\"(\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3})?\"\\s\"([A-z]\\d{4}-\\d{4};?)+\"\\s*$"}},
  {RequestType::enroll, std::regex{"^(ENRL)\\s\"([0-9]{10})\"\\s\"([0-9a-fA-F]{2}:[0-9a-fA-F]{2}:[0-9a-fA-F]{2}:[0-9a-fA-F]{2}:[0-9a-fA-F]{2}:[0-9a-fA-F]{2})\"\\s*$"}},
  {RequestType::drop, std::regex{"^(CDRP)\\s\"([0-9]{10})\"\\s*$"}},
  {RequestType::enroll_list, std::regex{"^(ELST)\\s*$"}},
  {RequestType::class_list, std::regex{"^(CLST)\\s*$"}},
  {RequestType::attend, std::regex{"^(ATTN)\\s\"([0-9]{10})\"\\s\"([0-9a-fA-F]{2}:[0-9a-fA-F]{2}:[0-9a-fA-F]{2}:[0-9a-fA-F]{2}:[0-9a-fA-F]{2}:[0-9a-fA-F]{2})\"\\s\"(\\d{2}-\\d{2}-\\d{4})\"\\s\"(\\d{2}\\d{2})\"\\s*$"}},
  {RequestType::manual_attend, std::regex{"^(MTTN)\\s\"([^\"]*)\"\\s\"([A-z0-9]+)\"\\s\"(\\d{2}-\\d{2}-\\d{4})\"\\s\"(\\d{2}\\d{2})\"\\s*$"}},
  {RequestType::check_attendance, std::regex{"^(CCHK)\\s\"([0-9]{10})\"\\s*$"}},
  {RequestType::class_attendance, std::regex{"^(ATRP)\\s\"([0-9]{10})\"\\s*$"}}
};

// TODO: Maybe make this a private static member function (?)
// See standards/requirements document for message specification
auto match_string(std::string const& request)
{
  auto matches = std::smatch{};
  auto end = regex_map.end();
  auto match_iter = std::find_if(regex_map.begin(), end,
  [&](auto const& pair) {
    // pair is the std::pair of RequestType and std::regex
    return std::regex_match(request, matches, pair.second);
  });

  if(match_iter == end)
  {
    return std::make_tuple(false, RequestType::invalid, std::smatch{});
  }

  return std::make_tuple(true, match_iter->first, matches);
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

    std::copy(matches.begin() + 1, matches.end(), std::back_inserter(values));

    if(type == RequestType::class_create)
    {
      values.push_back(stac::utility::extract_class_meetings(matches[0].str()));
    }
    m_values = values;
  }
}
