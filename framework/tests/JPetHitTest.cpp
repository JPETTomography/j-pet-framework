#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetHitTest
#include <boost/test/unit_test.hpp>

#define private public

#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetTSlot/JPetTSlot.h"
#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetSignal/JPetSignal.h"
#include "../JPetHit/JPetHit.h"

#include <cstddef>

class JPetBarrelSlot;
class JPetScin;
class JPetTSlot;
class JPetSigCh;
class JPetSignal;
class JPetHit;

BOOST_AUTO_TEST_SUITE(FirstSuite)
  
BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetHit hit;
  BOOST_CHECK_EQUAL(hit.GetEnergy(), 0.0f);
  BOOST_CHECK_EQUAL(hit.GetQualityOfEnergy(), 0.0f);
  BOOST_CHECK_EQUAL(hit.GetTime(), 0.0f);
  BOOST_CHECK_EQUAL(hit.GetQualityOfTime(), 0.0f);
  
  BOOST_CHECK(hit.fPos != NULL);
  BOOST_CHECK(hit.fSignals == NULL);
  BOOST_CHECK(hit.fBarrelSlot == NULL);
  BOOST_CHECK(hit.fScintillator == NULL);
  BOOST_CHECK(hit.fTSlot == NULL);
}

BOOST_AUTO_TEST_CASE(init_constructor )
{
  // Create requied data
  Vector3 position(1.0f,2.0f,3.0f);
  JPetSignal leftSignal;
  JPetSignal rightSignal;
  JPetSignals bothSignals(leftSignal,rightSignal);
  JPetBarrelSlot barrelSlot;
  JPetScin scintillator;
  JPetTSlot tSlot;
  
  JPetHit hit(0.10f,0.20f,0.30f,0.40f,position,bothSignals,barrelSlot,scintillator,tSlot);
  
  //boost checks
  BOOST_CHECK_EQUAL(hit.GetEnergy(), 0.10f);
  BOOST_CHECK_EQUAL(hit.GetQualityOfEnergy(), 0.20f);
  BOOST_CHECK_EQUAL(hit.GetTime(), 0.30f);
  BOOST_CHECK_EQUAL(hit.GetQualityOfTime(), 0.40f);
  BOOST_CHECK_EQUAL(hit.GetPosX(),1.0f);
  BOOST_CHECK_EQUAL(hit.GetPosY(),2.0f);
  BOOST_CHECK_EQUAL(hit.GetPosZ(),3.0f);
  BOOST_CHECK_EQUAL(hit.GetPos(0),1.0f);
  BOOST_CHECK_EQUAL(hit.GetPos(1),2.0f);
  BOOST_CHECK_EQUAL(hit.GetPos(2),3.0f);
  
  BOOST_CHECK(hit.fPos != NULL);
  BOOST_CHECK(hit.fSignals != NULL);
  BOOST_CHECK(hit.fBarrelSlot != NULL);
  BOOST_CHECK(hit.fScintillator != NULL);
  BOOST_CHECK(hit.fTSlot != NULL);
}

BOOST_AUTO_TEST_CASE(set_get_test)
{

  // Create requied data
  
  Vector3 position(1.0f,2.0f,3.0f);
  JPetSignal leftSignal;
  JPetSignal rightSignal;
  JPetSignals bothSignals(leftSignal,rightSignal);
  JPetBarrelSlot barrelSlot;
  JPetScin scintillator;
  JPetTSlot tSlot;
  
  JPetHit hit;
  
  //boost checks
  
  hit.SetEnergy(0.10f);
  hit.SetQualityOfEnergy(0.20f);
  hit.SetTime(0.30f);
  hit.SetQualityOfTime(0.40f);
  BOOST_CHECK_EQUAL(hit.GetEnergy(), 0.10f);
  BOOST_CHECK_EQUAL(hit.GetQualityOfEnergy(), 0.20f);
  BOOST_CHECK_EQUAL(hit.GetTime(), 0.30f);
  BOOST_CHECK_EQUAL(hit.GetQualityOfTime(), 0.40f);
  hit.SetPosX(1.0f);
  hit.SetPosY(2.0f);
  hit.SetPosZ(3.0f);
  BOOST_CHECK_EQUAL(hit.GetPosX(),1.0f);
  BOOST_CHECK_EQUAL(hit.GetPosY(),2.0f);
  BOOST_CHECK_EQUAL(hit.GetPosZ(),3.0f);
}

BOOST_AUTO_TEST_SUITE_END()
