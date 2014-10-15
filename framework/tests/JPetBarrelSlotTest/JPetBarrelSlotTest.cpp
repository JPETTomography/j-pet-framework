#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetBarrelSlotTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetBarrelSlot/JPetBarrelSlot.h"

//  public:
//JPetBarrelSlot();
//  JPetBarrelSlot(int slotId, int layerID, int layerRad, int slotTheta);
//  inline int getSlotID() const { return fSlotID; }
//  inline int getLayerID() const { return fLayerID; }
//  inline int getLayerRad() const { return fLayerRad; }
//  inline float getSlotTheta() const { return fSlotTheta; }
//  inline void setSlotID(int id) { fSlotID = id; }
//  inline void setLayerID(int id) { fLayerID = id; }
//  inline void setLayerRad(int layerRad) { fLayerRad = layerRad; }
//  inline void setSlotTheta(float slotTheta) { fSlotTheta = slotTheta;}

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetBarrelSlot slot;
  float epsilon = 0.0001;
  BOOST_REQUIRE_EQUAL(slot.getSlotID(), 0);
  BOOST_REQUIRE_EQUAL(slot.getLayerID(), 0);
  BOOST_REQUIRE_EQUAL(slot.getLayerRad(), 0);
  BOOST_REQUIRE_CLOSE(slot.getSlotTheta(), 0., epsilon);
}

BOOST_AUTO_TEST_CASE( constructor )
{
  JPetBarrelSlot slot(1, 2, 3, 5.5);
  float epsilon = 0.0001;
  BOOST_REQUIRE_EQUAL(slot.getSlotID(), 1);
  BOOST_REQUIRE_EQUAL(slot.getLayerID(), 2);
  BOOST_REQUIRE_EQUAL(slot.getLayerRad(), 3);
  BOOST_REQUIRE_CLOSE(slot.getSlotTheta(), 5.5, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
