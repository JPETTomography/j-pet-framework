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
 *  @file JPetGeantEventInformation.cpp
 */

#include "JPetGeantEventInformation/JPetGeantEventInformation.h"

ClassImp(JPetGeantEventInformation)

JPetGeantEventInformation::JPetGeantEventInformation()
    : fVtxPosition(0, 0, 0), fVtxPromptPosition(0, 0, 0), fGenGammaNum(fMaxGammaNumberIndex), fnRun(0), fLifetime(0), fPromptLifetime(0),
      fMomentumGamma(4)
{
}

JPetGeantEventInformation::~JPetGeantEventInformation() {}

void JPetGeantEventInformation::Clear()
{
  fGenGammaNum.ResetAllBits();
  fnRun = 0;
  fLifetime = 0.;
  fPromptLifetime = 0.;
  fVtxPosition.SetXYZ(0, 0, 0);
  fVtxPromptPosition.SetXYZ(0, 0, 0);
  fMomentumGamma.clear();
  fMomentumGamma.resize(4);
}
