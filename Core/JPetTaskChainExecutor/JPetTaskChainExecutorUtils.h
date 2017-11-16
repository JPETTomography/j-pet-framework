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
 *  @file JPetTaskChainExecutorUtils.h
 */

#ifndef JPETTASKCHAINEXECUTORUTILS_H
#define JPETTASKCHAINEXECUTORUTILS_H

#include "../JPetParamManager/JPetParamManager.h"
#include "../JPetParams/JPetParams.h"

/**
 * JPetTaskChainExecutorUtils contains methods that can be used by JPetTaskExecutor.
 * This preprocessing
 * is typically done before running main tasks.
 */
class JPetTaskChainExecutorUtils
{
public:
  /// process() method depends on the options can: 1.saves paramBank locally in ASCII format
  static bool process(const JPetParams& params);
  static JPetParams generateParams(const jpet_options_tools::OptsStrAny& opts);
  static std::shared_ptr<JPetParamManager> generateParamManager(const std::map<std::string, boost::any>& options);
  static JPetParams generateParams(const JPetParams& inParams, const JPetParams& controlParams);
};
#endif /*  !JPETTASKCHAINEXECUTORUTILS_H */
