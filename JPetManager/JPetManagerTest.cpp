#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetManagerTest
#include <boost/test/unit_test.hpp>
#include <boost/any.hpp>
using boost::any_cast;

#include "../JPetManager/JPetManager.h"
#include "../JPetOptionValidator/JPetAdditionalValidators.cpp"
#include "../JPetOptionsGenerator/JPetAdditionalTransformations.cpp"
#include "../JPetCommonTools/JPetCommonTools.h"
//JPetManger
// public methods:
// static JPetManager& getManager();
// ~JPetManager();
// void run();
// void registerTask(const TaskGenerator& taskGen);
// void parseCmdLine(int argc, char** argv);
// inline std::vector<JPetOptions> getOptions() const { return fOptions;}


BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( create_unique_manager )
{
  JPetManager& manager = JPetManager::getManager();
  JPetManager* pManager = &manager;
  JPetManager& manager2 = JPetManager::getManager(); // it should be the same Manager
  JPetManager* pManager2 = &manager2;

  BOOST_REQUIRE_EQUAL(pManager, pManager2);
}

BOOST_AUTO_TEST_CASE( manager_getOptions )
{
  JPetManager& manager = JPetManager::getManager();
  auto options = manager.getOptions();
  BOOST_REQUIRE_EQUAL(options.size(), 0);
}

BOOST_AUTO_TEST_CASE( emptyRun )
{
  JPetManager& manager = JPetManager::getManager();
  BOOST_REQUIRE(manager.run());
  auto options = manager.getOptions();
  BOOST_REQUIRE_EQUAL(options.size(), 0);
}

BOOST_AUTO_TEST_CASE( additionalValidator )
{

  auto commandLine = "main.x -t hld -f unitTestData/JPetCmdParserTest/testfile.hld -i 10";
  auto args_char = JPetCommonTools::createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();


  JPetManager& manager = JPetManager::getManager();
  manager.addValidationFunctionForUserOptions("runId_int", additionalCheckIfRunIdIsOk);
  manager.parseCmdLine(argc, const_cast<const char**>(argv));
  auto options = manager.getOptions();
}


BOOST_AUTO_TEST_CASE( additionalTransformator )
{

  auto commandLine = "main.x -t hld -f unitTestData/JPetCmdParserTest/testfile.hld -i 10";
  auto args_char = JPetCommonTools::createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();


  JPetManager& manager = JPetManager::getManager();
  manager.addTransformationFunctionForUserOption("runId_int", setAdditionalRunIdInTheMap);
  manager.parseCmdLine(argc, const_cast<const char**>(argv));
  auto options = manager.getOptions();
  BOOST_REQUIRE_EQUAL(any_cast<int>(options.front().getOptions().at("additionalRunID_int")), 10);
}

BOOST_AUTO_TEST_SUITE_END()
