// Global Functions - Functions.h
#include "../HeaderFiles/Functions.h"
#include <iostream>
#include <boost/property_tree/json_parser.hpp>


namespace DB
{

namespace FUNCTIONS
{

std::ostream& operator<< (std::ostream& p_stream, DBConfigData const& p_dbConfigData)
{
  p_stream <<
           "db_configFileName = " << p_dbConfigData.m_db_configFileName <<
           ", db_name = " << p_dbConfigData.m_db_name <<
           ", db_username = " << p_dbConfigData.m_db_username <<
           ", db_password = " << p_dbConfigData.m_db_password <<
           ", db_hostname = " << p_dbConfigData.m_db_hostname <<
           ", db_port = " << p_dbConfigData.m_db_port << std::endl;

  return p_stream;
}

void DBConfigControler::readConfigFileAndFillDBConfigData(const std::string& p_configFileName, DBConfigData& p_dbConfigData)
{
  boost::property_tree::ptree content;
  try {
    read_json(p_configFileName, content);

    p_dbConfigData.m_db_configFileName = content.get<std::string>("configFileName");
    p_dbConfigData.m_db_name = content.get<std::string>("db_name");
    p_dbConfigData.m_db_username = content.get<std::string>("db_username");
    p_dbConfigData.m_db_password = content.get<std::string>("db_password");
    p_dbConfigData.m_db_hostname = content.get<std::string>("db_hostname");
    p_dbConfigData.m_db_port = content.get<std::string>("db_port");

  } catch (const std::runtime_error& error) {
    std::string message = "Error opening config file. Error = " + std::string(error.what());
    std::cerr << message << std::endl;
  }
}

} // namespace FUNCTIONS

} // namespace DB
