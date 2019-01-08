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
 *  @file JPetScopeConfigParserTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetScopeConfigParser

#include <boost/test/unit_test.hpp>
#include "JPetScopeConfigParser.h"
#include "JPetScopeConfigPOD.h"
#include <algorithm>

std::string gInputConfigJsonFilenameTest = "unitTestData/JPetScopeConfigParser/example.json";

BOOST_AUTO_TEST_SUITE(JPetScopeConfigParserTestSuite)

BOOST_AUTO_TEST_CASE(defaultConstructor)
{
  JPetScopeConfigParser parser;
}

BOOST_AUTO_TEST_CASE(transformToNumbers)
{
  using VecOfStrings = std::vector<std::string>;
  using VecOfNums = std::vector<int>;
  JPetScopeConfigParser parser;
  BOOST_REQUIRE(parser.transformToNumbers(VecOfStrings {""}).empty());
  BOOST_REQUIRE(parser.transformToNumbers(VecOfStrings {"1"}) == (VecOfNums {1}));
  BOOST_REQUIRE(parser.transformToNumbers(VecOfStrings {"1", "2"}) == (VecOfNums {1, 2}));
  BOOST_REQUIRE(parser.transformToNumbers(VecOfStrings {"1", "2", "10"}) == (VecOfNums {1, 2, 10}));
  BOOST_REQUIRE(parser.transformToNumbers(VecOfStrings {"a"}).empty());
  BOOST_REQUIRE(parser.transformToNumbers(VecOfStrings {"1", "a", "10"}) == (VecOfNums {1, 10}));
  BOOST_REQUIRE(parser.transformToNumbers(VecOfStrings {"a", "2", "5"}) == (VecOfNums {2, 5}));
  BOOST_REQUIRE(parser.transformToNumbers(VecOfStrings {"1 2", "3", "7 a 3", "1.2"}) == (VecOfNums {1, 2, 3, 7, 1}));
}

BOOST_AUTO_TEST_CASE(generateFileNames)
{
  using VecOfNums = std::vector<int>;
  using VecOfStrings = std::vector<std::string>;
  JPetScopeConfigParser parser;
  BOOST_REQUIRE(parser.generateFileNames("", "", (VecOfNums {})).empty());
  BOOST_REQUIRE(parser.generateFileNames("example", "config1", (VecOfNums {1})) == (VecOfStrings {"example_config1_1"}));
  BOOST_REQUIRE(parser.generateFileNames("example", "config2", (VecOfNums {1, 3})) == (VecOfStrings {"example_config2_1", "example_config2_3"}));
}

BOOST_AUTO_TEST_CASE(generateDirectories)
{
  using VecOfNums = std::vector<int>;
  using VecOfStrings = std::vector<std::string>;
  JPetScopeConfigParser parser;
  BOOST_REQUIRE(parser.generateDirectories("", (VecOfNums {})).empty());
  BOOST_REQUIRE(parser.generateDirectories("dir", (VecOfNums {1})) == (VecOfStrings {"dir/1"}));
  BOOST_REQUIRE(parser.generateDirectories("dir2", (VecOfNums {1, 3})) == (VecOfStrings {"dir2/1", "dir2/3"}));
}

BOOST_AUTO_TEST_CASE(getJsonContent)
{
  JPetScopeConfigParser parser;
  BOOST_REQUIRE(parser.getJsonContent("").empty());
  BOOST_REQUIRE(parser.getJsonContent("blabla.iki").empty());
  BOOST_REQUIRE(parser.getJsonContent("nonexistent.json").empty());
  BOOST_REQUIRE(!parser.getJsonContent(gInputConfigJsonFilenameTest).empty());
}

BOOST_AUTO_TEST_CASE(getInputDirectoriesAndFakeInputFile)
{
  JPetScopeConfigParser parser;
  using namespace scope_config;
  Config config;
  BOOST_REQUIRE(parser.getInputDirectoriesAndFakeInputFiles("").empty());
  BOOST_REQUIRE(parser.getInputDirectoriesAndFakeInputFiles(gInputConfigJsonFilenameTest).empty());
}

BOOST_AUTO_TEST_CASE(getConfig)
{
  using namespace scope_config;
  using VecOfStrings = std::vector<std::string>;
  JPetScopeConfigParser parser;
  Config emptyConf = parser.getConfig("");
  BOOST_REQUIRE_EQUAL(emptyConf.fName, "");
  BOOST_REQUIRE_EQUAL(emptyConf.fLocation, "");
  BOOST_REQUIRE(emptyConf.fCollimatorPositions.empty());
  Config config;
  config.fLocation = "data";
  config.fCollimatorPositions = VecOfStrings { "1 5 2", "12", "6"};
  config.fName = "config1";
  auto res = parser.getConfig(gInputConfigJsonFilenameTest);
  BOOST_REQUIRE(res.fName == config.fName);
  BOOST_REQUIRE(res.fLocation == config.fLocation);
  BOOST_REQUIRE(res.fCollimatorPositions == config.fCollimatorPositions);
}

BOOST_AUTO_TEST_CASE(getElementsWithExistingDirs)
{
  std::vector<std::pair<std::string, std::string>> dirsAndFakeFiles =
    {std::make_pair("./", "file1"), std::make_pair("fake/directory", "file2")};
  JPetScopeConfigParser parser;
  auto result = parser.getElementsWithExistingDirs(dirsAndFakeFiles);
  BOOST_REQUIRE_EQUAL(result.size(), 1u);
  BOOST_REQUIRE_EQUAL(result.at(0).first, "./");
  BOOST_REQUIRE_EQUAL(result.at(0).second, "file1");
  BOOST_REQUIRE(parser.getElementsWithExistingDirs({}).empty());
}

BOOST_AUTO_TEST_SUITE_END()
