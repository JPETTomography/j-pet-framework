/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file JPetSigCh.cpp
 *  @brief description
 */

#include "JPetSigCh.h"
#include <limits>
#include <cstring>

ClassImp(JPetSigCh);

const float JPetSigCh::kUnset = std::numeric_limits<float>::infinity();

void JPetSigCh::Init() {
  SetNameTitle("JPetSigCh", "Signal Channel Structure");
  fValue = kUnset;
  fType = Leading;
  fThreshold = kUnset;
  fThresholdNumber = 0;
}

JPetSigCh::JPetSigCh(EdgeType Edge, float EdgeTime) {
  Init();
  /// @todo: perform some sanity checks of the given values
  assert(EdgeTime > 0.);

  fType = Edge;
  fValue = EdgeTime;

}

bool JPetSigCh::isCharge() const {
  if (fType == Charge) {
    return true;
  }
  return false;
}

bool JPetSigCh::isTime() const {
  if (fType == Trailing || fType == Leading) {
    return true;
  }
  return false;
}

bool JPetSigCh::compareByThresholdValue(const JPetSigCh& A,
                                        const JPetSigCh& B) {
  if (A.getThreshold() < B.getThreshold()) {
    return true;
  }
  return false;
}

bool JPetSigCh::compareByThresholdNumber(const JPetSigCh& A,
                                         const JPetSigCh& B) {
  if (A.getThresholdNumber() < B.getThresholdNumber()) {
    return true;
  }
  return false;
}
JPetSigCh JPetSigCh::makeSigCh(const JPetPM & pm, const JPetTRB & trb, const JPetFEB & feb, const JPetTOMBChannel & channel, float val, EdgeType type, float thr, Int_t daqch, unsigned int threshold_number){
   JPetSigCh sigChObject;
   sigChObject.fPM = const_cast<JPetPM*>(&pm);
   sigChObject.fTRB = const_cast<JPetTRB*>(&trb);
   sigChObject.fFEB = const_cast<JPetFEB*>(&feb);
   sigChObject.fTOMBChannel = const_cast<JPetTOMBChannel*>(&channel);
   sigChObject.fValue = val;
   sigChObject.fType = type;
   sigChObject.fThreshold = thr;
   sigChObject.fDAQch = daqch;
   sigChObject.fThresholdNumber = threshold_number;
   return sigChObject;
  }
