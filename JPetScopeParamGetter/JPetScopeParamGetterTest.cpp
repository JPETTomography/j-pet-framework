#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetScopeParamGetterTest
#include <boost/test/unit_test.hpp>
#include "../JPetScopeParamGetter/JPetScopeParamGetter.h"

BOOST_AUTO_TEST_SUITE(ScopeParamGetterTS)

BOOST_AUTO_TEST_CASE(defaultConstructorTest)
{
  JPetScopeParamGetter paramGetter;
}

BOOST_AUTO_TEST_CASE(fillingOnce)
{
  JPetScopeParamGetter::clearParamCache();
  using namespace scope_config;
  JPetScopeParamGetter paramGetter;
  const char* testConfigFile = "unitTestData/JPetScopeParamGetterTest/config.json";
  JPetParamBank* bank = paramGetter.generateParamBank(testConfigFile);
  
  BOOST_REQUIRE_EQUAL(bank->getScintillatorsSize() , 2);
  BOOST_REQUIRE_EQUAL(bank->getPMsSize() , 4);
  BOOST_REQUIRE_EQUAL(bank->getPMCalibsSize() , 0); 
  BOOST_REQUIRE_EQUAL(bank->getBarrelSlotsSize() , 2);
  BOOST_REQUIRE_EQUAL(bank->getLayersSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getFramesSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getFEBsSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getTRBsSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getTOMBChannelsSize() , 0);

  auto tombChannels = bank->getTOMBChannels();
  BOOST_REQUIRE(tombChannels.empty());
}

BOOST_AUTO_TEST_CASE(fillingTwiceSame)
{
  JPetScopeParamGetter::clearParamCache();
  using namespace scope_config;
  JPetScopeParamGetter paramGetter;
  const char* testConfigFile = "unitTestData/JPetScopeParamGetterTest/config.json";
  JPetParamBank* bank = paramGetter.generateParamBank(testConfigFile);
  
  BOOST_REQUIRE_EQUAL(bank->getScintillatorsSize() , 2);
  BOOST_REQUIRE_EQUAL(bank->getPMsSize() , 4);
  BOOST_REQUIRE_EQUAL(bank->getPMCalibsSize() , 0); 
  BOOST_REQUIRE_EQUAL(bank->getBarrelSlotsSize() , 2);
  BOOST_REQUIRE_EQUAL(bank->getLayersSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getFramesSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getFEBsSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getTRBsSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getTOMBChannelsSize() , 0);
  auto scints = bank->getScintillators();
  BOOST_REQUIRE_EQUAL(scints.at(32)->getID(),32); 
  BOOST_REQUIRE_EQUAL(scints.at(12)->getID(),12); 
  JPetParamBank* bank2 = paramGetter.generateParamBank(testConfigFile);

  BOOST_REQUIRE_EQUAL(bank2->getScintillatorsSize() , 2);
  BOOST_REQUIRE_EQUAL(bank2->getPMsSize() , 4);
  BOOST_REQUIRE_EQUAL(bank2->getPMCalibsSize() , 0); 
  BOOST_REQUIRE_EQUAL(bank2->getBarrelSlotsSize() , 2);
  BOOST_REQUIRE_EQUAL(bank2->getLayersSize() , 0);
  BOOST_REQUIRE_EQUAL(bank2->getFramesSize() , 0);
  BOOST_REQUIRE_EQUAL(bank2->getFEBsSize() , 0);
  BOOST_REQUIRE_EQUAL(bank2->getTRBsSize() , 0);
  BOOST_REQUIRE_EQUAL(bank2->getTOMBChannelsSize() , 0);
  auto scints2 = bank2->getScintillators();
  BOOST_REQUIRE_EQUAL(scints2.at(32)->getID(),32); 
  BOOST_REQUIRE_EQUAL(scints2.at(12)->getID(),12); 

  BOOST_REQUIRE_EQUAL(bank->getScintillatorsSize() , 2);
  BOOST_REQUIRE_EQUAL(bank->getPMsSize() , 4);
  BOOST_REQUIRE_EQUAL(bank->getPMCalibsSize() , 0); 
  BOOST_REQUIRE_EQUAL(bank->getBarrelSlotsSize() , 2);
  BOOST_REQUIRE_EQUAL(bank->getLayersSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getFramesSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getFEBsSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getTRBsSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getTOMBChannelsSize() , 0);
  scints = bank->getScintillators();
  BOOST_REQUIRE_EQUAL(scints.at(32)->getID(),32); 
  BOOST_REQUIRE_EQUAL(scints.at(12)->getID(),12); 
}

