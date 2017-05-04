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
 *  @file JPetOptionsGenerator.cpp
 */

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "JPetOptionsGenerator.h"
#include "../JPetCommonTools/JPetCommonTools.h"
#include "../JPetLoggerInclude.h"
#include "../JPetOptions/JPetOptionsTools.h"
#include "../JPetScopeConfigParser/JPetScopeConfigParser.h"
#include "../JPetOptionsGenerator/JPetOptionsTypeHandler.h"
#include "../JPetOptionValidator/JPetOptionValidator.h"

using boost::any_cast;
using namespace std;

JPetOptionsGenerator::JPetOptionsGenerator()
{
}

bool JPetOptionsGenerator::isOptionSet(const std::map<std::string, boost::any>& optionsMap, const std::string& option) const
{
  return (bool)optionsMap.count(option);
}

boost::any JPetOptionsGenerator::getOptionValue(const std::map<std::string, boost::any>& optionsMap, std::string option) const
{
  return optionsMap.at(option);
}

std::pair <std::string, boost::any>JPetOptionsGenerator::appendSlash(boost::any option)
{
  auto path = JPetCommonTools::appendSlashToPathIfAbsent(any_cast<std::string>(option));
  return std::make_pair("outputPath_std::string", path);
}

std::pair <std::string, boost::any>JPetOptionsGenerator::getLowerEventBound(boost::any option)
{
  int firstEvent = any_cast<std::vector<int>>(option)[0];
  if (firstEvent >= 0) {
    return std::make_pair("firstEvent_int", firstEvent);
  } else
    return std::make_pair("wrongFirstEvent_int", -1);
}

std::pair <std::string, boost::any>JPetOptionsGenerator::getHigherEventBound(boost::any option)
{
  int lastEvent = any_cast<std::vector<int>>(option)[1];
  if (lastEvent >= 0) {
    return std::make_pair("lastEvent_int", lastEvent);
  } else
    return std::make_pair("wrongLastEvent_int", -1);
}

std::pair <std::string, boost::any>JPetOptionsGenerator::setInputFileType(boost::any option)
{
  auto inputFileType = any_cast<std::string>(option);
  return std::make_pair("inputFileType_std::string", inputFileType);
}

std::map<std::string, boost::any> JPetOptionsGenerator::variablesMapToOption(const po::variables_map& variablesMap) const
{
  std::map<std::string, boost::any> optionsMap;
  for (auto & option : variablesMap) {
    optionsMap[option.first] = option.second.value();
  }
  return optionsMap;
}


std::map<std::string, std::vector<std::pair <std::string, boost::any>(*)(boost::any)> > JPetOptionsGenerator::generateTransformationMap() const
{
  std::map<std::string, std::vector<std::pair <std::string, boost::any>(*)(boost::any)> > transformationMap;
  transformationMap["outputPath_std::string"].push_back(&appendSlash);
  transformationMap["range_std::vector<int>"].push_back(&getLowerEventBound);
  transformationMap["range_std::vector<int>"].push_back(&getHigherEventBound);
  transformationMap["type_std::string"].push_back(&setInputFileType);
  return transformationMap;
}


std::map<std::string, boost::any> JPetOptionsGenerator::transformOptions(std::map<std::string, boost::any>& optionsMap) const
{
  auto transformationMap = generateTransformationMap();
  for (auto & validGroup : transformationMap) {
    if (optionsMap.count(validGroup.first)) {
      for (auto & validFunct : validGroup.second) {
        std::pair <std::string, boost::any> transformed = validFunct(optionsMap.at(validGroup.first));
        optionsMap[transformed.first] = transformed.second;
      }
    }
  }
  return optionsMap;
}

/// We add additional options to already existing one.
/// If the key already exists the element will not be updated.
void JPetOptionsGenerator::addNewOptionsFromCfgFile(const std::string& cfgFile, std::map<std::string, boost::any>& options) const
{
  jpet_options_tools::Options optionsFromJson = jpet_options_tools::createOptionsFromConfigFile(cfgFile);
  options.insert(optionsFromJson.begin(), optionsFromJson.end());
}

std::string JPetOptionsGenerator::getConfigFileName(const po::variables_map& optsMap) const
{
  if (optsMap.count("userCfg_std::string")) {
    return optsMap["userCfg_std::string"].as<std::string>();
  } else {
    return "";
  }
}

void JPetOptionsGenerator::addMissingDefaultOptions(std::map<std::string, std::string>& stringMap) const
{
  std::map<std::string, std::string> defaultOptions = JPetOptions::getDefaultOptions();
  stringMap.insert(defaultOptions.begin(), defaultOptions.end());
}

std::vector<JPetOptions> JPetOptionsGenerator::generateOptions(const po::variables_map& optsMap) const
{

  auto options = variablesMapToOption(optsMap);
  auto cfgFileName = getConfigFileName(optsMap);
  if (!cfgFileName.empty()) {
    addNewOptionsFromCfgFile(cfgFileName, options);
  }

  options = transformOptions(options);

  if (!JPetOptionValidator::areCorrectOptions(options)) {
    throw std::invalid_argument("Wrong user options provided! Check the log!");
  }

  auto files = any_cast<std::vector<std::string>>(getOptionValue(options, "file_std::vector<std::string>"));
  std::vector<JPetOptions>  optionContainer;

  /// @todo change it to be properly initialized
  JPetOptionsTypeHandler optTypeHandler({"int", "std::string"});

  /// In case of scope there is one special input file
  /// which is a json config file which must be parsed.
  /// Based on its content the set of input directories are generated.
  /// The input directories contain data files.
  /// The config input file name also should be stored in a special option field.
  if (any_cast<std::string>(getOptionValue(options, "type_std::string")) == "scope") {
    assert(files.size() == 1); /// there should be only file which is config.
    auto configFileName = files.front();
    options["scopeConfigFile_std::string"] =  configFileName;
    JPetScopeConfigParser scopeConfigParser;
    /// The scope module must use a fake input file name which will be used to
    /// produce the correct output file names by the following modules.
    /// At the same time, the input directory with true input files must be
    /// also added. The container of pairs <directory, fileName> is generated
    /// based on the content of the configuration file.
    JPetScopeConfigParser::DirFileContainer dirsAndFiles = scopeConfigParser.getInputDirectoriesAndFakeInputFiles(configFileName);
    for (const auto & dirAndFile : dirsAndFiles) {
      options["scopeInputDirectory_std::string"] = dirAndFile.first;
      options["inputFile_std::string"] = dirAndFile.second;
      auto stringMap = optTypeHandler.anyMapToStringMap(options);
      addMissingDefaultOptions(stringMap);
      optionContainer.push_back(JPetOptions(stringMap));
    }
  } else {
    /// for every single input file we create separate JPetOptions
    for (const auto & file : files) {
      options["inputFile_std::string"] = file;
      auto stringMap = optTypeHandler.anyMapToStringMap(options);
      addMissingDefaultOptions(stringMap);
      optionContainer.push_back(JPetOptions(stringMap));
    }
  }
  return optionContainer;
}
