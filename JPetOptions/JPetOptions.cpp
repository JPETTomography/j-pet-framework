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
 *  @file JPetOptions.cpp
 */

#include "./JPetOptions.h"
#include "../JPetLoggerInclude.h"
#include "../JPetOptionsGenerator/JPetOptionsGenerator.h"

JPetOptions::JPetOptions()
{
  setStringToFileTypeConversion();
  fOptions = JPetOptionsGenerator::getDefaultOptions();
}

JPetOptions::JPetOptions(const Options& opts):
  fOptions(opts)
{
  setStringToFileTypeConversion();
}

void JPetOptions::handleErrorMessage(const std::string& errorMessage, const std::out_of_range& outOfRangeException) const
{
  std::cerr << errorMessage << outOfRangeException.what() << '\n';
  ERROR(errorMessage);
}

JPetOptions::FileType JPetOptions::handleFileType(const std::string& fileType) const
{
  try {
    auto option = any_cast<std::string>(fOptions.at(fileType));
    try {
      return fStringToFileType.at(option);
    } catch (const std::out_of_range& outOfRangeFileTypeException) {
    }
  } catch (const std::out_of_range& outOfRangeOptionException) {
    std::string errorMessage = "Out of range error in Options container ";
    handleErrorMessage(errorMessage, outOfRangeOptionException);
  }

  return FileType::kUndefinedFileType;
}

void JPetOptions::setStringToFileTypeConversion()
{
  fStringToFileType = {
    {"", kNoType},
    {"root", kRoot},
    {"scope", kScope},
    {"raw", kRaw},
    {"hld", kHld},
    {"zip", kZip},
    {"phys.eve", kPhysEve},
    {"phys.hit", kPhysHit},
    {"phys.sig", kPhysSig},
    {"raw.sig", kRawSig},
    {"reco.sig", kRecoSig},
    {"tslot.cal", kTslotCal},
    {"tslot.raw", kTslotRaw}
  };
}


JPetOptions::FileType JPetOptions::getInputFileType() const
{
  return handleFileType("inputFileType_std::string");
}

JPetOptions::FileType JPetOptions::getOutputFileType() const
{
  return handleFileType("outputFileType_std::string");
}

void JPetOptions::resetEventRange()
{
  fOptions.at("firstEvent_int") = -1;
  fOptions.at("lastEvent_int") = -1;
}

JPetOptions::Options JPetOptions::resetEventRange(const Options& srcOpts)
{
  Options opts(srcOpts);
  opts.at("firstEvent_int") = -1;
  opts.at("lastEvent_int") = -1;
  return opts; 
}

/// It returns the total number of events calculated from
/// first and last event given in the range of events to calculate.
/// If first or last event is set to -1 then the -1 is returned.
/// If last - first < 0 then -1 is returned.
/// Otherwise last - first +1 is returned.
long long JPetOptions::getTotalEvents() const
{
  long long first = getFirstEvent();
  long long last = getLastEvent();
  long long diff = -1;
  if ((first >= 0) && (last >= 0) && ((last - first) >= 0)) {
    diff = last - first + 1;
  }
  return diff;
}
