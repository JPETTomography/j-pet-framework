#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSignalTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetSignal/JPetSignal.h"
#include "../../JPetSigCh/JPetSigCh.h"
#include <vector>
#include <algorithm>

//JPeSignal
// public methods:
// JPetSignal();
// JPetSignal(double time, double qual, bool left);
// virtual ~JPetSignal();
// inline float GetT() const;
// inline float GetQual() const;
// inline bool IsLeft() const;
             


BOOST_AUTO_TEST_SUITE(FirstSuite)
  
//BOOST_AUTO_TEST_CASE( default_constructor )
//{
//  JPetSignal signal;
//  BOOST_CHECK_EQUAL(signal.GetT(), 0); 
//  BOOST_CHECK_EQUAL(signal.GetQual(), 0); 
//  BOOST_CHECK_EQUAL(signal.IsLeft(), true); 
//  BOOST_CHECK_EQUAL(signal.GetNTresholds(JPetSignal::Trailing), 0); 
//  BOOST_CHECK_EQUAL(signal.GetNTresholds(JPetSignal::Leading), 0); 
//}
//
//BOOST_AUTO_TEST_CASE( some_init_constructor )
//{
//
//  std::vector<ExtendedThreshold> leading;
//  std::vector<ExtendedThreshold> trailing;
// 
//  JPetSignal signal(100, 2, false, leading, trailing);
//  BOOST_CHECK_EQUAL(signal.GetT(), 100); 
//  BOOST_CHECK_EQUAL(signal.GetQual(), 2); 
//  BOOST_CHECK_EQUAL(signal.IsLeft(), false); 
//  BOOST_CHECK_EQUAL(signal.GetNTresholds(JPetSignal::Trailing), 0); 
//  BOOST_CHECK_EQUAL(signal.GetNTresholds(JPetSignal::Leading), 0); 
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
//  BOOST_CHECK_EQUAL(signal.GetNTresholds(JPetSignal::Trailing), 1); 
//  BOOST_CHECK_EQUAL(signal.GetNTresholds(JPetSignal::Leading), 2); 
//  const std::vector<ExtendedThreshold>& resultLeading = signal.getLeadingPoints();
//  BOOST_CHECK_CLOSE( resultLeading.at(0).fThreshold,  leading.at(0).fThreshold, 0.01);
//  BOOST_CHECK_CLOSE( resultLeading.at(0).fTime,  leading.at(0).fTime, 0.01);
//  BOOST_CHECK_CLOSE( resultLeading.at(0).fQuality,  leading.at(0).fQuality, 0.01);
//  BOOST_CHECK_CLOSE( resultLeading.at(1).fTime,  leading.at(1).fTime, 0.01);
//  BOOST_CHECK_CLOSE( resultLeading.at(1).fTime,  leading.at(1).fTime, 0.01);
//  BOOST_CHECK_CLOSE( resultLeading.at(1).fQuality,  leading.at(1).fQuality, 0.01);
//  const std::vector<ExtendedThreshold>& resultTrailing = signal.getTrailingPoints();
//  BOOST_CHECK_CLOSE( resultTrailing.at(0).fTime,  trailing.at(0).fTime, 0.01);
//}

BOOST_AUTO_TEST_SUITE_END()
