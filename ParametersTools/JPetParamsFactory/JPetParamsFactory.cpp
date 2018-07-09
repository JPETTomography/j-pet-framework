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
 *  @file JPetParamsFactory.cpp
 */

#include "./JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "./JPetParamManager/JPetParamManager.h"
#include "./JPetParamsFactory.h"

namespace jpet_params_factory
{

JPetParams generateParams(const jpet_options_tools::OptsStrAny& opts)
{
  std::shared_ptr<JPetParamManager> paramManager2 = JPetParamManager::generateParamManager(opts);
  return JPetParams(opts, paramManager2);
}

JPetParams generateParams(const JPetParams& inParams, const JPetParams& controlParams)
{
  using namespace jpet_options_generator_tools;
  JPetParams newParams(generateOptionsForTask(inParams.getOptions(), controlParams.getOptions()), inParams.getParamManagerAsShared());
  return  newParams;
}

}
