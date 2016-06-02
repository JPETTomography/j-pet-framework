#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetScopeParamGetterTest
#include <boost/test/unit_test.hpp>
#include "../JPetScopeParamGetter/JPetScopeParamGetter.h"

BOOST_AUTO_TEST_SUITE(ScopeParamGetterTS)

BOOST_AUTO_TEST_CASE(defaultConstructorTest)
{
  JPetScopeParamGetter paramGetter;
}

BOOST_AUTO_TEST_CASE(dummyFillingTest)
{
  JPetScopeParamGetter::clearParamCache();
  using namespace scope_config;
  using VecOfStrings = std::vector<std::string>;
  JPetScopeParamGetter paramGetter;
  const char* testConfigFile = "unitTestData/JPetScopeParamGetterTest/config.json";
  JPetParamBank* bank = paramGetter.generateParamBank(testConfigFile);
  
  BOOST_REQUIRE(bank->getScintillatorsSize() == 2);
  BOOST_REQUIRE(bank->getPMsSize() == 4);
  BOOST_REQUIRE(bank->getPMCalibsSize() == 0); 
  BOOST_REQUIRE(bank->getBarrelSlotsSize() == 2);
  BOOST_REQUIRE(bank->getLayersSize() == 0);
  BOOST_REQUIRE(bank->getFramesSize() == 0);
  BOOST_REQUIRE(bank->getFEBsSize() == 0);
  BOOST_REQUIRE(bank->getTRBsSize() == 0);
  BOOST_REQUIRE(bank->getTOMBChannelsSize() == 0);
}

BOOST_AUTO_TEST_SUITE_END()
