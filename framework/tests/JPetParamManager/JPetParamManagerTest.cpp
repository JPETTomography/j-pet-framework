#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamManagerTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetParamManager/JPetParamManager.h"

#include <cstddef>

const char* gDefaultConfigFile = "DBConfig/configDB.cfg";

BOOST_AUTO_TEST_SUITE(JPetParamManagerTestSuite)

void checkContainersSize(const JPetParamBank &bank)
{
  BOOST_REQUIRE_EQUAL(bank.getScintillatorsSize(), 2);
  BOOST_REQUIRE_EQUAL(bank.getPMsSize(), 4);
  BOOST_REQUIRE_EQUAL(bank.getPMCalibsSize(), 0);	// It is not 0 for e.g. run_id = 2 - FOR run_id=2 NOT for run_id=1 YES. In test run_id is set to 1 so the size=0
  BOOST_REQUIRE_EQUAL(bank.getFEBsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getTRBsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getBarrelSlotsSize(), 2);
  BOOST_REQUIRE_EQUAL(bank.getTOMBChannelsSize(), 4);
}

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetParamManager paramMgr;
}  

BOOST_AUTO_TEST_CASE(constructor)
{
  JPetParamManager paramMgr(gDefaultConfigFile);
}

BOOST_AUTO_TEST_CASE(generateParamBankTest)
{
  JPetParamManager l_paramManagerInstance(gDefaultConfigFile);
  l_paramManagerInstance.getParametersFromDatabase(1);
  
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.fBank != NULL, true);
  
  checkContainersSize(*l_paramManagerInstance.fBank);
}

BOOST_AUTO_TEST_CASE(writeAndReadDataFromFileByWriterAndReaderObjectsTest)
{
  JPetParamManager l_paramManagerInstance(gDefaultConfigFile);
  
  l_paramManagerInstance.getParametersFromDatabase(1);

  /*  
  const char* testDatafile = "testDataFile.txt";
  JPetWriter writer(testDatafile);
  BOOST_CHECK(l_paramManagerInstance.saveParametersToFile(testDatafile) == true);

  Error in <TFile::ReadBuffer>: error reading all requested bytes from file testDataFile.txt, got 228 of 300
  Error in 	: testDataFile.txt failed to read the file type data.
  Error in <TFile::WriteObject>: File testDataFile.txt is not writable
  */
  
  /*
  JPetReader reader(testDatafile);
  BOOST_CHECK(l_paramManagerInstance.readParametersFromFile(&reader) == true);

  // Errors after writing objects to file and start reading
  Error in <TFile::ReadBuffer>: error reading all requested bytes from file testDataFile.txt, got 228 of 300
  Error in <TFile::Init>: testDataFile.txt failed to read the file type data.
  Error in <TFile::WriteObject>: File testDataFile.txt is not writable
  Error in <TFile::ReadBuffer>: error reading all requested bytes from file testDataFile.txt, got 228 of 300
  Error in <TFile::Init>: testDataFile.txt failed to read the file type data.
  */
}

BOOST_AUTO_TEST_CASE(writeAndReadDataFromFileByFileNameTest)
{
  const char* testDatafile = "testDataFile.txt";
  JPetParamManager l_paramManagerInstance(gDefaultConfigFile);
  
  l_paramManagerInstance.getParametersFromDatabase(1);
  
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.fBank != NULL, true);
  
  BOOST_CHECK(l_paramManagerInstance.saveParametersToFile(testDatafile) == true);
  
  l_paramManagerInstance.fBank->clear();
  
  BOOST_CHECK(l_paramManagerInstance.readParametersFromFile(testDatafile) == true);
  
  checkContainersSize(*l_paramManagerInstance.fBank);
}

BOOST_AUTO_TEST_CASE(clearParametersTest)
{
  JPetParamManager l_paramManagerInstance(gDefaultConfigFile);
  
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
  JPetParamManager l_paramManagerInstance(gDefaultConfigFile);
  
  l_paramManagerInstance.getParametersFromDatabase(1);
  
  const JPetParamBank &bank = l_paramManagerInstance.getParamBank();
  
  checkContainersSize(bank);
}

BOOST_AUTO_TEST_SUITE_END()
