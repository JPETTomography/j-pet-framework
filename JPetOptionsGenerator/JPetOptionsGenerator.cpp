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
#include <cassert>

#include "JPetOptionsGenerator.h"
#include "../JPetCommonTools/JPetCommonTools.h"
#include "../JPetLoggerInclude.h"
#include "../JPetScopeConfigParser/JPetScopeConfigParser.h"
#include "../JPetOptionsGenerator/JPetOptionsTypeHandler.h"
#include "../JPetOptionValidator/JPetOptionValidator.h"
#include "./JPetAdditionalTransformations.h"

using boost::any_cast;
using namespace std;
using namespace jpet_options_tools;

std::map<std::string, boost::any> JPetOptionsGenerator::kDefaultOptions = {
  {"inputFile_std::string", std::string("")},
  {"inputFileType_std::string", std::string("")},
  {"scopeConfigFile_std::string", std::string("")},
  {"scopeInputDirectory_std::string", std::string("")},
  {"outputPath_std::string", std::string("")},
  {"outputFile_std::string", std::string("test.root")},
  {"outputFileType_std::string", std::string("root")},
  {"firstEvent_int", -1},
  {"lastEvent_int", -1},
  {"progressBar_bool", false},
  {"runId_int", -1},
  {"unpackerConfigFile_std::string", std::string("conf_trb3.xml")},
  {"unpackerCalibFile_std::string", std::string("")}
};

std::map<std::string, std::string> JPetOptionsGenerator::kOptCmdLineNameToExtendedName = {
  {"type", "type_std::string"},
  {"file", "file_std::vector<std::string>"},
  {"outputPath", "outputPath_std::string"},
  {"range", "range_std::vector<int>"},
  {"unpackerConfigFile", "unpackerConfigFile_std::string"},
  {"unpackerCalibFile", "unpackerCalibFile_std::string"},
  {"runId", "runId_int"},
  {"progressBar", "progressBar_bool"},
  {"localDB", "localDB_std::string"},
  {"localDBCreate", "localDBCreate_std::string"},
  {"userCfg", "userCfg_std::string"}
};

JPetOptionsGenerator::JPetOptionsGenerator()
{
}

/// Function returns a map of Options
/// based on the number of registered tasks and provided options.
/// The elements of the map are pairs filename -> OptionsForAllTasks
/// , where OptionsForAllTasks is a container with elements correspondig to the
/// options assigned for given task.
/// e.g. if there are 4 files and for each file there are 3 tasks, then the map
/// should have 4 containers with 3 option elements each.
/// In this version it is assumed that for every file the same number of tasks are
/// provided defined by nbOfRegisteredTasks arguments.
JPetOptionsGenerator::OptsForFiles JPetOptionsGenerator::generateOptionsForTasks(const OptsStrAny& inOptions,  int nbOfRegisteredTasks)
{
  using namespace jpet_options_tools;
  OptsForFiles  optsForAllFiles;

  if (nbOfRegisteredTasks <= 0) {
    ERROR("nbOfRegisteredTasks <= 0");
    return optsForAllFiles;
  }

  auto options(inOptions);
  ///Generate general set of options
  auto files = getInputFiles(options);

  ///Now generate set of options for every file
  std::map<std::string, OptsStrAny> optionsPerFile;

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
    for (const auto& dirAndFile : dirsAndFiles) {
      options["scopeInputDirectory_std::string"] = dirAndFile.first;
      options["inputFile_std::string"] = dirAndFile.second;
      optionsPerFile[dirAndFile.second] = options;
    }
  } else {
    for (const auto& file : files) {
      options["inputFile_std::string"] = file;
      optionsPerFile[file] = options;
    }
  }
  assert(nbOfRegisteredTasks > 0);

  /// Finally, multiple the options for every task.
  for (const auto& el : optionsPerFile) {
    std::vector<OptsStrAny>  currOpts(nbOfRegisteredTasks, el.second);
    optsForAllFiles[el.first] = setCorrectRangeAndOutputForNonFirstOption(currOpts);
  }
  return optsForAllFiles;
}

/// Function returns a map of Options
/// based on the number of registered tasks and provided command line arguments.
/// The elements of the map are pairs filename -> OptionsForAllTasks
/// , where OptionsForAllTasks is a container with elements correspondig to the
/// options assigned for given task.
/// e.g. if there are 4 files and for each file there are 3 tasks, then the map
/// should have 4 containers with 3 option elements each.
/// In this version it is assumed that for every file the same number of tasks are
/// provided defined by nbOfRegisteredTasks arguments.
JPetOptionsGenerator::OptsForFiles JPetOptionsGenerator::generateOptions(const po::variables_map& cmdLineArgs, int nbOfRegisteredTasks)
{
  using namespace jpet_options_tools;
  OptsForFiles  optsForAllFiles;

  if (cmdLineArgs.empty()) {
    ERROR("cmdLineArgs is empty");
    return optsForAllFiles;
  }
  if (nbOfRegisteredTasks <= 0) {
    ERROR("nbOfRegisteredTasks <= 0");
    return optsForAllFiles;
  }

  ///Generate general set of options
  auto options = JPetOptionsGenerator::generateAndValidateOptions(cmdLineArgs);
  auto files = getInputFiles(options);

  ///Now generate set of options for every file
  std::map<std::string, OptsStrAny> optionsPerFile;

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
    for (const auto& dirAndFile : dirsAndFiles) {
      options["scopeInputDirectory_std::string"] = dirAndFile.first;
      options["inputFile_std::string"] = dirAndFile.second;
      optionsPerFile[dirAndFile.second] = options;
    }
  } else {
    for (const auto& file : files) {
      options["inputFile_std::string"] = file;
      optionsPerFile[file] = options;
    }
  }
  assert(nbOfRegisteredTasks > 0);

  /// Finally, multiple the options for every task.
  for (const auto& el : optionsPerFile) {
    std::vector<OptsStrAny>  currOpts(nbOfRegisteredTasks, el.second);
    optsForAllFiles[el.first] = setCorrectRangeAndOutputForNonFirstOption(currOpts);
  }
  return optsForAllFiles;
}

