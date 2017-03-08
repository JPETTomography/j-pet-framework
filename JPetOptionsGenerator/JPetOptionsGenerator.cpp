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

#include "JPetOptionsGenerator.h"
#include <iostream>
#include "../JPetCommonTools/JPetCommonTools.h"
#include "../JPetLoggerInclude.h"
#include "../JPetOptions/JPetOptionsTools.h"
#include "../JPetScopeConfigParser/JPetScopeConfigParser.h"
#include <stdexcept>

using boost::any_cast;

JPetOptionsGenerator::JPetOptionsGenerator()
{

}
JPetOptionsGenerator::~JPetOptionsGenerator()
{

}
bool JPetOptionsGenerator::isOptionSet(const std::map<std::string, boost::any>& variablesMap, const std::string& option) const
{
  return (bool)variablesMap.count(option);
}

std::string JPetOptionsGenerator::getOptionValue(const std::map<std::string, boost::any>& variablesMap, std::string option) const
{
  return any_cast<std::string>(variablesMap.at(option));
}

std::map<std::string, boost::any> JPetOptionsGenerator::variablesMapToOption(const po::variables_map& variablesMap) const
{
  std::map<std::string, boost::any> optionsMap;
  std::map<std::string, std::string> tmpMap = JPetOptions::getDefaultOptions();
  for(auto &option : variablesMap){
    //if(variablesMap.count(option.first)){
      if(option.first=="file")
        optionsMap.at(option.first)= variablesMap[option.first].as<std::vector<std::string>>();
      if(option.first=="range")
        optionsMap.at(option.first)=variablesMap[option.first].as<std::vector<int>>();
      if(option.first=="runId")
        optionsMap.at(option.first)=variablesMap[option.first].as<int>();  
    optionsMap.at(option.first) = variablesMap[option.first].as<std::string>();
   // }
  }
  return optionsMap;
}

std::map<std::string, std::string> JPetOptionsGenerator::anyMapToStringMap(const std::map<std::string, boost::any> & map) const
{
  std::map<std::string, std::string> optionsMap;
  for(auto &option : optionsMap){
    optionsMap.at(option.first) = any_cast<std::string>(map.at(option.first));
  }
  return optionsMap;
}

bool JPetOptionsGenerator::areCorrectOptions(const std::map<std::string, boost::any>& variablesMap) const
{
  /* Parse range of events */
  if (variablesMap.count("range")) {
    if ((any_cast<std::vector<int>>(variablesMap.at("range"))).size() != 2) {
      ERROR("Wrong number of bounds in range.");
      std::cerr << "Wrong number of bounds in range: " << (any_cast<std::vector<int>>(variablesMap.at("range"))).size() << std::endl;
      return false;
    }
    if (
      (any_cast<std::vector<int>>(variablesMap.at("range"))).at(0)
      >  (any_cast<std::vector<int>>(variablesMap.at("range"))).at(1)) {
      ERROR("Wrong range of events.");
      std::cerr << "Wrong range of events." << std::endl;
      return false;
    }
  }

  if (!isCorrectFileType(getOptionValue(variablesMap, "type"))) {
    ERROR("Wrong type of file.");
    std::cerr << "Wrong type of file: " << getOptionValue(variablesMap, "type") << std::endl;
    std::cerr << "Possible options: hld, zip, root or scope" << std::endl;
    return false;
  }

  if (isOptionSet(variablesMap, "runId")) {
    int l_runId = any_cast<int>(variablesMap.at("runId"));

    if (l_runId <= 0) {
      ERROR("Run id must be a number larger than 0.");
      std::cerr << "Run id must be a number larger than 0." << l_runId << std::endl;
      return false;
    }
  }

  if (isOptionSet(variablesMap, "localDB")) {
    std::string localDBName = getOptionValue(variablesMap, "localDB");
    if ( !JPetCommonTools::ifFileExisting(localDBName) ) {
      ERROR("File : " + localDBName + " does not exist.");
      std::cerr << "File : " << localDBName << " does not exist" << std::endl;
      return false;
    }
  }

  std::vector<std::string> fileNames= any_cast<std::vector<std::string>>(variablesMap.at("file"));
  for (unsigned int i = 0; i < fileNames.size(); i++) {
    if ( ! JPetCommonTools::ifFileExisting(fileNames[i]) ) {
      std::string fileName = fileNames[i];
      ERROR("File : " + fileName + " does not exist.");
      std::cerr << "File : " << fileNames[i] << " does not exist" << std::endl;
      return false;
    }
  }


  /// The run number option is neclegted if the input file is set as "scope"
  if (isOptionSet(variablesMap, "runId")) {
    if (getOptionValue(variablesMap, "type") == "scope") {
      WARNING("Run number was specified but the input file type is a scope!\n The run number will be ignored!");
    }
  }

  /// Check if output path exists
  if (isOptionSet(variablesMap, "outputPath")) {
    auto dir = getOptionValue(variablesMap, "outputPath");
    if (!JPetCommonTools::isDirectory(dir)) {
      ERROR("Output directory : " + dir + " does not exist.");
      std::cerr << "Output directory: " << dir << " does not exist" << std::endl;
      return false;
    }
  }
  return true;
}

