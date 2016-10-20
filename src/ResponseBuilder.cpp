#include "ResponseBuilder.hpp"

using stac::core::ResponseBuilder;

// Example:
// ERR "Invalid response: ..."
std::string ResponseBuilder::invalid_request(std::string message)
{
  std::stringstream ss{};
  ss << "ERR " << "\"Invalid response: " << message
     << "\"";
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
