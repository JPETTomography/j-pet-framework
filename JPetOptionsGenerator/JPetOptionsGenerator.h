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

#include "boost/program_options.hpp" // Library parsing command line arguments
#include <string>
#include "../JPetCmdParser/JPetCmdParser.h"
#include "../JPetOptions/JPetOptions.h"
#include <boost/any.hpp>
#include <typeinfo>
#include <iostream>
#include <utility>

class JPetOptionsGenerator
{
public:
  JPetOptionsGenerator();
  ~JPetOptionsGenerator();
  
  std::map<std::string, std::function<bool(std::pair <std::string, boost::any>)> > validationMap;

  std::map<std::string, std::vector<std::function<std::pair <std::string, boost::any>(boost::any)>> > transformationMap;

  std::vector<JPetOptions> generateOptions(const po::variables_map& optsMap) const;

  std::map<std::string, boost::any> transformOptions(std::map<std::string, boost::any>& optionsMap);
  
  bool areCorrectOptions(const std::map<std::string, boost::any>& options) const;
  
  bool isOptionSet(const std::map<std::string, boost::any>& variablesMap, const std::string& option) const; 
  
  boost::any getOptionValue(const std::map<std::string, boost::any>& variablesMap, std::string option) const;

  std::map<std::string, boost::any> variablesMapToOption(const po::variables_map& variablesMap) const; 

  std::map<std::string, std::string> anyMapToStringMap(const std::map<std::string, boost::any>& map) const;

  bool isNumberBoundsInRangeValid(std::pair <std::string, boost::any> option); 

  bool isRangeOfEventsValid(std::pair <std::string, boost::any> option);

  bool isCorrectFileType(std::pair <std::string, boost::any> option);

  bool isRunIdValid(std::pair <std::string, boost::any> option);

  bool isLocalDBValid(std::pair <std::string, boost::any> option);

  bool areFilesValid(std::pair <std::string, boost::any> option);

  bool isOutputDirectoryValid(std::pair <std::string, boost::any> option);

 
  inline const std::vector<std::string>& getFileNames(const po::variables_map& variablesMap) const {
    return variablesMap["file"].as< std::vector<std::string> >();
  }

  inline int getLowerEventBound(const po::variables_map& variablesMap) const {
    return variablesMap["range"].as< std::vector<int> >()[0];
  }
  inline int getHigherEventBound(const po::variables_map& variablesMap) const {
    return variablesMap["range"].as< std::vector<int> >()[1];
  }
  inline const int getRunNumber(const po::variables_map& variablesMap) const {
    return variablesMap["runId"].as<int>();
  }

  inline bool isProgressBarSet(const po::variables_map& variablesMap) const {
    return variablesMap["progressBar"].as<bool>();
  }

};
#endif
