#include "Utility.hpp"

namespace stac { namespace utility
{
  auto split_string(std::string str)
  {
    std::vector<std::string> parts{};
    boost::algorithm::split(parts, str, boost::algorithm::is_any_of("-"));
    return parts;
  }
  
  std::string reorder_date_format(std::string date)
  {
    auto parts = split_string(date);
    return parts[2] + '-' + parts[1] + '-' + parts[2];
  }

  int generate_random_id(int start, int length)
  {
    std::stringstream ss{};
    auto start_str = std::to_string(start);
    ss << start;
    auto rest = length - start_str.size();
    for(unsigned i = 0; i < rest; ++i)
    {
      ss << i;
    }

    return std::stoi(ss.str());
  }
} // utility
} // stac