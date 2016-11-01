#include "ResponseBuilder.hpp"

using stac::core::ResponseBuilder;

// Example:
// ERR "Invalid response: ..."
std::string ResponseBuilder::invalid_request(std::string message)
{
  std::stringstream ss{};
  ss << "ERR " << "\"Invalid response: " << message << "\"";
  return ss.str();
}

// Example:
// LOGR S
std::string ResponseBuilder::login_response(bool is_success)
{
  std::stringstream ss{};
  ss << "LOGR " << (is_success ? "S": "F");
  return ss.str();
}

// Example:
// LOGO S
std::string ResponseBuilder::logout_reponse(bool is_success)
{
  std::stringstream ss{};
  ss << "LOGO " << (is_success ? "S" : "F");
  return ss.str();
}

// Example:
// ERR "It was only a flesh wound!"
std::string ResponseBuilder::error_response(std::string err_message)
{
  std::stringstream ss{};
  ss << "ERR: \"" << err_message << "\"";
  return ss.str();
}

// Example:
// REGR S 
std::string ResponseBuilder::register_response(bool is_success)
{
	std::stringstream ss{};
	ss << "REGR " << (is_success ? "S" : "F");
	return ss.str();
}

// Example
// HRBT => OK
std::string ResponseBuilder::heartbeat_response()
{
  std::stringstream ss{};
  ss << "OK";
  return ss.str();
}

std::string ResponseBuilder::class_search_response(bool is_success, std::vector<int> const& class_ids)
{
  std::stringstream ss{};
  ss << "CSRR " << (is_success ? "S" : "F") << ' ';
  for(auto const id: class_ids)
  {
    ss << "\"" << id << "\"";
  }
  return ss.str();
}

std::string ResponseBuilder::class_view_response(bool is_success, boost::optional<stac::core::Class> maybe_class)
{
  std::stringstream ss{};
  if(is_success)
  {
    ss << "CDTR " << "S" << ' '
     << "\"" << maybe_class->id << "\"" << ' '
     << "\"" << maybe_class->institution << "\"" << ' '
     << "\"" << maybe_class->name << "\"" << ' '
     << "\"" << maybe_class->admin_id << "\"" << ' '
     << "\"" << maybe_class->meetings << "\"";
  }
  else
  {
    ss << "CDTR " << "F";
  }

  return ss.str();
}

std::string ResponseBuilder::create_class_response(bool is_success, int class_id)
{
  std::stringstream ss{};
  if(is_success)
  {
    ss << "CRER " << "S " << "\"" << class_id << "\"";
  }
  else
  {
    ss << "CRER " << "F";
  }
  return ss.str();
}
