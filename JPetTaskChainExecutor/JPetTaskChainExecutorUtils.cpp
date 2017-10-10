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
#include "../JPetOptionsTools/JPetOptionsTools.h"
#include "../JPetCommonTools/JPetCommonTools.h"


bool JPetTaskChainExecutorUtils::process(const JPetParams& params)
{
  using namespace jpet_options_tools;
  auto options =  params.getOptions();
  auto paramMgr = params.getParamManager();
  if (!paramMgr) {
    ERROR("Param manager is not set");
    return false;
  }
  auto runNum = getRunNumber(options);
  if (runNum >= 0) {
    try {
      paramMgr->fillParameterBank(runNum);
    } catch (const std::exception& e) {
      ERROR(std::string("Param bank was not generated correctly with error: ") + e.what() + "\n The run number used:" + JPetCommonTools::intToString(runNum));
      return false;
    }
    if (isLocalDBCreate(options)) {
      JPetParamSaverAscii saver;
      saver.saveParamBank(paramMgr->getParamBank(), runNum, getLocalDBCreate(options));
    }
  }

  /// @todo this part of the code should be removed after new construct check
  //auto inputFile = getInputFile(options);
  //auto inputFileType = FileTypeChecker::getInputFileType(options);
  //auto unpackerConfigFile = getUnpackerConfigFile(options);
  //auto unpackerCalibFile = getUnpackerCalibFile(options);

  //if (inputFileType == FileTypeChecker::kHld) {
  //unpackFile(inputFile, getTotalEvents(options), unpackerConfigFile, unpackerCalibFile);
  //}
  ///// Assumption that if the file is zipped than it is in the hld format
  ///// and we will also unpack if from hld  after unzipping.
  //else if ( inputFileType == FileTypeChecker::kZip) {
  //INFO( std::string("Unzipping file before unpacking") );
  //if ( !unzipFile(inputFile) ) {
  //ERROR( std::string("Problem with unpacking file: ") + inputFile );
  //return false;
  //} else {
  //INFO( std::string("Unpacking") );
  //auto unzippedFilename = JPetCommonTools::stripFileNameSuffix(std::string(inputFile)).c_str();
  //unpackFile(unzippedFilename, getTotalEvents(options), unpackerConfigFile, unpackerCalibFile);
  //}
  //}

  //if (FileTypeChecker::getInputFileType(options) == FileTypeChecker::kUndefinedFileType) {
  //ERROR( Form("Unknown file type provided for file: %s", getInputFile(options)) );
  //return false;
  //}
  return true;
}

/// Function unpacks file of the hld format into a root tree
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

///@todo this function should be moved to some other class
std::vector<JPetParams> JPetTaskChainExecutorUtils::generateParams(const OptionsPerFile& opts)
{
  std::vector<JPetParams> params;
  std::shared_ptr<JPetParamManager> paramManager2 = JPetTaskChainExecutorUtils::generateParamManager(opts.front());

  params.reserve(opts.size());
  for (const auto& opt : opts) {
    params.push_back(JPetParams(opt, paramManager2));
  }
  return params;
}

///@todo this function should be moved to some other class
std::shared_ptr<JPetParamManager> JPetTaskChainExecutorUtils::generateParamManager(const std::map<std::string, boost::any>& options)
{
  using namespace jpet_options_tools;
  if (isLocalDB(options)) {
    std::set<ParamObjectType> expectMissing;
    if (FileTypeChecker::getInputFileType(options) == FileTypeChecker::kScope) {
      expectMissing.insert(ParamObjectType::kTRB);
      expectMissing.insert(ParamObjectType::kFEB);
      expectMissing.insert(ParamObjectType::kFrame);
      expectMissing.insert(ParamObjectType::kLayer);
      expectMissing.insert(ParamObjectType::kTOMBChannel);
    }
    return std::make_shared<JPetParamManager>(new JPetParamGetterAscii(getLocalDB(options)), expectMissing);
  } else {
    return std::make_shared<JPetParamManager>();
  }
}

bool JPetTaskChainExecutorUtils::unzipFile(const char* filename)
{
  if ( JPetCommonTools::exctractFileNameSuffix(filename) == ".gz")
    return !( system( ( std::string("gzip -dk ") + std::string(filename) ).c_str() ) );
  else if ( JPetCommonTools::exctractFileNameSuffix(filename) == ".xz" )
    return !( system( (std::string("xz -dk ") + std::string(filename) ).c_str() ) );
  else
    return false;
}
