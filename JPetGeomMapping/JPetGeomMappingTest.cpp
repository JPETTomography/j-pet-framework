#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetGeomMappingTest
#include <boost/test/unit_test.hpp>
#include "./JPetGeomMapping.h"
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

BOOST_FIXTURE_TEST_CASE(mappingFirst, myFixture)
{
  auto bank = fparamManagerInstance.getParamBank();
  auto mapping  = JPetGeomMapping(bank);
  BOOST_REQUIRE_EQUAL(mapping.getLayersCount(), 1);
  BOOST_REQUIRE_EQUAL(mapping.getLayersCount(), 1);
  JPetLayer layerOK(1, true, "Layer01", 40);
  JPetLayer layerWrong(2, true, "Layer02", 50);

  BOOST_REQUIRE_EQUAL(mapping.getLayerNumber(layerOK), 1);
  BOOST_REQUIRE_EQUAL(mapping.getLayerNumber(layerWrong), JPetGeomMapping::kBadLayerNumber);

  BOOST_REQUIRE_EQUAL(mapping.getSlotsCount(0), JPetGeomMapping::kBadSlotNumber);
  BOOST_REQUIRE_EQUAL(mapping.getSlotsCount(1), 2);
  BOOST_REQUIRE_EQUAL(mapping.getSlotsCount(2), JPetGeomMapping::kBadSlotNumber);

  JPetBarrelSlot slotOK1(1, true, "C1_C2", 0, 1);
  slotOK1.setLayer(layerOK);
  JPetBarrelSlot slotOK2(2, true, "C3_C4", 90, 1);
  slotOK2.setLayer(layerOK);
  JPetBarrelSlot slotWrong(3, true, "C2AA", 5, 9);

  BOOST_REQUIRE_EQUAL(mapping.getSlotNumber(slotOK1), 1);
  BOOST_REQUIRE_EQUAL(mapping.getSlotNumber(slotOK2), 2);
  BOOST_REQUIRE_EQUAL(mapping.getSlotNumber(slotWrong), JPetGeomMapping::kBadSlotNumber);

  auto sizes = mapping.getLayersSizes();
  BOOST_REQUIRE(!sizes.empty());
  BOOST_REQUIRE_EQUAL(sizes.size(), 1);
}

BOOST_AUTO_TEST_SUITE_END()

