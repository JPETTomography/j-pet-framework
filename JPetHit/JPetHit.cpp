/**
 *  @file JPetHit.cpp
 *  @author Damian Trybek, damian.trybek@uj.edu.pl
 *  @copyright Copyright (c) 2013, Damian Trybek
 */

#include "./JPetHit.h"
#include "../JPetLoggerInclude.h"

#include "TString.h"

ClassImp(JPetHit);

JPetHit::JPetHit() :
    TNamed("JPetHit","Hit Structure"), fEnergy(0.0f), fQualityOfEnergy(0.0f), fTime(0.0f),
    fQualityOfTime(0.0f),
    fBarrelSlot(NULL), fScintillator(NULL) { 
  fIsSignalAset = false;
  fIsSignalBset = false;
}

JPetHit::JPetHit(float e, float qe, float t, float qt, TVector3& pos, JPetPhysSignal& siga, JPetPhysSignal& sigb,
                  JPetBarrelSlot& bslot, JPetScin& scin) : 
    TNamed("JPetHit","Hit Structure") ,fEnergy(e), fQualityOfEnergy(qe), fTime(t),
    fQualityOfTime(qt), fPos(pos), fSignalA(siga), fSignalB(sigb), fBarrelSlot(&bslot), fScintillator(&scin) {

  fIsSignalAset = true ;
  fIsSignalBset = true ;
  checkConsistency();
}

JPetHit::~JPetHit() {
}


/** @brief Checks whether both signals set in this Hit object
 *  come from the same barrel slot and opposite-side PMTs and logs 
 *  an error message if not.
 *
 *  Pairing two signals originating from photomultipliers belonging to
 *  two different barrel slots or the same barrel side (i.e. attached 
 *  to different scintillators) would make no physical sense. This method 
 *  ensures that it is not the case.
 * 
 *  If the signals come from the same barrel slot and opposite-side PMTs, 
 *  this method only returns true.
 *  Otherwise, false is returned and an appropriate error message is logged.
 *
 *  @return true if both signals are consistently from the same barrel slot.
 */
bool JPetHit::checkConsistency() const{

  
  if( !fIsSignalAset || !fIsSignalBset ){
    return true; // do not claim incosistency if signals are not set yet
  }

  int slot_a = getSignalA().getPM().getBarrelSlot().getID();
  int slot_b = getSignalB().getPM().getBarrelSlot().getID();
  
  if( slot_a != slot_b ){
    ERROR( Form("Signals added to Hit come from different barrel slots: %d and %d." ,
		slot_a, slot_b) );
    return false;
  }
  
  if( getSignalA().getPM().getSide() == getSignalB().getPM().getSide() ){
    ERROR( Form("Signals added to Hit come from PMTs at the same side. PMTs: %d and %d." ,
		getSignalA().getPM().getID(), getSignalB().getPM().getID()) );
    return false;
  }

  
  return true;
}

void JPetHit::setSignals(JPetPhysSignal & p_sigA, JPetPhysSignal & p_sigB) {
  fSignalA = p_sigA;
  fIsSignalAset = true;
  fSignalB = p_sigB;
  fIsSignalBset = true;
  checkConsistency();
}

void JPetHit::setSignalA(JPetPhysSignal & p_sig) {
  fSignalA=p_sig;
  fIsSignalAset=true;
  checkConsistency();
}
void JPetHit::setSignalB(JPetPhysSignal & p_sig) {
  fSignalB=p_sig;
  fIsSignalBset=true;
  checkConsistency();  
}
