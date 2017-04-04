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

boost::any JPetOptionsGenerator::getOptionValue(const std::map<std::string, boost::any>& variablesMap, std::string option) const
{
  return any_cast<boost::any>(variablesMap.at(option));
}

std::map<std::string, boost::any> JPetOptionsGenerator::variablesMapToOption(const po::variables_map& variablesMap) const
{
  std::map<std::string, boost::any> optionsMap;
  for(auto &option : variablesMap){
    optionsMap.at(option.first) = variablesMap[option.first].as<boost::any>();
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

bool JPetOptionsGenerator::areCorrectOptions(const std::map<std::string, boost::any>& optionsMap) const
{
  for(auto &option : optionsMap){
    if( validationMap.at(option.first)(std::pair <std::string, boost::any> (option.first, option.second)) == false);
      ERROR("ERROR VALIDATON FOR " + option.first);
      return false;
  }
  return true;
}

std::map<std::string, boost::any> JPetOptionsGenerator::transformOptions(std::map<std::string, boost::any>& optionsMap)
{
  for(auto &option : optionsMap){
    for(auto &validFunct : transformationMap.at(option.first)){
        auto transformed = validFunct(option.second);
        optionsMap[transformed.first] = transformed.second;
    }
  }
  return optionsMap;
}
  /* Parse range of events */
bool JPetOptionsGenerator::isNumberBoundsInRangeValid(std::pair <std::string, boost::any> option){
  if( any_cast<std::vector<int>>(option.second).size()!=2){
    ERROR("Wrong number of bounds in range.");
    std::cerr << "Wrong number of bounds in range: " << (any_cast<std::vector<int>>(option.second).size()) << std::endl;
    return false;
  }
  return true;
}

bool JPetOptionsGenerator::isRangeOfEventsValid(std::pair <std::string, boost::any> option){
  if( any_cast<std::vector<int>>(option.second).at(0) > any_cast<std::vector<int>>(option.second).at(1)){
    ERROR("Wrong number of bounds in range.");
    std::cerr << "Wrong number of bounds in range: " << (any_cast<std::vector<int>>(option.second).size()) << std::endl;
    return false;
  }
  return true;
}

bool JPetOptionsGenerator::isCorrectFileType(std::pair <std::string, boost::any> option){
  std::string type = any_cast<std::string>(option.second);
  if (type == "hld" || type == "root" || type == "scope" || type == "zip") {
      return true;
  } else {
    ERROR("Wrong type of file.");
    std::cerr << "Possible options: hld, zip, root or scope" << std::endl;
    return false;
  }
}

bool JPetOptionsGenerator::isRunIdValid(std::pair <std::string, boost::any> option){
  if( any_cast<int>(option.second) <=0){
    ERROR("Run id must be a number larger than 0.");
    return false;
  }
  return true;
}

bool JPetOptionsGenerator::isLocalDBValid(std::pair <std::string, boost::any> option){
  if( !JPetCommonTools::ifFileExisting(any_cast<std::string>(option.second)) ){
    ERROR("File doed not exist.");
    return false;
  }
  return true;
}

bool JPetOptionsGenerator::areFilesValid(std::pair <std::string, boost::any> option){
  std::vector<std::string> fileNames= any_cast<std::vector<std::string>>(option.second);
  for ( unsigned int i = 0; i < fileNames.size(); i++ ){
    if( !JPetCommonTools::ifFileExisting(fileNames[i])){
      ERROR("File : " + fileNames[i] + " does not exist.");
      return false;
    }
  }
  return true;
}

bool JPetOptionsGenerator::isOutputDirectoryValid(std::pair <std::string, boost::any> option){
    if(!JPetCommonTools::isDirectory(any_cast<std::string>(option.second))){
      ERROR("Output directory does not exist.");
      return false;
    }
  return true;
}


/*
======?????????
  /// The run number option is neclegted if the input file is set as "scope"
  if (isOptionSet(variablesMap, "runId")) {
    if (getOptionValue(variablesMap, "type") == "scope") {
      WARNING("Run number was specified but the input file type is a scope!\n The run number will be ignored!");
    }
  }

======?????????

  */

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

  options = transformOptions(options);

  if (!areCorrectOptions(options)) {
    throw std::invalid_argument("Wrong user options provided! Check the log!");
  }

  auto fileType = getOptionValue(options, "type");
//  if (isCorrectFileType(fileType)) {
//    options["inputFileType"] = fileType;
//  }
//  if (isOptionSet(options, "outputPath")) {
//    options["outputPath"] = JPetCommonTools::appendSlashToPathIfAbsent(getOptionValue(options, "outputPath"));
//  }
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
