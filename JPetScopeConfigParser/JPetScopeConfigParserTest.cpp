/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file JPetScopeConfigParser.h
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
  /// The result is still empty, because now the result contains only elements with directories which actually exist
  /// and there are no directories in this location.
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
  BOOST_REQUIRE(emptyConf.fBSlots.empty());
  BOOST_REQUIRE(emptyConf.fPMs.empty());
  BOOST_REQUIRE(emptyConf.fScins.empty());
  BOOST_REQUIRE(emptyConf.fCollimatorPositions.empty());

  Config config;
  config.fLocation = "data";
  config.fCollimatorPositions = VecOfStrings { "1 5 2", "12", "6"};
  config.fBSlots = std::vector<BSlot> { BSlot(-1, false, "", -1., -1), BSlot(-1, false, "", -1., -1)};
  config.fPMs = std::vector<PM> {PM(3, "C2"), PM(98, "C4"), PM(32, "C1"), PM(42, "C3")};
  config.fScins = std::vector<Scin> {Scin(32), Scin(12)};
  config.fName = "config1";

  auto res = parser.getConfig(gInputConfigJsonFilenameTest);

  BOOST_REQUIRE(res.fName == config.fName);
  BOOST_REQUIRE(res.fLocation == config.fLocation);
  BOOST_REQUIRE(res.fCollimatorPositions == config.fCollimatorPositions);

  BOOST_REQUIRE(res.fPMs.size() == config.fPMs.size());
  for (auto i = 0u ; i < config.fPMs.size(); i++) {
    BOOST_REQUIRE(config.fPMs[i].fId == res.fPMs[i].fId);
    BOOST_REQUIRE(config.fPMs[i].fPrefix == res.fPMs[i].fPrefix);
  }

  BOOST_REQUIRE(res.fScins.size() == config.fScins.size());
  for (auto i = 0u ; i < config.fScins.size(); i++) {
    BOOST_REQUIRE(config.fScins[i].fId == res.fScins[i].fId);
  }

  BOOST_REQUIRE(res.fBSlots.size() == config.fBSlots.size());
  for (auto i = 0u ; i < config.fBSlots.size(); i++) {
    BOOST_REQUIRE(config.fBSlots[i].fId == res.fBSlots[i].fId);
    BOOST_REQUIRE(config.fBSlots[i].fActive == res.fBSlots[i].fActive);
    BOOST_REQUIRE(config.fBSlots[i].fName == res.fBSlots[i].fName);
    BOOST_REQUIRE_CLOSE(config.fBSlots[i].fTheta,  res.fBSlots[i].fTheta, 0.00001);
    BOOST_REQUIRE(config.fBSlots[i].fFrame == res.fBSlots[i].fFrame);
  }
}

BOOST_AUTO_TEST_CASE(getElementsWithExistingDirs)
{
  std::vector<std::pair<std::string, std::string> >  dirsAndFakeFiles = { std::make_pair("./", "file1"), std::make_pair("fake/directory", "file2")};
  JPetScopeConfigParser parser;
  auto result = parser.getElementsWithExistingDirs(dirsAndFakeFiles );
  BOOST_REQUIRE_EQUAL(result.size(), 1u);
  BOOST_REQUIRE_EQUAL(result.at(0).first, "./");
  BOOST_REQUIRE_EQUAL(result.at(0).second, "file1");
  BOOST_REQUIRE(parser.getElementsWithExistingDirs({}).empty());
}

BOOST_AUTO_TEST_CASE(areObjectsWithDuplicatedIds)
{
  using namespace scope_config;
  using VecOfStrings = std::vector<std::string>;
  JPetScopeConfigParser parser;

  /// No duplicates
  Config config;
  config.fLocation = "data";
  config.fCollimatorPositions = VecOfStrings { "1 5 2", "12", "6"};
  config.fBSlots = std::vector<BSlot> { BSlot(-1, false, "", -1., -1), BSlot(-2, false, "", -1., -1)};
  config.fPMs = std::vector<PM> {PM(3, "C2"), PM(98, "C4"), PM(32, "C1"), PM(42, "C3")};
  config.fScins = std::vector<Scin> {Scin(32), Scin(12)};
  config.fName = "config1";
  BOOST_REQUIRE(!parser.areObjectsWithDuplicatedIds(config));

  /// Same Bslots ids.
  Config config2;
  config2.fLocation = "data";
  config2.fCollimatorPositions = VecOfStrings { "1 5 2", "12", "6"};
  config2.fBSlots = std::vector<BSlot> { BSlot(-1, false, "", -1., -1), BSlot(-1, false, "", -1., -1)};
  config2.fPMs = std::vector<PM> {PM(3, "C2"), PM(98, "C4"), PM(32, "C1"), PM(42, "C3")};
  config2.fScins = std::vector<Scin> {Scin(32), Scin(12)};
  config2.fName = "config2";
  BOOST_REQUIRE(parser.areObjectsWithDuplicatedIds(config2));

  /// Same PM ids.
  Config config3;
  config3.fLocation = "data";
  config3.fCollimatorPositions = VecOfStrings { "1 5 2", "12", "6"};
  config3.fBSlots = std::vector<BSlot> { BSlot(-1, false, "", -1., -1), BSlot(-2, false, "", -1., -1)};
  config3.fPMs = std::vector<PM> {PM(3, "C2"), PM(98, "C4"), PM(32, "C1"), PM(98, "C3")};
  config3.fScins = std::vector<Scin> {Scin(32), Scin(12)};
  config3.fName = "config3";
  BOOST_REQUIRE(parser.areObjectsWithDuplicatedIds(config3));

  /// Same Scins ids.
  Config config4;
  config4.fLocation = "data";
  config4.fCollimatorPositions = VecOfStrings { "1 5 2", "12", "6"};
  config4.fBSlots = std::vector<BSlot> { BSlot(-1, false, "", -1., -1), BSlot(-2, false, "", -1., -1)};
  config4.fPMs = std::vector<PM> {PM(3, "C2"), PM(98, "C4"), PM(32, "C1"), PM(11, "C3")};
  config4.fScins = std::vector<Scin> {Scin(32), Scin(32)};
  config4.fName = "config4";
  BOOST_REQUIRE(parser.areObjectsWithDuplicatedIds(config4));

  /// Empty config.
  Config config5;
  BOOST_REQUIRE(!parser.areObjectsWithDuplicatedIds(config5));
}

BOOST_AUTO_TEST_SUITE_END()
