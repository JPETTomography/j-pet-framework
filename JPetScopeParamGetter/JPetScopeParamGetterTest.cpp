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
  using namespace scope_config;
  using VecOfStrings = std::vector<std::string>;
  JPetScopeParamGetter paramGetter;
  Config config;
  config.fLocation="data";
  config.fCollimatorPositions = VecOfStrings { "1 5 2", "12", "6"};
  config.fBSlots= std::vector<BSlot>{ BSlot(-1,false,"",-1., -1), BSlot(-1,false,"",-1., -1)};
  config.fPMs = std::vector<PM>{PM(3,"C2"), PM(98, "C4"), PM(32, "C1"), PM(42, "C3")}; 
  config.fScins=std::vector<Scin>{Scin(32), Scin(12)};
  config.fName="config1";
  JPetParamBank* bank = paramGetter.generateParamBank(config);
  
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
