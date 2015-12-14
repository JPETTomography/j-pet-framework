/**
  *  @copyright Copyright (c) 2014, Wojciech Krzemien
  *  @file JPetParamBank.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */

#include "./JPetParamBank.h"
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

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
