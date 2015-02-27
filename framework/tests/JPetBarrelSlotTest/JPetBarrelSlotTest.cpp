#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetBarrelSlotTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetBarrelSlot/JPetBarrelSlot.h"

// JPetBarrelSlot();
// JPetBarrelSlot(int id, bool isActive, std::string name, float theta);
// 
// inline bool operator==(const JPetBarrelSlot& bslot) { return getID() == bslot.getID(); }
// inline bool operator!=(const JPetBarrelSlot& bslot) { return getID() != bslot.getID(); }
//
// inline int getID() const { return fId; }
// inline float getTheta() const { return fTheta; }
// inline bool isActive() const { return fIsActive; }
// inline std::string getName() const { return fName; }
// inline const JPetLayer & getLayer() { return static_cast<JPetLayer&>(*(fTRefLayer.GetObject())); }
// 
// void setLayer(JPetLayer &p_layer)
// {
//   fTRefLayer = &p_layer;
// }


BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetBarrelSlot slot;
  float epsilon = 0.0001;
  BOOST_REQUIRE_EQUAL(slot.getID(), -1);
  BOOST_REQUIRE_CLOSE(slot.getTheta(), -1., epsilon);
  BOOST_REQUIRE(!slot.isActive());
  BOOST_REQUIRE(slot.getName().empty());
  BOOST_REQUIRE(slot.getInFrameID()==-1);
}

BOOST_AUTO_TEST_CASE( constructor )
{
  JPetBarrelSlot slot(1, true, "pepe", 5.5, 6);
  float epsilon = 0.0001;
  BOOST_REQUIRE_EQUAL(slot.getID(), 1);
  BOOST_REQUIRE_CLOSE(slot.getTheta(), 5.5, epsilon);
  BOOST_REQUIRE(slot.isActive());
  BOOST_REQUIRE(slot.getName()=="pepe");
  BOOST_REQUIRE(slot.getInFrameID()==6);
}

BOOST_AUTO_TEST_SUITE_END()
