/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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
 */

#include "JPetSigCh.h"
#include <cstring>
#include <limits>

ClassImp(JPetSigCh);

const float JPetSigCh::kUnset = std::numeric_limits<float>::infinity();

void JPetSigCh::init() {
  fValue = kUnset;
  fType = Leading;
  fThreshold = kUnset;
  fThresholdNumber = 0;
  fDAQch = -1;
  fPM = NULL;
  fFEB = NULL;
  fTRB = NULL;
  fTOMBChannel = NULL;
}

/**
 * Constructor
 * @todo Perform some sanity checks of the given values
 */
JPetSigCh::JPetSigCh(EdgeType Edge, float EdgeTime) {
  init();
  assert(EdgeTime > 0.);
  fType = Edge;
  fValue = EdgeTime;
}

bool JPetSigCh::compareByThresholdValue(
  const JPetSigCh& A, const JPetSigCh& B)
{
  if (A.getThreshold() < B.getThreshold()) {
    return true;
  }
  return false;
}

bool JPetSigCh::compareByThresholdNumber(
  const JPetSigCh& A, const JPetSigCh& B)
{
  if (A.getThresholdNumber() < B.getThresholdNumber()) {
    return true;
  }
  return false;
}

void JPetSigCh::Clear(Option_t *)
{
  init();
}
