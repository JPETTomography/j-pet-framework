// Database Handler - DBHandler.cpp
#include <iostream>
#include <fstream>
#include "../HeaderFiles/DBHandler.h"

using namespace std;
using namespace pqxx;
namespace DB
{
	
	namespace SERVICES
	{
		
		DBHandler* DBHandler::m_instance = nullptr;
		const char* DBHandler::kDefaultConfigFile ="../DBConfig/configDB.cfg"; ///@todo add description somewhere
		
		void DBHandler::createInstance(string configFile){
			deleteInstance();
			FUNCTIONS::DBConfigData l_dbconfig;
			FUNCTIONS::DBConfigControler::readConfigFileAndFillDBConfigData(configFile, l_dbconfig);
			m_instance = new DBHandler(l_dbconfig);
		}
		DBHandler& DBHandler::getInstance(){
			if(m_instance)
				return *m_instance;
			throw string("");
		}
		
		void DBHandler::deleteInstance()
		{
			if(nullptr != m_instance)
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
		m_connection(new connection("dbname="+m_db_name+" user="+m_db_username+ " password="+m_db_password+" host="+m_db_hostname+" port="+m_db_port)),
		m_work(*m_connection)
		{
		}
		
		DBHandler::DBHandler(string p_db_name,
				     string p_db_username,
		       string p_db_password,
		       string p_db_hostname,
		       string p_db_port) :
		       m_db_name(p_db_name),
		       m_db_username(p_db_username),
		       m_db_password(p_db_password),
		       m_db_hostname(p_db_hostname),
		       m_db_port(p_db_port),
		       m_connection(new connection("dbname="+p_db_name+" user="+p_db_username+ " password="+p_db_password+" host="+p_db_hostname+" port="+p_db_port)),
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
					       cout << "Opened database successfully: " << m_connection->dbname() << endl;
				       }
				       else
				       {
					       cout << "Can't open database" << endl;
					       return 1;
				       }
			       }
			       catch (const exception &e)
			       {
				       cerr << e.what() << endl;
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
			       catch (const exception &e)
			       {
				       cerr << e.what() << endl;
				       return 1;
			       }
			       
			       return 0;
		       }
		       
		       pqxx::result DBHandler::querry(string p_sqlQuerry)
		       {
			       result l_result;
			       
			       try
			       {
				       if( !m_connection->is_open() )
				       {
					       connect();
				       }
				       
				       l_result = m_work.exec(p_sqlQuerry);
				       //m_work.commit(); // wytlumaczone dlaczego zakomentowane w notatkach
			       }
			       catch(const exception &e)
			       {
				       cerr << e.what() << endl;
				       return result();
			       }
			       
			       return l_result;
		       }
		       
		       size_t DBHandler::sizeForQuerry(string p_sqlQuerry)
		       {
			       return querry(p_sqlQuerry).size();
		       }
		       
		       void DBHandler::commit()
		       {
			       m_work.commit();
		       }
		       
		       const char* DBHandler::dbName() const throw (string)
		       {
			       const char *l_dbName = m_connection->dbname();
			       
			       if(l_dbName)
			       {
				       return l_dbName;
			       }
			       throw string("No database name");
		       }
		       
		       const char* DBHandler::username() const throw (string)
		       {
			       const char *l_dbUsername = m_connection->username();
			       
			       if(l_dbUsername)
			       {
				       return l_dbUsername;
			       }
			       throw string("No database username");
		       }
		       
		       const char* DBHandler::hostname() const throw (string)
		       {
			       const char *l_dbHostname = m_connection->hostname();
			       
			       if(l_dbHostname)
			       {
				       return l_dbHostname;
			       }
			       throw string("No database hostname");
		       }
		       
		       const char* DBHandler::port() const throw (string)
		       {
			       const char *l_dbPort = m_connection->port();
			       
			       if(l_dbPort)
			       {
				       return l_dbPort;
			       }
			       throw string("No database port");
		       }
		       
		       void DBHandler::showDBConfigData() const
		       {
			       cout << m_dbconfig;
		       }
		       
	}
	
}
