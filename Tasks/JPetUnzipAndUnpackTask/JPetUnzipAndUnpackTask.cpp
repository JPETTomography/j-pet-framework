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
 *  @file JPetUnzipAndUnpackTask.cpp
 */

#include "./JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "./JPetOptionsTools/JPetOptionsTools.h"
#include "./JPetOptionsTools/JPetOptionsTools.h"
#include "./JPetCommonTools/JPetCommonTools.h"
#include "./JPetUnpacker/JPetUnpacker.h"
#include "./JPetUnzipAndUnpackTask.h"
#include "./JPetParams/JPetParams.h"

JPetUnzipAndUnpackTask::JPetUnzipAndUnpackTask(const char* name):
  JPetTask(name), fUnpackHappened(false){}

bool JPetUnzipAndUnpackTask::init(const JPetParams& inParams)
{
  fOptions = inParams.getOptions();
  return true;
}

bool JPetUnzipAndUnpackTask::run(const JPetDataInterface&)
{
  using namespace jpet_options_tools;
  auto inputFile = getInputFile(fOptions);
  auto inputFileType = FileTypeChecker::getInputFileType(fOptions);
  auto unpackerConfigFile = getUnpackerConfigFile(fOptions);
  auto unpackerCalibFile = getUnpackerCalibFile(fOptions);
  if (inputFileType == FileTypeChecker::kHld) {
    unpackFile(inputFile, getTotalEvents(fOptions), unpackerConfigFile, unpackerCalibFile);
    fUnpackHappened = true;
  }
  else if ( inputFileType == FileTypeChecker::kZip) {
    INFO( std::string("Unzipping file before unpacking") );
    if ( !unzipFile(inputFile) ) {
      ERROR( std::string("Problem with unpacking file: ") + inputFile );
      return false;
    } else {
      INFO( std::string("Unpacking") );
      auto unzippedFilename = JPetCommonTools::stripFileNameSuffix(std::string(inputFile)).c_str();
      unpackFile(unzippedFilename, getTotalEvents(fOptions), unpackerConfigFile, unpackerCalibFile);
      fUnpackHappened = true;
    }
  }

  if (FileTypeChecker::getInputFileType(fOptions) == FileTypeChecker::kUndefinedFileType) {
    ERROR( Form("Unknown file type provided for file: %s", getInputFile(fOptions).c_str()) );
    return false;
  }
  return true;
}

bool JPetUnzipAndUnpackTask::terminate(JPetParams& outParams)
{
  using namespace jpet_options_tools;
  if (fUnpackHappened) {
    OptsStrAny new_opts;
    jpet_options_generator_tools::setOutputFileType(new_opts, "hldRoot");
    if (jpet_options_tools::isOptionSet(fOptions, "firstEvent_int") &&
      jpet_options_tools::isOptionSet(fOptions, "lastEvent_int")) {
      if ( jpet_options_tools::getOptionAsInt(fOptions, "firstEvent_int") != -1 &&
        jpet_options_tools::getOptionAsInt(fOptions, "lastEvent_int") != -1 ) {
        jpet_options_generator_tools::setResetEventRangeOption(new_opts, true);
      }
    }
    jpet_options_generator_tools::setOutputFile(new_opts,
      JPetCommonTools::replaceDataTypeInFileName(getInputFile(fOptions), "hld")
    );
    outParams = JPetParams(new_opts, outParams.getParamManagerAsShared());
  }
  return true;
}

bool JPetUnzipAndUnpackTask::unzipFile(const std::string& filename)
{
  if (JPetCommonTools::exctractFileNameSuffix(filename) == ".gz")
    return !(system(( std::string("gzip -dk ") + std::string(filename)).c_str()));
  else if ( JPetCommonTools::exctractFileNameSuffix(filename) == ".xz")
    return !(system( (std::string("xz -dk ") + std::string(filename)).c_str()));
  else if (JPetCommonTools::exctractFileNameSuffix(filename) == ".bz2")
    return !(system( (std::string("bzip2 -dk ") + std::string(filename)).c_str()));
  else if (JPetCommonTools::exctractFileNameSuffix(filename) == ".zip")
    return !(system((std::string("unzip ") + std::string(filename)).c_str()));
  else
    return false;
}

void JPetUnzipAndUnpackTask::unpackFile(const std::string& filename,
  long long nevents, const std::string& configfile = "",
  const std::string& calibfile = "")
{
  JPetUnpacker unpacker;
  if (nevents > 0) {
    unpacker.setParams(filename, nevents, configfile, calibfile);
    WARNING(std::string("Even though the range of events was set, only the first ")
      + JPetCommonTools::intToString(nevents)
      + std::string(" will be unpacked by the unpacker. \n The unpacker always starts from the beginning of the file.")
    );
  } else {
    unpacker.setParams(filename, 100000000, configfile, calibfile);
  }
  unpacker.exec();
}
