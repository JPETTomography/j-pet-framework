#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetEventTest
#include <boost/test/unit_test.hpp>

#define private public

#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetTSlot/JPetTSlot.h"
#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetSignal/JPetSignal.h"
#include "../JPetHit/JPetHit.h"
#include "../JPetEvent/JPetEvent.h"

#include <cstddef>

//class JPetBarrelSlot;
//class JPetScin;
//class JPetTSlot;
//class JPetSigCh;
//class JPetSignal;
//class Vector3;
//class JPetHit;
//class JPetEvent;

BOOST_AUTO_TEST_SUITE(FirstSuite)
  
BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetEvent event;
  BOOST_CHECK_EQUAL(event.GetTime(), 0.0f);
  BOOST_CHECK_EQUAL(event.GetQualityOfTime(), 0.0f);
  
  BOOST_CHECK(event.fHits->first == NULL);
  BOOST_CHECK(event.fHits->second == NULL);
}

BOOST_AUTO_TEST_SUITE_END()
