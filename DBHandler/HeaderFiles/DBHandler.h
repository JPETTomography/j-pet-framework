// Database Handler - DBHandler.h (Singleton)
#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <pqxx/pqxx>
#include <string>
//#include "../HeaderFiles/Declarations.h"
#include "../HeaderFiles/Functions.h"


namespace DB
{
	using namespace std;
	using namespace pqxx;
	namespace SERVICES
	{
		
		class DBHandler
		{
			
		public:
			static DBHandler&getInstance(void);
			static void createInstance(string configFile);
			static void deleteInstance(void);
			
			virtual ~DBHandler(void);
			
			virtual int connect(void);
			virtual int disconnect(void);
			virtual result querry(string p_sqlQuerry);
			virtual size_t sizeForQuerry(string p_sqlQuerry);
			virtual void commit(void);
			
			const char* dbName(void) const throw (string);
			const char* username(void) const throw (string);
			const char* hostname(void) const throw (string);
			const char* port(void) const throw (string);
			
			void showDBConfigData(void) const;
			
		protected:
			DB::FUNCTIONS::DBConfigData m_dbconfig;
			
			string m_db_name;
			string m_db_username;
			string m_db_password;
			string m_db_hostname;
			string m_db_port;
			shared_ptr<connection> m_connection;
			work m_work;
		private:
			static DBHandler* m_instance;
			static const char* kDefaultConfigFile;
			
			DBHandler(DB::FUNCTIONS::DBConfigData l_dbconfig);
			DBHandler(string p_db_name,string p_db_username,string p_db_password,string p_db_hostname,string p_db_port);
			DBHandler(const DBHandler& p_dbHandler) = delete;
			DBHandler(DBHandler&& p_dbHandler) = delete;
			DBHandler& operator=(const DBHandler& p_dbHandler) = delete;
			DBHandler& operator=(DBHandler && p_dbHandler) = delete;
		};
		
	}
}
#endif // DBHANDLER_H
