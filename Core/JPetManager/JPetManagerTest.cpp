/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file JPetManagerTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetManagerTest

#include <boost/test/unit_test.hpp>
#include "./JPetManager/JPetManager.h"
#include <cstdio> //for std::remove

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(create_unique_manager)
{
  JPetManager& manager = JPetManager::getManager();
  JPetManager* pManager = &manager;
  JPetManager& manager2 = JPetManager::getManager();
  JPetManager* pManager2 = &manager2;
  BOOST_REQUIRE_EQUAL(pManager, pManager2);
}

BOOST_AUTO_TEST_CASE(threadsEnabled)
{
  JPetManager& manager = JPetManager::getManager();
  BOOST_REQUIRE(!manager.areThreadsEnabled());
  manager.setThreadsEnabled(true);
  BOOST_REQUIRE(manager.areThreadsEnabled());
  manager.setThreadsEnabled(false);
  BOOST_REQUIRE(!manager.areThreadsEnabled());
}

BOOST_AUTO_TEST_CASE(emptyRun)
{
  JPetManager& manager = JPetManager::getManager();
  BOOST_CHECK_THROW(manager.run(0, nullptr), std::exception);
}

BOOST_AUTO_TEST_CASE(goodRootRun)
{
  JPetManager& manager = JPetManager::getManager();
  const char* args[7] = {
    "test/Path",
    "--file",
    "unitTestData/JPetManagerTest/goodRootFile.root",
    "--type",
    "root",
    "-p",
    "conf_trb3.xml"
  };
  BOOST_REQUIRE_NO_THROW(manager.run(7, args));
}

BOOST_AUTO_TEST_CASE(goodZipRun)
{
  std::remove("unitTestData/JPetManagerTest/xx14099113231.hld");
  JPetManager& manager = JPetManager::getManager();
  const char* args[14] = {"test/Path", "--file", "unitTestData/JPetManagerTest/xx14099113231.hld.xz", "--type", "zip", "-p", "unitTestData/JPetManagerTest/conf_trb3.xml", "-r", "0", "10", "-l", "unitTestData/JPetManagerTest/large_barrel.json", "-i", "44"};
  BOOST_REQUIRE_NO_THROW(manager.run(14, args));
}

BOOST_AUTO_TEST_CASE(goodMCRun)
{
  JPetManager &manager = JPetManager::getManager();
  const char* args[11] = {
    "test/Path",
    "--file",
    "unitTestData/JPetManagerTest/goodMCFile.mcGeant.root",
    "--type",
    "mcGeant",
    "-p",
    "conf_trb3.xml",
    "-l",
    "unitTestData/JPetManagerTest/large_barrel.json",
    "-i",
    "44"
  };
  BOOST_REQUIRE_NO_THROW(manager.run(11, args));
}

BOOST_AUTO_TEST_SUITE_END()
