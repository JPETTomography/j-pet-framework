/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetOptionsToolsTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetOptionsTest

#include "JPetOptionsGenerator/JPetOptionsTypeHandler.h"
#include "JPetOptionsTools/JPetOptionsTools.h"
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <boost/any.hpp>
#include <iostream>
#include <typeinfo>
#include <string>

using boost::any_cast;
const std::string dataDir = "unitTestData/JPetOptionsToolsTest/";

using namespace std;
using namespace jpet_options_tools;

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(createConfigFileFromOptions)
{
  std::map<std::string, std::string> options = {{"TimeWindow", "10"}, {"SomeOption", "true"}, {"AnotherOption", "4.5"}};
  std::string outFile = "test_cfg.json";
  BOOST_REQUIRE(jpet_options_tools::createConfigFileFromOptions(options, outFile));
  boost::filesystem::remove("test_cfg.json");
}

BOOST_AUTO_TEST_CASE(createOptionsFromConfigFile)
{
  auto inFile = "unitTestData/JPetOptionsToolsTest/newInputTestCfg.json";
  std::map<std::string, boost::any> options = jpet_options_tools::createOptionsFromConfigFile(inFile);
  std::map<std::string, std::string> expectedStringMap = {
      {"myOption_std::string", "great"}, {"myAnotherOption_std::string", "wat"}, {"NumberOption_std::string", "12.2"}};
  std::map<std::string, boost::any> expected(expectedStringMap.begin(), expectedStringMap.end());
  expected["intOption_int"] = 123;
  expected["boolOption_bool"] = true;
  std::vector<std::string> v1 = {"firstOption", "secondOption", "thirdOption"};
  expected["vectorOfStringOtption_std::vector<std::string>"] = v1;
  std::vector<int> v2 = {1, 2, 3};
  expected["vectorOfIntOption_std::vector<int>"] = v2;
  BOOST_REQUIRE_EQUAL(options.size(), 7);

  std::vector<std::string> keys_expected;
  std::vector<std::string> keys;
  for (const auto& el : expected)
  {
    keys_expected.push_back(el.first);
  }
  for (const auto& el : options)
  {
    keys.push_back(el.first);
  }
  std::sort(keys.begin(), keys.end());
  std::sort(keys_expected.begin(), keys_expected.end());
  BOOST_REQUIRE_EQUAL_COLLECTIONS(keys.begin(), keys.end(), keys_expected.begin(), keys_expected.end());

  for (const auto& opt : options)
  {
    if (JPetOptionsTypeHandler::getTypeOfOption(opt.first) == "std::string")
    {
      BOOST_REQUIRE_EQUAL(any_cast<std::string>(opt.second), any_cast<std::string>(expected[opt.first]));
    }
    else if (JPetOptionsTypeHandler::getTypeOfOption(opt.first) == "int")
    {
      BOOST_REQUIRE_EQUAL(any_cast<int>(opt.second), any_cast<int>(expected[opt.first]));
    }
    else if (JPetOptionsTypeHandler::getTypeOfOption(opt.first) == "bool")
    {
      BOOST_REQUIRE_EQUAL(any_cast<bool>(opt.second), any_cast<bool>(expected[opt.first]));
    }
    else if (JPetOptionsTypeHandler::getTypeOfOption(opt.first) == "std::vector<std::string>")
    {
      auto vectorStringOption = any_cast<std::vector<std::string>>(opt.second);
      BOOST_REQUIRE_EQUAL_COLLECTIONS(vectorStringOption.begin(), vectorStringOption.end(), v1.begin(), v1.end());
    }
    else if (JPetOptionsTypeHandler::getTypeOfOption(opt.first) == "std::vector<int>")
    {
      auto vectorIntOption = any_cast<std::vector<int>>(opt.second);
      BOOST_REQUIRE_EQUAL_COLLECTIONS(vectorIntOption.begin(), vectorIntOption.end(), v2.begin(), v2.end());
    }
  }
}

