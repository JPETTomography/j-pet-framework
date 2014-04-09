#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetCmdParser
#include <boost/test/unit_test.hpp>

#define private public

#include "../JPetCmdParser/JPetCmdParser.h"
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
}

BOOST_AUTO_TEST_CASE( constructor )
{
}

BOOST_AUTO_TEST_SUITE_END()
