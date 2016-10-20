#pragma once

#include <string>
#include <sstream>

#include "RequestMessage.hpp"

namespace stac
{
namespace core
{
struct ResponseBuilder
{
  std::string invalid_request(std::string message);
  std::string login_response(bool is_success);
  std::string logout_reponse(bool is_success);
  std::string error_response(std::string err_message);
  std::string register_response(bool is_success);
};
}
}
