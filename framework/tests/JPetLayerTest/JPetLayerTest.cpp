#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetLayerTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetLayer/JPetLayer.h"

// JPetLayer();
// JPetLayer(int id, bool isActive, std::string name, float radius);
// 
// inline bool operator==(const JPetLayer& layer) { return getId() == layer.getId(); }
// inline bool operator!=(const JPetLayer& layer) { return getId() != layer.getId(); }
// 
// inline int getId() const { return fId; }
// inline bool getIsActive() const { return fIsActive; }
// inline std::string getName() const { return fName; }
// inline float getRadius() const { return fRadius; }
// inline const JPetFrame& getFrame() { return static_cast<JPetFrame&>(*(fTRefFrame.GetObject())); }
// inline void setFrame(JPetFrame &frame) { fTRefFrame = &frame; }

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetLayer layer;
  double epsilon =0.00001;
  BOOST_REQUIRE_EQUAL(layer.getId(), -1);
  BOOST_REQUIRE(!layer.getIsActive());
  BOOST_REQUIRE(layer.getName().empty());
  BOOST_REQUIRE_CLOSE(layer.getRadius(), -1, epsilon);
}

BOOST_AUTO_TEST_CASE( second_constructor )
{
  JPetLayer layer(1, true, "ala", 10.5);
  double epsilon =0.00001;
  BOOST_REQUIRE_EQUAL(layer.getId(), 1);
  BOOST_REQUIRE(layer.getIsActive());
  BOOST_REQUIRE(layer.getName()=="ala");
  BOOST_REQUIRE_CLOSE(layer.getRadius(), 10.5, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
