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


BOOST_AUTO_TEST_SUITE(JPetScopeConfigParserTestSuite)

///po stworzeniu obiektu, bez wczytania pliku 
//przetestowac co zwracaja wtedy wszystkie publiczne funkcje

BOOST_AUTO_TEST_CASE(readDataTest)
{
  std::string inputConfigJsonFileNameTest = "unitTestData/JPetScopeConfigParser/example.json";
  std::string outputFileNameTest = "config1";
  unsigned int scopeReaderConfigParserPositionsSize = 5;
  
  JPetScopeConfigParser scopeReaderConfigParser;
  scopeReaderConfigParser.readData(inputConfigJsonFileNameTest);
  
  BOOST_REQUIRE_EQUAL(scopeReaderConfigParser.getFileName(), outputFileNameTest);
  BOOST_REQUIRE(scopeReaderConfigParser.getPositions().size() == scopeReaderConfigParserPositionsSize);
}

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
