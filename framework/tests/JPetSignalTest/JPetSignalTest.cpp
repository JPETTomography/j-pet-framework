#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSignalTest

#include <boost/test/unit_test.hpp>
#include "../../JPetSignal/JPetSignal.h"


// Tests
BOOST_AUTO_TEST_SUITE(ParamDataTS)

BOOST_AUTO_TEST_CASE(TimeTest)
{
  JPetSignal signal;
  signal.SetTime(8.f);
  
  BOOST_REQUIRE_EQUAL(signal.GetTime(), 8.f);
}

BOOST_AUTO_TEST_CASE(EnergyTest)
{
  JPetSignal signal;
  signal.SetEnergy(16.f);
  
  BOOST_REQUIRE_EQUAL(signal.GetEnergy(), 16.f);
}

BOOST_AUTO_TEST_CASE(QualityOfTimeTest)
{
  JPetSignal signal;
  
  BOOST_REQUIRE_EQUAL(signal.GetQualityOfTime(), 0.f);
}

BOOST_AUTO_TEST_CASE(QualityOfEnergyTest)
{
  JPetSignal signal;
  
  BOOST_REQUIRE_EQUAL(signal.GetQualityOfEnergy(), 0.f);
}

BOOST_AUTO_TEST_CASE(IsLeftTest)
{
  JPetSignal signal;
  
  BOOST_REQUIRE_EQUAL(signal.IsLeft(), true);
}

BOOST_AUTO_TEST_CASE(GetNPointsTest)
{
  JPetSignal signal;

  BOOST_REQUIRE_EQUAL(signal.GetNPoints(JPetSigCh::Trailing), 0);
  BOOST_REQUIRE_EQUAL(signal.GetNPoints(JPetSigCh::Leading), 0);
}

BOOST_AUTO_TEST_CASE(AddLeadingPointTest)
{
  JPetSignal      signal;
  const JPetSigCh sigCh;

  signal.AddPoint(sigCh);
  BOOST_REQUIRE_EQUAL(signal.GetNPoints(JPetSigCh::Leading), 1);
}

BOOST_AUTO_TEST_CASE(AddTrailingPointTest)
{
  JPetSignal      signal;
  const JPetSigCh sigCh(JPetSigCh::Trailing, 8.f);

  signal.AddPoint(sigCh);
  BOOST_REQUIRE_EQUAL(signal.GetNPoints(JPetSigCh::Trailing), 1);
}

BOOST_AUTO_TEST_CASE(GetNullPointsTest)
{
  JPetSignal signal;
  BOOST_CHECK(signal.GetPoints(JPetSigCh::Trailing)[0] == NULL);
  BOOST_CHECK(signal.GetPoints(JPetSigCh::Leading)[0] == NULL);
}

BOOST_AUTO_TEST_CASE(GetTrailingAndLeadingPointsTest)
{
  JPetSignal signal;
  JPetSigCh  sigCh(JPetSigCh::Trailing, 8.f);

  signal.AddPoint(sigCh);
  BOOST_CHECK( ( (JPetSigCh*)signal.GetPoints(JPetSigCh::Trailing)[0] )->GetType() == JPetSigCh::Trailing);
  BOOST_CHECK(signal.GetPoints(JPetSigCh::Trailing)[1] == NULL);
  BOOST_CHECK(signal.GetNumberOfSetTrailingEdgePoints() == 1);
  
  sigCh.SetType(JPetSigCh::Leading);
  signal.AddPoint(sigCh);
  BOOST_CHECK( ( (JPetSigCh*)signal.GetPoints(JPetSigCh::Leading)[0] )->GetType() == JPetSigCh::Leading);
}

BOOST_AUTO_TEST_CASE(GetTrailingAndLeadingPointTest)
{
  JPetSignal signal;
  JPetSigCh  sigCh(JPetSigCh::Trailing, 8.f);

  signal.AddPoint(sigCh);
  signal.AddPoint(sigCh);
  sigCh.SetType(JPetSigCh::Leading);
  signal.AddPoint(sigCh);
  signal.AddPoint(sigCh);
  BOOST_CHECK(signal.GetNumberOfSetTrailingEdgePoints() == 2);
  BOOST_CHECK(signal.GetNumberOfSetLeadingEdgePoints() == 2);
  
  sigCh = signal.GetPoint(0, JPetSigCh::Trailing);
  BOOST_CHECK(sigCh.GetType() == JPetSigCh::Trailing);
  
  sigCh = signal.GetPoint(1, JPetSigCh::Leading);
  BOOST_CHECK(sigCh.GetType() == JPetSigCh::Leading);
}

BOOST_AUTO_TEST_CASE(SetAndGetTSlotIndexTest)
{
  JPetSignal signal;
  signal.SetTSlotIndex(8);
  BOOST_CHECK(signal.GetTSlotIndex() == 8);
}

