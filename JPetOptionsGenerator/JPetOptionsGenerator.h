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

#include "../JPetOptions/JPetOptions.h"
#include "../JPetOption/JPetOption.h"
#include "../JPetOptionValidator/JPetOptionValidator.h"

namespace po = boost::program_options;

class JPetOptionsGenerator
{
public:
  using OptNameValPair = std::pair<std::string, boost::any>;
  using Transformer = std::function<OptNameValPair(boost::any opt)>;
  using CmdLineArgs = po::variables_map;

  JPetOptionsGenerator();

  std::vector<JPetOptions> generateOptions(const po::variables_map& optsMap);
  std::string getConfigFileName(const po::variables_map& optsMap) const;
  void addNewOptionsFromCfgFile(const std::string& cfgFile, std::map<std::string, boost::any>& options) const;
  void addMissingDefaultOptions(std::map<std::string, boost::any>& options) const;

  void createMapOfBoolOptionFromUser(const std::map<std::string, boost::any>& optionsMap);

  bool isOptionSet(const std::map<std::string, boost::any>& optionsMap, const std::string& option) const;
  boost::any getOptionValue(const std::map<std::string, boost::any>& optionsMap, std::string option) const;

  std::map<std::string, boost::any> variablesMapToOption(const po::variables_map& variablesMap);
  std::map<std::string, std::vector<Transformer> > generateTransformationMap() const;
  void addTransformFunction(const std::string& name, Transformer transformFunction);

  std::map<std::string, boost::any> transformOptions(std::map<std::string, boost::any>& optionsMap) const;
  /// transformation functions ?
  static std::pair <std::string, boost::any>appendSlash(boost::any option);
  static std::pair <std::string, boost::any>setInputFileType(boost::any option);
  static std::pair <std::string, boost::any>getLowerEventBound(boost::any option);
  static std::pair <std::string, boost::any>getHigherEventBound(boost::any option);

  static std::map<std::string, boost::any> getDefaultOptions() {
    return kDefaultOptions;
  }
  std::vector<std::string> getVectorOfOptionFromUser() const;

  JPetOptionValidator& getValidator();

protected:
  static std::map<std::string, boost::any> kDefaultOptions;
private:
  std::map<std::string, std::vector<Transformer> > fTransformationMap;
  std::vector<std::string> fVectorOfOptionFromUser;
  JPetOptionValidator fValidator;
  

};
#endif
