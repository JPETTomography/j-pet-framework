#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetPMCalibTest
#include <boost/test/unit_test.hpp>
#include "JPetPMCalib.h"
#include "JPetPMCalibFactory.h"


const float epsilon = 0.0001f;

BOOST_AUTO_TEST_SUITE(JPetPMCalibTestSuite)

BOOST_AUTO_TEST_CASE(DefaultConstructorTest)
{
  JPetPMCalib pmCalib(256, "PMCalib", 2.f, 4.f, 8.f, 16.f, 32.f, 64, 128);
  BOOST_REQUIRE_EQUAL(pmCalib.getID(), 256);
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

BOOST_AUTO_TEST_SUITE(FactorySuite)

class TestParamGetter : public JPetParamGetter
{
  ParamObjectsDescriptions getAllBasicData(ParamObjectType, const int runId) {
    ParamObjectsDescriptions result;
    switch (runId) {
    case 0: //No pmCalibs
      break;
    case 1: //Simple single object
      result = {
        {
          1, {
            {"id", "1"},
            {"name", "PMCalib"},
            {"opthv", "2"},
            {"c2e1", "4"},
            {"c2e2", "8"},
            {"gain_alpha", "16"},
            {"gain_beta", "32"},
            {"assignment_id", "64"},
            {"assignment_photomultiplier_id", "128"}
          }
        }
      };
      break;
    case 2: //Simple two objects
      result = {
        {
          1, {
            {"id", "1"},
            {"name", "PMCalib"},
            {"opthv", "2"},
            {"c2e1", "4"},
            {"c2e2", "8"},
            {"gain_alpha", "16"},
            {"gain_beta", "32"},
            {"assignment_id", "64"},
            {"assignment_photomultiplier_id", "128"}
          }
        },
        {
          5, {
            {"id", "5"},
            {"name", "PMMorab"},
            {"opthv", "3"},
            {"c2e1", "5"},
            {"c2e2", "9"},
            {"gain_alpha", "17"},
            {"gain_beta", "33"},
            {"assignment_id", "65"},
            {"assignment_photomultiplier_id", "129"}
          }
        }
      };
      break;
    case 3: //Object with missing field
      result = {
        {
          1, {
            {"id", "1"},
            {"opthv", "2"},
            {"c2e1", "4"},
            {"c2e2", "8"},
            {"gain_alpha", "16"},
            {"gain_beta", "32"},
            {"assignment_id", "64"},
            {"assignment_photomultiplier_id", "128"}
          }
        }
      };
      break;
    case 4: //Object with wrong field
      result = {
        {
          1, {
            {"id", "1"},
            {"name", "PMCalib"},
            {"opthv", "whatisthis"},
            {"c2e1", "4"},
            {"c2e2", "8"},
            {"gain_alpha", "16"},
            {"gain_beta", "32"},
            {"assignment_id", "64"},
            {"assignment_photomultiplier_id", "128"}
          }
        }
      };
      break;
    }
    return result;
  }
  ParamRelationalData getAllRelationalData(ParamObjectType, ParamObjectType, const int) {
    return ParamRelationalData(); //Irrelevant for this test.
  }
};

TestParamGetter paramGetter;

BOOST_AUTO_TEST_CASE( no_pmCalibs )
{
  JPetPMCalibFactory factory(paramGetter, 0);
  auto& pmCalibs = factory.getPMCalibs();
  BOOST_REQUIRE_EQUAL(pmCalibs.size(), 0u);
}

BOOST_AUTO_TEST_CASE( single_object )
{
  JPetPMCalibFactory factory(paramGetter, 1);
  auto& pmCalibs = factory.getPMCalibs();
  BOOST_REQUIRE_EQUAL(pmCalibs.size(), 1u);
  auto pmCalib = pmCalibs[1];
  BOOST_REQUIRE_EQUAL(pmCalib->getID(), 1);
  BOOST_REQUIRE_EQUAL(pmCalib->GetNamePM(), "PMCalib");
  BOOST_REQUIRE_CLOSE(pmCalib->GetOpthv(), 2.f, epsilon);
  BOOST_REQUIRE_CLOSE(pmCalib->GetECalConst1(), 4.f, epsilon);
  BOOST_REQUIRE_CLOSE(pmCalib->GetECalConst2(), 8.f, epsilon);
  BOOST_REQUIRE_CLOSE(pmCalib->GetGainalpha(), 16.f, epsilon);
  BOOST_REQUIRE_CLOSE(pmCalib->GetGainbeta(), 32.f, epsilon);
  BOOST_REQUIRE_EQUAL(pmCalib->GetPMCalibAssignment().id, 64);
  BOOST_REQUIRE_EQUAL(pmCalib->GetPMCalibAssignment().photomultiplier_id, 128);
}

BOOST_AUTO_TEST_CASE( two_objects )
{
  JPetPMCalibFactory factory(paramGetter, 2);
  auto& pmCalibs = factory.getPMCalibs();
  BOOST_REQUIRE_EQUAL(pmCalibs.size(), 2u);
  auto pmCalib = pmCalibs[1];
  BOOST_REQUIRE_EQUAL(pmCalib->getID(), 1);
  BOOST_REQUIRE_EQUAL(pmCalib->GetNamePM(), "PMCalib");
  BOOST_REQUIRE_CLOSE(pmCalib->GetOpthv(), 2.f, epsilon);
  BOOST_REQUIRE_CLOSE(pmCalib->GetECalConst1(), 4.f, epsilon);
  BOOST_REQUIRE_CLOSE(pmCalib->GetECalConst2(), 8.f, epsilon);
  BOOST_REQUIRE_CLOSE(pmCalib->GetGainalpha(), 16.f, epsilon);
  BOOST_REQUIRE_CLOSE(pmCalib->GetGainbeta(), 32.f, epsilon);
  BOOST_REQUIRE_EQUAL(pmCalib->GetPMCalibAssignment().id, 64);
  BOOST_REQUIRE_EQUAL(pmCalib->GetPMCalibAssignment().photomultiplier_id, 128);
  pmCalib = pmCalibs[5];
  BOOST_REQUIRE_EQUAL(pmCalib->getID(), 5);
  BOOST_REQUIRE_EQUAL(pmCalib->GetNamePM(), "PMMorab");
  BOOST_REQUIRE_CLOSE(pmCalib->GetOpthv(), 3.f, epsilon);
  BOOST_REQUIRE_CLOSE(pmCalib->GetECalConst1(), 5.f, epsilon);
  BOOST_REQUIRE_CLOSE(pmCalib->GetECalConst2(), 9.f, epsilon);
  BOOST_REQUIRE_CLOSE(pmCalib->GetGainalpha(), 17.f, epsilon);
  BOOST_REQUIRE_CLOSE(pmCalib->GetGainbeta(), 33.f, epsilon);
  BOOST_REQUIRE_EQUAL(pmCalib->GetPMCalibAssignment().id, 65);
  BOOST_REQUIRE_EQUAL(pmCalib->GetPMCalibAssignment().photomultiplier_id, 129);
}

BOOST_AUTO_TEST_CASE( missing_field )
{
  JPetPMCalibFactory factory(paramGetter, 3);
  BOOST_REQUIRE_THROW(factory.getPMCalibs(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE( wrong_field )
{
  JPetPMCalibFactory factory(paramGetter, 4);
  BOOST_REQUIRE_THROW(factory.getPMCalibs(), std::bad_cast);
}

BOOST_AUTO_TEST_SUITE_END()
