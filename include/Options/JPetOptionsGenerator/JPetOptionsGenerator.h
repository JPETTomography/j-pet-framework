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
 *  @file JPetOptionsGenerator.h
 */

#ifndef _JPET_OPTIONS_GENERATOR_H_
#define _JPET_OPTIONS_GENERATOR_H_

#include "./JPetOptionsTools/JPetOptionsTools.h"
#include "boost/program_options.hpp"
#include <boost/any.hpp>
#include <vector>
#include <string>
#include <map>

namespace po = boost::program_options;

/**
 * @brief Class for generating options with the help of BOOST LIBs.
 */
class JPetOptionsGenerator
{
public:
  using OptsStrAny = std::map<std::string, boost::any>;
  using OptsForTasks = OptsStrAny;
  using OptsForFiles = std::map<std::string, OptsForTasks>;
  using TransformersMap = std::map<std::string, std::vector<jpet_options_tools::Transformer>>;
  OptsStrAny generateAndValidateOptions(const po::variables_map& cmdLineArgs);
  OptsForFiles generateOptionsForTasks(const OptsStrAny& opt, int nbOfRegisteredTasks = 1);

private:
  std::vector<std::string> getOptionsToBeValidated(const OptsStrAny& optionsMap) const;
};

#endif /* !_JPET_OPTIONS_GENERATOR_H_ */
