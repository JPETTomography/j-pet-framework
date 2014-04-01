#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSignalTest 
#include <boost/test/unit_test.hpp>

#define private public

#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetSignal/JPetSignal.h"
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
  
BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetSignal signal;
  BOOST_CHECK_EQUAL(signal.GetT(), 0); 
  BOOST_CHECK_EQUAL(signal.GetQual(), 0); 
  BOOST_CHECK_EQUAL(signal.IsLeft(), true); 
  BOOST_CHECK_EQUAL(signal.GetNTresholds(JPetSignal::kRising), 0); 
  BOOST_CHECK_EQUAL(signal.GetNTresholds(JPetSignal::kFalling), 0); 
}

BOOST_AUTO_TEST_CASE( some_init_constructor )
{

  std::vector<ExtendedThreshold> falling;
  std::vector<ExtendedThreshold> rising;
 
  JPetSignal signal(100, 2, false, falling, rising);
  BOOST_CHECK_EQUAL(signal.GetT(), 100); 
  BOOST_CHECK_EQUAL(signal.GetQual(), 2); 
  BOOST_CHECK_EQUAL(signal.IsLeft(), false); 
  BOOST_CHECK_EQUAL(signal.GetNTresholds(JPetSignal::kRising), 0); 
  BOOST_CHECK_EQUAL(signal.GetNTresholds(JPetSignal::kFalling), 0); 
  
}

BOOST_AUTO_TEST_CASE( gettersPointsTest )
{

  std::vector<ExtendedThreshold> falling;
  ExtendedThreshold thresh;
  thresh.fThreshold = 2;
  thresh.fTime = 2.5;
  thresh.fQuality = 10;
  falling.push_back(thresh);
  thresh.fThreshold = 10;
  thresh.fTime = 100;
  thresh.fQuality = 50;
  thresh.fSigCh = JPetSigCh(5); 
  falling.push_back(thresh);
  std::vector<ExtendedThreshold> rising;
  thresh.fSigCh = JPetSigCh(1000); 
  thresh.fThreshold = 1100;
  rising.push_back(thresh);
 
  JPetSignal signal(100, 2, false, falling, rising);
  BOOST_CHECK_EQUAL(signal.GetNTresholds(JPetSignal::kRising), 1); 
  BOOST_CHECK_EQUAL(signal.GetNTresholds(JPetSignal::kFalling), 2); 
  const std::vector<ExtendedThreshold>& resultFalling = signal.getFallingPoints();
  BOOST_CHECK_CLOSE( resultFalling.at(0).fThreshold,  falling.at(0).fThreshold, 0.01);
  BOOST_CHECK_CLOSE( resultFalling.at(0).fTime,  falling.at(0).fTime, 0.01);
  BOOST_CHECK_CLOSE( resultFalling.at(0).fQuality,  falling.at(0).fQuality, 0.01);
  BOOST_CHECK_CLOSE( resultFalling.at(1).fTime,  falling.at(1).fTime, 0.01);
  BOOST_CHECK_CLOSE( resultFalling.at(1).fTime,  falling.at(1).fTime, 0.01);
  BOOST_CHECK_CLOSE( resultFalling.at(1).fQuality,  falling.at(1).fQuality, 0.01);
  const std::vector<ExtendedThreshold>& resultRising = signal.getRisingPoints();
  BOOST_CHECK_CLOSE( resultRising.at(0).fTime,  rising.at(0).fTime, 0.01);
}

BOOST_AUTO_TEST_SUITE_END()
