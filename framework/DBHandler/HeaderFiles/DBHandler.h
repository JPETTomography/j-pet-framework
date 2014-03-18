// Database Handler - DBHandler.h (Singleton)
#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <pqxx/pqxx>
#include <string>
//#include "../HeaderFiles/Declarations.h"
#include "../HeaderFiles/Functions.h"


namespace DB
{

namespace SERVICES
{

class DBHandler
{
private:
  static DBHandler *m_instance;

public:
  static DBHandler& getInstance(void);
  static void deleteInstance(void);

protected:
  DB::FUNCTIONS::DBConfigData m_dbconfig;
  static DBHandler& getInstanceForTestsDemand(void);//uzywam tej metody w testach bo jest inna sciezka do pliku conf.

private:
  DBHandler(DB::FUNCTIONS::DBConfigData l_dbconfig);
  //DBHandler(void);
  DBHandler(std::string p_db_name,
            std::string p_db_username,
            std::string p_db_password,
            std::string p_db_hostname,
            std::string p_db_port);
  DBHandler(const DBHandler &p_dbHandler) = delete;
  DBHandler(DBHandler &&p_dbHandler) = delete;
  DBHandler& operator=(const DBHandler &p_dbHandler) = delete;
  DBHandler& operator=(DBHandler &&p_dbHandler) = delete;

public:
  virtual ~DBHandler(void);

protected:
  std::string m_db_name;
  std::string m_db_username;
  std::string m_db_password;
  std::string m_db_hostname;
  std::string m_db_port;
  
  std::shared_ptr<pqxx::connection> m_connection; //pqxx::connection *m_connection;
  pqxx::work m_work;

public:
  virtual int connect(void);
  virtual int disconnect(void);
  virtual pqxx::result querry(std::string p_sqlQuerry);
  virtual size_t sizeForQuerry(std::string p_sqlQuerry);
  virtual void commit(void);

  const char* dbName(void) const throw (std::string);
  const char* username(void) const throw (std::string);
  const char* hostname(void) const throw (std::string);
  const char* port(void) const throw (std::string);

  void showDBConfigData(void) const;
};

} // namespace SERVICES

} // namespace DB

#endif // DBHANDLER_H
