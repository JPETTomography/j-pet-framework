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
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

ClassImp (JPetParamBank);

JPetParamBank::JPetParamBank():fDummy(false){}
JPetParamBank::JPetParamBank(const bool d):fDummy(d){}
const bool JPetParamBank::isDummy()const{return fDummy;}
JPetParamBank::JPetParamBank(const JPetParamBank& paramBank):fDummy(false){
  copyMapValues(fScintillators, paramBank.fScintillators);
  copyMapValues(fPMs, paramBank.fPMs);
  copyMapValues(fPMCalibs, paramBank.fPMCalibs);
  copyMapValues(fFEBs, paramBank.fFEBs);
  copyMapValues(fTRBs, paramBank.fTRBs);
  copyMapValues(fBarrelSlots, paramBank.fBarrelSlots);
  copyMapValues(fLayers, paramBank.fLayers);
  copyMapValues(fFrames, paramBank.fFrames);
  copyMapValues(fTOMBChannels, paramBank.fTOMBChannels);
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


int JPetParamBank::getSize(ParamObjectType type) const
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

int JPetParamBank::getTOMBChannelFromDescription(std::string p_desc)
{
  // parsing the string description of a TOMB channel to extract the channel number
  // convention: tast 4 characters of the description represent the number
  const char * l_pattern = ".*\\s(\\d{1,4}).*";
  boost::regex l_regex(l_pattern);
  boost::smatch l_matches;

  int l_TOMB_no = -1;

  if (boost::regex_match(p_desc, l_matches, l_regex))
  {
    l_TOMB_no = boost::lexical_cast<int>( l_matches[1] );
  } else
  {
    // @todo: handle parsing error somehow
    ERROR( "Unable to parse TOMBInput description to get channel number." );
  }
  return l_TOMB_no;
}
