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
#include <algorithm>

std::string gInputConfigJsonFilenameTest = "../../unitTestData/JPetScopeConfigParser/example.json";

BOOST_AUTO_TEST_SUITE(JPetScopeConfigParserTestSuite)

BOOST_AUTO_TEST_CASE(defaultConstructor)
{
  JPetScopeConfigParser parser;
  BOOST_REQUIRE(parser.getLoadedConfigData().empty());
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

BOOST_AUTO_TEST_CASE(getJsonContent)
{
  JPetScopeConfigParser parser;
  BOOST_REQUIRE(parser.getLoadedConfigData().empty());
  BOOST_REQUIRE(parser.getJsonContent("").empty());

  BOOST_REQUIRE(parser.getJsonContent("blabla.iki").empty());
  BOOST_REQUIRE(parser.getLoadedConfigData().empty());

  BOOST_REQUIRE(parser.getJsonContent("nonexistent.json").empty());
  BOOST_REQUIRE(parser.getLoadedConfigData().empty());

  BOOST_REQUIRE(!parser.getJsonContent(gInputConfigJsonFilenameTest).empty());
  BOOST_REQUIRE(parser.getLoadedConfigData().empty());
}

BOOST_AUTO_TEST_CASE(loadConfigFile)
{
  JPetScopeConfigParser parser;
  BOOST_REQUIRE(!parser.loadConfigFile(""));
  BOOST_REQUIRE(parser.getLoadedConfigData().empty());
  BOOST_REQUIRE(parser.loadConfigFile(gInputConfigJsonFilenameTest));
  BOOST_REQUIRE(!parser.getLoadedConfigData().empty());
}

BOOST_AUTO_TEST_CASE(getInputFileNames)
{
  using VecOfStrings = std::vector<std::string>;
  JPetScopeConfigParser parser;
  BOOST_REQUIRE(parser.getInputFileNames("").empty());
  VecOfStrings expectedRes {"config1_1", "config1_5",
                            "config1_2", "config1_12",
                            "config1_6"};
  std::transform(expectedRes.begin(), expectedRes.end(),expectedRes.begin(), 
                [&](std::string name) {
                  return gInputConfigJsonFilenameTest+"_"+name;
                }); 
  BOOST_REQUIRE(parser.getInputFileNames(gInputConfigJsonFilenameTest) == expectedRes);
}


//
//BOOST_AUTO_TEST_CASE(readDataTest)
//{
//std::string inputconfigjsonfilenametest = "unittestdata/jpetscopeconfigparser/example.json";
//std::string outputFileNameTest = "config1";
//unsigned int scopeReaderConfigParserPositionsSize = 5;

//JPetScopeConfigParser scopeReaderConfigParser;
//scopeReaderConfigParser.readData(inputConfigJsonFileNameTest);

//BOOST_REQUIRE_EQUAL(scopeReaderConfigParser.getFileName(), outputFileNameTest);
//BOOST_REQUIRE(scopeReaderConfigParser.getPositions().size() == scopeReaderConfigParserPositionsSize);
//}

BOOST_AUTO_TEST_CASE(noExistingTest)
{
  /*std::string inputConfigJsonFileNameTest = "unitTestData/JPetScopeConfigParser/notExistingFile.json";
  std::string outputFileNameTest = "config1";
  unsigned int scopeReaderConfigParserPositionsSize = 5;

  JPetScopeConfigParser scopeReaderConfigParser;
  scopeReaderConfigParser.readData(inputConfigJsonFileNameTest);*/

  //BOOST_REQUIRE_EQUAL(scopeReaderConfigParser.getFileName(), outputFileNameTest);
  //BOOST_REQUIRE(scopeReaderConfigParser.getPositions().size() == scopeReaderConfigParserPositionsSize);
}

///wk dodac test otwierajacy nieistniejacy plik json
///przetestowac co zwracaja wtedy wszystkie publiczne funkcje

BOOST_AUTO_TEST_SUITE_END()
