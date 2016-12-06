/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetCommonToolsTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetCommonToolsTest
#include <boost/test/unit_test.hpp>
#include <map>
#include "JPetCommonTools.h"


BOOST_AUTO_TEST_SUITE(CommonToolsTestSuite)

BOOST_AUTO_TEST_CASE(findSubstringTest)
{
  std::string str("There are two needles in this haystack with needles.");
  std::string str2("needle");
  
  std::size_t found = JPetCommonTools::findSubstring(str, str2);
  BOOST_REQUIRE_EQUAL(found != std::string::npos, true);
}

BOOST_AUTO_TEST_CASE(ItoaTest)
{
  int testNumber = 64;
  
  std::string intAsASting = JPetCommonTools::Itoa(testNumber);
  BOOST_REQUIRE_EQUAL(intAsASting == "64", true);
}

BOOST_AUTO_TEST_CASE(intToStringTest)
{
  int testNumber = 64;
  
  std::string intAsASting = JPetCommonTools::intToString(testNumber);
  BOOST_REQUIRE_EQUAL(intAsASting == "64", true);
}

BOOST_AUTO_TEST_CASE(doubleToStringTest)
{
  double testNumber = 256.3264;
  
  std::string doubleAsASting = JPetCommonTools::doubleToString(testNumber);
  BOOST_REQUIRE_EQUAL(doubleAsASting == "256.326", true);
}

BOOST_AUTO_TEST_CASE(stringToIntTest)
{
  std::string testString = "1024";
  
  int stringAsAInt = JPetCommonTools::stringToInt(testString);
  BOOST_REQUIRE_EQUAL(stringAsAInt == 1024, true);
}

BOOST_AUTO_TEST_CASE(toBoolTest)
{
  std::string testString = "0";
  
  bool stringAsABool = JPetCommonTools::to_bool(testString);
  BOOST_REQUIRE_EQUAL(stringAsABool == false, true);
}

BOOST_AUTO_TEST_CASE(ifFileExistingTest)
{
  std::string fileTest = "run_tests.pl";
  
  bool ifFileExisting = JPetCommonTools::ifFileExisting(fileTest);
  BOOST_REQUIRE_EQUAL(ifFileExisting, true);
}

BOOST_AUTO_TEST_CASE(mapAreEqualTest)
{
  std::map<int, int> mapTestLeft, mapTestRight;
  bool areMapsEqual = JPetCommonTools::mapComparator(mapTestLeft, mapTestRight);
  BOOST_REQUIRE_EQUAL(areMapsEqual, true);
}

BOOST_AUTO_TEST_CASE(mapAreNotEqualTest)
{
  std::map<char,int> first;
  first['a']=10;
  first['b']=30;
  first['c']=50;
  first['d']=70;
  std::map<char,int> second;
  
  bool areMapsEqual = JPetCommonTools::mapComparator(first, second);
  BOOST_REQUIRE_EQUAL(areMapsEqual, false);
}

BOOST_AUTO_TEST_CASE(stripFileNameSuffixTest)
{
  std::string fileTest = "run_tests.pl";
  
  std::string stripFileNameSuffix = JPetCommonTools::stripFileNameSuffix(fileTest);
  BOOST_REQUIRE_EQUAL(stripFileNameSuffix == "run_tests", true);
}

BOOST_AUTO_TEST_CASE(currentFullPathTest)
{
  std::string currentFullPathTest = boost::filesystem::path(boost::filesystem::current_path()).string();
  
  std::string currentFullPath = JPetCommonTools::currentFullPath();
  BOOST_REQUIRE_EQUAL(currentFullPath == currentFullPathTest, true);
}

BOOST_AUTO_TEST_CASE(extractPathFromFileTest)
{
  std::string currentFullPathTest = boost::filesystem::path(boost::filesystem::current_path()).string();
  std::string currentFullPathTestWithFileName = currentFullPathTest + "/" + "run_tests.pl";
  
  std::string result = JPetCommonTools::extractPathFromFile(currentFullPathTestWithFileName);
  BOOST_REQUIRE_EQUAL(result.compare(currentFullPathTest), 0);
}

BOOST_AUTO_TEST_CASE(isDirectory)
{
  BOOST_REQUIRE(JPetCommonTools::isDirectory(boost::filesystem::initial_path().string()));
  BOOST_REQUIRE(!JPetCommonTools::isDirectory("fake/directory/baba"));
}

BOOST_AUTO_TEST_CASE(appendSlashToPathIfAbsent)
{
  BOOST_REQUIRE_EQUAL(JPetCommonTools::appendSlashToPathIfAbsent(""), "");
  BOOST_REQUIRE_EQUAL(JPetCommonTools::appendSlashToPathIfAbsent("./"), "./");
  BOOST_REQUIRE_EQUAL(JPetCommonTools::appendSlashToPathIfAbsent("/home/"), "/home/");
  BOOST_REQUIRE_EQUAL(JPetCommonTools::appendSlashToPathIfAbsent("/home"), "/home/");
  BOOST_REQUIRE_EQUAL(JPetCommonTools::appendSlashToPathIfAbsent("home/bbl/be"), "home/bbl/be/");
  BOOST_REQUIRE_EQUAL(JPetCommonTools::appendSlashToPathIfAbsent("test"), "test/");
}

BOOST_AUTO_TEST_CASE(tryToUnzipSomethingNotExistingFile)
{
  BOOST_REQUIRE(!JPetCommonTools::unzipFile("kiko.gz"));
  std::string initialPath= boost::filesystem::path(boost::filesystem::current_path()).string();
  initialPath = initialPath.substr(0, initialPath.find("build") );
  std::string wrongZipPath = initialPath + "j-pet-framework/unitTestData/JPetCommonToolsTest/wrongZip.gz";
  BOOST_REQUIRE(!JPetCommonTools::unzipFile( wrongZipPath.c_str() ));
    
}

BOOST_AUTO_TEST_SUITE_END()

