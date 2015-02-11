#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetFrameTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetFrame/JPetFrame.h"

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
  BOOST_REQUIRE_EQUAL(frame.getId(), -1);
  BOOST_REQUIRE(!frame.getIsActive());
  BOOST_REQUIRE(frame.getStatus().empty());
  BOOST_REQUIRE(frame.getDescription().empty());
  BOOST_REQUIRE_EQUAL(frame.getVersion(), -1);
  BOOST_REQUIRE_EQUAL(frame.getCreator(), -1);
}

BOOST_AUTO_TEST_CASE( second_constructor )
{
  JPetFrame frame(1, true, "ok", "descr1", 2.0, 1);
  BOOST_REQUIRE_EQUAL(frame.getId(), 1);
  BOOST_REQUIRE(frame.getIsActive());
  BOOST_REQUIRE(frame.getStatus()=="ok");
  BOOST_REQUIRE(frame.getDescription()== "descr1");
  BOOST_REQUIRE_EQUAL(frame.getVersion(), 2.0);
  BOOST_REQUIRE_EQUAL(frame.getCreator(), 1);
}

BOOST_AUTO_TEST_SUITE_END()
