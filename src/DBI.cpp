#include "DBI.hpp"

using namespace stac::db;

DBI::DBI(std::string const conStr,
         std::string const username,
         std::string const password,
         std::string const schema)
    : driver(get_driver_instance())
{
  std::cout << "Connecting to MySQL database on " << conStr << '\n';
  con = std::shared_ptr<sql::Connection>(driver->connect(conStr, username, password));
  con->setSchema(schema);
}

int DBI::RegisterUser(std::string fname, std::string lname, std::string uname, std::string password)
{
  int r = 0;
  try
  {
    std::string statement = "INSERT INTO STACDB.Users (`FName`, `LName`, `UName`, `Password`) VALUES('" + fname + "', '" + lname + "', '" + uname + "', '" + password + "');";
    con->createStatement()->execute(statement);
  }
  catch (sql::SQLException &e)
  {
    r = 1;
    print_sql_error(std::cout, e);
  }
  return r;
}

int DBI::LoginUser(std::string uname, std::string password)
{
  int r = 0;
  try
  {
    std::string resultP;
    std::string statement = "SELECT `UName`,`Password` FROM STACDB.Users WHERE `UName`='" + uname + "';";
    auto res = std::unique_ptr<sql::ResultSet>(con->createStatement()->executeQuery(statement));
    while (res->next())
    {
      resultP = res->getString("Password");
    }
    if (resultP != password)
    {
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

int DBI::RegisterAdmin(std::string fname, std::string lname, std::string uname, std::string password)
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

int DBI::LoginAdmin(std::string uname, std::string password)
{
  std::string resultP{};
  int r = 0;
  try
  {
    std::string statement =
        "SELECT `UName`,`Password` FROM STACDB.Admins WHERE `UName`='" + uname + "';";
    auto res = std::unique_ptr<sql::ResultSet>(con->createStatement()->executeQuery(statement));
    while (res->next())
    {
      resultP = res->getString("Password");
    }
    if (resultP != password)
    {
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

int DBI::GetAdminIdFromName(std::string name)
{
  int result = 0;
  try
  {
    std::string statement = "SELECT ID from Admins WHERE UName='" + name + "';";
    auto p_stmt = std::unique_ptr<sql::PreparedStatement>(con->prepareStatement(statement));

    auto res = std::unique_ptr<sql::ResultSet>(p_stmt->executeQuery());
    if (res->next())
    {
      result = res->getInt("ID");
    }
  }
  catch (sql::SQLException &e)
  {
    result = -e.getErrorCode();
    print_sql_error(std::cout, e);
  }
  return result;
}

int DBI::GetUserIdFromName(std::string name)
{
  int result = 0;
  try
  {
    std::string statement = "SELECT ID from Users WHERE UName='" + name + "';";
    auto p_stmt = std::unique_ptr<sql::PreparedStatement>(con->prepareStatement(statement));

    auto res = std::unique_ptr<sql::ResultSet>(p_stmt->executeQuery());
    if (res->next())
    {
      result = res->getInt("ID");
    }
  }
  catch (sql::SQLException &e)
  {
    result = -e.getErrorCode();
    print_sql_error(std::cout, e);
  }

  return result;
}

std::vector<int> DBI::SelectClassID(std::string class_name, std::string institution)
{
  std::vector<int> result{};
  std::string statement =
    "SELECT ClassID FROM STACDB.Classes WHERE ClassName LIKE '" + class_name + "%' AND Institution LIKE '" + institution+ "%';";

  auto p_stmt = std::unique_ptr<sql::PreparedStatement>(con->prepareStatement(statement));

  auto res = std::unique_ptr<sql::ResultSet>(p_stmt->executeQuery());
  while (res->next())
  {
    auto r1 = res->getInt("ClassID");
    auto r2 = res->getString("ClassID");
    (void)r2;
    result.push_back(r1);
  }

  return result;
}

boost::optional<stac::core::Class> DBI::SelectClassDetails(int class_id)
{
  std::string statement = "SELECT ClassID, ClassName, Institution, MeetTimes, StartDate, EndDate, PublicIPAddress, UName FROM stacdb.classes LEFT JOIN stacdb.admins on stacdb.classes.AdminID = stacdb.admins.ID WHERE ClassID=" + std::to_string(class_id) + ";";
  auto p_stmt = std::unique_ptr<sql::PreparedStatement>(con->prepareStatement(statement));
  p_stmt->setInt(1, class_id);

  auto res = std::unique_ptr<sql::ResultSet>(p_stmt->executeQuery());
  if (res->next())
  {
    auto id = res->getInt("ClassID");
    auto name = res->getString("ClassName");
    auto admin_name = res->getString("UName");
    auto institution = res->getString("Institution");
    auto meet_time = res->getString("MeetTimes");
    auto start_date = res->getString("StartDate");
    auto end_date = res->getString("EndDate");
    auto ip = res->getString("PublicIPAddress");
    stac::core::Class cls{id, name, institution, admin_name, meet_time, start_date, end_date, ip};
    return cls;
  }
  else
  {
    return boost::none;
  }
}

int DBI::CreateClass(std::string class_name,
                     int admin_id,
                     std::string institution,
                     std::string start_date,
                     std::string end_date,
                     std::string ip_address,
                     std::string meetings,
                     int class_id)
{
  std::string statement = "INSERT INTO STACDB.Classes (ClassName, AdminID, Institution, MeetTimes, StartDate, EndDate, PublicIPAddress, ClassID) VALUES (?,?,?,?,?,?,?,?);";
  auto p_stmt = std::unique_ptr<sql::PreparedStatement>(con->prepareStatement(statement));
  p_stmt->setString(1, class_name);
  p_stmt->setInt(2, admin_id);
  p_stmt->setString(3, institution);
  p_stmt->setString(4, meetings);
  p_stmt->setString(5, start_date);
  p_stmt->setString(6, end_date);
  p_stmt->setString(7, ip_address);
  p_stmt->setInt(8, class_id);

  p_stmt->executeUpdate();
  return class_id;
}

int DBI::RemoveUserFromEnrolledClass(std::string crn, std::string username)
{
  int res = 0;
  int userID = 0;
  std::string statement = "SELECT `ID` FROM STACDB.Users WHERE `UName` = '" + username + "';";
  auto stmt = std::unique_ptr<sql::Statement>(con->createStatement());
  auto res_set = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(statement));
  while (res_set->next()) {
    userID = res_set->getInt("ID");
  }
  statement =
    "DELETE FROM STACDB.Enrollment WHERE `UserID`='" +
      std::to_string(userID) + "' and`ClassID`='" + crn + "';";
  stmt = std::unique_ptr<sql::Statement>(con->createStatement());
  stmt->execute(statement);
  return res;
}

std::vector<int> DBI::UserSelectClass(std::string username)
{
  std::string statement = "SELECT `ID` FROM STACDB.Users WHERE `UName` = '" + username + "';";
  auto stmt = std::unique_ptr<sql::Statement>(con->createStatement());
  auto res = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(statement));
  auto userID = 0;
  std::vector<int> ids{};
  while (res->next()) {
    userID = res->getInt("ID");
  }
  statement = "SELECT `ClassID` from STACDB.Enrollment where UserID ='" + std::to_string(userID) + "';";
  stmt = std::unique_ptr<sql::Statement>(con->createStatement());
  res = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(statement));
  while (res->next()) {
    auto classID = res->getInt("ClassID");
    ids.push_back(classID);
  }
  return ids;
}

std::vector<int> DBI::AdminSelectClass(std::string username)
{
  std::string statement = "SELECT `ID` FROM STACDB.Admins WHERE `UName` = '" + username + "';";
  auto stmt = std::unique_ptr<sql::Statement>(con->createStatement());
  auto res = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(statement));
  int userID = 0;
  std::vector<int> result{};
  while (res->next()) {
    userID = res->getInt("ID");
  }
  statement = "SELECT `ClassID` from STACDB.Classes where AdminID ='" + std::to_string(userID) + "';";
  stmt = std::unique_ptr<sql::Statement>(con->createStatement());
  res = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(statement));
  while (res->next()) {
    auto classID = res->getInt("ClassID");
    result.push_back(classID);
  }
  return result;
}

int DBI::InsertUserIntoEnrollment(std::string crn,
                                  std::string username,
                                  std::string deviceID,
                                  std::string deviceFlag)
{
  int r = 0;
  int userID = 0;
  std::string statement{};
  
  deviceID = "FF:FF:FF:FF:FF:FF";
  deviceFlag = "0";
  try {
    statement = "SELECT `ID` FROM STACDB.Users WHERE `UName` = '" + username + "';";
    auto stmt = std::unique_ptr<sql::Statement>(con->createStatement());
    auto res = std::unique_ptr<sql::ResultSet>(stmt->executeQuery(statement));
    while (res->next()) {
      userID = res->getInt("ID");
    }
    statement =
      "INSERT INTO STACDB.Enrollment (`UserID`, `ClassID`, `DeviceID`, `DeviceChangeFlag`) VALUES('" +
        std::to_string(userID) + "', '" +
        crn + "', '" +
        deviceID + "', '" +
        deviceFlag + "');";
    stmt = std::unique_ptr<sql::Statement>(con->createStatement());
    stmt->execute(statement);
  }
  catch (sql::SQLException &e) {
    r = 1;
    print_sql_error(std::cout, e);
  }
  return r;
}