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
    fQualityOfTime(0.0f), fPos(new TVector3()),
    fBarrelSlot(NULL), fScintillator(NULL) {

}

JPetHit::JPetHit(float e, float qe, float t, float qt, TVector3& pos, JPetSignal& lsig, JPetSignal& rsig, 
                  JPetBarrelSlot& bslot, JPetScin& scin) : 
    TNamed("JPetHit","Hit Structure") ,fEnergy(e), fQualityOfEnergy(qe), fTime(t),
    fQualityOfTime(qt), fPos(&pos), fLeftSignal(lsig), fRightSignal(rsig), fBarrelSlot(&bslot), fScintillator(&scin) {
}

JPetHit::~JPetHit() {
}
