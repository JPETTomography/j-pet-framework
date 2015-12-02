#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetPMTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetPM/JPetPM.h"

//  public:
//  JPetPM();
//  inline Side getSide() const { return fSide; }
//  inline int getID() const { return fID; }
//  inline int getHVset() const { return fHVset; }
//  inline int getHVopt() const { return fHVopt; }
//  inline float getHVgain(GainNumber nr) { return (nr == kFirst) ? fHVgain.first : fHVgain.second; }
//  inline std::pair<float, float> getHVgain() { return fHVgain; }
//  inline void setSide(Side side) { fSide = side; }
//  inline void setID(int id) { fID = id; }
//  inline void setHVset(int set) { fHVset = set; }
//  inline void setHVopt(int opt) { fHVopt= opt; }
//  inline void setHVgain(float g1, float g2) { fHVgain.first = g1; fHVgain.second = g2; }
//  inline void setHVgain(const std::pair<float,float>& gain) { fHVgain = gain; }

BOOST_AUTO_TEST_SUITE(FirstSuite)
  
BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetPM pm;
  float epsilon = 0.0001; 
  BOOST_REQUIRE_EQUAL(pm.getSide(), JPetPM::SideA);
  BOOST_REQUIRE_EQUAL(pm.getID(), 0);
  BOOST_REQUIRE_EQUAL(pm.getHVset(), 0);
  BOOST_REQUIRE_EQUAL(pm.getHVopt(), 0);
  BOOST_REQUIRE_CLOSE(pm.getHVgain(JPetPM::kFirst), 0, epsilon);
  BOOST_REQUIRE_CLOSE(pm.getHVgain(JPetPM::kSecond), 0, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