BOOST_AUTO_TEST_CASE(createConfigFileFromOptionsAndReadItBack)
{
  std::map<std::string, std::string> options = {
    {"TimeWindow_std::string", "11"}, {"SomeOption_std::string", "false"}, {"AnotherOption_std::string", "4.5"}
  };
  std::string cfgFile = "test_cfg2.json";
  BOOST_REQUIRE(jpet_options_tools::createConfigFileFromOptions(options, cfgFile));
  auto loadedOptions = jpet_options_tools::createOptionsFromConfigFile(cfgFile);
  BOOST_REQUIRE_EQUAL(options.size(), loadedOptions.size());
  std::vector<std::string> keys_expected;
  std::vector<std::string> values_expected;
  std::vector<std::string> keys;
  std::vector<std::string> values;
  for (const auto& el : loadedOptions) {
    keys_expected.push_back(el.first);
    values_expected.push_back(any_cast<std::string>(el.second));
  }
  for (const auto& el : options) {
    keys.push_back(el.first);
    values.push_back(el.second);
  }
  std::sort(keys.begin(), keys.end());
  std::sort(values.begin(), values.end());
  std::sort(keys_expected.begin(), keys_expected.end());
  std::sort(values_expected.begin(), values_expected.end());
  BOOST_REQUIRE_EQUAL_COLLECTIONS(keys.begin(), keys.end(), keys_expected.begin(), keys_expected.end());
  BOOST_REQUIRE_EQUAL_COLLECTIONS(values.begin(), values.end(), values_expected.begin(), values_expected.end());
  boost::filesystem::remove("test_cfg2.json");
}

BOOST_AUTO_TEST_CASE(createOptionsFromConfigFileThatDoesNotExist)
{
  auto inFile = "nonExistingTestCfg.json";
  auto options = jpet_options_tools::createOptionsFromConfigFile(inFile);
  BOOST_REQUIRE(options.empty());
}

BOOST_AUTO_TEST_CASE(createConfigFileFromEmptyMap)
{
  jpet_options_tools::OptsStrStr options = {};
  std::string cfgFile = "test_cfg3.json";
  BOOST_REQUIRE(jpet_options_tools::createConfigFileFromOptions(options, cfgFile));
  boost::filesystem::remove("test_cfg3.json");
}

BOOST_AUTO_TEST_CASE(createOptionsFromConfigFileThatHasWrongFormat)
{
  auto inFile = "unitTestData/JPetOptionsToolsTest/wrongInputFile.json";
  auto options = jpet_options_tools::createOptionsFromConfigFile(inFile);
  BOOST_REQUIRE_EQUAL(options.size(), 0);
}

BOOST_AUTO_TEST_CASE(checkIfGetOptionAndIsOptionWork)
{
  std::map<std::string, boost::any> options = {
    {"firstEvent_int", -1},
    {"lastEvent_int", -1},
    {"progressBar_bool", false},
    {"runID_int", -1},
    {"unpackerConfigFile_std::string", std::string("conf_trb3.xml")},
    {"unpackerCalibFile_std::string", std::string("")}
  };

  BOOST_REQUIRE(isOptionSet(options, "firstEvent_int"));
  BOOST_REQUIRE(isOptionSet(options, "lastEvent_int"));

  BOOST_REQUIRE_EQUAL(any_cast<int>(getOptionValue(options, "firstEvent_int")), -1);
  BOOST_REQUIRE_EQUAL(any_cast<int>(getOptionValue(options, "lastEvent_int")), -1);
}

