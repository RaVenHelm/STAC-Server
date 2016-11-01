#pragma once

#include <string>
#include <vector>
#include <sstream>

#include <boost/algorithm/string.hpp>

namespace stac { namespace utility
{
  auto split_string(std::string);
  std::string reorder_date_format(std::string);
  int generate_random_id(int start, int length);
} // utility
} // stac