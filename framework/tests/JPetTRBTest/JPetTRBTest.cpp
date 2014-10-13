#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTRBTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetTRB/JPetTRB.h"

//  public:
//  JPetTRB();
//  JPetTRB(int id, int type, int channel,);
//  inline int getID() const { return fID; }
//  inline int getChannel() const { return fChannel; }
//  inline int getType() const { return fType; }
//  inline void setID(int id) { fID = id; }
//  inline void setType(int type) { fType = type; }
//  inline void setChannel(int ch) { fChannel = ch; }


BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetTRB trb;
  BOOST_REQUIRE_EQUAL(trb.getID(), 0);
  BOOST_REQUIRE_EQUAL(trb.getType(), 0);
  BOOST_REQUIRE_EQUAL(trb.getChannel(), 0);
}

BOOST_AUTO_TEST_CASE( constructor )
{
  JPetTRB trb(12, 1, 224);
  BOOST_REQUIRE_EQUAL(trb.getID(), 12);
  BOOST_REQUIRE_EQUAL(trb.getType(), 1);
  BOOST_REQUIRE_EQUAL(trb.getChannel(), 224);
}

BOOST_AUTO_TEST_SUITE_END()
