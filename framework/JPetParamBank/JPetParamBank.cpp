/**
  *  @copyright Copyright (c) 2014, Wojciech Krzemien
  *  @file JPetParamBank.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */ 

#include "./JPetParamBank.h"

ClassImp (JPetParamBank);

JPetParamBank::JPetParamBank():
  fScintillators("JPetScin", 100),
  fPMs("JPetPM", 100),
  fFEBs("JPetFEB", 100),
  fTRBs("JPetTRB", 100),
  fTOMBChannels("JPetTOMBChannel", 500)
{ /* */}

void JPetParamBank::clear() 
{
  fScintillators.Clear();
  fPMs.Clear();
  fFEBs.Clear();
  fTRBs.Clear();
  fTOMBChannels.Clear();
}


int JPetParamBank::getSize(JPetParamBank::ParamObjectType type) const 
{
  int size =-1;
  switch (type) {
    case kScintillator:
      size = getScintillatorsSize();
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
