#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetOptionsTest
#include <boost/test/unit_test.hpp>
#include "JPetOptionsTools.h"
#include <boost/filesystem.hpp>
#include <iostream>
#include <boost/any.hpp>
#include <string>
#include <typeinfo>
#include "../JPetOptionsGenerator/JPetOptionsTypeHandler.h"
using boost::any_cast;
const std::string dataDir = "unitTestData/JPetOptionsToolsTest/";
using namespace std;
BOOST_AUTO_TEST_SUITE(FirstSuite)


BOOST_AUTO_TEST_CASE( createConfigFileFromOptions )
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
  std::map<std::string, std::string> expectedStringMap = {{"myOption_std::string", "great"}, {"myAnotherOption_std::string", "wat"}, {"NumberOption_std::string", "12.2"}};
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
  for (const auto& el : expected) {
    keys_expected.push_back(el.first);
  }
  for (const auto& el : options) {
    keys.push_back(el.first);
  }
  std::sort(keys.begin(), keys.end());
  std::sort(keys_expected.begin(), keys_expected.end());
  BOOST_REQUIRE_EQUAL_COLLECTIONS(keys.begin(), keys.end(), keys_expected.begin(), keys_expected.end());

  std::vector<std::string> allowedTypes = { "int", "std::string", "bool", "std::vector<std::string>", "std::vector<int>"};
  for (const auto& opt :  options) {
    if (JPetOptionsTypeHandler::getTypeOfOption(opt.first) == "std::string") {
      BOOST_REQUIRE_EQUAL(any_cast<std::string>(opt.second), any_cast<std::string>(expected[opt.first]));
    } else if (JPetOptionsTypeHandler::getTypeOfOption(opt.first) == "int") {
      BOOST_REQUIRE_EQUAL(any_cast<int>(opt.second), any_cast<int>(expected[opt.first]));
    } else if (JPetOptionsTypeHandler::getTypeOfOption(opt.first) == "bool") {
      BOOST_REQUIRE_EQUAL(any_cast<bool>(opt.second), any_cast<bool>(expected[opt.first]));
    } else if (JPetOptionsTypeHandler::getTypeOfOption(opt.first) == "std::vector<std::string>") {
      auto vectorStringOption =  any_cast< std::vector<std::string> >(opt.second);
      BOOST_REQUIRE_EQUAL_COLLECTIONS(vectorStringOption.begin(), vectorStringOption.end(), v1.begin(), v1.end());
    } else if (JPetOptionsTypeHandler::getTypeOfOption(opt.first) == "std::vector<int>") {
      auto vectorIntOption =  any_cast< std::vector<int> >(opt.second);
      BOOST_REQUIRE_EQUAL_COLLECTIONS(vectorIntOption.begin(), vectorIntOption.end(), v2.begin(), v2.end());
    }
  }
}

