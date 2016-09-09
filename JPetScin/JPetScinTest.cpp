#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetScinTest
#include <boost/test/unit_test.hpp>
#include "JPetScin.h"
#include "JPetScinFactory.h"



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

const float epsilon = 0.0001;

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetScin scint;
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
  JPetScin scint(1, 10.34, 100, 4.5, 2.5);
  BOOST_REQUIRE_EQUAL(scint.getID(), 1);
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

BOOST_AUTO_TEST_SUITE(FactorySuite)

class TestParamGetter : public JPetParamGetter
{
  ParamObjectsDescriptions getAllBasicData(ParamObjectType type, const int runId)
  {
    ParamObjectsDescriptions result;
    switch (type) {
      case ParamObjectType::kScintillator:
        switch (runId) {
          case 0: //No scins
            break;
          case 1: //Simple single object
          case 5: //Wrong relation
            result = {
              {1, {
                    {"id", "1"},
                    {"attenuation_length", "10.34"},
                    {"length", "100"},
                    {"width", "4.5"},
                    {"height", "2.5"}
                  }
              }
            };
            break;
          case 2: //Simple two objects
            result = {
              {1, {
                    {"id", "1"},
                    {"attenuation_length", "10.34"},
                    {"length", "100"},
                    {"width", "4.5"},
                    {"height", "2.5"}
                  }
              },
              {5, {
                    {"id", "5"},
                    {"attenuation_length", "11.34"},
                    {"length", "101"},
                    {"width", "5.5"},
                    {"height", "3.5"}
                  }
              }
            };
            break;
          case 3: //Object with missing field
            result = {
              {1, {
                    {"id", "1"},
                    {"length", "100"},
                    {"width", "4.5"},
                    {"height", "2.5"}
                  }
              }
            };
            break;
          case 4: //Object with wrong field
            result = {
              {1, {
                    {"id", "1"},
                    {"attenuation_length", "none"},
                    {"length", "100"},
                    {"width", "4.5"},
                    {"height", "2.5"}
                  }
              }
            };
            break;
        }
        break;
      case ParamObjectType::kBarrelSlot:
        result = {
          {1, {
                {"id", "1"},
                {"active", "1"},
                {"name", "pepe"},
                {"theta1", "5.5"},
                {"frame_id", "6"}
              }
          }
        };
        break;
      case ParamObjectType::kLayer:
        result = {
          {1, {
                {"id", "1"},
                {"active", "1"},
                {"name", "ala"},
                {"radius", "10.5"}
              }
          }
        };
        break;
      case ParamObjectType::kFrame:
        result = {
          {1, {
                {"id", "1"},
                {"active", "1"},
                {"status", "ok"},
                {"description", "descr1"},
                {"version", "2"},
                {"creator_id", "1"}
              }
          }
        };
        break;
      default: //Other cases not needed.
        break;
    }
    return result;
  }
  ParamRelationalData getAllRelationalData(ParamObjectType type1, ParamObjectType, const int runId)
  {
    ParamRelationalData result;
    switch (type1) {
      case ParamObjectType::kScintillator:
        switch (runId) {
          case 0: //No relations
            break;
          case 1: //Simple single object
            result = {
              {1, 1}
            };
            break;
          case 2: //Simple two objects
            result = {
              {1, 1},
              {5, 1}
            };
            break;
          case 5: //Wrong relation
            result = {
              {1, 43}
            };
            break;
        }
        break;
      case ParamObjectType::kBarrelSlot:
      case ParamObjectType::kLayer:
        result = {
          {1, 1}
        };
        break;
      default: //Other cases not needed.
        break;
    }
    return result;
  }
};

TestParamGetter paramGetter;

BOOST_AUTO_TEST_CASE( no_scins )
{
  JPetFrameFactory frameFactory(paramGetter, 0);
  JPetLayerFactory layerFactory(paramGetter, 0, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 0, layerFactory);
  JPetScinFactory factory(paramGetter, 0, barrelSlotFactory);
  auto & scins = factory.getScins();
  BOOST_REQUIRE_EQUAL(scins.size(), 0);
}

