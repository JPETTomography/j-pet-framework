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
 *  @file JPetTaskIOTools.cpp
 */

#include "./JPetTaskIOTools.h"
#include "./JPetLoggerInclude.h"
#include "./JPetCommonTools/JPetCommonTools.h"
#include <TString.h>

using namespace jpet_options_tools;

namespace JPetTaskIOTools
{

std::tuple<bool, long long, long long> setUserLimits(const OptsStrAny& opts, const long long kTotEventsFromReader)
{
  const auto kLastEvent = getLastEvent(opts);
  const auto kFirstEvent = getFirstEvent(opts);
  auto first = 0ll;
  auto last = 0ll;
  if ( kTotEventsFromReader < 1) {
    WARNING("kTotEvetnsFromReader < 1, first and last set to -1");
    first = last = -1;
  } else {
    if ( kFirstEvent < 0) {
      first = 0;
    } else {
      first = kFirstEvent < kTotEventsFromReader ? kFirstEvent : kTotEventsFromReader - 1;
    }
    if (kLastEvent < 0)  {
      last = kTotEventsFromReader - 1;
    } else {
      last = kLastEvent < kTotEventsFromReader ? kLastEvent : kTotEventsFromReader - 1;
    }
  }
  if (first < 0) {
    ERROR("first <0");
    return std::make_tuple(false, -1, -1);
  }
  if (last < 0) {
    ERROR("last < 0");
    return std::make_tuple(false, -1, -1);
  }
  if (first > last) {
    ERROR("first > last");
    return std::make_tuple(false, -1, -1);
  }
  assert(first >= 0);
  assert(last >= 0);
  assert(first <= last);
  return std::make_tuple(true, first, last);
}

std::tuple<bool, std::string, std::string, bool> setInputAndOutputFile(const OptsStrAny& opts,  bool prevResetOutputPath,
    const std::string& inFileType, const std::string& outFileType )
{
  bool resetOutputPath = prevResetOutputPath;
  if (!isOptionSet(opts, "inputFile_std::string")) {
    ERROR("No inputFile option provided");
    return std::make_tuple(false, "", "", false);
  }
  // handle input file path
  std::string inputFilename = getInputFile(opts);
  if ( JPetCommonTools::extractDataTypeFromFileName(inputFilename) != inFileType ) {
    WARNING(Form("Input file type %s does not match the one provided by the previous module (%s).",
                 inFileType.c_str(), JPetCommonTools::extractDataTypeFromFileName(inputFilename).c_str()));
  }
  inputFilename = JPetCommonTools::replaceDataTypeInFileName(inputFilename, inFileType);

  // handle output file path
  auto outFileFullPath = inputFilename;
  if (isOptionSet(opts, "outputPath_std::string")) {
    std::string outputPath(getOutputPath(opts));
    if (!outputPath.empty()) {
      outFileFullPath = outputPath + JPetCommonTools::extractFileNameFromFullPath(getInputFile(opts));
      resetOutputPath = true;
    }
  }
  outFileFullPath = JPetCommonTools::replaceDataTypeInFileName(outFileFullPath, outFileType);
  return std::make_tuple(true, inputFilename, outFileFullPath, resetOutputPath);
}

OptsStrAny setOutputOptions(const JPetParams& oldParams, bool resetOutputPath, const std::string& fullOutPath)
{
  OptsStrAny new_opts = oldParams.getOptions();
  if (FileTypeChecker::getInputFileType(oldParams.getOptions()) == FileTypeChecker::kHldRoot) {
    jpet_options_generator_tools::setOutputFileType(new_opts, "root");
  }

  if ( jpet_options_tools::getOptionAsInt(oldParams.getOptions(), "firstEvent_int") != -1 &&
       jpet_options_tools::getOptionAsInt(oldParams.getOptions(), "lastEvent_int") != -1 ) {
    jpet_options_generator_tools::setResetEventRangeOption(new_opts, true);
  }

  if (resetOutputPath) {
    jpet_options_generator_tools::setOutputPath(new_opts, "");
  }
  jpet_options_generator_tools::setOutputFile(new_opts, fullOutPath);

  return new_opts;
}

}
