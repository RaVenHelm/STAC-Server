#pragma once

#include <string>

namespace stac
{
namespace config
{
struct DBConfig
{
  std::string ip;
  std::string port = "3306";
  std::string username;
  std::string password;
  std::string schema;
};

DBConfig load_db_config_from_file(std::string const& filename);
std::string connection_string(DBConfig const& config);
}
}
