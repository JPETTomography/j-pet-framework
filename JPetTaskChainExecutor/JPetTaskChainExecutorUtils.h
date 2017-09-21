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

#include "../JPetUnpacker/JPetUnpacker.h"
#include "../JPetParamManager/JPetParamManager.h"
#include "../JPetScopeLoader/JPetScopeLoader.h"
#include "../JPetParams/JPetParams.h"
#include <boost/concept_check.hpp>

/**
 * JPetTaskChainExecutorUtils contains methods that can be used by JPetTaskExecutor
 * to execute some tasks e.g. unpack hld file based on options. This preprocessing
 * is tipically done before running main tasks.
 */
class JPetTaskChainExecutorUtils
{
public:
  using OptionsPerFile = std::vector<jpet_options_tools::OptsStrAny>;
  /// process() method depends on the options can: 1.saves paramBank locally in ASCII format , 2. generate and add ScopeLoader
  /// 3. unpack the hld file.
  static bool process(const JPetParams& params);
  static void unpackFile(const char* filename, long long nevents, const char* configfile, const char* calibfile);
  /// system(...) is returning integer, 0 when everything went smoothly and error code when not.
  /// Here I just convert return value into boolean type - Sz.N.
  static bool unzipFile(const char* filename);
  static std::vector<JPetParams> generateParams(const OptionsPerFile& opts);
  static std::shared_ptr<JPetParamManager> generateParamManager(const std::map<std::string, boost::any>& options);
};
#endif /*  !JPETTASKCHAINEXECUTORUTILS_H */
