/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetUnpackTask.cpp
 */

#include "JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "JPetOptionsTools/JPetOptionsTools.h"
#include "JPetCommonTools/JPetCommonTools.h"
#include "JPetUnpackTask/JPetUnpackTask.h"
#include "JPetParams/JPetParams.h"
#include <fstream>

using namespace jpet_options_tools;

JPetUnpackTask::JPetUnpackTask(const char* name): JPetTask(name) {}

bool JPetUnpackTask::init(const JPetParams& inParams)
{
  INFO("UnpackTask started.");
  fOptions = inParams.getOptions();

  // Reading options from the command line
  fInputFile = JPetCommonTools::extractFileNameFromFullPath(
    getInputFile(fOptions)
  );
  fInputFilePath = JPetCommonTools::appendSlashToPathIfAbsent(
    JPetCommonTools::extractPathFromFile(getInputFile(fOptions))
  );
  if (getOutputPath(fOptions) != "") {
    fOutputFilePath = JPetCommonTools::appendSlashToPathIfAbsent(
      getOutputPath(fOptions)
    );
  } else {
    fOutputFilePath = fInputFilePath;
  }

  fXMLConfFile = getUnpackerConfigFile(fOptions);
  if (!boost::filesystem::exists(fXMLConfFile)) {
    ERROR("The Unpacker XML configuration file does not exist, exiting.");
    return false;
  }

  if (getTotalEvents(fOptions) > 0) {
    fEventsToProcess = getTotalEvents(fOptions);
  }

  // Reading parameters from the user json file
  if (isOptionSet(fOptions, kTOTOffsetCalibKey)) {
    fTOTOffsetCalibFile = getOptionAsString(fOptions, kTOTOffsetCalibKey);
    if(!boost::filesystem::exists(fTOTOffsetCalibFile)){
      ERROR(Form("No TOT offset calibration file found with the provided name: %s", fTOTOffsetCalibFile.c_str()));
      return false;
    }
  } else {
    ERROR("No TOT offset calibration file set int the user options, exiting.");
  }
  if (isOptionSet(fOptions, kTDCnonlinearityCalibKey)) {
    fTDCnonlinearityCalibFile = getOptionAsString(fOptions, kTDCnonlinearityCalibKey);
    if(!boost::filesystem::exists(fTDCnonlinearityCalibFile)){
      ERROR(Form("No TDC nonlinearity file found with the provided name: %s", fTDCnonlinearityCalibFile.c_str()));
      return false;
    }
  } else {
    ERROR("No TDC nonlinearity file set int the user options, exiting.");
  }

  return true;
}

bool JPetUnpackTask::run(const JPetDataInterface&)
{
  if (DetectorTypeChecker::getDetectorType(fOptions) == DetectorTypeChecker::DetectorType::kBarrel) {

    int refChannelOffset = 65;
    fUnpacker2 = new Unpacker2();

    INFO(Form("Using Unpacker2 to process first %i events", fEventsToProcess));

    fUnpacker2->UnpackSingleStep(
      fInputFile, fInputFilePath, fOutputFilePath,
      fXMLConfFile, fEventsToProcess, refChannelOffset,
      fTOTOffsetCalibFile, fTDCnonlinearityCalibFile
    );

  } else if (DetectorTypeChecker::getDetectorType(fOptions) == DetectorTypeChecker::DetectorType::kModular) {

    int refChannelOffset = 105;
    fUnpacker2D = new Unpacker2D();

    INFO(Form("Using Unpacker2D to process first %i events", fEventsToProcess));

    fUnpacker2D->UnpackSingleStep(
      fInputFile, fInputFilePath, fOutputFilePath,
      fXMLConfFile, fEventsToProcess, refChannelOffset,
      fTOTOffsetCalibFile, fTDCnonlinearityCalibFile
    );

  } else {
    return false;
  }
  return true;
}

bool JPetUnpackTask::terminate(JPetParams& outParams)
{
  if (fUnpacker2) {
    delete fUnpacker2;
    fUnpacker2 = 0;
  }
  if (fUnpacker2D) {
    delete fUnpacker2D;
    fUnpacker2D = 0;
  }

  OptsStrAny new_opts;
  jpet_options_generator_tools::setOutputFileType(new_opts, "hldRoot");
  jpet_options_generator_tools::setOutputFile(
    new_opts,
    JPetCommonTools::replaceDataTypeInFileName(getInputFile(fOptions), "hld")
  );
  outParams = JPetParams(new_opts, outParams.getParamManagerAsShared());
  INFO("UnpackTask finished.");

  return true;
}
