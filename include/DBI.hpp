#pragma once

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
  DBI(std::string const conStr,
      std::string const username,
      std::string const password,
      std::string const schema)
    : driver(get_driver_instance())
  {
    std::cout << "Connecting to MySQL database on " << conStr << '\n';
    con = std::shared_ptr<sql::Connection>(driver->connect(conStr, username, password));
    con->setSchema(schema);
  }

  int RegisterUser(std::string fname, std::string lname, std::string uname, std::string password)
	{
		int r = 0;
		try {
			std::string statement
        = "INSERT INTO STACDB.Users (`FName`, `LName`, `UName`, `Password`) VALUES('"
          + fname + "', '" + lname + "', '" + uname + "', '" + password + "');";
  			con->createStatement()->execute(statement);
		}
		catch (sql::SQLException &e) {
			r = 1;
      print_sql_error(std::cout, e);
		}
		return r;
	}

  int LoginUser(std::string uname, std::string password)
	{
		int r = 0;
		try
    {
      std::string resultP;
			std::string statement
        = "SELECT `UName`,`Password` FROM STACDB.Users WHERE `UName`='" + uname + "';";
			auto res = std::unique_ptr<sql::ResultSet>(con->createStatement()->executeQuery(statement));
			while (res->next()) {
				resultP = res->getString("Password");
			}
			if (resultP != password) {
				r = 1;
			}
		}
		catch (sql::SQLException &e)
    {
			r = 2;
			print_sql_error(std::cout, e);
		}

    return r;
	}

	int RegisterAdmin(std::string fname, std::string lname, std::string uname, std::string password)
	{
		int r = 0;
		try
    {
			std::string statement =
        "INSERT INTO STACDB.Admins (`FName`, `LName`, `UName`, `Password`) VALUES('" + fname + "', '" + lname + "', '" + uname + "', '" + password + "');";
			con->createStatement()->execute(statement);
		}
		catch (sql::SQLException &e)
    {
			r = 1;
			print_sql_error(std::cout, e);
		}
		return r;
	}

  int LoginAdmin(std::string uname, std::string password)
	{
		std::string resultP{};
		int r = 0;
		try
    {
			std::string statement =
        "SELECT `UName`,`Password` FROM STACDB.Admins WHERE `UName`='" + uname + "';";
      auto res = std::unique_ptr<sql::ResultSet>(con->createStatement()->executeQuery(statement));
			while (res->next()) {
				resultP = res->getString("Password");
			}
			if (resultP != password) {
				r = 1;
			}
		}
		catch (sql::SQLException &e)
    {
			r = 2;
			print_sql_error(std::cout, e);
		}

    return r;
	}
}; // DBI
} // db
} // stac