std::vector<JPetOptions> JPetOptionsGenerator::generateOptions(const po::variables_map& optsMap) const
{
  jpet_options_tools::Options optionsFromJson;
  /// If json config file with user options was specified we must add the options from it.
  if (optsMap.count("userCfg")) {
    auto jsonCfgFile = optsMap["userCfg"].as<std::string>();
    optionsFromJson = jpet_options_tools::createOptionsFromConfigFile(jsonCfgFile);
  }
  std::map<std::string, boost::any> options = variablesMapToOption(optsMap);
  std::map<std::string, std::string> defaultOptions = JPetOptions::getDefaultOptions(); 
  /// We add additional options to already existing one.
  /// If the key already exists the element will not be updated.
  options.insert(optionsFromJson.begin(), optionsFromJson.end());
  options.insert(defaultOptions.begin(), defaultOptions.end());

  auto fileType = getOptionValue(options, "type");
//  if (isCorrectFileType(fileType)) {
//    options["inputFileType"] = fileType;
//  }
  if (isOptionSet(options, "outputPath")) {
    options["outputPath"] = JPetCommonTools::appendSlashToPathIfAbsent(getOptionValue(options, "outputPath"));
  }
//  if (isOptionSet(optionsFromCmd, "progressBar")) {
//    options["progressBar"] = "true";
//  }
//  if (isOptionSet(optionsFromCmd, "localDB")) {
//    options["localDB"] = getOptionValue(optionsFromCmd, "localDB");
//  }
//  if (isOptionSet(optionsFromCmd, "localDBCreate")) {
//    options["localDBCreate"] = getOptionValue(optionsFromCmd, "localDBCreate");
//  }
  auto firstEvent  = getLowerEventBound(optsMap);
  auto lastEvent  = getHigherEventBound(optsMap);
  if (firstEvent >= 0) options["firstEvent"] = std::to_string(firstEvent);
  if (lastEvent >= 0) options["lastEvent"] = std::to_string(lastEvent);
  auto files = getFileNames(optsMap);

  if (!areCorrectOptions(options)) {
    throw std::invalid_argument("Wrong user options provided! Check the log!");
  }


  std::vector<JPetOptions>  optionContainer;
  /// In case of scope there is one special input file
  /// which is a json config file which must be parsed.
  /// Based on its content the set of input directories are generated.
  /// The input directories contain data files.
  /// The config input file name also should be stored in a special option field.
  if (fileType == "scope") {
    assert(files.size() == 1); /// there should be only file which is config.
    auto configFileName = files.front();
    options.at("scopeConfigFile") =  configFileName;
    JPetScopeConfigParser scopeConfigParser;
    /// The scope module must use a fake input file name which will be used to
    /// produce the correct output file names by the following modules.
    /// At the same time, the input directory with true input files must be
    /// also added. The container of pairs <directory, fileName> is generated
    /// based on the content of the configuration file.
    JPetScopeConfigParser::DirFileContainer dirsAndFiles = scopeConfigParser.getInputDirectoriesAndFakeInputFiles(configFileName);
    for (const auto & dirAndFile : dirsAndFiles) {
      options.at("scopeInputDirectory") = dirAndFile.first;
      options.at("inputFile")= dirAndFile.second;
      optionContainer.push_back(JPetOptions(anyMapToStringMap(options)));
    }
  } else {
    /// for every single input file we create separate JPetOptions
    for (const auto & file : files) {
      options.at("inputFile") = file;
      optionContainer.push_back(JPetOptions(anyMapToStringMap(options)));
    }
  }
  return optionContainer;
}
