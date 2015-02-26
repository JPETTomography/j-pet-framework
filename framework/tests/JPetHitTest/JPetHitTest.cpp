#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetHitTest
#include <boost/test/unit_test.hpp>

#define private public
#include "../../JPetHit/JPetHit.h"
#include "../../JPetScin/JPetScin.h"
#include "../../JPetBarrelSlot/JPetBarrelSlot.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)
BOOST_AUTO_TEST_CASE( default_constructor )
{
  JPetHit hit;
  double epsilon = 0.0001;  
  BOOST_REQUIRE_CLOSE(hit.getEnergy(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfEnergy(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getTime(), 0.0f, epsilon);
  BOOST_REQUIRE_CLOSE(hit.getQualityOfTime(), 0.0f, epsilon);
  
  BOOST_REQUIRE_CLOSE(hit.fPos.X(),0, epsilon );
  BOOST_REQUIRE_CLOSE(hit.fPos.Y(),0, epsilon );
  BOOST_REQUIRE_CLOSE(hit.fPos.Z(),0, epsilon );
  
//  BOOST_REQUIRE(hit.fSignals->first == NULL);
//  BOOST_REQUIRE(hit.fSignals->second == NULL);
//  BOOST_REQUIRE(hit.fBarrelSlot == NULL);
  //BOOST_REQUIRE(hit.fScintillator == NULL);
  //BOOST_REQUIRE(hit.fTSlot == NULL);
}

BOOST_AUTO_TEST_CASE(init_constructor )
{
  // Create requied data
  TVector3 position(1.0f,2.0f,3.0f);
  JPetPhysSignal leftSignal;
  JPetPhysSignal rightSignal;
  /*JPetHit::JPetSignals bothSignals = std::make_pair(&leftSignal,&rightSignal);
  JPetBarrelSlot barrelSlot;
  JPetScin scintillator;
  JPetTSlot tSlot;
  
  JPetHit hit(0.10f,0.20f,0.30f,0.40f,position,bothSignals,barrelSlot,scintillator,tSlot);
  
  //boost checks
  BOOST_REQUIRE_EQUAL(hit.GetEnergy(), 0.10f);
  BOOST_REQUIRE_EQUAL(hit.GetQualityOfEnergy(), 0.20f);
  BOOST_REQUIRE_EQUAL(hit.GetTime(), 0.30f);
  BOOST_REQUIRE_EQUAL(hit.GetQualityOfTime(), 0.40f);
  BOOST_REQUIRE_EQUAL(hit.GetPosX(),1.0f);
  BOOST_REQUIRE_EQUAL(hit.GetPosY(),2.0f);
  BOOST_REQUIRE_EQUAL(hit.GetPosZ(),3.0f);
  BOOST_REQUIRE_EQUAL(hit.GetPos(0),1.0f);
  BOOST_REQUIRE_EQUAL(hit.GetPos(1),2.0f);
  BOOST_REQUIRE_EQUAL(hit.GetPos(2),3.0f);
  
  BOOST_REQUIRE(hit.fPos != NULL);
  BOOST_REQUIRE(hit.fSignals->first != NULL);
  BOOST_REQUIRE(hit.fSignals->second != NULL);
  BOOST_REQUIRE(hit.fBarrelSlot != NULL);
  BOOST_REQUIRE(hit.fScintillator != NULL);
  BOOST_REQUIRE(hit.fTSlot != NULL);*/
}


BOOST_AUTO_TEST_CASE(set_get_scalars_test){
  JPetHit hit;
  float time = 0.1;
  float timeDiff = 0.2;
  float timeQual = 0.3;
  float timeDiffQual = 0.4;
  float energy = 0.5;
  float energyQual = 0.6;
  
  hit.setTime(time);
  hit.setQualityOfTime(timeQual);
  hit.setTimeDiff(timeDiff);
  hit.setQualityOfTimeDiff(timeDiffQual);
  hit.setEnergy(energy);
  hit.setQualityOfEnergy(energyQual);

  BOOST_REQUIRE_EQUAL(hit.getTime(), time);
  BOOST_REQUIRE_EQUAL(hit.getQualityOfTime(), timeQual);
  BOOST_REQUIRE_EQUAL(hit.getTimeDiff(), timeDiff);
  BOOST_REQUIRE_EQUAL(hit.getQualityOfTimeDiff(), timeDiffQual);
  BOOST_REQUIRE_EQUAL(hit.getEnergy(), energy);
  BOOST_REQUIRE_EQUAL(hit.getQualityOfEnergy(), energyQual);
  
}


BOOST_AUTO_TEST_CASE(set_get_objects_test)
{

  // Create requied data
  
  TVector3 position(1.0f,2.0f,3.0f);
  JPetPhysSignal leftSignal;
  JPetPhysSignal rightSignal;

  float timeA = 123.0;
  float timeB = 456.0;
  leftSignal.setTime( timeA );
  rightSignal.setTime( timeB );

  int scinID = 42;
  JPetScin scin;
  scin.setID( scinID );
  JPetBarrelSlot slot;

  JPetHit hit;
  hit.setSignalA( leftSignal );
  hit.setSignalB( rightSignal );

  hit.setScintillator( scin );
  hit.setBarrelSlot( slot );

  BOOST_REQUIRE_EQUAL( hit.getScintillator().getID(), scinID );
  BOOST_REQUIRE_EQUAL( &(hit.getScintillator()), &scin );
  BOOST_REQUIRE_EQUAL( &(hit.getBarrelSlot()), &slot );

  BOOST_REQUIRE_EQUAL( hit.getSignalA().getTime(), timeA );
  BOOST_REQUIRE_EQUAL( hit.getSignalB().getTime(), timeB );

}

BOOST_AUTO_TEST_SUITE_END()
