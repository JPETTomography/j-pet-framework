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

using namespace jpet_options_tools;

JPetUnzipAndUnpackTask::JPetUnzipAndUnpackTask(const char* name):
  JPetTask(name), fUnpackHappened(false) {}

bool JPetUnzipAndUnpackTask::init(const JPetParams& inParams)
{
  fOptions = inParams.getOptions();

  auto unpackerCalibFileFromCmdLine = getUnpackerCalibFile(fOptions);
  if (isOptionSet(inParams.getOptions(), kTOToffsetCalibKey)) {
    fTOToffsetCalibFile = getOptionAsString(inParams.getOptions(), kTOToffsetCalibKey);
    if (!unpackerCalibFileFromCmdLine.empty()) {
      WARNING("The calibration file with TOT stretcher offsets was defined both on the command line and in user parameters\n"
              "The file given as a user parameter will be used.");
    }
  } else {
    if (unpackerCalibFileFromCmdLine.empty()) {
      WARNING("No calibration file with TOT stretcher offsets was provided by the user. Expect incorrect TOT values.");
    } else {
      fTOToffsetCalibFile = unpackerCalibFileFromCmdLine;
      WARNING("Using the calibration file with TOT stretcher offsets defined on the command line.\n"
              "Note that it can also be given as a user parameter in the JSON file.");
    }
  }

  if (isOptionSet(inParams.getOptions(), kTDCnonlinearityCalibKey)) {
    fTDCnonlinearityCalibFile = getOptionAsString(inParams.getOptions(), kTDCnonlinearityCalibKey);
  } else {
    WARNING("No file with TDC nonlinearity calibration was provided by the user.");
  }

  return true;
}

bool JPetUnzipAndUnpackTask::run(const JPetDataInterface&)
{
  using namespace jpet_options_tools;
  const auto inputFile = getInputFile(fOptions);
  const auto inputFileType = FileTypeChecker::getInputFileType(fOptions);
  const auto unzippedFilename = JPetCommonTools::stripFileNameSuffix(inputFile);
  const auto unpackerConfigFile = getUnpackerConfigFile(fOptions);

  bool runStatus = false;

  switch (inputFileType) {
  case FileTypeChecker::kHld:
    INFO("Unpacking file " + inputFile);
    runStatus = unpackFile(inputFile, getTotalEvents(fOptions), unpackerConfigFile, fTOToffsetCalibFile, fTDCnonlinearityCalibFile);
    fUnpackHappened = true;
    break;
  case FileTypeChecker::kZip:
    INFO("Unzipping file before unpacking, file name: " + inputFile);
    runStatus = unzipFile(inputFile);
    if (!runStatus) {
      ERROR("Problem with unzipping file: " + inputFile );
      break;
    }
    INFO("Unpacking file " + unzippedFilename);
    runStatus = unpackFile(unzippedFilename, getTotalEvents(fOptions), unpackerConfigFile, fTOToffsetCalibFile, fTDCnonlinearityCalibFile);
    fUnpackHappened = true;
    break;
  case FileTypeChecker::kUndefinedFileType:
    runStatus = false;
    ERROR("Undefined input file type: " + inputFile);
    break;
  case FileTypeChecker::kNoType:
  case FileTypeChecker::kScope:
  case FileTypeChecker::kHldRoot:
  case FileTypeChecker::kMCGeant:
  case FileTypeChecker::kRoot:
  default:
    runStatus = true;
    break;
  }

  if (!runStatus) {
    ERROR("Error occurred while unpacking/unzipping file: " + inputFile);
  }

  return runStatus;
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

bool JPetUnzipAndUnpackTask::unpackFile(const std::string& filename,
                                        long long nevents, const std::string& configfile = "",
                                        const std::string& totCalibFile = "", const std::string& tdcCalibFile = "")
{
  JPetUnpacker unpacker;
  if (nevents > 0) {
    unpacker.setParams(filename, nevents, configfile, totCalibFile, tdcCalibFile);
    WARNING(std::string("Even though the range of events was set, only the first ")
            + JPetCommonTools::intToString(nevents)
            + std::string(" will be unpacked by the unpacker. \n The unpacker always starts from the beginning of the file.")
           );
  } else {
    unpacker.setParams(filename, 100000000, configfile, totCalibFile, tdcCalibFile);
  }
  return unpacker.exec();
}