BOOST_AUTO_TEST_CASE(fillingTwiceDifferent)
{
  JPetScopeParamGetter::clearParamCache();
  using namespace scope_config;
  JPetScopeParamGetter paramGetter;
  const char* testConfigFile = "unitTestData/JPetScopeParamGetterTest/config.json";
  const char* testConfigFile2 = "unitTestData/JPetScopeParamGetterTest/config2.json";
  JPetParamBank* bank = paramGetter.generateParamBank(testConfigFile);
  
  BOOST_REQUIRE_EQUAL(bank->getScintillatorsSize() , 2);
  BOOST_REQUIRE_EQUAL(bank->getPMsSize() , 4);
  BOOST_REQUIRE_EQUAL(bank->getPMCalibsSize() , 0); 
  BOOST_REQUIRE_EQUAL(bank->getBarrelSlotsSize() , 2);
  BOOST_REQUIRE_EQUAL(bank->getLayersSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getFramesSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getFEBsSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getTRBsSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getTOMBChannelsSize() , 0);
  auto scints = bank->getScintillators();
  BOOST_REQUIRE_EQUAL(scints.at(32)->getID(),32); 
  BOOST_REQUIRE_EQUAL(scints.at(12)->getID(),12); 
  
  JPetParamBank* bank2 = paramGetter.generateParamBank(testConfigFile2);

  BOOST_REQUIRE_EQUAL(bank2->getScintillatorsSize() , 2);
  BOOST_REQUIRE_EQUAL(bank2->getPMsSize() , 4);
  BOOST_REQUIRE_EQUAL(bank2->getPMCalibsSize() , 0); 
  BOOST_REQUIRE_EQUAL(bank2->getBarrelSlotsSize(), 2);
  BOOST_REQUIRE_EQUAL(bank2->getLayersSize() , 0);
  BOOST_REQUIRE_EQUAL(bank2->getFramesSize() , 0);
  BOOST_REQUIRE_EQUAL(bank2->getFEBsSize() , 0);
  BOOST_REQUIRE_EQUAL(bank2->getTRBsSize() , 0);
  BOOST_REQUIRE_EQUAL(bank2->getTOMBChannelsSize() , 0);
  auto scints2 = bank2->getScintillators();
  BOOST_REQUIRE_EQUAL(scints2.at(11)->getID(),11); 
  BOOST_REQUIRE_EQUAL(scints2.at(33)->getID(),33); 

  BOOST_REQUIRE_EQUAL(bank->getScintillatorsSize() , 2);
  BOOST_REQUIRE_EQUAL(bank->getPMsSize() , 4);
  BOOST_REQUIRE_EQUAL(bank->getPMCalibsSize() , 0); 
  BOOST_REQUIRE_EQUAL(bank->getBarrelSlotsSize() , 2);
  BOOST_REQUIRE_EQUAL(bank->getLayersSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getFramesSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getFEBsSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getTRBsSize() , 0);
  BOOST_REQUIRE_EQUAL(bank->getTOMBChannelsSize() , 0);
  scints = bank->getScintillators();
  BOOST_REQUIRE_EQUAL(scints.at(12)->getID(),12); 
  BOOST_REQUIRE_EQUAL(scints.at(32)->getID(),32); 
}

BOOST_AUTO_TEST_SUITE_END()