JPetOptionsGenerator::OptsStrAny JPetOptionsGenerator::generateAndValidateOptions(const po::variables_map& cmdLineArgs)
{
  JPetOptionValidator validator;
  OptsStrAny options;
  if (cmdLineArgs.empty()) {
    ERROR("cmdLineArgs are empty");
    return options;
  }
  options = addTypeSuffixes(transformToStrAnyMap(cmdLineArgs));
  auto cfgFileName = getConfigFileName(options);
  if (!cfgFileName.empty()) {
    addNewOptionsFromCfgFile(cfgFileName, options);
  }
  createMapOfBoolOptionFromUser(options);

  options = addMissingDefaultOptions(options);

  auto transformationMap = generateTransformationMap(options);
  options = transformOptions(transformationMap, options);

  if (!validator.areCorrectOptions(options, fVectorOfOptionFromUser)) {
    throw std::invalid_argument("Wrong user options provided! Check the log!");
  }
  return options;
}

std::vector<std::string> JPetOptionsGenerator::getVectorOfOptionFromUser() const
{
  return fVectorOfOptionFromUser;
}


std::map<std::string, boost::any> JPetOptionsGenerator::transformToStrAnyMap(const po::variables_map& inMap)
{
  std::map<std::string, boost::any> outMap;
  for (auto& option : inMap) {
    outMap[option.first] = option.second.value();
  }
  return outMap;
}

JPetOptionsGenerator::OptsStrAny JPetOptionsGenerator::addTypeSuffixes(const std::map<std::string, boost::any>& oldMap)
{
  std::map<std::string, boost::any> newMap(oldMap);

  for (auto& elem : kOptCmdLineNameToExtendedName) {
    auto oldKey = elem.first;
    auto newKey = elem.second;
    const auto it = newMap.find(oldKey);
    if (it != newMap.end()) {
      newMap[newKey] = it->second;
      newMap.erase(it);
    }
  }
  return newMap;
}

std::map<std::string, std::vector<Transformer> > JPetOptionsGenerator::generateTransformationMap(OptsStrAny& options)
{
  std::map<std::string, std::vector<Transformer> > transformationMap;
  /// The keys used here corresponds to the keys defined in the CmdArgMap !!!
  transformationMap["outputPath_std::string"].push_back(appendSlash);
  transformationMap["range_std::vector<int>"].push_back(generateLowerEventBound);
  transformationMap["range_std::vector<int>"].push_back(generateHigherEventBound);
  addTransformFunction(transformationMap, "type_std::string", jpet_options_tools::generateSetFileTypeTransformator(options));
  return transformationMap;
}

void JPetOptionsGenerator::addTransformFunction(TransformersMap& map,  const std::string& name, Transformer transformFunction)
{
  map[name].push_back(transformFunction);
}

void JPetOptionsGenerator::createMapOfBoolOptionFromUser(const std::map<std::string, boost::any>& optionsMap)
{
  for ( auto& opt : optionsMap) {
    fVectorOfOptionFromUser.push_back(opt.first);
  }
}

std::map<std::string, boost::any> JPetOptionsGenerator::transformOptions(const TransformersMap& transformationMap, const std::map<std::string, boost::any>& oldOptionsMap)
{
  std::cout << "inTransform options" << std::endl;
  std::map<std::string, boost::any> newOptionsMap(oldOptionsMap);

  for (auto& transformGroup : transformationMap) {
    auto key = transformGroup.first;
    if (newOptionsMap.find(key) != newOptionsMap.end()) {
      for (auto& transformFunc : transformGroup.second) {
        auto newOpt = transformFunc(newOptionsMap.at(key));
        newOptionsMap[newOpt.first] = newOpt.second;
      }
    }
  }
  return newOptionsMap;
}

/// We add additional options to already existing one.
/// If the key already exists the element will not be updated.
void JPetOptionsGenerator::addNewOptionsFromCfgFile(const std::string& cfgFile, std::map<std::string, boost::any>& options) const
{
  std::map<std::string, boost::any> optionsFromJson = jpet_options_tools::createOptionsFromConfigFile(cfgFile);
  options.insert(optionsFromJson.begin(), optionsFromJson.end());
}

std::map<std::string, boost::any>  JPetOptionsGenerator::addMissingDefaultOptions(const std::map<std::string, boost::any>& oldOptions)
{
  std::map<std::string, boost::any> newOptions(oldOptions);
  auto defaultOptions = JPetOptionsGenerator::getDefaultOptions();
  newOptions.insert(defaultOptions.begin(), defaultOptions.end());
  return newOptions;
}

std::map<std::string, boost::any> JPetOptionsGenerator::getDefaultOptions()
{
  return kDefaultOptions;
}
