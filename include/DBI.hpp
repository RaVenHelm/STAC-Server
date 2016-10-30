#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

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

	int GetAdminIdFromName(std::string name)
	{
		int result = 0;
		try
		{
			std::string statement = "SELCT ID from Admins WHERE UName='?';";
			auto p_stmt = std::unique_ptr<sql::PreparedStatement>(con->prepareStatement(statement));
			p_stmt->setString(1, name);

			auto res = std::unique_ptr<sql::ResultSet>(p_stmt->executeQuery());
			if(res->next()) {
				result = res->getInt("ID");
			}
		}
		catch(sql::SQLException &e)
		{
			result = -e.getErrorCode();
			print_sql_error(std::cout, e);
		}

		return result;
	}

	int GetUserIdFromName(std::string name)
	{
		int result = 0;
		try
		{
			std::string statement = "SELCT ID from Users WHERE UName='?';";
			auto p_stmt = std::unique_ptr<sql::PreparedStatement>(con->prepareStatement(statement));
			p_stmt->setString(1, name);
			
			auto res = std::unique_ptr<sql::ResultSet>(p_stmt->executeQuery());
			if(res->next()) {
				result = res->getInt("ID");
			}
		}
		catch(sql::SQLException &e)
		{
			result = -e.getErrorCode();
			print_sql_error(std::cout, e);
		}

		return result;
	}

	std::vector<int> SelectClassID(std::string class_name, std::string institution)
	{
		std::vector<int> result{};
		std::string statement = "SELECT ClassID FROM STACDB.Classes WHERE ClassName LIKE '?%' AND Institution LIKE '?%';";

		auto p_stmt = std::unique_ptr<sql::PreparedStatement>(con->prepareStatement(statement));
		p_stmt->setString(1, class_name);
		p_stmt->setString(2, institution);

		auto res = std::unique_ptr<sql::ResultSet>(p_stmt->executeQuery());
		while(res->next())
		{
			result.push_back(res->getInt("ClassID"));
		}

		return result;
	}

	std::vector<stac::core::Class> SelectClassDetails(int class_id)
	{
		std::vector<stac::core::Class> result{};
		std::string statement = "SELECT * FROM STACDB.Classes WHERE ClassID=?;";
		auto p_stmt = std::unique_ptr<sql::PreparedStatement>(con->prepareStatement(statement));
		p_stmt->setInt(1, class_id);

		auto res = std::unique_ptr<sql::ResultSet>(p_stmt->executeQuery());
		while(res->next())
		{
			auto id = res->getInt("ClassID");
			auto name = res->getString("ClassName");
			auto admin_id = res->getInt("AdminID");
			auto institution = res->getString("Institution");
			auto meet_time = res->getString("MeetTimes");
			auto start_date = res->getString("StartDate");
			auto end_date = res->getString("EndDate");
			auto ip = res->getString("PublicIPAddress");
			stac::core::Class cls{id, name, institution, admin_id, meet_time, start_date, end_date, ip};
			result.push_back(cls);
		}
		return result;
	}

	int CreateClass(std::string class_name,
									int admin_id,
							    std::string institution,
									std::string start_date,
									std::string end_date,
									std::string ip_address,
									std::string meetings)
	{
		std::string statement = "INSERT INTO stacdb.Classes (ClassName, AdminID, Institution, MeetTimes, StartDate, EndDate, PublicIPAdress) VALUES (?,?,?,?,?,?,?);";
		auto p_stmt = std::unique_ptr<sql::PreparedStatement>(con->prepareStatement(statement));
		p_stmt->setString(1, class_name);
		p_stmt->setInt(2, admin_id);
		p_stmt->setString(3, institution);
		p_stmt->setString(4, meetings);
		p_stmt->setString(5, start_date);
		p_stmt->setString(6, end_date);
		p_stmt->setString(7, ip_address);

		auto record_code = p_stmt->executeUpdate();

		return record_code;
	}
}; // DBI
} // db
} // stac
