#pragma once

#include <string>
#include <vector>

namespace stac
{
namespace core
{
struct Class
{
  int id;
  std::string name;
  std::string institution;
  int admin_id;
  std::string meetings;
  std::string start_date;
  std::string end_date;
  std::string ip_address;
};
}
}