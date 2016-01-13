// Global Functions - Functions.h
#include <iostream>
#include "../HeaderFiles/Functions.h"


namespace DB
{

namespace FUNCTIONS
{

std::ostream& operator<< (std::ostream &p_stream, DBConfigData const &p_dbConfigData)
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

void DBConfigControler::readConfigFileAndFillDBConfigData(std::string p_configFileName, DBConfigData &p_dbConfigData)
{
  libconfig::Config cfg;

  try
  {
    cfg.readFile(p_configFileName.c_str());
  }
  catch(const libconfig::FileIOException &fioex)
  {
    std::cerr << "I/O error while reading file." << std::endl;
  }
  catch(const libconfig::ParseException &pex)
  {
    std::cerr << "Parse error" << std::endl;
    //std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
    //          << " - " << pex.getError() << std::endl;
  }

  try
  {
    std::string l_db_configFileName = cfg.lookup("configFileName");
    p_dbConfigData.m_db_configFileName = l_db_configFileName;

    libconfig::Setting &l_settings = cfg.lookup("DBHandler.Configuration");

    std::string l_db_name = l_settings[0]["db_name"];
    p_dbConfigData.m_db_name = l_db_name;

    std::string l_db_username = l_settings[0]["db_username"];
    p_dbConfigData.m_db_username = l_db_username;

    std::string l_db_password = l_settings[0]["db_password"];
    p_dbConfigData.m_db_password = l_db_password;

    std::string l_db_hostname = l_settings[0]["db_hostname"];
    p_dbConfigData.m_db_hostname = l_db_hostname;

    std::string l_db_port = l_settings[0]["db_port"];
    p_dbConfigData.m_db_port = l_db_port;
  }
  catch(const libconfig::SettingNotFoundException &nfex)
  {
    std::cerr << "No 'name' setting in configuration file." << std::endl;
  }
}

} // namespace FUNCTIONS

} // namespace DB
