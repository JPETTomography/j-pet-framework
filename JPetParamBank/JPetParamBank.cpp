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
 *  @file JPetParamBank.cpp
 */

#include "./JPetParamBank.h"

ClassImp (JPetParamBank);

JPetParamBank::JPetParamBank():fDummy(false){}
JPetParamBank::JPetParamBank(const bool d):fDummy(d){}
const bool JPetParamBank::isDummy()const{return fDummy;}
JPetParamBank::JPetParamBank(const JPetParamBank& paramBank):fDummy(false){
  initVectorWith(fScintillators, paramBank.fScintillators);
  initVectorWith(fPMs, paramBank.fPMs);
  initVectorWith(fPMCalibs, paramBank.fPMCalibs);
  initVectorWith(fFEBs, paramBank.fFEBs);
  initVectorWith(fTRBs, paramBank.fTRBs);
  initVectorWith(fBarrelSlots, paramBank.fBarrelSlots);
  initVectorWith(fLayers, paramBank.fLayers);
  initVectorWith(fFrames, paramBank.fFrames);
  initVectorWith(fTOMBChannels, paramBank.fTOMBChannels);
}

JPetParamBank::~JPetParamBank()
{
}

void JPetParamBank::clear()
{
  fScintillators.clear();
  fPMs.clear();
  fPMCalibs.clear();
  fFEBs.clear();
  fTRBs.clear();
  fBarrelSlots.clear();
  fLayers.clear();
  fFrames.clear();
  fTOMBChannels.clear();
}


int JPetParamBank::getSize(JPetParamBank::ParamObjectType type) const 
{
  int size =-1;
  switch (type) {
    case kScintillator:
      size = getScintillatorsSize();
      break;
    case kPM:
      size = getPMsSize();
      break;
    case kPMCalib:
      size = getPMCalibsSize();
      break;
    case kBarrelSlot:
      size = getBarrelSlotsSize();
      break;
    case kLayer:
      size = getLayersSize();
      break;
    case kFrame:
      size = getFramesSize();
      break;
    case kFEB:
      size = getFEBsSize();
      break;
    case kTRB:
      size = getTRBsSize();
      break;
    case kTOMBChannel:
      size = getTOMBChannelsSize();
      break;
    default:
      ERROR("bad type");
      break;
  }
  return size; 
}
