#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamManagerTest
#include <cstddef>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include "../JPetParamManager/JPetParamManager.h"
#include "../JPetParamGetterAscii/JPetParamGetterAscii.h"
#include <string>

const std::string dataDir = "unitTestData/JPetParamManagerTest/";
const std::string dataFileName = dataDir + "data.json";

BOOST_AUTO_TEST_SUITE(JPetParamManagerTestSuite)

BOOST_AUTO_TEST_CASE(generateParamManager)
{
  std::map<std::string, boost::any> emptyOpts;
  auto paramMgr = JPetParamManager::generateParamManager(emptyOpts);
  BOOST_REQUIRE(paramMgr);
  BOOST_REQUIRE(!paramMgr->isNullObject());
}

BOOST_AUTO_TEST_CASE(generateParamManagerForScopeCase)
{
  std::map<std::string, boost::any> opts;
  opts["inputFileType_std::string"] = std::string("scope");
  opts["localDB_std::string"] = std::string("unitTestData/JPetScopeLoaderTest/test_params.json");
  opts["runId_int"] = int(1);
  std::shared_ptr<JPetParamManager> paramMgr = JPetParamManager::generateParamManager(opts);
  BOOST_REQUIRE(paramMgr);
  BOOST_REQUIRE(!paramMgr->isNullObject());
  BOOST_REQUIRE(!paramMgr->getExpectMissing().empty());
  paramMgr->fillParameterBank(1);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().isDummy(), false);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getScintillatorsSize(), 2);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getPMsSize(), 4);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getFEBsSize(), 0);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getTRBsSize(), 0);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getBarrelSlotsSize(), 2);
  BOOST_REQUIRE_EQUAL(paramMgr->getParamBank().getTOMBChannelsSize(), 0);
}


void checkContainersSize(const JPetParamBank& bank)
{
  JPetDBParamGetter::clearParamCache();
  BOOST_REQUIRE_EQUAL(bank.getScintillatorsSize(), 2);
  BOOST_REQUIRE_EQUAL(bank.getPMsSize(), 4);
  BOOST_REQUIRE_EQUAL(bank.getFEBsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getTRBsSize(), 1);
  BOOST_REQUIRE_EQUAL(bank.getBarrelSlotsSize(), 2);
  BOOST_REQUIRE_EQUAL(bank.getTOMBChannelsSize(), 4);
}

BOOST_AUTO_TEST_CASE(default_constructor)
{
  JPetDBParamGetter::clearParamCache();
  JPetParamManager paramMgr;
  BOOST_REQUIRE(paramMgr.getExpectMissing().empty());
}
BOOST_AUTO_TEST_CASE(generateParamBankTest)
{
  JPetDBParamGetter::clearParamCache();
  JPetParamManager l_paramManagerInstance(new JPetParamGetterAscii(dataFileName));
  l_paramManagerInstance.fillParameterBank(1);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().isDummy(), false);

  checkContainersSize(l_paramManagerInstance.getParamBank());
  BOOST_REQUIRE(l_paramManagerInstance.getExpectMissing().empty());
}

// BOOST_AUTO_TEST_CASE(writeAndReadDataFromFileByWriterAndReaderObjectsTest)
// {
//  DB::SERVICES::DBHandler::createDBConnection(gDefaultConfigFile);
//
//   JPetParamManager l_paramManagerInstance;
//
//   l_paramManagerInstance.getParametersFromDatabase(1);
//
//   const char* testDatafile = "testDataFile.txt";
//   JPetWriter writer(testDatafile);
//   BOOST_CHECK(l_paramManagerInstance.saveParametersToFile(testDatafile) == true);
//
//   JPetReader reader(testDatafile);
//   BOOST_CHECK(l_paramManagerInstance.readParametersFromFile(&reader) == true);
// }

BOOST_AUTO_TEST_CASE(writeAndReadDataFromFileByFileNameTest)
{
  JPetDBParamGetter::clearParamCache();
  std::string testDatafile = dataDir + "testDataFile.txt";
  JPetParamManager l_paramManagerInstance(new JPetParamGetterAscii(dataFileName));


  l_paramManagerInstance.fillParameterBank(1);

  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().isDummy(), false);

  BOOST_CHECK(l_paramManagerInstance.saveParametersToFile(testDatafile) == true);

  boost::filesystem::remove(testDatafile);
}

BOOST_AUTO_TEST_CASE(some_Test_that_had_no_name)
{
  JPetDBParamGetter::clearParamCache();

  JPetParamManager l_paramManagerInstance(new JPetParamGetterAscii(dataFileName));

  l_paramManagerInstance.fillParameterBank(1);

  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().isDummy(), false);

  checkContainersSize(l_paramManagerInstance.getParamBank());

  l_paramManagerInstance.clearParameters();

  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getScintillatorsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getPMsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getFEBsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getTRBsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getBarrelSlotsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getTOMBChannelsSize(), 0);
}

BOOST_AUTO_TEST_CASE(getParamBankTest)
{
  JPetDBParamGetter::clearParamCache();

  JPetParamManager l_paramManagerInstance(new JPetParamGetterAscii(dataFileName));

  l_paramManagerInstance.fillParameterBank(1);

  const JPetParamBank& bank = l_paramManagerInstance.getParamBank();

  checkContainersSize(bank);
}

BOOST_AUTO_TEST_CASE(getParamBankTestWithScopeSettings)
{
  JPetDBParamGetter::clearParamCache();

  std::set<ParamObjectType> expectMissing;
  expectMissing.insert(ParamObjectType::kTRB);
  expectMissing.insert(ParamObjectType::kFEB);
  expectMissing.insert(ParamObjectType::kFrame);
  expectMissing.insert(ParamObjectType::kLayer);
  expectMissing.insert(ParamObjectType::kTOMBChannel);

  const std::string dataFileNameWithScope("unitTestData/JPetScopeLoaderTest/test_params.json");
  JPetParamManager l_paramManagerInstance(new JPetParamGetterAscii(dataFileNameWithScope), expectMissing);

  l_paramManagerInstance.fillParameterBank(1);

  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().isDummy(), false);
  BOOST_REQUIRE(!l_paramManagerInstance.getExpectMissing().empty());

  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getScintillatorsSize(), 2);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getPMsSize(), 4);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getFEBsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getTRBsSize(), 0);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getBarrelSlotsSize(), 2);
  BOOST_REQUIRE_EQUAL(l_paramManagerInstance.getParamBank().getTOMBChannelsSize(), 0);

}
BOOST_AUTO_TEST_SUITE_END()
