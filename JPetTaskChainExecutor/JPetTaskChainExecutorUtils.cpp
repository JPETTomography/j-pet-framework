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
  return true;
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
