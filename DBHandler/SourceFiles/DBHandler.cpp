// Database Handler - DBHandler.cpp
#include <iostream>
#include <fstream>
#include "../HeaderFiles/DBHandler.h"


namespace DB
{

namespace SERVICES
{

DBHandler* DBHandler::m_instance = nullptr;
const char* DBHandler::kDefaultConfigFile ="../../DBConfig/configDB.cfg"; ///@todo add description somewhere

/// function invokes the configuration file only if the getInstance is invoked for the first time
DBHandler& DBHandler::getInstance(const char* configFile)  {
  if(m_instance == nullptr)
  {
    FUNCTIONS::DBConfigData l_dbconfig;
    FUNCTIONS::DBConfigControler::readConfigFileAndFillDBConfigData(configFile, l_dbconfig);

    m_instance = new DBHandler(l_dbconfig);
  }
  return *m_instance;
}


DBHandler& DBHandler::getInstance()
{
  return getInstance(kDefaultConfigFile);
}

void DBHandler::deleteInstance()
{
  if(m_instance != nullptr)
  {
    delete m_instance;
    m_instance = nullptr;
  }
}


DBHandler::DBHandler(FUNCTIONS::DBConfigData p_dbconfig) :
                                                              m_dbconfig(p_dbconfig),
                                                              m_db_name(p_dbconfig.m_db_name),
                                                              m_db_username(p_dbconfig.m_db_username),
                                                              m_db_password(p_dbconfig.m_db_password),
                                                              m_db_hostname(p_dbconfig.m_db_hostname),
                                                              m_db_port(p_dbconfig.m_db_port),
                                                              m_connection(new pqxx::connection("dbname="+m_db_name+" user="+m_db_username+ " password="+m_db_password+" host="+m_db_hostname+" port="+m_db_port)),
                                                              m_work(*m_connection)
{
}

/*DBHandler::DBHandler() :
                        m_db_name("..."),
                        m_db_username("..."),
                        m_db_password("..."),
                        m_db_hostname("..."),
                        m_db_port("..."),
                        m_connection(new pqxx::connection("dbname="+m_db_name+" user="+m_db_username+ " password="+m_db_password+" host="+m_db_hostname+" port="+m_db_port)),
                        m_work(*m_connection)
{
}*/

DBHandler::DBHandler(std::string p_db_name,
                     std::string p_db_username,
                     std::string p_db_password,
                     std::string p_db_hostname,
                     std::string p_db_port) :
                                             m_db_name(p_db_name),
                                             m_db_username(p_db_username),
                                             m_db_password(p_db_password),
                                             m_db_hostname(p_db_hostname),
                                             m_db_port(p_db_port),
                                             m_connection(new pqxx::connection("dbname="+p_db_name+" user="+p_db_username+ " password="+p_db_password+" host="+p_db_hostname+" port="+p_db_port)),
                                             m_work(*m_connection)
{
}

DBHandler::~DBHandler()
{
}

int DBHandler::connect()
{
  try
  {  
    if(m_connection->is_open())
    {
      std::cout << "Opened database successfully: " << m_connection->dbname() << std::endl;
    }
    else
    {
      std::cout << "Can't open database" << std::endl;
      return 1;
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  
  return 0;
}

int DBHandler::disconnect()
{
  try
  {  
    if(m_connection->is_open())
    {
      //m_connection->disconnect();
      m_connection->deactivate();
      //m_work.commit();
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  
  return 0;
}

pqxx::result DBHandler::querry(std::string p_sqlQuerry)
{
  pqxx::result l_result;
  
  try
  {
    if( !m_connection->is_open() )
    {
      connect();
    }

    l_result = m_work.exec(p_sqlQuerry);
    //m_work.commit(); // wytlumaczone dlaczego zakomentowane w notatkach
  }
  catch(const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    return pqxx::result();
  }
  
  return l_result;
}

size_t DBHandler::sizeForQuerry(std::string p_sqlQuerry)
{
  return querry(p_sqlQuerry).size();
}

void DBHandler::commit()
{
  m_work.commit();
}

const char* DBHandler::dbName() const throw (std::string)
{
  const char *l_dbName = m_connection->dbname();
  
  if(l_dbName)
  {
    return l_dbName;
  }
  throw std::string("No database name");
}

const char* DBHandler::username() const throw (std::string)
{
  const char *l_dbUsername = m_connection->username();

  if(l_dbUsername)
  {
    return l_dbUsername;
  }
  throw std::string("No database username");
}

const char* DBHandler::hostname() const throw (std::string)
{
  const char *l_dbHostname = m_connection->hostname();

  if(l_dbHostname)
  {
    return l_dbHostname;
  }
  throw std::string("No database hostname");
}

const char* DBHandler::port() const throw (std::string)
{
  const char *l_dbPort = m_connection->port();

  if(l_dbPort)
  {
    return l_dbPort;
  }
  throw std::string("No database port");
}

void DBHandler::showDBConfigData() const
{
  std::cout << m_dbconfig;
}

}	// namespace DATA

}	// namespace DB

// usunac
/*void DBHandler::insertIntoTableMyTab(int l_id, std::string l_name, int l_age)
{
  std::string l_querry = "INSERT INTO mytab(id, name, age) VALUES(" +
        m_work.quote(l_id) + ", " +
        m_work.quote(l_name) + ", " +
        m_work.quote(l_age) +
        ")";

  pqxx::transaction_base &l_txn = m_work;
  l_txn.exec(l_querry);
  l_txn.commit();

  //querry("INSERT INTO mytab VALUES(1, 'Jonh', 25);");
}*/
