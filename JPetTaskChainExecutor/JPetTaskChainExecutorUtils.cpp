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
 *  @file JPetTaskChainExecutorUtils.cpp
 */

#include <cassert>
#include "./JPetTaskChainExecutorUtils.h"
#include "../JPetTaskLoader/JPetTaskLoader.h"
#include "../JPetParamGetterAscii/JPetParamGetterAscii.h"
#include "../JPetParamGetterAscii/JPetParamSaverAscii.h"

bool JPetTaskChainExecutorUtils::process(const JPetOptions& options, JPetParamManager* paramMgr, std::list<JPetTaskRunnerInterface*>& tasks)
{
  assert(paramMgr);
  auto runNum = options.getRunNumber();
  if (runNum >= 0) {
    try {
      paramMgr->fillParameterBank(runNum);
    } catch (const std::exception& e) {
      ERROR(std::string("Param bank was not generated correctly with error: ") + e.what() + "\n The run number used:" + JPetCommonTools::intToString(runNum));
      return false;
    }
    if (options.isLocalDBCreate()) {
      JPetParamSaverAscii saver;
      saver.saveParamBank(paramMgr->getParamBank(), runNum, options.getLocalDBCreate());
    }
  }
  auto inputFile = options.getInputFile();
  auto inputFileType = options.getInputFileType();
  auto unpackerConfigFile = options.getUnpackerConfigFile();
  auto unpackerCalibFile = options.getUnpackerCalibFile();

  if (inputFileType == JPetOptions::kScope) {
    JPetScopeLoader* module = new JPetScopeLoader(new JPetScopeTask("JPetScopeReader", "Process Oscilloscope ASCII data into JPetRecoSignal structures."));
    module->setParamManager(paramMgr);
    tasks.push_front(module);
  } else if (inputFileType == JPetOptions::kHld) {
    unpackFile(inputFile, options.getTotalEvents(), unpackerConfigFile, unpackerCalibFile);
  }
  /// Assumption that if the file is zipped than it is in the hld format
  /// and we will also unpack if from hld  after unzipping.
  else if ( inputFileType == JPetOptions::kZip) {
    INFO( std::string("Unzipping file before unpacking") );
    if ( !unzipFile(inputFile) ) {
      ERROR( std::string("Problem with unpacking file: ") + inputFile );
      return false;
    } else {
      INFO( std::string("Unpacking") );
      auto unzippedFilename = JPetCommonTools::stripFileNameSuffix(std::string(inputFile)).c_str();
      unpackFile(unzippedFilename, options.getTotalEvents(), unpackerConfigFile, unpackerCalibFile);
    }
  }

  if (options.getInputFileType() == JPetOptions::kUndefinedFileType)
    ERROR( Form("Unknown file type provided for file: %s", options.getInputFile()) );
  return true;
}

void JPetTaskChainExecutorUtils::unpackFile(const char* filename, long long nevents, const char* configfile = "", const char* calibfile = "")
{
  JPetUnpacker unpacker;
  if (nevents > 0) {
    unpacker.setParams(filename, nevents, configfile, calibfile);
    WARNING(std::string("Even though the range of events was set, only the first ") + JPetCommonTools::intToString(nevents) + std::string(" will be unpacked by the unpacker. \n The unpacker always starts from the beginning of the file."));
  } else {
    unpacker.setParams(filename, 100000000, configfile, calibfile);
  }
  unpacker.exec();
}

JPetParamManager* JPetTaskChainExecutorUtils::generateParamManager(const JPetOptions& options)
{
  if (options.isLocalDB()) {
    std::set<ParamObjectType> expectMissing;
    if (options.getInputFileType() == JPetOptions::kScope) {
      expectMissing.insert(ParamObjectType::kTRB);
      expectMissing.insert(ParamObjectType::kFEB);
      expectMissing.insert(ParamObjectType::kFrame);
      expectMissing.insert(ParamObjectType::kLayer);
      expectMissing.insert(ParamObjectType::kTOMBChannel);
    }
    return new JPetParamManager(new JPetParamGetterAscii(options.getLocalDB()), expectMissing);
  } else {
    return new JPetParamManager();
  }
}
