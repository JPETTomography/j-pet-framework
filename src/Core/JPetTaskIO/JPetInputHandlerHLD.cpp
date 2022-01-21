/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetInputHandlerHLD.cpp
 */

#include "JPetTaskIO/JPetInputHandlerHLD.h"
#include "JPetCommonTools/JPetCommonTools.h"
#include "JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "JPetTaskIO/JPetTaskIOTools.h"

#include "unpacker.hpp"

JPetInputHandlerHLD::JPetInputHandlerHLD() {}

bool JPetInputHandlerHLD::openInput(const char* inputFilename, const JPetParams& params)
{
  using namespace jpet_options_tools;
  auto options = params.getOptions();

  fFile.open(inputFilename, std::ios::in | std::ios::binary);

  if (!fFile)
  {
    ERROR(Form("Failed to open input file: %s", inputFilename));
    return false;
  }

  return true;
}

void JPetInputHandlerHLD::closeInput() { fFile.close(); }

TObject& JPetInputHandlerHLD::getEntry() { return fEntryData; }

bool JPetInputHandlerHLD::nextEntry()
{
  if (fEntryRange.currentEntry == fEntryRange.lastEntry)
  {
    return false;
  }
  fEntryRange.currentEntry++;

  int success = unpacker::get_time_window(fEntryData.fMetaData, fEntryData.fOriginalData, fEntryData.fFilteredData, fEntryData.fPreprocData, fFile);

  if (success == 0)
  {
    return false;
  }

  return true;
}

bool JPetInputHandlerHLD::setEntryRange(const jpet_options_tools::OptsStrAny& options)
{
  bool isOK = false;
  auto firstEntry = 0ll;
  auto lastEntry = 0ll;
  std::tie(isOK, firstEntry, lastEntry) = calculateEntryRange(options);
  if (!isOK)
  {
    ERROR("Some error occured in setEntryRange");
    return false;
  }
  fEntryRange.firstEntry = firstEntry;
  fEntryRange.lastEntry = lastEntry;
  fEntryRange.currentEntry = firstEntry;
  return true;
}

std::tuple<bool, long long, long long> JPetInputHandlerHLD::calculateEntryRange(const jpet_options_tools::OptsStrAny& options) const
{
  auto totalEntries = 1000000000ll;
  // @todo: consider scanning the HLD file first to determine the number of time windows inside
  WARNING("Unpacker of the HLD files is not able to determine the total number of events. Progressbar display may not be reliable.");
  return JPetTaskIOTools::setUserLimits(options, totalEntries);
}
