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
  std::string class_search_response(bool is_success, std::vector<int> const& class_ids);
  std::string class_view_response(bool is_success, int class_id, std::string institution, int admin_name, std::string meetings);
  std::string create_class_response(bool is_success, int class_id);
  std::string heartbeat_response();
};
}
}
