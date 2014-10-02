// Database Handler Test Suite - DBHandlerTestSuite.cpp
#ifndef DBHANDLER_TESTSUITE_H
#define DBHANDLER_TESTSUITE_H

#define BOOST_TEST_MODULE DBHandlerTestSuite
#include <boost/test/included/unit_test.hpp>
//#include "../HeaderFiles/DBHandler.h"
#include "DBHandlerHelper.cpp"


namespace DB
{

namespace TEST
{

int g_runIdToInsertQuerry = 0;
int g_runSizeBeforeInsert = 0;


struct ConfigDataHelper
{
  std::string l_dbConfigDataFileName;
  DB::FUNCTIONS::DBConfigData l_dbConfigData;

  ConfigDataHelper(void);
  void readConfigFileAndFillDBConfigData();
};


ConfigDataHelper::ConfigDataHelper() : l_dbConfigDataFileName("../../Config/configDB.cfg")
{
  readConfigFileAndFillDBConfigData();
}

void ConfigDataHelper::readConfigFileAndFillDBConfigData()
{
  DB::FUNCTIONS::DBConfigControler::readConfigFileAndFillDBConfigData(l_dbConfigDataFileName, l_dbConfigData);
}


class DBHandlerTestSuite
{
protected:
  SERVICES::DBHandler &m_dbHandlerInstance; // UWAGA
  ConfigDataHelper m_configDataHelper;

public:
  DBHandlerTestSuite(void);
  ~DBHandlerTestSuite(void);

protected:
  void operationOnFakeRow(int p_runId, std::string p_fakeQuerry);
  int checkTableSize(std::string p_tableName) const;
};

DBHandlerTestSuite::DBHandlerTestSuite() : m_dbHandlerInstance(DBHandlerHelper::getInstance("../../Config/configDB.cfg")) // UWAGA
{
}

DBHandlerTestSuite::~DBHandlerTestSuite()
{
}

void DBHandlerTestSuite::operationOnFakeRow(int p_runId, std::string p_fakeQuerry)
{
  g_runIdToInsertQuerry = p_runId;
  pqxx::result l_sqlResults = m_dbHandlerInstance.querry(p_fakeQuerry);
  //m_dbHandlerInstance.commit(); // wytlumaczone dlaczego zakomentowane w notatce 08.02.14
  size_t l_sqlResultSize = l_sqlResults.size();
  BOOST_CHECK(l_sqlResultSize == 0);
}

int DBHandlerTestSuite::checkTableSize(std::string p_tableName) const
{
  //std::string l_sqlQuerry = "SELECT * FROM \"" + p_tableName + "\"";
  //size_t l_sizeForRunResults = m_dbHandlerInstance.sizeForQuerry(l_sqlQuerry);

  std::string l_sqlQuerry = "SELECT * FROM sizeOfTableFunction('" + p_tableName + "');";
  pqxx::result l_querryResult = m_dbHandlerInstance.querry(l_sqlQuerry);
  pqxx::result::const_iterator row = l_querryResult.begin();
  int l_sizeoftablefunction = row["sizeoftablefunction"].as<int>();

  return l_sizeoftablefunction;
}

// Tests
BOOST_AUTO_TEST_SUITE(DBHandlerTS)

BOOST_FIXTURE_TEST_CASE(establishConnectionTest, DBHandlerTestSuite)
{
  BOOST_CHECK(m_dbHandlerInstance.connect() == 0);

  g_runSizeBeforeInsert = checkTableSize("Run");
}

BOOST_FIXTURE_TEST_CASE(sqlInsertQuerryTest, DBHandlerTestSuite)
{
  std::string l_sqlQuerry = "SELECT id from \"Run\" ORDER BY id DESC LIMIT 1;";
  pqxx::result l_sqlResults = m_dbHandlerInstance.querry(l_sqlQuerry);
  size_t l_sqlResultSize = l_sqlResults.size();

  int l_runIdToInsertQuerry = 0;

  if(l_sqlResultSize == 1)
  {
    int l_biggestRunId = l_sqlResults.begin()["id"].as<int>();
    BOOST_REQUIRE(l_biggestRunId >= 1);

    l_runIdToInsertQuerry = (l_biggestRunId + 1);
  }
  else
  {
    l_runIdToInsertQuerry = 1;
  }

  BOOST_REQUIRE(l_runIdToInsertQuerry >= 1);

  // Get existing id from "Setup" otherwise stop testing
  l_sqlQuerry = "SELECT id from \"Setup\" LIMIT 1;";
  l_sqlResults = m_dbHandlerInstance.querry(l_sqlQuerry);
  l_sqlResultSize = l_sqlResults.size();

  int l_setupIdToInsertQuerry = 0;

  if(l_sqlResultSize == 1)
  {
    l_setupIdToInsertQuerry = l_sqlResults.begin()["id"].as<int>();
  }
  else
  {
    /*ERROR:  insert or update on table "Run" violates foreign key constraint "fk1426b4acd263"
    DETAIL:  Key (setup_id)=( "l_setupIdToInsertQuerry" ) is not present in table "Setup".*/
    exit(EXIT_FAILURE);
  }

  BOOST_REQUIRE(l_setupIdToInsertQuerry >= 1);

  std::stringstream l_sqlInsertQuerry;
  l_sqlInsertQuerry << "INSERT INTO \"Run\" VALUES(" << l_runIdToInsertQuerry << ", '2014-01-19', 'filepath', 'run test', 'first run', " << l_setupIdToInsertQuerry << ", 1, 1, 1);";
  operationOnFakeRow(l_runIdToInsertQuerry, l_sqlInsertQuerry.str());
}

BOOST_FIXTURE_TEST_CASE(sizeForQuerryTest, DBHandlerTestSuite)
{
  std::string l_sqlQuerry = "SELECT * FROM \"Run\"";
  size_t l_sizeForRunResults = m_dbHandlerInstance.sizeForQuerry(l_sqlQuerry);

  BOOST_CHECK(l_sizeForRunResults == static_cast<unsigned int>(g_runSizeBeforeInsert + 1));
}

BOOST_FIXTURE_TEST_CASE(sqlDeleteQuerryTest, DBHandlerTestSuite)
{
  std::string l_sqlQuerry = "SELECT id from \"Run\";";
  pqxx::result l_sqlResults = m_dbHandlerInstance.querry(l_sqlQuerry);
  size_t l_sqlResultSize = l_sqlResults.size();

  BOOST_REQUIRE(l_sqlResultSize >= 1);

  if(g_runIdToInsertQuerry > 0)
  {
    std::stringstream l_sqlDeleteQuerry;
    l_sqlDeleteQuerry << "DELETE FROM \"Run\" WHERE id=" << g_runIdToInsertQuerry << ";";
    operationOnFakeRow(0, l_sqlDeleteQuerry.str());
  }
}

BOOST_FIXTURE_TEST_CASE(dbNameTest, DBHandlerTestSuite)
{
  const char* l_dbName = m_dbHandlerInstance.dbName();
  BOOST_CHECK( strcmp(l_dbName, (m_configDataHelper.l_dbConfigData.m_db_name).c_str()) == 0 );
}

BOOST_FIXTURE_TEST_CASE(usernameTest, DBHandlerTestSuite)
{
  const char* l_username = m_dbHandlerInstance.username();
  BOOST_CHECK( strcmp(l_username, (m_configDataHelper.l_dbConfigData.m_db_username).c_str()) == 0 );
}

BOOST_FIXTURE_TEST_CASE(hostnameTest, DBHandlerTestSuite)
{
  const char* l_hostname = m_dbHandlerInstance.hostname();
  BOOST_CHECK( strcmp(l_hostname, (m_configDataHelper.l_dbConfigData.m_db_hostname).c_str()) == 0 );
}

BOOST_FIXTURE_TEST_CASE(portTest, DBHandlerTestSuite)
{
  const char* l_port = m_dbHandlerInstance.port();
  BOOST_CHECK( strcmp(l_port, (m_configDataHelper.l_dbConfigData.m_db_port).c_str()) == 0 );
}

BOOST_FIXTURE_TEST_CASE(commitAfterAllTests, DBHandlerTestSuite)
{
  m_dbHandlerInstance.commit(); // przy zalozeniu ze zawsze wykona sie ten test jako ostatni-potem jeszcze tylko disconnect()
}

BOOST_FIXTURE_TEST_CASE(disconnectionSuccessfulCase, DBHandlerTestSuite)
{
  BOOST_CHECK(m_dbHandlerInstance.disconnect() == 0);
}


BOOST_AUTO_TEST_SUITE_END()

} // namespace TEST

} // namespace DB

#endif // DBHANDLER_TESTSUITE_H
