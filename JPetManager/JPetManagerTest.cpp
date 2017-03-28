#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetManagerTest
#include <boost/test/unit_test.hpp>


#include "../JPetManager/JPetManager.h"


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
  BOOST_REQUIRE_EQUAL(options.size(), 0u);
}

BOOST_AUTO_TEST_CASE( emptyRun )
{
  JPetManager& manager = JPetManager::getManager();
  BOOST_REQUIRE(manager.run());
  auto options = manager.getOptions();
  BOOST_REQUIRE_EQUAL(options.size(), 0u);
}

BOOST_AUTO_TEST_SUITE_END()
