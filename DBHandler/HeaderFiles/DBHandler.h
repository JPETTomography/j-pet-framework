/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file DBHandler.h
 */

#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <pqxx/pqxx>
#include <string>
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
			static void createDBConnection(string configFile);
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
