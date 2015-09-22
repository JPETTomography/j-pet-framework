/**
  *  @copyright Copyright (c) 2014, Wojciech Krzemien
  *  @file JPetTaskOptions.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */

#include "./JPetTaskOptions.h"
#include "../../JPetLoggerInclude.h"

JPetTaskOptions::JPetTaskOptions()
{
  setStringToFileTypeConversion();
  //use some defaults
}

JPetTaskOptions::JPetTaskOptions(const Options& opts):
  fOptions(opts)
{
  setStringToFileTypeConversion();
  if(areCorrect(opts)) {
    setOptions(opts);
  } else { 
    ERROR("Options are not correct using default ones");    
  }
}

void JPetTaskOptions::setStringToFileTypeConversion()
{
  fStringToFileType = {
    {"raw", kRaw},
    {"hld", kHld},
    {"phys.eve", kPhysEve},
    {"phys.hit", kPhysHit},
    {"phys.sig", kPhysSig},
    {"raw.sig", kRawSig},
    {"reco.sig", kRecoSig},
    {"tslot.cal", kTslotCal},
    {"tslot.raw", kTslotRaw}
  };
}

bool JPetTaskOptions::areCorrect(const Options& opts) const
{
  return true;
}
