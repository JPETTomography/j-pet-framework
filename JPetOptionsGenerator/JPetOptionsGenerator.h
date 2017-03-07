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

class JPetOptionsGenerator
{
public:
  JPetOptionsGenerator();
  ~JPetOptionsGenerator();
  
  std::vector<JPetOptions> generateOptions(const po::variables_map& optsMap) const;
  
  bool areCorrectOptions(const std::map<std::string, boost::any>& options) const;
  
  bool isOptionSet(const std::map<std::string, boost::any>& variablesMap, const std::string& option) const; 
  
  std::string getOptionValue(const std::map<std::string, boost::any>& variablesMap, std::string& option) const;

  std::map<std::string, boost::any> variablesMapToOption(const po::variables_map& variablesMap) const; 
  
  inline const std::vector<std::string>& getFileNames(const po::variables_map& variablesMap) const {
    return variablesMap["file"].as< std::vector<std::string> >();
  }
  inline bool isCorrectFileType(const std::string& type) const {
    if (type == "hld" || type == "root" || type == "scope" || type == "zip") {
      return true;
    }
    return false;
  }

//  inline const std::string& getOutputPath(const po::variables_map& variablesMap) const {
//    return variablesMap["outputPath"].as<std::string>();
//  }

//  inline bool isOutputPath(const po::variables_map& variablesMap) const {
//    return (bool)variablesMap.count("outputPath");
//  }

//  inline const std::string& getFileType(const po::variables_map& variablesMap) const {
//    return variablesMap["type"].as<std::string>();
//  }

//  inline bool IsFileTypeSet(const po::variables_map& variablesMap) const {
//    return (bool)variablesMap.count("type");
//  }

  inline int getLowerEventBound(const po::variables_map& variablesMap) const {
    return variablesMap["range"].as< std::vector<int> >()[0];
  }
  inline int getHigherEventBound(const po::variables_map& variablesMap) const {
    return variablesMap["range"].as< std::vector<int> >()[1];
  }
//  inline bool isParamSet(const po::variables_map& variablesMap) const {
//    return (bool)variablesMap.count("param");
//  }
//  inline const std::string& getParam(const po::variables_map& variablesMap) const {
//    return variablesMap["param"].as< std::string >();
//  }

//  inline bool isRunNumberSet(const po::variables_map& variablesMap) const {
//    return (bool)variablesMap.count("runId");
//  }

  inline const int getRunNumber(const po::variables_map& variablesMap) const {
    return variablesMap["runId"].as<int>();
  }

  inline bool isProgressBarSet(const po::variables_map& variablesMap) const {
    return variablesMap["progressBar"].as<bool>();
  }

//  static inline bool isLocalDBSet(const po::variables_map& variablesMap) {
//    return variablesMap.count("localDB") > 0;
//  }
//  static inline std::string getLocalDBName(const po::variables_map& variablesMap) {
//    return variablesMap["localDB"].as<std::string>();
// }

//  static inline bool isLocalDBCreateSet(const po::variables_map& variablesMap) {
//    return variablesMap.count("localDBCreate") > 0;
//  }
//  static inline std::string getLocalDBCreateName(const po::variables_map& variablesMap) {
//    return variablesMap["localDBCreate"].as<std::string>();
//  }

};
#endif
