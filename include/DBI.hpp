#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <boost/optional.hpp>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "Class.hpp"

namespace stac
{
namespace db
{
template <typename OutputStream>
void print_sql_error(OutputStream &os, sql::SQLException &exception)
{
  os << "# ERR: SQLException" << exception.what();
  os << " (MySQL error code: " << exception.getErrorCode();
  os << ", SQLState: " << exception.getSQLState() << " )\n";
}

class DBI
{
private:
  sql::Driver *driver;
  std::shared_ptr<sql::Connection> con;

public:
  //Creates the connection. The way this is setup allows simple connections to be opened by just doing object.function...
  DBI(std::string const conStr,
      std::string const username,
      std::string const password,
      std::string const schema);

  int RegisterUser(std::string fname, std::string lname, std::string uname, std::string password);
  int LoginUser(std::string uname, std::string password);
  int RegisterAdmin(std::string fname, std::string lname, std::string uname, std::string password);
  int LoginAdmin(std::string uname, std::string password);
  int GetAdminIdFromName(std::string name);
  int GetUserIdFromName(std::string name);
  std::vector<int> SelectClassID(std::string class_name, std::string institution);
  boost::optional<stac::core::Class> SelectClassDetails(int class_id);
  int CreateClass(std::string class_name,
                  int admin_id,
                  std::string institution,
                  std::string start_date,
                  std::string end_date,
                  std::string ip_address,
                  std::string meetings);
}; // DBI
} // db
} // stac
