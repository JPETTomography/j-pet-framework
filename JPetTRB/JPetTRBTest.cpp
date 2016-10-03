#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTRBTest
#include <boost/test/unit_test.hpp>
#include "JPetTRB.h"
#include "JPetTRBFactory.h"



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
  JPetTRB trb(1, 1, 224);
  BOOST_REQUIRE_EQUAL(trb.getID(), 1);
  BOOST_REQUIRE_EQUAL(trb.getType(), 1);
  BOOST_REQUIRE_EQUAL(trb.getChannel(), 224);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FactorySuite)

class TestParamGetter : public JPetParamGetter
{
  ParamObjectsDescriptions getAllBasicData(ParamObjectType, const int runId)
  {
    ParamObjectsDescriptions result;
    switch (runId) {
      case 0: //No TRBs
        break;
      case 1: //Simple single object
        result = {
          {1, {
                {"id", "1"},
                {"type", "1"},
                {"channel", "224"}
              }
          }
        };
        break;
      case 2: //Simple two objects
        result = {
          {1, {
                {"id", "1"},
                {"type", "1"},
                {"channel", "224"}
              }
          },
          {5, {
                {"id", "5"},
                {"type", "2"},
                {"channel", "225"}
              }
          }
        };
        break;
      case 3: //Object with missing field
        result = {
          {1, {
                {"id", "1"},
                {"channel", "224"}
              }
          }
        };
        break;
      case 4: //Object with wrong field
        result = {
          {1, {
                {"id", "1"},
                {"type", "torus"},
                {"channel", "224"}
              }
          }
        };
        break;
    }
    return result;
  }
  ParamRelationalData getAllRelationalData(ParamObjectType, ParamObjectType, const int) {return ParamRelationalData();} //Irrelevant for this test.
};

TestParamGetter paramGetter;

BOOST_AUTO_TEST_CASE( no_trbs )
{
  JPetTRBFactory factory(paramGetter, 0);
  auto & trbs = factory.getTRBs();
  BOOST_REQUIRE_EQUAL(trbs.size(), 0);
}

BOOST_AUTO_TEST_CASE( single_object )
{
  JPetTRBFactory factory(paramGetter, 1);
  auto & trbs = factory.getTRBs();
  BOOST_REQUIRE_EQUAL(trbs.size(), 1);
  auto trb = trbs[1];
  BOOST_REQUIRE_EQUAL(trb->getID(), 1);
  BOOST_REQUIRE_EQUAL(trb->getType(), 1);
  BOOST_REQUIRE_EQUAL(trb->getChannel(), 224);
}

BOOST_AUTO_TEST_CASE( two_objects )
{
  JPetTRBFactory factory(paramGetter, 2);
  auto & trbs = factory.getTRBs();
  BOOST_REQUIRE_EQUAL(trbs.size(), 2);
  auto trb = trbs[1];
  BOOST_REQUIRE_EQUAL(trb->getID(), 1);
  BOOST_REQUIRE_EQUAL(trb->getType(), 1);
  BOOST_REQUIRE_EQUAL(trb->getChannel(), 224);
  trb = trbs[5];
  BOOST_REQUIRE_EQUAL(trb->getID(), 5);
  BOOST_REQUIRE_EQUAL(trb->getType(), 2);
  BOOST_REQUIRE_EQUAL(trb->getChannel(), 225);
}

BOOST_AUTO_TEST_CASE( missing_field )
{
  JPetTRBFactory factory(paramGetter, 3);
  BOOST_REQUIRE_THROW(factory.getTRBs(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( wrong_field )
{
  JPetTRBFactory factory(paramGetter, 4);
  BOOST_REQUIRE_THROW(factory.getTRBs(), std::bad_cast);
}

BOOST_AUTO_TEST_SUITE_END()
