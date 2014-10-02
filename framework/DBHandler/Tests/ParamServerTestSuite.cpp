// Param Server Test Suite - ParamServer.h (Parameter Server)
#ifndef PARAMSERVER_TESTSUITE_H
#define PARAMSERVER_TESTSUITE_H

#define BOOST_TEST_MODULE ParamServerTestSuite

#define SHOW_DEBUG 0

#include <boost/test/included/unit_test.hpp>
#include "../HeaderFiles/ParamServer.h"
#include "DBHandlerHelper.cpp"
//#include "ParamServerHelper.cpp"


namespace DB
{

namespace TEST
{

class ParamServerTestSuite
{
protected:
  SERVICES::DBHandler &m_dbHandlerInstance;
  SERVER::ParamServer *m_paramServer;

public:
  ParamServerTestSuite(void);
  ~ParamServerTestSuite(void);

protected:
  inline bool ifFileExists(std::string p_fileName)
  {
    std::ifstream l_file(p_fileName.c_str());
    return l_file;
  }
};


ParamServerTestSuite::ParamServerTestSuite() :
                                              m_dbHandlerInstance(DBHandlerHelper::getInstance("../../Config/configDB.cfg")), // UWAGA
                                              m_paramServer(new SERVER::ParamServer(DBHandlerHelper::getInstance("../../Config/configDB.cfg")))
{
}

ParamServerTestSuite::~ParamServerTestSuite()
{
  delete m_paramServer;
  DB::SERVICES::DBHandler::deleteInstance();  // do przemyslenia!
}

// Tests
BOOST_AUTO_TEST_SUITE(ParamServerTS)

BOOST_FIXTURE_TEST_CASE(runInformationTest, ParamServerTestSuite)
{
#if SHOW_DEBUG
  std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
#endif

  std::string l_sqlQuerry = "SELECT * FROM runDataFunction();";
  pqxx::result l_runDbResults = m_dbHandlerInstance.querry(l_sqlQuerry);
  size_t l_sqlResultsSize = l_runDbResults.size();

  if(l_sqlResultsSize)
  {
    pqxx::result::const_iterator row = l_runDbResults.begin();
    int l_runId = row["run_id"].as<int>();
    std::string l_runStart = row["runstart"].as<std::string>();
    std::string l_filePath = row["filepath"].as<std::string>();
    std::string l_runDescription = row["rundescription"].as<std::string>();
    std::string l_information = row["information"].as<std::string>();

    DATA::RunData l_runData = *m_paramServer->runInformation(l_runId);

  #if SHOW_DEBUG
    std::cout << l_runData;
  #endif

    BOOST_CHECK(l_runData.runStart() == l_runStart);
    BOOST_CHECK(l_runData.filePath() == l_filePath);
    BOOST_CHECK(l_runData.runDescription() == l_runDescription);
    BOOST_CHECK(l_runData.information() == l_information);
  }
}

BOOST_FIXTURE_TEST_CASE(paramServerConstructorWithRunIdTest, ParamServerTestSuite)
{
#if SHOW_DEBUG
  std::cout << "TEST = " << boost::unit_test::framework::current_test_case().p_name << std::endl;
#endif

  std::string l_sqlQuerry = "SELECT * FROM runDataFunction();";
  pqxx::result l_runDbResults = m_dbHandlerInstance.querry(l_sqlQuerry);
  size_t l_sqlResultsSize = l_runDbResults.size();

  if(l_sqlResultsSize)
  {
    pqxx::result::const_iterator row = l_runDbResults.begin();
    int l_runId = row["run_id"].as<int>();

    DB::SERVER::ParamServer l_paramServer(l_runId);
    BOOST_CHECK(l_paramServer.photoMultiplier_Map().empty() == false);
    BOOST_CHECK(l_paramServer.runData_Map().empty() == false);
    BOOST_CHECK(l_paramServer.TRBThreshold_Map().empty() == false);
    BOOST_CHECK(l_paramServer.photoMultiplierId_Map().empty() == false);
    BOOST_CHECK(l_paramServer.TOMBInput_Map().empty() == false);
    BOOST_CHECK(l_paramServer.passedInformation_Map().empty() == false);
  }
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace TEST

} // namespace DB

#endif // PARAMSERVER_TESTSUITE_H
