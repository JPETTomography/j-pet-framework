/**
 *  @copyright Copyright (c) 2014, Aleksander Gajos
 *  @file JPetPhysSignal.cpp
 *  @author Aleksander Gajos, alek.gajos@gmail.com
 */


#include "./JPetPhysSignal.h"

ClassImp(JPetPhysSignal);

JPetPhysSignal::JPetPhysSignal() :
  fTime(0),
  fQualityOfTime(0),
  fPhe(0),
  fQualityOfPhe(0)
{
  SetNameTitle("JPetPhysSignal", "Physical signal structure");
}


JPetPhysSignal::~JPetPhysSignal()
{ }

void JPetPhysSignal::setRecoSignal(const JPetRecoSignal& recoSignal){
   fRecoSignal = recoSignal;
   setPM( recoSignal.getPM() );
   setBarrelSlot( recoSignal.getBarrelSlot() );
   setTSlotIndex( recoSignal.getTSlotIndex() );
}
