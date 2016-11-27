#include "Utility.hpp"

#include <random>
#include <regex>

namespace stac { namespace utility
{
  template <typename IntType = int>
  auto make_random(IntType min = 0, IntType max = 9)
  {
    std::random_device device{};
    std::mt19937 gen{device()};
    std::uniform_int_distribution<IntType> dist{min, max};
    return dist(gen);
  }
  
  auto split_string(std::string str)
  {
    std::vector<std::string> parts{};
    boost::algorithm::split(parts, str, boost::algorithm::is_any_of("-"));
    return parts;
  }
  
  std::string reorder_date_format(std::string date)
  {
    auto parts = split_string(date);
    return parts[2] + '-' + parts[0] + '-' + parts[1];
  }

  int generate_random_id(int start, int length)
  {
    std::stringstream ss{};
    auto start_str = std::to_string(start);
    ss << start;
    auto rest = length - start_str.size();
    for(unsigned i = 0; i < rest; ++i)
    {
      ss << make_random();
    }

    return std::stoi(ss.str());
  }

  std::string extract_class_meetings(std::string msg)
  {
    static const std::regex pattern {"^CRCR\\s\".+\"\\s\".+\"\\s\".+\"\\s\".+\"\\s\".*\"\\s\"(.+)\"\\s*"};
    std::string result{};
    std::smatch matches{};

    if(std::regex_match(msg, matches, pattern))
    {
      if(matches.size() == 2)
      {
        result = matches[1].str();
      }
    }
    return result;
  }

  std::string convert_time(std::string time_str)
  {
    auto hours = time_str.substr(0, 2);
    auto mins = time_str.substr(2, 2);

    return hours + ":" + mins + ":00";
  }
} // utility
} // stac