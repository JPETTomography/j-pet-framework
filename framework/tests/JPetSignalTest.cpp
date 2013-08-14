#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSignalTest 
#include <boost/test/unit_test.hpp>

#define private public

#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetSignal/JPetSignal.h"
#include <vector>

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
  std::vector<JPetSigCh> falling;
  falling.push_back(JPetSigCh() );
  falling.push_back(JPetSigCh() );
  std::vector<JPetSigCh> rising;
  rising.push_back(JPetSigCh() );
  JPetSignal signal(100, 2, false, falling, rising);
  BOOST_CHECK_EQUAL(signal.GetT(), 100); 
  BOOST_CHECK_EQUAL(signal.GetQual(), 2); 
  BOOST_CHECK_EQUAL(signal.IsLeft(), false); 
  BOOST_CHECK_EQUAL(signal.GetNTresholds(JPetSignal::kRising), 1); 
  BOOST_CHECK_EQUAL(signal.GetNTresholds(JPetSignal::kFalling), 2); 
}

BOOST_AUTO_TEST_SUITE_END()
