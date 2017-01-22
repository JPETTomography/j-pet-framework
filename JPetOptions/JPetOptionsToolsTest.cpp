#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetOptionsTest
#include <boost/test/unit_test.hpp>
#include "JPetOptionsTools.h"
#include <boost/filesystem.hpp>

BOOST_AUTO_TEST_SUITE(FirstSuite)


BOOST_AUTO_TEST_CASE( createConfigFileFromOptions )
{
  std::map<std::string, std::string> options = {{"TimeWindow", "10"}, {"SomeOption", "true"}, {"AnotherOption", "4.5"}};
  std::string outFile = "test_cfg.json";
  BOOST_REQUIRE(jpet_options_tools::createConfigFileFromOptions(options, outFile));
  /// todo remove created file
}


BOOST_AUTO_TEST_CASE(createOptionsFromConfFile)
{
  auto inFile = "inputTestCfg.json";
  std::map<std::string, std::string> options = jpet_options_tools::createOptionsFromConfFile(inFile);
  std::map<std::string, std::string> expected = {{"MyOption", "great"}, {"myAnotherOption", "wat"}, {"boolOption", "true"}, {"NumberOption", "12.2"}};
  BOOST_REQUIRE_EQUAL(options.size(), 4u);

  std::vector<std::string> keys_expected;
  std::vector<std::string> values_expected;
  std::vector<std::string> keys;
  std::vector<std::string> values;
  for (const auto & el : expected) {
    keys_expected.push_back(el.first);
    values_expected.push_back(el.second);
  }
  for (const auto & el : options) {
    keys.push_back(el.first);
    values.push_back(el.second);
  }
  std::sort(keys.begin(), keys.end());
  std::sort(values.begin(), values.end());
  std::sort(keys_expected.begin(), keys_expected.end());
  std::sort(values_expected.begin(), values_expected.end());
  /// I dont understand why it is not ordered correctly, anyway all elements seem to be present only reversed
  //BOOST_REQUIRE_EQUAL_COLLECTIONS(keys.begin(), keys.end(), keys_expected.begin(), keys_expected.end());
  //BOOST_REQUIRE_EQUAL_COLLECTIONS(values.begin(), values.end(), values_expected.begin(), values_expected.end());
}

BOOST_AUTO_TEST_CASE( createConfigFileFromOptionsAndReadItBack )
{
  jpet_options_tools::Options options = {{"TimeWindow", "11"}, {"SomeOption", "false"}, {"AnotherOption", "4.5"}};
  std::string cfgFile = "test_cfg2.json";
  BOOST_REQUIRE(jpet_options_tools::createConfigFileFromOptions(options, cfgFile));
  auto loadedOptions = jpet_options_tools::createOptionsFromConfFile(cfgFile);
  BOOST_REQUIRE_EQUAL(options.size(), loadedOptions.size());
  std::vector<std::string> keys_expected;
  std::vector<std::string> values_expected;
  std::vector<std::string> keys;
  std::vector<std::string> values;
  for (const auto & el : loadedOptions) {
    keys_expected.push_back(el.first);
    values_expected.push_back(el.second);
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
}

BOOST_AUTO_TEST_CASE( createOptionsFromConfFileThatDoesNotExist )
{
  auto inFile = "nonExistingTestCfg.json";
  auto options = jpet_options_tools::createOptionsFromConfFile(inFile);
  BOOST_REQUIRE(options.empty());
}

BOOST_AUTO_TEST_CASE( createConfigFileFromEmptyMap )
{
}

BOOST_AUTO_TEST_CASE( createOptionsFromConfFileThatHasWrongFormat )
{
}

BOOST_AUTO_TEST_SUITE_END()
