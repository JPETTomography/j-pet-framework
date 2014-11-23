#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetPMCalibTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetPMCalib/JPetPMCalib.h"


BOOST_AUTO_TEST_SUITE(JPetPMCalibTS)

BOOST_AUTO_TEST_CASE(DefaultConstructorTest)
{
  JPetPMCalib pmCalib(256, "PMCalib", 2.f, 4.f, 8.f, 16.f, 32.f, 64, 128);
  float epsilon = 0.0001f;
  BOOST_REQUIRE_EQUAL(pmCalib.GetId(), 256);
  BOOST_REQUIRE_EQUAL(pmCalib.GetNamePM(), "PMCalib");
  BOOST_REQUIRE_CLOSE(pmCalib.GetOpthv(), 2.f, epsilon);
  BOOST_REQUIRE_CLOSE(pmCalib.GetECalConst1(), 4.f, epsilon);
  BOOST_REQUIRE_CLOSE(pmCalib.GetECalConst2(), 8.f, epsilon);
  BOOST_REQUIRE_CLOSE(pmCalib.GetGainalpha(), 16.f, epsilon);
  BOOST_REQUIRE_CLOSE(pmCalib.GetGainbeta(), 32.f, epsilon);
  BOOST_REQUIRE_EQUAL(pmCalib.GetPMCalibAssignment().id, 64);
  BOOST_REQUIRE_EQUAL(pmCalib.GetPMCalibAssignment().photomultiplier_id, 128);
}

BOOST_AUTO_TEST_SUITE_END()
