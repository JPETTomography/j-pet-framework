#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetParamBankToolsTest
#include <boost/test/unit_test.hpp>
#include "JPetParamBankTools.h"
#include "../JPetParamManager/JPetParamManager.h"
#include "../JPetParamGetterAscii/JPetParamGetterAscii.h"

const std::string dataDir = "unitTestData/JPetParamManagerTest/";
const std::string dataFileName = dataDir + "data.json";

struct myFixture {
  myFixture(): fparamManagerInstance(new JPetParamGetterAscii(dataFileName)) {
    fparamManagerInstance.fillParameterBank(1);
  }
  ~myFixture() {}
  JPetParamManager fparamManagerInstance;
};

BOOST_AUTO_TEST_SUITE(FirstSuite)
BOOST_AUTO_TEST_CASE(emptyBank)
{
  JPetParamBank bank;
  BOOST_REQUIRE(JPetParamBankTools::getTOMBMap(bank).empty());
}

BOOST_FIXTURE_TEST_CASE(minimalBank, myFixture)
{
  auto bank = fparamManagerInstance.getParamBank();
  auto mapping  = JPetParamBankTools::getTOMBMap(bank);
  BOOST_REQUIRE(!mapping.empty());
  BOOST_REQUIRE_EQUAL(mapping.size(), 4u);
  auto layer = 1;
  auto barrelSlot = 1;
  auto side = JPetPM::SideB;
  auto threshold  = 0;
  BOOST_REQUIRE_EQUAL(mapping.count(std::make_tuple(layer, barrelSlot, side, threshold)), 1);
  auto result_tomb = mapping.at(std::make_tuple(layer, barrelSlot, side, threshold));
  BOOST_REQUIRE_EQUAL(result_tomb, 1);
  layer = 1;
  barrelSlot = 1;
  side = JPetPM::SideA;
  threshold  = 0;
  result_tomb = mapping.at(std::make_tuple(layer, barrelSlot, side, threshold));
  BOOST_REQUIRE_EQUAL(result_tomb, 2);
  layer = 1;
  barrelSlot = 2;
  side = JPetPM::SideA;
  threshold  = 0;
  result_tomb = mapping.at(std::make_tuple(layer, barrelSlot, side, threshold));
  BOOST_REQUIRE_EQUAL(result_tomb, 3);
  layer = 1;
  barrelSlot = 2;
  side = JPetPM::SideB;
  threshold  = 0;
  result_tomb = mapping.at(std::make_tuple(layer, barrelSlot, side, threshold));
  BOOST_REQUIRE_EQUAL(result_tomb, 4);
}

BOOST_AUTO_TEST_SUITE_END()
