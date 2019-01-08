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
 *  @file JPetScopeLoaderTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ScopeLoader
#define BOOST_TEST_LOG_LEVEL message

#include "./JPetScopeLoader/JPetScopeLoader.h"
#include "./JPetCommonTools/JPetCommonTools.h"
#include "./JPetManager/JPetManager.h"
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <functional>
#include <cstddef>

BOOST_AUTO_TEST_SUITE (JPetScopeLoaderTestSuite)

BOOST_AUTO_TEST_CASE (getFilePrefix)
{
  JPetScopeLoader reader(0);
  BOOST_REQUIRE(reader.getFilePrefix("").empty());
  BOOST_REQUIRE(reader.getFilePrefix("abkabd").empty());
  BOOST_REQUIRE(reader.getFilePrefix("jfsd808").empty());
  BOOST_REQUIRE_EQUAL(reader.getFilePrefix("c1_0554.txt"), "c1");
  BOOST_REQUIRE_EQUAL(reader.getFilePrefix("c098_0554.txt"), "c098");
  BOOST_REQUIRE_EQUAL(reader.getFilePrefix("cq_"), "cq");
  BOOST_REQUIRE_EQUAL(reader.getFilePrefix("a_ss_q"), "a");
}

BOOST_AUTO_TEST_CASE (createInputScopeFileNames)
{
  JPetScopeLoader reader(0);
  BOOST_REQUIRE(reader.createInputScopeFileNames("", {}).empty());
  BOOST_REQUIRE(reader.createInputScopeFileNames("non_existing", {}).empty());
  BOOST_REQUIRE(!reader.createInputScopeFileNames(
    "unitTestData/JPetScopeLoaderTest/scope_files/0", {{"C1", 0}, {"C2", 1}, {"C3", 2}, {"C4", 3}}).empty());
  std::map<std::string, int>  expectedRes0 {
    {"C1_00003.txt", 0}, {"C1_00004.txt", 0},  {"C2_00003.txt", 1}, {"C2_00004.txt", 1},
    {"C3_00003.txt", 2}, {"C3_00004.txt", 2}, {"C4_00003.txt", 3}, {"C4_00004.txt", 3}
  };
  std::map<std::string, int>  expectedRes;
  std::string pathToFiles = "unitTestData/JPetScopeLoaderTest/scope_files/0";
  for (const auto& el : expectedRes0) {
    expectedRes[pathToFiles + "/" + el.first] = el.second;
  }
  std::map<std::string, int> obtainedRes = reader.createInputScopeFileNames(
    pathToFiles, {{"C1", 0}, {"C2", 1}, {"C3", 2}, {"C4", 3}});
  BOOST_REQUIRE(!obtainedRes.empty());
  BOOST_REQUIRE_EQUAL(obtainedRes.size(), expectedRes.size());
  auto it2 = obtainedRes.begin();
  for (auto it = expectedRes.begin(); it != expectedRes.end(); ++it) {
    BOOST_REQUIRE_EQUAL(it->first, it2->first);
    BOOST_REQUIRE_EQUAL(it->second, it2->second);
    ++it2;
  }
}

BOOST_AUTO_TEST_CASE (isCorrectScopeFileName)
{
  JPetScopeLoader reader(0);
  BOOST_REQUIRE(!reader.isCorrectScopeFileName(""));
  BOOST_REQUIRE(!reader.isCorrectScopeFileName("C1_004.gif"));
  BOOST_REQUIRE(!reader.isCorrectScopeFileName("C1004.txt"));
  BOOST_REQUIRE(!reader.isCorrectScopeFileName("004.txt"));
  BOOST_REQUIRE(!reader.isCorrectScopeFileName("C5_abc.txt"));
  BOOST_REQUIRE(reader.isCorrectScopeFileName("C1_023.txt"));
  BOOST_REQUIRE(reader.isCorrectScopeFileName("C5_000.txt"));
  BOOST_REQUIRE(reader.isCorrectScopeFileName("AA_004.txt"));
  BOOST_REQUIRE(reader.isCorrectScopeFileName("AA_004.txt"));
}

BOOST_AUTO_TEST_CASE (generate_root_file)
{
  const char* test_root_filename = "unitTestData/JPetScopeLoaderTest/test_file_test_0.reco.sig.root";
  boost::filesystem::remove(test_root_filename);
  auto commandLine = "main.exe  -t scope -f unitTestData/JPetScopeLoaderTest/test_file.json -l unitTestData/JPetScopeLoaderTest/test_params.json -i 1";
  auto args_char = JPetCommonTools::createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();
  JPetManager& manager = JPetManager::getManager();
  manager.parseCmdLine(argc, argv);
  manager.run(argc, argv);
  BOOST_REQUIRE_MESSAGE(boost::filesystem::exists(test_root_filename), "File " << test_root_filename << " does not exist.");
  BOOST_REQUIRE_MESSAGE(boost::filesystem::exists("test.root"), "File " << "test.root" << " does not exist.");
}

BOOST_AUTO_TEST_CASE (position_does_not_exist)
{
  const char* test_root_filename = "unitTestData/JPetScopeLoaderTest/wrong_file_test_30.reco.sig.root";
  boost::filesystem::remove(test_root_filename);
  auto commandLine = "main.exe  -t scope -f unitTestData/JPetScopeLoaderTest/wrong_file.json -l unitTestData/JPetScopeLoaderTest/test_params.json -i 1";
  auto args_char = JPetCommonTools::createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();
  JPetManager& manager = JPetManager::getManager();
  manager.parseCmdLine(argc, argv);
  manager.run(argc, argv);
  BOOST_REQUIRE_MESSAGE(!boost::filesystem::exists(test_root_filename), "File " << test_root_filename << " exists.");
}

