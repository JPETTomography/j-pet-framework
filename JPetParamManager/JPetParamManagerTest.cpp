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

BOOST_AUTO_TEST_CASE(generateParamBankTest)
{
	DB::SERVICES::DBHandler::createDBConnection(gDefaultConfigFile);
	
  JPetParamManager l_paramManagerInstance;
  l_paramManagerInstance.getParametersFromDatabase(1);
  
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().isDummy(), false);
  
  checkContainersSize(l_paramManagerInstance.getParamBank());
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
  
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().isDummy(), false);
  
  BOOST_CHECK(l_paramManagerInstance.saveParametersToFile(testDatafile) == true);
}

BOOST_AUTO_TEST_CASE(some_Test_that_had_no_name)
{
	DB::SERVICES::DBHandler::createDBConnection(gDefaultConfigFile);
	
  JPetParamManager l_paramManagerInstance;
  
  l_paramManagerInstance.getParametersFromDatabase(1);
  
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().isDummy(),false);
  
  checkContainersSize(l_paramManagerInstance.getParamBank());
  
  l_paramManagerInstance.clearParameters();
  
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getScintillatorsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getPMsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getPMCalibsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getFEBsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getTRBsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getBarrelSlotsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getTOMBChannelsSize(), 0);
}

BOOST_AUTO_TEST_CASE(getParamBankTest)
{
	DB::SERVICES::DBHandler::createDBConnection(gDefaultConfigFile);
	
  JPetParamManager l_paramManagerInstance;
  
  l_paramManagerInstance.getParametersFromDatabase(1);
  
  const JPetParamBank &bank = l_paramManagerInstance.getParamBank();
  
  checkContainersSize(bank);
}
BOOST_AUTO_TEST_SUITE_END()
