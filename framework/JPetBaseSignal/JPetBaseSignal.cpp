/**
 *  @copyright Copyright (c) 2014, Wojciech Krzemien
 *  @file JPetBaseSignal.h
 *  @author Aleksander Gajos, alek.gajos@gmail.com
 */

#include "./JPetBaseSignal.h"

ClassImp(JPetBaseSignal);

JPetBaseSignal::JPetBaseSignal() :
    TNamed("JPetBaseSignal", "Base Signal structure"), fPM(0), fBarrelSlot(0),
    fTSlotIndex(0) {
}

JPetBaseSignal::~JPetBaseSignal() {
}
