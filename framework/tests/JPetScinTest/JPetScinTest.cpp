#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetScinTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetScin/JPetScin.h"

//  public:
//JPetScin();
//JPetScin(int id, float attenLen, float length, float height, float width);
//inline int getID() const { return fID; }
//inline float getAttenLen() const { return fAttenLen; }
//inline ScinDimensions getScinSize() const { return fScinSize; }
//float getScinSize(Dimension dim) const;
//inline void setID(int id) { fID = id; }
//inline void setAttenLen(float attenLen) { fAttenLen = attenLen; }
//inline void setScinSize(ScinDimensions size) { fScinSize = size; }
//void setScinSize(Dimension dim, float value);


BOOST_AUTO_TEST_SUITE(FirstSuite)
  
BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetScin scint;
  float epsilon = 0.0001; 
  BOOST_REQUIRE_EQUAL(scint.getID(), 0);
  BOOST_REQUIRE_CLOSE(scint.getAttenLen(), 0, epsilon);
  BOOST_REQUIRE_CLOSE(scint.getScinSize(JPetScin::kLength), 0, epsilon);
  BOOST_REQUIRE_CLOSE(scint.getScinSize(JPetScin::kHeight), 0, epsilon);
  BOOST_REQUIRE_CLOSE(scint.getScinSize(JPetScin::kWidth), 0, epsilon);
  JPetScin::ScinDimensions size = scint.getScinSize();
  BOOST_REQUIRE_CLOSE(size.fLength, 0, epsilon);
  BOOST_REQUIRE_CLOSE(size.fHeight, 0, epsilon);
  BOOST_REQUIRE_CLOSE(size.fWidth, 0, epsilon);

}

BOOST_AUTO_TEST_CASE( constructor )
{
  JPetScin scint(25, 10.34, 100, 4.5, 2.5);
  float epsilon = 0.0001; 
  BOOST_REQUIRE_EQUAL(scint.getID(), 25);
  BOOST_REQUIRE_CLOSE(scint.getAttenLen(), 10.34, epsilon);
  BOOST_REQUIRE_CLOSE(scint.getScinSize(JPetScin::kLength), 100, epsilon);
  BOOST_REQUIRE_CLOSE(scint.getScinSize(JPetScin::kHeight), 4.5, epsilon);
  BOOST_REQUIRE_CLOSE(scint.getScinSize(JPetScin::kWidth), 2.5, epsilon);
  JPetScin::ScinDimensions size = scint.getScinSize();
  BOOST_REQUIRE_CLOSE(size.fLength, 100, epsilon);
  BOOST_REQUIRE_CLOSE(size.fHeight, 4.5, epsilon);
  BOOST_REQUIRE_CLOSE(size.fWidth, 2.5, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