BOOST_AUTO_TEST_CASE( createConfigFileFromOptionsAndReadItBack )
{
  std::map<std::string, std::string> options = {{"TimeWindow_std::string", "11"}, {"SomeOption_std::string", "false"}, {"AnotherOption_std::string", "4.5"}};
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

BOOST_AUTO_TEST_CASE( createOptionsFromConfigFileThatDoesNotExist )
{
  auto inFile = "nonExistingTestCfg.json";
  auto options = jpet_options_tools::createOptionsFromConfigFile(inFile);
  BOOST_REQUIRE(options.empty());
}

//BOOST_AUTO_TEST_CASE( createConfigFileFromEmptyMap )
//{
//jpet_options_tools::Options options = {};
//std::string cfgFile = "test_cfg3.json";
//BOOST_REQUIRE(jpet_options_tools::createConfigFileFromOptions(options, cfgFile));
//boost::filesystem::remove("test_cfg3.json");
//}


BOOST_AUTO_TEST_CASE( createOptionsFromConfigFileThatHasWrongFormat )
{
  auto inFile = "unitTestData/JPetOptionsToolsTest/wrongInputFile.json";
  auto options = jpet_options_tools::createOptionsFromConfigFile(inFile);
  BOOST_REQUIRE_EQUAL(options.size(),  0);
}

//BOOST_AUTO_TEST_CASE( my_test1 )
//{
//JPetOptions opts;
//auto default_opts =  JPetOptionsGenerator::getDefaultOptions();
//std::vector<std::string> allowedTypes = { "int", "std::string", "bool", "std::vector<std::string>", "std::vector<int>"};
//BOOST_REQUIRE(JPetCommonTools::mapComparator(JPetOptionsTypeHandler::anyMapToStringMap(opts.getOptions()), JPetOptionsTypeHandler::anyMapToStringMap(default_opts)));
//}

//BOOST_AUTO_TEST_CASE(petOptionsBasicTest)
//{
//JPetOptions::Options options = {
//{"inputFile_std::string", std::string("input")},
//{"scopeConfigFile_std::string", std::string("test.json")},
//{"scopeInputDirectory_std::string", std::string("scopeData")},
//{"outputPath_std::string", std::string("/home/test")},
//{"outputFile_std::string", std::string("output")},
//{"firstEvent_int", 8246821},
//{"lastEvent_int", 8246821},
//{"runId_int", 2001},
//{"progressBar_bool", true},
//{"inputFileType_std::string", std::string("root")},
//{"outputFileType_std::string", std::string("scope")},
//{"unpackerConfigFile_std::string", std::string("conf_trb3.xml")},
//{"unpackerCalibFile_std::string", std::string("")}
//};

//JPetOptions petOptions(options);
//BOOST_REQUIRE_EQUAL(petOptions.getInputFile(), "input");
//BOOST_REQUIRE_EQUAL(petOptions.getScopeConfigFile(), "test.json");
//BOOST_REQUIRE_EQUAL(petOptions.getScopeInputDirectory(), "scopeData");
//BOOST_REQUIRE_EQUAL(petOptions.getOutputPath(), "/home/test");
//BOOST_REQUIRE_EQUAL(petOptions.getOutputFile(), "output");
//auto firstEvent = petOptions.getFirstEvent();
//BOOST_REQUIRE_EQUAL(firstEvent, 8246821);
//auto lastEvent = petOptions.getLastEvent();
//BOOST_REQUIRE_EQUAL(lastEvent, 8246821);
//int runNumberHex = petOptions.getRunNumber();
//BOOST_REQUIRE_EQUAL(runNumberHex, 2001);
//BOOST_REQUIRE_EQUAL(petOptions.isProgressBar(), true);
//BOOST_REQUIRE_EQUAL(petOptions.getInputFileType(), JPetOptions::FileType::kRoot);
//BOOST_REQUIRE_EQUAL(petOptions.getOutputFileType(), JPetOptions::FileType::kScope);
//std::vector<std::string> allowedTypes = { "int", "std::string", "bool", "std::vector<std::string>", "std::vector<int>"};
//auto default_opts =  JPetOptionsGenerator::getDefaultOptions();
//BOOST_REQUIRE(JPetCommonTools::mapComparator(JPetOptionsTypeHandler::anyMapToStringMap(petOptions.getOptions()), JPetOptionsTypeHandler::anyMapToStringMap(options)));
//BOOST_REQUIRE(!JPetCommonTools::mapComparator(JPetOptionsTypeHandler::anyMapToStringMap(default_opts), JPetOptionsTypeHandler::anyMapToStringMap(petOptions.getOptions())));
//}

//BOOST_AUTO_TEST_CASE(getTotalEventsTest)
//{
//JPetOptions::Options options = {
//{"inputFile_std::string", std::string("input")},
//{"scopeConfigFile_std::string", std::string("test.json")},
//{"scopeInputDirectory_std::string", std::string("scopeData")},
//{"outputFile_std::string", std::string("output")},
//{"firstEvent_int", -1},
//{"lastEvent_int", -1},
//{"runId_int", 2001},
//{"progressBar_bool", true},
//{"inputFileType_std::string", std::string("root")},
//{"outputFileType_std::string", std::string("scope")},
//{"unpackerConfigFile_std::string", std::string("conf_trb3.xml")},
//{"unpackerCalibFile_std::string", std::string("")}
//};
//BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), -1);

//options.at("firstEvent_int") = 0;
//options.at("lastEvent_int") = -1;

//BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), -1);

//options.at("firstEvent_int") = 0;
//options.at("lastEvent_int") = -1;
//BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), -1);

//options.at("firstEvent_int") = 0;
//options.at("lastEvent_int") = 0;
//BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), 1);

//options.at("firstEvent_int") = 0;
//options.at("lastEvent_int") = 1;
//BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), 2);

//options.at("firstEvent_int") = 7;
//options.at("lastEvent_int") = 9;
//BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), 3);

//options.at("firstEvent_int") = 6;
//options.at("lastEvent_int") = 5;
//BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), -1);

//options.at("firstEvent_int") = 9;
//options.at("lastEvent_int") = 5;
//BOOST_REQUIRE_EQUAL(JPetOptions(options).getTotalEvents(), -1);
//}

BOOST_AUTO_TEST_SUITE_END()
