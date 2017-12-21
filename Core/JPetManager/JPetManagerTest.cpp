#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetManagerTest
#include <boost/test/unit_test.hpp>

#include "./JPetManager/JPetManager.h"

#include "./JPetOptionsGenerator/JPetOptionsGenerator.h"
#include "./JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include <cstdio> //for std::remove

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( create_unique_manager )
{
  JPetManager& manager = JPetManager::getManager();
  JPetManager* pManager = &manager;
  JPetManager& manager2 = JPetManager::getManager(); // it should be the same Manager
  JPetManager* pManager2 = &manager2;

  BOOST_REQUIRE_EQUAL(pManager, pManager2);
}

BOOST_AUTO_TEST_CASE( threadsEnabled )
{
  JPetManager& manager = JPetManager::getManager();
  BOOST_REQUIRE(!manager.areThreadsEnabled());
  manager.setThreadsEnabled(true);
  BOOST_REQUIRE(manager.areThreadsEnabled());
  manager.setThreadsEnabled(false);
  BOOST_REQUIRE(!manager.areThreadsEnabled());
}

BOOST_AUTO_TEST_CASE( manager_getOptions )
{
  JPetManager& manager = JPetManager::getManager();
  auto options = manager.getOptions();
  BOOST_REQUIRE_EQUAL(options.size(), 0u);
}

BOOST_AUTO_TEST_CASE( emptyRun )
{
  JPetManager& manager = JPetManager::getManager();
  BOOST_REQUIRE(!manager.run(0, nullptr));
  auto options = manager.getOptions();
  BOOST_REQUIRE_EQUAL(options.size(), 0u);
}

BOOST_AUTO_TEST_CASE( goodRootRun )
{
  JPetManager& manager = JPetManager::getManager();
  manager.clearRegisteredTasks();
  const char* args[7] = {"test/Path", "--file", "unitTestData/JPetManagerTest/goodRootFile.root", "--type", "root", "-p", "conf_trb3.xml"};
  BOOST_REQUIRE(manager.run(7, args));
}

BOOST_AUTO_TEST_CASE(goodZipRun)
{
  std::remove("unitTestData/JPetManagerTest/xx14099113231.hld");
  JPetManager& manager = JPetManager::getManager();
  manager.clearRegisteredTasks();
  const char* args[14] = {"test/Path", "--file", "unitTestData/JPetManagerTest/xx14099113231.hld.xz", "--type", "zip", "-p", "unitTestData/JPetManagerTest/conf_trb3.xml", "-r", "0", "10", "-l", "unitTestData/JPetManagerTest/large_barrel.json", "-i", "44"};
  BOOST_REQUIRE(manager.run(14, args));
}

BOOST_AUTO_TEST_SUITE_END()
