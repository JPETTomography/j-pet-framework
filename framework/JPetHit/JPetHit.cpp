/**
 *  @file JPetHit.cpp
 *  @author Damian Trybek, damian.trybek@uj.edu.pl
 *  @copyright Copyright (c) 2013, Damian Trybek
 */

#include "./JPetHit.h"

#include "TString.h"

ClassImp(JPetHit);

JPetHit::JPetHit() :
    TNamed("JPetHit","Hit Structure"), fEnergy(0.0f), fQualityOfEnergy(0.0f), fTime(0.0f),
    fQualityOfTime(0.0f), fPos(new TVector3()), fSignals(new std::pair<JPetSignal*,JPetSignal*>),
    fBarrelSlot(NULL), fScintillator(NULL), fTSlot(NULL) {
  *fSignals = std::make_pair((JPetSignal*)NULL,(JPetSignal*)NULL);
}

JPetHit::JPetHit(float e, float qe, float t, float qt, TVector3& pos, JPetSignals& sigs, 
                  JPetBarrelSlot& bslot, JPetScin& scin, JPetTSlot& tslot) : 
    TNamed("JPetHit","Hit Structure") ,fEnergy(e), fQualityOfEnergy(qe), fTime(t),
    fQualityOfTime(qt), fPos(&pos), fSignals(&sigs), fBarrelSlot(&bslot), fScintillator(&scin),
    fTSlot(&tslot) {
}

JPetHit::~JPetHit() {
}
