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
using namespace std;

JPetUnpackTask::JPetUnpackTask(const char* name) : JPetTask(name) {}

bool JPetUnpackTask::init(const JPetParams& inParams)
{
  INFO("UnpackTask started.");
  fOptions = inParams.getOptions();

  fInputFile = JPetCommonTools::extractFileNameFromFullPath(getInputFile(fOptions));
  fInputFilePath = JPetCommonTools::appendSlashToPathIfAbsent(
    JPetCommonTools::extractPathFromFile(getInputFile(fOptions))
  );

  if (getOutputPath(fOptions) != "") {
    fOutputFilePath = JPetCommonTools::appendSlashToPathIfAbsent(getOutputPath(fOptions));
  } else {
    fOutputFilePath = fInputFilePath;
  }

  fXMLConfFile = getUnpackerConfigFile(fOptions);

  if (getTotalEvents(fOptions) > 0) {
    fEventsToProcess = getTotalEvents(fOptions);
  }

  auto totCalibSet = isOptionSet(fOptions, kTOTOffsetCalibKey);
  if (totCalibSet) {
    fTOTOffsetCalibFile = getOptionAsString(fOptions, kTOTOffsetCalibKey);
  } else {
    WARNING("No TOT offset calibration file set int the user options!");
  }

  auto tdcCalibSet = isOptionSet(fOptions, kTDCnonlinearityCalibKey);
  if (tdcCalibSet) {
    fTDCnonlinearityCalibFile = getOptionAsString(fOptions, kTDCnonlinearityCalibKey);
  } else {
    WARNING("No TDC nonlinearity file set int the user options!");
  }

  return validateFiles(
    fInputFilePath+fInputFile, fXMLConfFile,
    fTOTOffsetCalibFile, totCalibSet,
    fTDCnonlinearityCalibFile, tdcCalibSet
  );
}

bool JPetUnpackTask::run(const JPetDataInterface&)
{
  int refChannelOffset = 65;
  fUnpacker2 = new Unpacker2();

  INFO(Form("Using Unpacker2 to process first %i events", fEventsToProcess));
  fUnpacker2->UnpackSingleStep(
    fInputFile, fInputFilePath, fOutputFilePath,
    fXMLConfFile, fEventsToProcess, refChannelOffset,
    fTOTOffsetCalibFile, fTDCnonlinearityCalibFile
  );
  return true;
}

bool JPetUnpackTask::terminate(JPetParams& outParams)
{
  if (fUnpacker2) {
    delete fUnpacker2;
    fUnpacker2 = 0;
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

bool JPetUnpackTask::validateFiles(
  string fileNameWithPath, string xmlConfig,
  string totCalib, bool totCalibSet, string tdcCalib, bool tdcCalibSet
){
  if(!boost::filesystem::exists(fileNameWithPath)) {
    ERROR("The Unpacker did not find input HLD file");
    return false;
  }

  if (!boost::filesystem::exists(xmlConfig)) {
    ERROR("The Unpacker XML configuration file does not exist, exiting.");
    return false;
  }

  if(totCalibSet) {
    if(!boost::filesystem::exists(totCalib)){
      ERROR(Form("No TOT offset calibration file found with the provided name: %s", totCalib.c_str()));
      return false;
    }
  }

  if(tdcCalibSet){
    if(!boost::filesystem::exists(tdcCalib)){
      ERROR(Form("No TDC nonlinearity file found with the provided name: %s", tdcCalib.c_str()));
      return false;
    }
  }

  return true;
}
