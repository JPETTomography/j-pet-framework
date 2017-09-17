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

#include <typeinfo>
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <string>

#include "boost/program_options.hpp" // Library parsing command line arguments
#include <boost/any.hpp>

#include "../JPetOptionValidator/JPetOptionValidator.h"
#include "../JPetOptions/JPetOptionsTools.h"


namespace po = boost::program_options;

class JPetOptionsGenerator
{
public:
  using OptsStrAny = std::map<std::string, boost::any>;
  using OptsForTasks =  std::vector<OptsStrAny>;
  using OptsForFiles = std::map<std::string, OptsForTasks>;

  using OptNameValPair = std::pair<std::string, boost::any>;
  using Transformer = std::function<OptNameValPair(boost::any opt)>;
  using CmdLineArgs = po::variables_map;

  JPetOptionsGenerator();

  OptsForFiles generateOptions(const po::variables_map& cmdLineArgs, int nbOfRegisteredTasks = 1);

  ///Method generates the options set: option_name->value based on the input sets of command line args.
  ///Also missing options are added from the default set.
  std::map<std::string, boost::any> generateAndValidateOptions(const po::variables_map& cmdLineArgs);

  static OptsStrAny transformToStrAnyMap(const po::variables_map& variablesMap);
  ///Methods add type suffixes to the elements of the map
  static OptsStrAny addTypeSuffixes(const OptsStrAny& oldMap);

  std::string getConfigFileName(const std::map<std::string, boost::any>& optsMap) const;

  void addNewOptionsFromCfgFile(const std::string& cfgFile, std::map<std::string, boost::any>& options) const;
  void addMissingDefaultOptions(std::map<std::string, boost::any>& options) const;

  void createMapOfBoolOptionFromUser(const std::map<std::string, boost::any>& optionsMap);

  bool isOptionSet(const std::map<std::string, boost::any>& optionsMap, const std::string& option) const;
  boost::any getOptionValue(const std::map<std::string, boost::any>& optionsMap, std::string option) const;

  std::map<std::string, std::vector<Transformer> > generateTransformationMap() const;
  void addTransformFunction(const std::string& name, Transformer transformFunction);

  std::map<std::string, boost::any> transformOptions(std::map<std::string, boost::any>& optionsMap) const;

  static std::pair <std::string, boost::any>appendSlash(boost::any option);
  static std::pair <std::string, boost::any>setInputFileType(boost::any option);
  static std::pair <std::string, boost::any>getLowerEventBound(boost::any option);
  static std::pair <std::string, boost::any>getHigherEventBound(boost::any option);

  ///@todo that should be moved to tools
  /// Ignore the event range options for all but the first task.
  /// For all but the first task,
  /// the input path must be changed if
  /// the output path argument -o was given, because the input
  /// data for them will lay in the location defined by -o.
  static std::vector<jpet_options_tools::OptionsStrAny> setCorrectRangeAndOutputForNonFirstOption(const std::vector<jpet_options_tools::OptionsStrAny>& oldOptions);

  static std::map<std::string, boost::any> getDefaultOptions();
  std::vector<std::string> getVectorOfOptionFromUser() const;

protected:
  static std::map<std::string, boost::any> kDefaultOptions;
  static std::map<std::string, std::string> kOptCmdLineNameToExtendedName;

private:
  std::map<std::string, std::vector<Transformer> > fTransformationMap;
  std::vector<std::string> fVectorOfOptionFromUser;
};
#endif
