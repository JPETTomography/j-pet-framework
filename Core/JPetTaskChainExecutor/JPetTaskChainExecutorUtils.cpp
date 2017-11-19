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
#include "./JPetParamGetterAscii/JPetParamGetterAscii.h"
#include "./JPetParamGetterAscii/JPetParamSaverAscii.h"
#include "./JPetOptionsTools/JPetOptionsTools.h"
#include "./JPetCommonTools/JPetCommonTools.h"
#include "./JPetOptionsGenerator/JPetOptionsGeneratorTools.h"

///@todo this function should be moved to some other class
JPetParams JPetTaskChainExecutorUtils::generateParams(const jpet_options_tools::OptsStrAny& opts)
{
  std::shared_ptr<JPetParamManager> paramManager2 = JPetParamManager::generateParamManager(opts);
  return JPetParams(opts, paramManager2);
}


JPetParams JPetTaskChainExecutorUtils::generateParams(const JPetParams& inParams, const JPetParams& controlParams)
{
  using namespace jpet_options_generator_tools;
  JPetParams newParams(generateOptionsForTask(inParams.getOptions(), controlParams.getOptions()), inParams.getParamManagerAsShared());
  return  newParams;
}
