#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetManagerTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetManager/JPetManager.h"

//JPetManger
// public methods:
//   static JPetManager& GetManager();
//   ~JPetManager();
//   void Init();
//   void Run();
//   void AddTask(JPetAnalysisModule* mod);
             
BOOST_AUTO_TEST_SUITE(FirstSuite)
  
BOOST_AUTO_TEST_CASE( create_unique_manager )
{
  JPetManager& manager = JPetManager::GetManager();
  JPetManager* pManager = &manager;
  JPetManager& manager2 = JPetManager::GetManager(); // it should be the same Manager
  JPetManager* pManager2 = &manager2;

  BOOST_REQUIRE_EQUAL(pManager, pManager2); 
}

BOOST_AUTO_TEST_SUITE_END()
