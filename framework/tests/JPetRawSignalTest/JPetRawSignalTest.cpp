#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSignalTest

#include <boost/test/unit_test.hpp>
#include "../../JPetRawSignal/JPetRawSignal.h"
#include "../../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../../JPetPM/JPetPM.h"

// Tests
BOOST_AUTO_TEST_SUITE(ParamDataTS)

BOOST_AUTO_TEST_CASE(ToTTest) {
  JPetSigCh sigch;
  sigch.setType(JPetSigCh::Charge);
  sigch.setValue(17.f);
  JPetRawSignal signal;
  signal.addPoint(sigch);

  BOOST_REQUIRE_EQUAL(signal.getTOT(), 17.f);

  JPetRawSignal signal2;
  signal2.setTOTPoint(sigch);

  BOOST_REQUIRE_EQUAL(signal2.getTOT(), 17.f);
}

//
//BOOST_AUTO_TEST_CASE(QualityOfTimeTest) {
//  JPetSignal signal;
//
//  BOOST_REQUIRE_EQUAL(signal.getQualityOfTime(), 0.f);
//}
//
//BOOST_AUTO_TEST_CASE(QualityOfEnergyTest) {
//  JPetSignal signal;
//
//  BOOST_REQUIRE_EQUAL(signal.getQualityOfEnergy(), 0.f);
//}

BOOST_AUTO_TEST_CASE(GetNPointsTest) {
  JPetRawSignal signal;

  BOOST_REQUIRE_EQUAL(signal.getNPoints(JPetSigCh::Trailing), 0);
  BOOST_REQUIRE_EQUAL(signal.getNPoints(JPetSigCh::Leading), 0);
  BOOST_REQUIRE_EQUAL(signal.getNumberOfLeadingEdgePoints(), 0);
  BOOST_REQUIRE_EQUAL(signal.getNumberOfTrailingEdgePoints(), 0);

}

BOOST_AUTO_TEST_CASE(AddLeadingPointTest) {
  JPetRawSignal signal;
  const JPetSigCh sigCh;

  signal.addPoint(sigCh);
  BOOST_REQUIRE_EQUAL(signal.getNPoints(JPetSigCh::Leading), 1);
  BOOST_REQUIRE_EQUAL(signal.getNumberOfLeadingEdgePoints(), 1);
}

BOOST_AUTO_TEST_CASE(AddTrailingPointTest) {
  JPetRawSignal signal;
  const JPetSigCh sigCh(JPetSigCh::Trailing, 8.f);

  signal.addPoint(sigCh);
  BOOST_REQUIRE_EQUAL(signal.getNPoints(JPetSigCh::Trailing), 1);
  BOOST_REQUIRE_EQUAL(signal.getNumberOfTrailingEdgePoints(), 1);
}

BOOST_AUTO_TEST_CASE(GetVectorOfPointsTest) {
  JPetRawSignal signal;
  JPetSigCh sigch1(JPetSigCh::Trailing, 8.f);
  sigch1.setThreshold(100.f);
  sigch1.setThresholdNumber(2);
  JPetSigCh sigch2(JPetSigCh::Trailing, 17.f);
  sigch2.setThreshold(200.f);
  sigch2.setThresholdNumber(1);

  signal.addPoint(sigch1);
  signal.addPoint(sigch2);

  BOOST_REQUIRE_EQUAL(
      signal.getPoints(JPetSigCh::Trailing, JPetRawSignal::ByThrNum).at(0).getValue(),
      17.f);

  BOOST_REQUIRE_EQUAL(
      signal.getPoints(JPetSigCh::Trailing, JPetRawSignal::ByThrValue).at(0).getValue(),
      8.f);

  BOOST_REQUIRE_EQUAL(
      signal.getPoints(JPetSigCh::Leading, JPetRawSignal::ByThrValue).size(),
      0);

}

BOOST_AUTO_TEST_CASE(GetMapOfTimesVsThrNumTest) {

  JPetRawSignal signal;
  JPetSigCh sigch1(JPetSigCh::Trailing, 8.f);
  sigch1.setThreshold(100.f);
  sigch1.setThresholdNumber(1);
  JPetSigCh sigch2(JPetSigCh::Trailing, 17.f);
  sigch2.setThreshold(200.f);
  sigch2.setThresholdNumber(2);
  JPetSigCh sigch3(JPetSigCh::Trailing, 43.f);
  sigch3.setThreshold(400.f);
  sigch3.setThresholdNumber(4);

  signal.addPoint(sigch1);
  signal.addPoint(sigch2);
  signal.addPoint(sigch3);

  std::map<int, double> map;
  map = signal.getTimesVsThresholdNumber(JPetSigCh::Trailing);

  BOOST_REQUIRE_EQUAL( map[sigch1.getThresholdNumber()], sigch1.getValue() );
  BOOST_REQUIRE_EQUAL( map[sigch2.getThresholdNumber()], sigch2.getValue() );
  BOOST_REQUIRE_EQUAL( map[sigch3.getThresholdNumber()], sigch3.getValue() );
  BOOST_REQUIRE_EQUAL( map[3], 0.f );
}

BOOST_AUTO_TEST_CASE(GetMapOfTimesVsThrValueTest) {

  JPetRawSignal signal;
  JPetSigCh sigch1(JPetSigCh::Trailing, 8.f);
  sigch1.setThreshold(100.f);
  sigch1.setThresholdNumber(1);
  JPetSigCh sigch2(JPetSigCh::Trailing, 17.f);
  sigch2.setThreshold(200.f);
  sigch2.setThresholdNumber(2);
  JPetSigCh sigch3(JPetSigCh::Trailing, 43.f);
  sigch3.setThreshold(400.f);
  sigch3.setThresholdNumber(4);

  signal.addPoint(sigch1);
  signal.addPoint(sigch2);
  signal.addPoint(sigch3);

  std::map<int, double> map;
  map = signal.getTimesVsThresholdValue(JPetSigCh::Trailing);

  BOOST_REQUIRE_EQUAL( map[100], sigch1.getValue() );
  BOOST_REQUIRE_EQUAL( map[sigch2.getThreshold()], sigch2.getValue() );
  BOOST_REQUIRE_EQUAL( map[sigch3.getThreshold()], sigch3.getValue() );
  BOOST_REQUIRE_EQUAL( map[300], 0.f );
}


BOOST_AUTO_TEST_CASE(SetAndGetTSlotIndexTest) {
  JPetRawSignal signal;
  signal.setTSlotIndex(8);
  BOOST_CHECK(signal.getTSlotIndex() == 8);
}

BOOST_AUTO_TEST_CASE(SetAndGetTRefPMObjectTest) {
  JPetRawSignal signal;
  JPetPM PM;
  signal.setPM(PM);
  PM = signal.getPM();

  BOOST_CHECK(PM.getSide() == JPetPM::SideA);

}

BOOST_AUTO_TEST_CASE(SetAndGetTRefBarrelSlotObjectTest) {
  JPetRawSignal signal;
  JPetBarrelSlot barrelSlot(2, true, "bs2", 30., 2);
  signal.setBarrelSlot(barrelSlot);
  barrelSlot = signal.getBarrelSlot();

  BOOST_CHECK(barrelSlot.getID() == 2);

}

BOOST_AUTO_TEST_SUITE_END()

