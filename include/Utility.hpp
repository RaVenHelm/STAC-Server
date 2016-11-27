#pragma once

#include <string>
#include <vector>
#include <sstream>

#include <boost/algorithm/string.hpp>

namespace stac { namespace utility
{
  auto split_string(std::string);
  std::string reorder_date_format(std::string);
  std::string extract_class_meetings(std::string msg);
  int generate_random_id(int start, int length);
  std::string convert_time(std::string time_str);
} // utility
} // stac