BOOST_AUTO_TEST_CASE(getTotalEventsTest)
{
  OptsStrAny options = {
    {"inputFile_std::string", std::string("input")},
    {"scopeConfigFile_std::string", std::string("test.json")},
    {"scopeInputDirectory_std::string", std::string("scopeData")},
    {"outputFile_std::string", std::string("output")},
    {"firstEvent_int", -1},
    {"lastEvent_int", -1},
    {"runID_int", 2001},
    {"progressBar_bool", true},
    {"inputFileType_std::string", std::string("root")},
    {"outputFileType_std::string", std::string("scope")},
    {"unpackerConfigFile_std::string", std::string("conf_trb3.xml")},
    {"unpackerCalibFile_std::string", std::string("")}
  };

  BOOST_REQUIRE_EQUAL(getTotalEvents(options), -1);

  options.at("firstEvent_int") = 0;
  options.at("lastEvent_int") = -1;

  BOOST_REQUIRE_EQUAL(getTotalEvents(options), -1);

  options.at("firstEvent_int") = 0;
  options.at("lastEvent_int") = -1;
  BOOST_REQUIRE_EQUAL(getTotalEvents(options), -1);

  options.at("firstEvent_int") = 0;
  options.at("lastEvent_int") = 0;
  BOOST_REQUIRE_EQUAL(getTotalEvents(options), 1);

  options.at("firstEvent_int") = 0;
  options.at("lastEvent_int") = 1;
  BOOST_REQUIRE_EQUAL(getTotalEvents(options), 2);

  options.at("firstEvent_int") = 7;
  options.at("lastEvent_int") = 9;
  BOOST_REQUIRE_EQUAL(getTotalEvents(options), 3);

  options.at("firstEvent_int") = 6;
  options.at("lastEvent_int") = 5;
  BOOST_REQUIRE_EQUAL(getTotalEvents(options), -1);

  options.at("firstEvent_int") = 9;
  options.at("lastEvent_int") = 5;
  BOOST_REQUIRE_EQUAL(getTotalEvents(options), -1);
}

BOOST_AUTO_TEST_CASE(getOptionBy)
{
  std::vector<std::string> tmp = {"aa", "bb"};
  std::vector<int> intVector = {1, 2, 3};
  std::map<std::string, boost::any> opts = {
    {"my_string", std::string("my_value")},
    {"my_int", int(12)},
    {"my_float", float(12.5)},
    {"my_double", double(14.6)},
    {"my_bool", false},
    {"my_vectS", tmp},
    {"my_intV", intVector}
  };
  BOOST_REQUIRE_EQUAL(getOptionAsString(opts, "my_string"), std::string("my_value"));
  BOOST_REQUIRE_EQUAL(getOptionAsInt(opts, "my_int"), 12);
  BOOST_REQUIRE_EQUAL(getOptionAsFloat(opts, "my_float"), 12.5);
  BOOST_REQUIRE_EQUAL(getOptionAsDouble(opts, "my_double"), 14.6);
  BOOST_REQUIRE(!getOptionAsVectorOfStrings(opts, "my_vectS").empty());
  BOOST_REQUIRE_EQUAL(getOptionAsVectorOfStrings(opts, "my_vectS").size(), 2u);
  BOOST_REQUIRE_EQUAL(getOptionAsVectorOfInts(opts, "my_intV").size(), 3u);
  BOOST_REQUIRE_EQUAL(getOptionAsBool(opts, "my_bool"), false);
}

BOOST_AUTO_TEST_CASE(getDetectorTypeTest)
{
  OptsStrAny opt1 = {{"detectorType_std::string", std::string("bar")}};
  OptsStrAny opt2 = {{"detectorType_std::string", std::string("barrel")}};
  OptsStrAny opt3 = {{"detectorType_std::string", std::string("mod")}};
  OptsStrAny opt4 = {{"detectorType_std::string", std::string("modular")}};
  OptsStrAny opt5 = {{"detectorType_std::string", std::string("kloe")}};
  OptsStrAny opt6 = {{"detectorType_std::string", std::string("lhcb")}};
  BOOST_REQUIRE_EQUAL(DetectorTypeChecker::getDetectorType(opt1), DetectorTypeChecker::DetectorType::kBarrel);
  BOOST_REQUIRE_EQUAL(DetectorTypeChecker::getDetectorType(opt2), DetectorTypeChecker::DetectorType::kBarrel);
  BOOST_REQUIRE_EQUAL(DetectorTypeChecker::getDetectorType(opt3), DetectorTypeChecker::DetectorType::kModular);
  BOOST_REQUIRE_EQUAL(DetectorTypeChecker::getDetectorType(opt4), DetectorTypeChecker::DetectorType::kModular);
  BOOST_REQUIRE_EQUAL(DetectorTypeChecker::getDetectorType(opt5), DetectorTypeChecker::DetectorType::kBarrel);
  BOOST_REQUIRE_EQUAL(DetectorTypeChecker::getDetectorType(opt6), DetectorTypeChecker::DetectorType::kBarrel);
}

BOOST_AUTO_TEST_SUITE_END()
