// Global Functions - Functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <libconfig.h++>
#include <string>
//#include "../HeaderFiles/Declarations.h"
//#include "../HeaderFiles/DBHandler.h"
//#include "../HeaderFiles/ParamServer.h"


namespace DB
{

namespace FUNCTIONS
{

struct DBConfigData
{
  std::string m_db_configFileName;
  std::string m_db_name;
  std::string m_db_username;
  std::string m_db_password;
  std::string m_db_hostname;
  std::string m_db_port;

  friend std::ostream& operator<< (std::ostream &p_stream, DBConfigData const &p_dbConfigData);
};

class DBConfigControler
{
public:
  static void readConfigFileAndFillDBConfigData(std::string p_configFileName, struct DBConfigData &p_dbConfigData);
};

/*void deleteSingletonInstances()
{
  DB::SERVICES::DBHandler::deleteInstance();
}*/

} // namespace FUNCTIONS

} // namespace DB

#endif // FUNCTIONS_H
