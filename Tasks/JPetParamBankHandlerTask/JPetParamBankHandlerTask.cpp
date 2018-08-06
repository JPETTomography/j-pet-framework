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
 *  @file JPetParamBankHandlerTask.cpp
 */

#include "./JPetCommonTools/JPetCommonTools.h"
#include "JPetParamBankHandlerTask.h"

JPetParamBankHandlerTask::JPetParamBankHandlerTask(const char* name): JPetTask(name){}

/**
 * 1. If the input file type is 'hld', 'hld.root' or 'scope', the ParamBank
 * is created based on provided json file and run number.
 * 2. If the input file type is 'root', the ParamBank should always be read from
 * the input file, even if the user provided the run number and localDB flags.
 * The TRef-s contained in the 'root' file would only make sense with the
 * ParamBank from the same file a not with a newly created one.
 * 3. For any other file type, there is an attempt to generate ParamBank
 * from file, if failed and run number and localDB is provided, trying
 * to generate ParamBank from config.
 */
bool JPetParamBankHandlerTask::init(const JPetParams& params)
{
  using namespace jpet_options_tools;
  auto options = params.getOptions();
  switch (FileTypeChecker::getInputFileType(options)) {
    case FileTypeChecker::FileType::kHld:
    case FileTypeChecker::FileType::kHldRoot:
      return generateParamBankFromConfig(params);
      break;
    case FileTypeChecker::FileType::kRoot:
      return generateParamBankFromRootFile(params);
      break;
    case FileTypeChecker::FileType::kScope:
      return generateParamBankFromConfig(params);
      break;
    case FileTypeChecker::FileType::kMCGeant:
      return generateParamBankFromConfig(params);
      break;
    default:
      std::map<FileTypeChecker::FileType, std::string> fileTypeToString = {
        {FileTypeChecker::kNoType, ""},
        {FileTypeChecker::kRoot, "root"},
        {FileTypeChecker::kScope, "scope"},
        {FileTypeChecker::kHld, "hld"},
        {FileTypeChecker::kHldRoot, "hldRoot"},
        {FileTypeChecker::kZip, "zip"}
      };
      WARNING("Unrecognized file format: "
        +fileTypeToString[FileTypeChecker::getInputFileType(options)]
        + " but trying to generate ParamBank from file...");
      if (generateParamBankFromRootFile(params)) return true;
      else {
        if (getRunNumber(options) != -1 && isLocalDB(options)) {
          WARNING("Error while tring generate ParamBank from file: "
            + fileTypeToString[FileTypeChecker::getInputFileType(options)]
            + " but run number and localDB is set, trying to generate ParamBank from it...");
          return generateParamBankFromConfig(params);
        }
      break;
    }
  }
  return false;
}

bool JPetParamBankHandlerTask::run(const JPetDataInterface&)
{
  return true;
}

bool JPetParamBankHandlerTask::terminate(JPetParams&)
{
  return true;
}

bool JPetParamBankHandlerTask::generateParamBankFromRootFile(const JPetParams& params)
{
  using namespace jpet_options_tools;
  auto options = params.getOptions();
  if (getRunNumber(options) != -1) {
    WARNING("Input file was ROOT, but run number option is set, ignoring it");
  }
  if (isLocalDB(options)) {
    WARNING("Input file was ROOT, but localDB option is set, ignoring it");
  }
  JPetReader fReader;
  fReader.openFileAndLoadData(getInputFile(options).c_str());
  auto paramMgr = params.getParamManager();
  return paramMgr->readParametersFromFile(&fReader);
}

bool JPetParamBankHandlerTask::generateParamBankFromConfig(const JPetParams& params)
{
  using namespace jpet_options_tools;
  auto options = params.getOptions();
  if (getRunNumber(options) == -1 || !isLocalDB(options)) {
    ERROR("LocalDB and run number are required for Hld, HldRoot or Scope files");
    return false;
  }
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
      ERROR(std::string("Param bank was not generated correctly with error: ")
        + e.what() + "\n The run number used:"
        + JPetCommonTools::intToString(runNum));
      return false;
    }
    if (isLocalDBCreate(options)) {
      JPetParamSaverAscii saver;
      saver.saveParamBank(paramMgr->getParamBank(), runNum, getLocalDBCreate(options));
    }
  }
  return true;
}