BOOST_AUTO_TEST_CASE (folder_does_not_exist)
{
  const char* test_root_filename = "unitTestData/JPetScopeLoaderTest/wrong_file2_test_0.reco.sig.root";
  boost::filesystem::remove(test_root_filename);
  auto commandLine = "main.exe  -t scope -f unitTestData/JPetScopeLoaderTest/wrong_file2.json -l unitTestData/JPetScopeLoaderTest/test_params.json -i 1";
  auto args_char = JPetCommonTools::createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();
  JPetManager& manager = JPetManager::getManager();
  manager.run(argc, argv);
  BOOST_REQUIRE_MESSAGE(!boost::filesystem::exists(test_root_filename), "File " << test_root_filename << " exists.");
}

BOOST_AUTO_TEST_CASE (generate_root_file2)
{
  const char* test_root_filename1 = "unitTestData/JPetScopeLoaderTest/test_file2_test_0.reco.sig.root";
  const char* test_root_filename2 = "unitTestData/JPetScopeLoaderTest/test_file2_test_1.reco.sig.root";
  boost::filesystem::remove(test_root_filename1);
  boost::filesystem::remove(test_root_filename2);
  auto commandLine = "main.exe  -t scope -f unitTestData/JPetScopeLoaderTest/test_file2.json -l unitTestData/JPetScopeLoaderTest/test_params2.json -i 1";
  auto args_char = JPetCommonTools::createArgs(commandLine);
  auto argc = args_char.size();
  auto argv = args_char.data();
  JPetManager& manager = JPetManager::getManager();
  manager.run(argc, argv);
  BOOST_REQUIRE_MESSAGE(boost::filesystem::exists("test.root"), "File " << "test.root" << " does not exist.");
  BOOST_REQUIRE_MESSAGE(boost::filesystem::exists(test_root_filename1), "File " << test_root_filename1 << " does not exist.");
  BOOST_REQUIRE_MESSAGE(boost::filesystem::exists(test_root_filename2), "File " << test_root_filename2 << " does not exist.");
}

BOOST_AUTO_TEST_CASE (groupScopeFileNamesByTimeWindowIndex)
{
  std::map<std::string, int>  input {
    {"/some/path/C1_00003.txt", 0}, {"/some/path/C1_00004.txt", 0},  {"/some/path/C2_00003.txt", 1}, {"/some/path/C2_00004.txt", 1},
    {"/some/path/C3_00003.txt", 2}, {"/some/path/C3_00004.txt", 2}, {"/some/path/C4_00003.txt", 3}, {"/some/path/C4_00004.txt", 3}
  };
  auto obtainedRes = JPetScopeLoader::groupScopeFileNamesByTimeWindowIndex(input);
  std::map<int, std::map<std::string, int>>  expectedRes {
    {3, {{"/some/path/C1_00003.txt", 0}, {"/some/path/C2_00003.txt", 1}, {"/some/path/C3_00003.txt", 2}, {"/some/path/C4_00003.txt", 3}}},
    {4, {{"/some/path/C1_00004.txt", 0}, {"/some/path/C2_00004.txt", 1}, {"/some/path/C3_00004.txt", 2}, {"/some/path/C4_00004.txt", 3}}}
  };
  auto it2 = obtainedRes.begin();
  for (auto it = expectedRes.begin(); it != expectedRes.end(); ++it) {
    BOOST_REQUIRE_EQUAL(it->first, it2->first);
    auto mapExpected = it2->second;
    auto mapObtained = it->second;
    auto mIt2 = mapObtained.begin();
    for (auto mIt = mapExpected.begin(); mIt != mapExpected.end(); ++mIt) {
      BOOST_REQUIRE_EQUAL(mIt->first, mIt2->first);
      BOOST_REQUIRE_EQUAL(mIt->second, mIt2->second);
      ++mIt2;
    }
    ++it2;
  }
}

BOOST_AUTO_TEST_CASE(getTimeWindowIndex)
{
  BOOST_REQUIRE_EQUAL(JPetScopeLoader::getTimeWindowIndex(""), -1);
  BOOST_REQUIRE_EQUAL(JPetScopeLoader::getTimeWindowIndex("02"), -1);
  BOOST_REQUIRE_EQUAL(JPetScopeLoader::getTimeWindowIndex("023"), -1);
  BOOST_REQUIRE_EQUAL(JPetScopeLoader::getTimeWindowIndex("_000a"), 0);
  BOOST_REQUIRE_EQUAL(JPetScopeLoader::getTimeWindowIndex("0040a"), 0);
  BOOST_REQUIRE_EQUAL(JPetScopeLoader::getTimeWindowIndex("C1_0002"), 2);
  BOOST_REQUIRE_EQUAL(JPetScopeLoader::getTimeWindowIndex("C4_0004"), 4);
  BOOST_REQUIRE_EQUAL(JPetScopeLoader::getTimeWindowIndex("_0004"), 4);
  BOOST_REQUIRE_EQUAL(JPetScopeLoader::getTimeWindowIndex("_000a"), 0);
  BOOST_REQUIRE_EQUAL(JPetScopeLoader::getTimeWindowIndex("107349"), 349);
  BOOST_REQUIRE_EQUAL(JPetScopeLoader::getTimeWindowIndex("C1_0003.txt"), 3);
}

BOOST_AUTO_TEST_SUITE_END()
