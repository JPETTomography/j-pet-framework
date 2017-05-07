#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetOptionsTest
#include <boost/test/unit_test.hpp>
#include "JPetOptionsTools.h"
#include <boost/filesystem.hpp>
#include<iostream>
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
  auto inFile = "unitTestData/JPetOptionsToolsTest/inputTestCfg.json";
  std::map<std::string, boost::any> options = jpet_options_tools::createOptionsFromConfigFile(inFile);
  std::map<std::string, std::string> expectedStringMap = {{"myOption_std::string", "great"}, {"myAnotherOption_std::string", "wat"}, {"NumberOption_std::string", "12.2"}};
  std::map<std::string, boost::any> expected(expectedStringMap.begin(), expectedStringMap.end());
  expected["intOption_int"] = 123;
  expected["boolOption_bool"] = true;
  BOOST_REQUIRE_EQUAL(options.size(), 5);

   std::vector<std::string> keys_expected;
   std::vector<std::string> keys;
   for (const auto & el : expected) {
     keys_expected.push_back(el.first);
   }
   for (const auto & el : options) {
     keys.push_back(el.first);
   //  values.push_back(el.second);
   }
   std::sort(keys.begin(), keys.end());
  // std::sort(values.begin(), values.end());
   std::sort(keys_expected.begin(), keys_expected.end());
  // std::sort(values_expected.begin(), values_expected.end());
   BOOST_REQUIRE_EQUAL_COLLECTIONS(keys.begin(), keys.end(), keys_expected.begin(), keys_expected.end());
  // BOOST_REQUIRE_EQUAL_COLLECTIONS(values.begin(), values.end(), values_expected.begin(), values_expected.end());

  std::vector<std::string> allowedTypes = { "int", "std::string", "bool", "std::vector<std::string>", "std::vector<int>"};
  JPetOptionsTypeHandler typeHandler(allowedTypes);
   for(const auto & opt:  options){
    if (typeHandler.getTypeOfOption(opt.first) == "std::string"){
      BOOST_REQUIRE_EQUAL(any_cast<std::string>(opt.second), any_cast<std::string>(expected[opt.first]));
    }
    else if (typeHandler.getTypeOfOption(opt.first) == "int"){
      BOOST_REQUIRE_EQUAL(any_cast<int>(opt.second), any_cast<int>(expected[opt.first]));
    }
    else if (typeHandler.getTypeOfOption(opt.first) == "bool"){
      BOOST_REQUIRE_EQUAL(any_cast<bool>(opt.second), any_cast<bool>(expected[opt.first]));
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
  for (const auto & el : loadedOptions) {
    keys_expected.push_back(el.first);
    values_expected.push_back(any_cast<std::string>(el.second));
  }
  for (const auto & el : options) {
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

BOOST_AUTO_TEST_CASE( createConfigFileFromEmptyMap )
{
  jpet_options_tools::Options options = {};
  std::string cfgFile = "test_cfg3.json";
  BOOST_REQUIRE(jpet_options_tools::createConfigFileFromOptions(options, cfgFile));
  boost::filesystem::remove("test_cfg3.json");
}


BOOST_AUTO_TEST_CASE( createOptionsFromConfigFileThatHasWrongFormat )
{
  auto inFile = "unitTestData/JPetOptionsToolsTest/wrongInputFile.json";
  auto options = jpet_options_tools::createOptionsFromConfigFile(inFile);
  BOOST_REQUIRE_EQUAL(options.size(),  0);
}

BOOST_AUTO_TEST_SUITE_END()
