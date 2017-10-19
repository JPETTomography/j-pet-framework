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
 *  @file JPetOptionsGenerator.h
 */

#ifndef _JPET_OPTIONS_GENERATOR_H_
#define _JPET_OPTIONS_GENERATOR_H_

class JPetOptionsGenerator;

#include <vector>
#include <map>
#include <string>

#include "boost/program_options.hpp" // Library parsing command line arguments
#include <boost/any.hpp>

#include "../JPetOptionsTools/JPetOptionsTools.h"


namespace po = boost::program_options;

class JPetOptionsGenerator
{
public:
  using OptsStrAny = std::map<std::string, boost::any>;
  using OptsForTasks =  std::vector<OptsStrAny>;
  using OptsForFiles = std::map<std::string, OptsForTasks>;
  using TransformersMap = std::map<std::string, std::vector<jpet_options_tools::Transformer> >;

  /// Method generates the options set: option_name->value based on the input sets of command line args.
  /// Also missing options are added from the default set.
  /// And the basic validation is performed.
  /// The option set is common for all files and tasks.
  OptsStrAny generateAndValidateOptions(const po::variables_map& cmdLineArgs);
  
  /// Method returns a map of Options
  /// based on the number of registered tasks and provided options.
  /// The elements of the map are pairs filename -> OptionsForAllTasks
  /// , where OptionsForAllTasks is a container with elements correspondig to the
  /// options assigned for given task.
  /// e.g. if there are 4 files and for each file there are 3 tasks, then the map
  /// should have 4 containers with 3 option elements each.
  /// In this version it is assumed that for every file the same number of tasks are
  /// provided defined by nbOfRegisteredTasks arguments.
  OptsForFiles generateOptionsForTasks(const OptsStrAny& opt, int nbOfRegisteredTasks = 1);

  std::vector<std::string> getVectorOfOptionFromUser() const;
  void createMapOfBoolOptionFromUser(const OptsStrAny& optionsMap);

protected:
  static std::map<std::string, boost::any> kDefaultOptions;
  static std::map<std::string, std::string> kOptCmdLineNameToExtendedName;

private:
  std::vector<std::string> fVectorOfOptionFromUser;
};
#endif