BOOST_AUTO_TEST_CASE( single_object )
{
  JPetFrameFactory frameFactory(paramGetter, 1);
  JPetLayerFactory layerFactory(paramGetter, 1, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 1, layerFactory);
  JPetScinFactory factory(paramGetter, 1, barrelSlotFactory);
  auto & scins = factory.getScins();
  BOOST_REQUIRE_EQUAL(scins.size(), 1);
  auto scin = scins[1];
  BOOST_REQUIRE_EQUAL(scin->getID(), 1);
  BOOST_REQUIRE_CLOSE(scin->getAttenLen(), 10.34, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getScinSize(JPetScin::kLength), 100, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getScinSize(JPetScin::kHeight), 4.5, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getScinSize(JPetScin::kWidth), 2.5, epsilon);

  BOOST_REQUIRE_EQUAL(scin->getBarrelSlot().getID(), barrelSlotFactory.getBarrelSlots().at(1)->getID());
}

BOOST_AUTO_TEST_CASE( two_objects )
{
  JPetFrameFactory frameFactory(paramGetter, 2);
  JPetLayerFactory layerFactory(paramGetter, 2, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 2, layerFactory);
  JPetScinFactory factory(paramGetter, 2, barrelSlotFactory);
  auto & scins = factory.getScins();
  BOOST_REQUIRE_EQUAL(scins.size(), 2);
  auto scin = scins[1];
  BOOST_REQUIRE_EQUAL(scin->getID(), 1);
  BOOST_REQUIRE_CLOSE(scin->getAttenLen(), 10.34, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getScinSize(JPetScin::kLength), 100, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getScinSize(JPetScin::kHeight), 4.5, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getScinSize(JPetScin::kWidth), 2.5, epsilon);

  BOOST_REQUIRE_EQUAL(scin->getBarrelSlot().getID(), barrelSlotFactory.getBarrelSlots().at(1)->getID());

  scin = scins[5];
  BOOST_REQUIRE_EQUAL(scin->getID(), 5);
  BOOST_REQUIRE_CLOSE(scin->getAttenLen(), 11.34, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getScinSize(JPetScin::kLength), 101, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getScinSize(JPetScin::kHeight), 5.5, epsilon);
  BOOST_REQUIRE_CLOSE(scin->getScinSize(JPetScin::kWidth), 3.5, epsilon);

  BOOST_REQUIRE_EQUAL(scin->getBarrelSlot().getID(), barrelSlotFactory.getBarrelSlots().at(1)->getID());
}

BOOST_AUTO_TEST_CASE( missing_field )
{
  JPetFrameFactory frameFactory(paramGetter, 3);
  JPetLayerFactory layerFactory(paramGetter, 3, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 3, layerFactory);
  JPetScinFactory factory(paramGetter, 3, barrelSlotFactory);
  BOOST_REQUIRE_THROW(factory.getScins(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( wrong_field )
{
  JPetFrameFactory frameFactory(paramGetter, 4);
  JPetLayerFactory layerFactory(paramGetter, 4, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 4, layerFactory);
  JPetScinFactory factory(paramGetter, 4, barrelSlotFactory);
  BOOST_REQUIRE_THROW(factory.getScins(), std::bad_cast);
}

BOOST_AUTO_TEST_CASE( wrong_relation )
{
  JPetFrameFactory frameFactory(paramGetter, 5);
  JPetLayerFactory layerFactory(paramGetter, 5, frameFactory);
  JPetBarrelSlotFactory barrelSlotFactory(paramGetter, 5, layerFactory);
  JPetScinFactory factory(paramGetter, 5, barrelSlotFactory);
  BOOST_REQUIRE_THROW(factory.getScins(), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()