BOOST_AUTO_TEST_CASE(SetAndGetPMIDTest)
{
  JPetSignal signal;
  signal.SetPMID(Int_t(16));
  BOOST_CHECK(signal.GetPMID() == Int_t(16));
}

BOOST_AUTO_TEST_CASE(SetAndGetTRefPMObjectTest)
{
  JPetSignal signal;
  JPetPM *PM = new JPetPM;
  signal.SetPM(PM);
  PM = signal.GetPM();
  
  BOOST_CHECK(PM->getSide() == JPetPM::kLeft);
  
  delete PM;
}

BOOST_AUTO_TEST_CASE(SetAndGetTRefBarrelSlotObjectTest)
{
  JPetSignal signal;
  JPetBarrelSlot *barrelSlot = new JPetBarrelSlot;
  signal.SetBarrelSlot(barrelSlot);
  barrelSlot = signal.GetBarrelSlot();
  
  BOOST_CHECK(barrelSlot->getSlotID() == 0);
  
  delete barrelSlot;
}

BOOST_AUTO_TEST_SUITE_END()









//JPeSignal
// public methods:
// JPetSignal();
// JPetSignal(double time, double qual, bool left);
// virtual ~JPetSignal();
// inline float GetT() const;
// inline float GetQual() const;
// inline bool IsLeft() const;
             


//BOOST_AUTO_TEST_SUITE(FirstSuite)
  
//BOOST_AUTO_TEST_CASE( default_constructor )
//{
//  JPetSignal signal;
//  BOOST_REQUIRE_EQUAL(signal.GetT(), 0); 
//  BOOST_REQUIRE_EQUAL(signal.GetQual(), 0); 
//  BOOST_REQUIRE_EQUAL(signal.IsLeft(), true); 
//  BOOST_REQUIRE_EQUAL(signal.GetNTresholds(JPetSignal::Trailing), 0); 
//  BOOST_REQUIRE_EQUAL(signal.GetNTresholds(JPetSignal::Leading), 0); 
//}
//
//BOOST_AUTO_TEST_CASE( some_init_constructor )
//{
//
//  std::vector<ExtendedThreshold> leading;
//  std::vector<ExtendedThreshold> trailing;
// 
//  JPetSignal signal(100, 2, false, leading, trailing);
//  BOOST_REQUIRE_EQUAL(signal.GetT(), 100); 
//  BOOST_REQUIRE_EQUAL(signal.GetQual(), 2); 
//  BOOST_REQUIRE_EQUAL(signal.IsLeft(), false); 
//  BOOST_REQUIRE_EQUAL(signal.GetNTresholds(JPetSignal::Trailing), 0); 
//  BOOST_REQUIRE_EQUAL(signal.GetNTresholds(JPetSignal::Leading), 0); 
//  
//}
//
//BOOST_AUTO_TEST_CASE( gettersPointsTest )
//{
//
//  std::vector<ExtendedThreshold> leading;
//  ExtendedThreshold thresh;
//  thresh.fThreshold = 2;
//  thresh.fTime = 2.5;
//  thresh.fQuality = 10;
//  leading.push_back(thresh);
//  thresh.fThreshold = 10;
//  thresh.fTime = 100;
//  thresh.fQuality = 50;
//  thresh.fSigCh = JPetSigCh(5); 
//  leading.push_back(thresh);
//  std::vector<ExtendedThreshold> trailing;
//  thresh.fSigCh = JPetSigCh(1000); 
//  thresh.fThreshold = 1100;
//  trailing.push_back(thresh);
// 
//  JPetSignal signal(100, 2, false, leading, trailing);
//  BOOST_REQUIRE_EQUAL(signal.GetNTresholds(JPetSignal::Trailing), 1); 
//  BOOST_REQUIRE_EQUAL(signal.GetNTresholds(JPetSignal::Leading), 2); 
//  const std::vector<ExtendedThreshold>& resultLeading = signal.getLeadingPoints();
//  BOOST_REQUIRE_CLOSE( resultLeading.at(0).fThreshold,  leading.at(0).fThreshold, 0.01);
//  BOOST_REQUIRE_CLOSE( resultLeading.at(0).fTime,  leading.at(0).fTime, 0.01);
//  BOOST_REQUIRE_CLOSE( resultLeading.at(0).fQuality,  leading.at(0).fQuality, 0.01);
//  BOOST_REQUIRE_CLOSE( resultLeading.at(1).fTime,  leading.at(1).fTime, 0.01);
//  BOOST_REQUIRE_CLOSE( resultLeading.at(1).fTime,  leading.at(1).fTime, 0.01);
//  BOOST_REQUIRE_CLOSE( resultLeading.at(1).fQuality,  leading.at(1).fQuality, 0.01);
//  const std::vector<ExtendedThreshold>& resultTrailing = signal.getTrailingPoints();
//  BOOST_REQUIRE_CLOSE( resultTrailing.at(0).fTime,  trailing.at(0).fTime, 0.01);
//}

//BOOST_AUTO_TEST_SUITE_END()
