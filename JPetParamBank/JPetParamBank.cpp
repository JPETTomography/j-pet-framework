/**
  *  @copyright Copyright (c) 2014, Wojciech Krzemien
  *  @file JPetParamBank.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */

#include "./JPetParamBank.h"

ClassImp (JPetParamBank);

JPetParamBank::JPetParamBank()
{
  /* */
}

JPetParamBank::JPetParamBank(const JPetParamBank& paramBank)
{
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
