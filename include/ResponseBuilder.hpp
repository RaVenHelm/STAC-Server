#pragma once

#include <string>
#include <sstream>

#include <boost/optional.hpp>

#include "RequestMessage.hpp"
#include "Class.hpp"

namespace stac
{
namespace core
{
struct ResponseBuilder
{
  // I removed the boolean parameter, since the whole concept of an optional incorpoates
  // the idea of success or failure (i.e., depending on if the class has a value)
  std::string invalid_request(std::string message);
  std::string login_response(bool is_success);
  std::string logout_reponse(bool is_success);
  std::string error_response(std::string err_message);
  std::string register_response(bool is_success);
  std::string class_search_response(boost::optional<std::vector<int>> class_ids);
  std::string class_view_response(boost::optional<stac::core::Class> maybe_class);
  std::string create_class_response(int class_id);
  std::string enroll_response(bool is_success);
  std::string drop_response(bool is_success);
  std::string enroll_list_response(boost::optional<std::vector<int>> class_ids);
  std::string class_list_response(boost::optional<std::vector<int>> class_ids);
  std::string user_attend_response(bool is_success);
  std::string manual_attend_response(bool is_success);
  std::string check_attendance_response(boost::optional<std::vector<std::string>> attendance_times);
  std::string attendance_report_response(boost::optional<std::vector<std::string>> attendance_list);
  std::string heartbeat_response();
};
}
}
