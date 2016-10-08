#pragma once

#include <cstdio>
#include <iostream>
#include <memory>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

namespace stac
{
namespace db
{
template <typename OutputStream>
void print_sql_error(OutputStream& os, sql::SQLException& exception)
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
  DBI(std::string const conStr   = "138.86.104.164:3306",
      std::string const username = "SEClass",
      std::string const password = "BearsRock",
      std::string const schema   = "STACDB")
    : driver(get_driver_instance())
  {
    con = std::shared_ptr<sql::Connection>(driver->connect(conStr, username, password));
    con->setSchema(schema);
  }

  //Inserts users into the database after given info from the user
  void insertUser(std::string username, std::string ip, std::string statement)
  {
    con->createStatement()->executeQuery(statement);
  }

  void deleteUser(std::string userId, std::string statement)
  {
    con->createStatement()->executeQuery(statement);
  }

  std::string selectUser(std::string user, std::string statement)
  {
    std::string resultU, resultI, result, finalResults;
    auto res = std::unique_ptr<sql::ResultSet>(con->createStatement()->executeQuery(statement));
    while (res->next()) {
      resultU = res->getString("FName");
      resultI = res->getString("UName");
      result = resultU + " " + resultI + "\n";
      finalResults += result;
    }
    return finalResults;
  }

  void executeRaw(std::string const& query, std::string const& field)
  {
    auto res = std::unique_ptr<sql::ResultSet>(con->createStatement()->executeQuery(query));
    while(res->next())
    {
      std::cout << "Result from raw query: " << res->getString(field) << '\n';
    }
  }
}; // DBI
} // db
} // stac
