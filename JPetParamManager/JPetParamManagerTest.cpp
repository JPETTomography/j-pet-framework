#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamManagerTest
#include <cstddef>
#include <boost/test/unit_test.hpp>
#include "../DBHandler/HeaderFiles/DBHandler.h"
#include "../JPetParamManager/JPetParamManager.h"

const char* gDefaultConfigFile = "../DBConfig/configDB.cfg";

BOOST_AUTO_TEST_SUITE(JPetParamManagerTestSuite)

void checkContainersSize(const JPetParamBank &bank)
{
  BOOST_REQUIRE_EQUAL(bank.getScintillatorsSize(), 2);
  BOOST_REQUIRE_EQUAL(bank.getPMsSize(), 4);
  BOOST_REQUIRE_EQUAL(bank.getPMCalibsSize(), 0);// It is not 0 for e.g. run_id = 2 - FOR run_id=2 NOT for run_id=1 YES. In test run_id is set to 1 so the size=0
  BOOST_REQUIRE_EQUAL(bank.getFEBsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getTRBsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getBarrelSlotsSize(), 2);
  BOOST_REQUIRE_EQUAL(bank.getTOMBChannelsSize(), 4);
}

BOOST_AUTO_TEST_CASE(default_constructor)
{
	DB::SERVICES::DBHandler::createDBConnection(gDefaultConfigFile);
	JPetParamManager paramMgr;
}  

//ToDo: remake this tests without calling private methods
/*
BOOST_AUTO_TEST_CASE(generateParamBankTest)
{
	DB::SERVICES::DBHandler::createDBConnection(gDefaultConfigFile);
	
  JPetParamManager l_paramManagerInstance;
  l_paramManagerInstance.getParametersFromDatabase(1);
  
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.fBank != NULL, true);
  
  checkContainersSize(*l_paramManagerInstance.fBank);
}

BOOST_AUTO_TEST_CASE(writeAndReadDataFromFileByWriterAndReaderObjectsTest)
{
	DB::SERVICES::DBHandler::createDBConnection(gDefaultConfigFile);
	
  JPetParamManager l_paramManagerInstance;
  
  l_paramManagerInstance.getParametersFromDatabase(1);

  const char* testDatafile = "testDataFile.txt";
  JPetWriter writer(testDatafile);
  BOOST_CHECK(l_paramManagerInstance.saveParametersToFile(testDatafile) == true);
  
  JPetReader reader(testDatafile);
  BOOST_CHECK(l_paramManagerInstance.readParametersFromFile(&reader) == true);
}

BOOST_AUTO_TEST_CASE(writeAndReadDataFromFileByFileNameTest)
{
  const char* testDatafile = "testDataFile.txt";
  DB::SERVICES::DBHandler::createDBConnection(gDefaultConfigFile);
  
  JPetParamManager l_paramManagerInstance;
  
  l_paramManagerInstance.getParametersFromDatabase(1);
  
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.fBank != NULL, true);
  
  BOOST_CHECK(l_paramManagerInstance.saveParametersToFile(testDatafile) == true);
  
  l_paramManagerInstance.fBank->clear();
  
  BOOST_CHECK(l_paramManagerInstance.readParametersFromFile(testDatafile) == true);
  
  checkContainersSize(*l_paramManagerInstance.fBank);
}

BOOST_AUTO_TEST_CASE(clearParametersTest)
{
	DB::SERVICES::DBHandler::createDBConnection(gDefaultConfigFile);
	
  JPetParamManager l_paramManagerInstance;
  
  l_paramManagerInstance.getParametersFromDatabase(1);
  
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.fBank != NULL, true);
  
  checkContainersSize(*l_paramManagerInstance.fBank);
  
  l_paramManagerInstance.clearParameters();
  
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.fBank->getScintillatorsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.fBank->getPMsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.fBank->getPMCalibsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.fBank->getFEBsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.fBank->getTRBsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.fBank->getBarrelSlotsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.fBank->getTOMBChannelsSize(), 0);
}

BOOST_AUTO_TEST_CASE(getParamBankTest)
{
	DB::SERVICES::DBHandler::createDBConnection(gDefaultConfigFile);
	
  JPetParamManager l_paramManagerInstance;
  
  l_paramManagerInstance.getParametersFromDatabase(1);
  
  const JPetParamBank &bank = l_paramManagerInstance.getParamBank();
  
  checkContainersSize(bank);
}
*/
BOOST_AUTO_TEST_SUITE_END()
