#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetFrameTest
#include <boost/test/unit_test.hpp>

#include "./JPetFrame/JPetFrame.h"
#include "./JPetFrame/JPetFrameFactory.h"

// JPetFrame();
// JPetFrame(int id, bool isActive, std::string status, std::string description, int version, int creator_id);
//
// inline bool operator==(const JPetFrame& frame) { return getId() == frame.getId(); }
// inline bool operator!=(const JPetFrame& frame) { return getId() != frame.getId(); }
// 
// int getId() const { return fId; }
// bool getIsActive() const { return fIsActive; }
// std::string getStatus() const { return fStatus; }
// std::string getDescription() const { return fDescription; }
// int getVersion() const { return fVersion; }
// int getCreator() const { return fCreator_id; }

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetFrame frame;
  BOOST_REQUIRE_EQUAL(frame.getID(), -1);
  BOOST_REQUIRE(!frame.getIsActive());
  BOOST_REQUIRE(frame.getStatus().empty());
  BOOST_REQUIRE(frame.getDescription().empty());
  BOOST_REQUIRE_EQUAL(frame.getVersion(), -1);
  BOOST_REQUIRE_EQUAL(frame.getCreator(), -1);
}

BOOST_AUTO_TEST_CASE( second_constructor )
{
  JPetFrame frame(1, true, "ok", "descr1", 2, 1);
  BOOST_REQUIRE_EQUAL(frame.getID(), 1);
  BOOST_REQUIRE(frame.getIsActive());
  BOOST_REQUIRE(frame.getStatus()=="ok");
  BOOST_REQUIRE(frame.getDescription()== "descr1");
  BOOST_REQUIRE_EQUAL(frame.getVersion(), 2);
  BOOST_REQUIRE_EQUAL(frame.getCreator(), 1);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(FactorySuite)

class TestParamGetter : public JPetParamGetter
{
  ParamObjectsDescriptions getAllBasicData(ParamObjectType, const int runId)
  {
    ParamObjectsDescriptions result;
    switch (runId) {
      case 0: //No frames
        break;
      case 1: //Simple single object
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
      case 2: //Simple two objects
        result = {
          {1, {
                {"id", "1"},
                {"active", "1"},
                {"status", "ok"},
                {"description", "descr1"},
                {"version", "2"},
                {"creator_id", "1"}
              }
          },
          {5, {
                {"id", "5"},
                {"active", "0"},
                {"status", "fainted"},
                {"description", "looks like a fish"},
                {"version", "1"},
                {"creator_id", "99"}
              }
          }
        };
        break;
      case 3: //Object with missing field
        result = {
          {1, {
                {"id", "1"},
                {"active", "1"},
                {"status", "ok"},
                {"version", "2"},
                {"creator_id", "1"}
              }
          }
        };
        break;
      case 4: //Object with wrong field
        result = {
          {1, {
                {"id", "1"},
                {"active", "probably"},
                {"status", "ok"},
                {"description", "descr1"},
                {"version", "2"},
                {"creator_id", "1"}
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

BOOST_AUTO_TEST_CASE( no_frames )
{
  JPetFrameFactory factory(paramGetter, 0);
  auto & frames = factory.getFrames();
  BOOST_REQUIRE_EQUAL(frames.size(), 0u);
}

BOOST_AUTO_TEST_CASE( single_object )
{
  JPetFrameFactory factory(paramGetter, 1);
  auto & frames = factory.getFrames();
  BOOST_REQUIRE_EQUAL(frames.size(), 1u);
  auto frame = frames[1];
  BOOST_REQUIRE_EQUAL(frame->getID(), 1);
  BOOST_REQUIRE(frame->getIsActive());
  BOOST_REQUIRE(frame->getStatus()=="ok");
  BOOST_REQUIRE(frame->getDescription()== "descr1");
  BOOST_REQUIRE_EQUAL(frame->getVersion(), 2);
  BOOST_REQUIRE_EQUAL(frame->getCreator(), 1);
}

BOOST_AUTO_TEST_CASE( two_objects )
{
  JPetFrameFactory factory(paramGetter, 2);
  auto & frames = factory.getFrames();
  BOOST_REQUIRE_EQUAL(frames.size(), 2u);
  auto frame = frames[1];
  BOOST_REQUIRE_EQUAL(frame->getID(), 1);
  BOOST_REQUIRE(frame->getIsActive());
  BOOST_REQUIRE(frame->getStatus()=="ok");
  BOOST_REQUIRE(frame->getDescription()== "descr1");
  BOOST_REQUIRE_EQUAL(frame->getVersion(), 2);
  BOOST_REQUIRE_EQUAL(frame->getCreator(), 1);
  frame = frames[5];
  BOOST_REQUIRE_EQUAL(frame->getID(), 5);
  BOOST_REQUIRE(!frame->getIsActive());
  BOOST_REQUIRE(frame->getStatus()=="fainted");
  BOOST_REQUIRE(frame->getDescription()== "looks like a fish");
  BOOST_REQUIRE_EQUAL(frame->getVersion(), 1);
  BOOST_REQUIRE_EQUAL(frame->getCreator(), 99);
}

BOOST_AUTO_TEST_CASE( missing_field )
{
  JPetFrameFactory factory(paramGetter, 3);
  BOOST_REQUIRE_THROW(factory.getFrames(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( wrong_field )
{
  JPetFrameFactory factory(paramGetter, 4);
  BOOST_REQUIRE_THROW(factory.getFrames(), std::bad_cast);
}

BOOST_AUTO_TEST_SUITE_END()
