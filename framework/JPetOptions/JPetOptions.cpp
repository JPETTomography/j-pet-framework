/**
  *  @copyright Copyright (c) 2015, J-PET collaboration
  *  @file JPetOptions.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */

#include "./JPetOptions.h"
#include "../../JPetLoggerInclude.h"

JPetOptions::Options JPetOptions::kDefaultOptions = {
  {"inputFile", ""},
  {"inputFileType", ""},
  {"outputFile", "root"},
  {"outputFileType", "test.root"},
  {"firstEvent", "-1"},
  {"lastEvent", "-1"},
  {"progressBar", "false"},
  {"runId", "-1"}
};

JPetOptions::JPetOptions()
{
  setStringToFileTypeConversion();
  fOptions = JPetOptions::kDefaultOptions;
}

JPetOptions::JPetOptions(const Options& opts):
  fOptions(opts)
{
  setStringToFileTypeConversion();
  if (areCorrect(opts)) {
    setOptions(opts);
  } else {
    ERROR("Options are not correct using default ones");
  }
}

void JPetOptions::setStringToFileTypeConversion()
{
  fStringToFileType = {
    {"", kNoType},
    {"root", kRoot},
    {"scope", kScope},
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

bool JPetOptions::areCorrect(const Options& opts) const
{
  return true;
}

void JPetOptions::resetEventRange() {
  fOptions.at("firstEvent") = "-1";
  fOptions.at("lastEvent") = "-1";
}
