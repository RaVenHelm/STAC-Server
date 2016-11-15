#include "ResponseBuilder.hpp"

#include <algorithm>
#include <iterator>

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

std::string ResponseBuilder::class_search_response(boost::optional<std::vector<int>> class_ids)
{
  std::stringstream ss{};
  ss << "CSRR ";
  if(class_ids)
  {
    ss << "S ";
    std::vector<std::string> id_strings{};
    // convert the vector<int> to a vector<std::string>
    std::transform(class_ids->begin(), class_ids->end(), std::back_inserter(id_strings),
      [&](auto const i)
      {
        std::stringstream sstream{};
        sstream << "\"" << i << "\"";
        return sstream.str();
      });
    std::copy(id_strings.begin(), id_strings.end(), std::ostream_iterator<std::string>(ss, " "));
  }
  else
  {
    ss << 'F';
  }
  return ss.str();
}

std::string ResponseBuilder::class_view_response(boost::optional<stac::core::Class> maybe_class)
{
  std::stringstream ss{};
  if(maybe_class)
  {
    ss << "CDTR " << "S" << ' '
     << "\"" << maybe_class->id << "\"" << ' '
     << "\"" << maybe_class->institution << "\"" << ' '
     << "\"" << maybe_class->name << "\"" << ' '
     << "\"" << maybe_class->admin_name << "\"" << ' '
     << "\"" << maybe_class->start_date << "\"" << ' '
     << "\"" << maybe_class->end_date << "\"" << ' '
     << "\"" << maybe_class->ip_address << "\"" << ' '
     << "\"" << maybe_class->meetings << "\"";
  }
  else
  {
    ss << "CDTR " << "F";
  }

  return ss.str();
}

std::string ResponseBuilder::create_class_response(int class_id)
{
  std::stringstream ss{};
  if(class_id > 0)
  {
    ss << "CRER " << "S " << "\"" << class_id << "\"";
  }
  else
  {
    ss << "CRER " << "F";
  }
  return ss.str();
}

std::string ResponseBuilder::enroll_response(bool is_success)
{
  std::stringstream ss{};
  ss << "ENRR " << (is_success ? 'S' : 'F');
  return ss.str();
}

std::string ResponseBuilder::drop_response(bool is_success)
{
  std::stringstream ss{};
  ss << "CDRR " << (is_success ? 'S' : 'F');
  return ss.str();
}

std::string ResponseBuilder::enroll_list_response(boost::optional<std::vector<int>> class_ids)
{
  std::stringstream ss{};
  ss << "ELSR ";
  if(!class_ids)
  {
    ss << 'F';
  }
  else
  {
    auto ids = *class_ids;
    ss << "S ";
    std::for_each(ids.begin(), ids.end(),
      [&](auto const i)
      {
        ss << "\"" << i << "\" ";
      });
  }
  return ss.str();
}

std::string ResponseBuilder::class_list_response(boost::optional<std::vector<int>> class_ids)
{
  std::stringstream ss{};
  ss << "CLSR ";
  if(!class_ids)
  {
    ss << 'F';
  }
  else
  {
    auto ids = *class_ids;
    ss << "S ";
    std::for_each(ids.begin(), ids.end(),
      [&](auto const i)
      {
        ss << "\"" << i << "\" ";
      });
  }
  return ss.str();
}
