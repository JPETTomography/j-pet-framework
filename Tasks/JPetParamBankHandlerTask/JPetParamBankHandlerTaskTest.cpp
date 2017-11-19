#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamBankHandlerTask
#include <boost/test/unit_test.hpp>
#include "./JPetParamBankHandlerTask.h"
#include "./JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "./JPetParams/JPetParams.h"
#include "./JPetParamManager/JPetParamManager.h"
#include "./JPetCommonTools/JPetCommonTools.h"
#include "./JPetParamGetterAscii/JPetParamGetterAscii.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(goodRootFile)
{
  JPetParamBankHandlerTask task;
  auto options = jpet_options_generator_tools::getDefaultOptions();
  options["runId_int"] = -1;
  options["inputFileType_std::string"] = std::string("root");
  options["inputFile_std::string"] = std::string("unitTestData/JPetTaskChainExecutorTest/dabc_17025151847.unk.evt.root");
  std::shared_ptr<JPetParamManager> manager = std::make_shared<JPetParamManager>();
  JPetParams params(options, manager);
  auto& bank = manager->getParamBank();
  BOOST_REQUIRE(bank.isDummy());
  BOOST_REQUIRE(task.init(params));
  auto& bank2 = manager->getParamBank();
  BOOST_REQUIRE(!bank2.isDummy());
}

BOOST_AUTO_TEST_CASE(badRootFile)
{
  JPetParamBankHandlerTask task;
  auto options = jpet_options_generator_tools::getDefaultOptions();
  options["runId_int"] = -1;
  options["inputFileType_std::string"] = std::string("root");
  options["inputFile_std::string"] = std::string("unitTestData/auxdata.root");
  std::shared_ptr<JPetParamManager> manager = std::make_shared<JPetParamManager>();
  JPetParams params(options, manager);
  auto& bank = manager->getParamBank();
  BOOST_REQUIRE(bank.isDummy());
  BOOST_REQUIRE(!task.init(params));
  auto& bank2 = manager->getParamBank();
  BOOST_REQUIRE(bank2.isDummy());
}

BOOST_AUTO_TEST_CASE(badHldFile)
{
  JPetParamBankHandlerTask task;
  auto options = jpet_options_generator_tools::getDefaultOptions();
  //options["runId_int"] = 44;
  //options["localDB_std::string"] = std::string("unitTestData/JPetParamBankHandlerTask/large_barrel.json");
  options["inputFileType_std::string"] = std::string("hld");
  std::shared_ptr<JPetParamManager> manager = std::make_shared<JPetParamManager>();
  JPetParams params(options, manager);
  auto& bank = manager->getParamBank();
  BOOST_REQUIRE(bank.isDummy());
  BOOST_REQUIRE(!task.init(params));
  auto& bank2 = manager->getParamBank();
  BOOST_REQUIRE(bank2.isDummy());
}

BOOST_AUTO_TEST_CASE(goodUnknownFileFromFile)
{
  JPetParamBankHandlerTask task;
  auto options = jpet_options_generator_tools::getDefaultOptions();
  //options["runId_int"] = 44;
  //options["localDB_std::string"] = std::string("unitTestData/JPetParamBankHandlerTask/large_barrel.json");
  options["inputFile_std::string"] = std::string("unitTestData/JPetTaskChainExecutorTest/dabc_17025151847.unk.evt.root");
  options["inputFileType_std::string"] = std::string("unknown");
  std::shared_ptr<JPetParamManager> manager = std::make_shared<JPetParamManager>();
  JPetParams params(options, manager);
  auto& bank = manager->getParamBank();
  BOOST_REQUIRE(bank.isDummy());
  BOOST_REQUIRE(task.init(params));
  auto& bank2 = manager->getParamBank();
  BOOST_REQUIRE(!bank2.isDummy());
}

BOOST_AUTO_TEST_CASE(badUnknownFileFromFile)
{
  JPetParamBankHandlerTask task;
  auto options = jpet_options_generator_tools::getDefaultOptions();
  //options["runId_int"] = 44;
  //options["localDB_std::string"] = std::string("unitTestData/JPetParamBankHandlerTask/large_barrel.json");
  options["inputFile_std::string"] = std::string("unitTestData/auxdata.root");
  options["inputFileType_std::string"] = std::string("unknown");
  std::shared_ptr<JPetParamManager> manager = std::make_shared<JPetParamManager>();
  JPetParams params(options, manager);
  auto& bank = manager->getParamBank();
  BOOST_REQUIRE(bank.isDummy());
  BOOST_REQUIRE(!task.init(params));
  auto& bank2 = manager->getParamBank();
  BOOST_REQUIRE(bank2.isDummy());
}

BOOST_AUTO_TEST_CASE(goodUnknownFileFromConfig)
{
  JPetParamBankHandlerTask task;
  auto options = jpet_options_generator_tools::getDefaultOptions();
  options["runId_int"] = 44;
  options["localDB_std::string"] = std::string("unitTestData/JPetParamBankHandlerTask/large_barrel.json");
  options["inputFile_std::string"] = std::string("unitTestData/auxdata.root");
  options["inputFileType_std::string"] = std::string("unknown");
  std::shared_ptr<JPetParamManager> manager = std::make_shared<JPetParamManager>(new JPetParamGetterAscii("unitTestData/JPetParamBankHandlerTask/large_barrel.json"));
  JPetParams params(options, manager);
  auto& bank = manager->getParamBank();
  BOOST_REQUIRE(bank.isDummy());
  BOOST_REQUIRE(task.init(params));
  auto& bank2 = manager->getParamBank();
  BOOST_REQUIRE(!bank2.isDummy());
}

BOOST_AUTO_TEST_CASE(badUnknownFileFromConfig)
{
  JPetParamBankHandlerTask task;
  auto options = jpet_options_generator_tools::getDefaultOptions();
  options["runId_int"] = 1;
  options["localDB_std::string"] = std::string("unitTestData/JPetParamBankHandlerTask/large_barrel.json");
  options["inputFile_std::string"] = std::string("unitTestData/auxdata.root");
  options["inputFileType_std::string"] = std::string("unknown");
  std::shared_ptr<JPetParamManager> manager = std::make_shared<JPetParamManager>(new JPetParamGetterAscii("unitTestData/JPetParamBankHandlerTask/large_barrel.json"));
  JPetParams params(options, manager);
  auto& bank = manager->getParamBank();
  BOOST_REQUIRE(bank.isDummy());
  BOOST_REQUIRE(task.init(params));
  auto& bank2 = manager->getParamBank();
  BOOST_REQUIRE(!bank2.isDummy());
}

BOOST_AUTO_TEST_CASE(goodHldFile)
{
  JPetParamBankHandlerTask task;
  auto options = jpet_options_generator_tools::getDefaultOptions();
  options["runId_int"] = 44;
  options["localDB_std::string"] = std::string("unitTestData/JPetParamBankHandlerTask/large_barrel.json");
  options["inputFileType_std::string"] = std::string("hld");
  //JPetParamGetterAscii* getter = ;
  std::shared_ptr<JPetParamManager> manager = std::make_shared<JPetParamManager>(new JPetParamGetterAscii("unitTestData/JPetParamBankHandlerTask/large_barrel.json"));
  JPetParams params(options, manager);
  auto& bank = manager->getParamBank();
  BOOST_REQUIRE(bank.isDummy());
  BOOST_REQUIRE(task.init(params));
  auto& bank2 = manager->getParamBank();
  BOOST_REQUIRE(!bank2.isDummy());
}


BOOST_AUTO_TEST_SUITE_END()
