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
#include <vector>
#include <string>

using boost::any_cast;
using namespace std;

JPetOptionsGenerator::JPetOptionsGenerator()
{

}
JPetOptionsGenerator::~JPetOptionsGenerator()
{

}
bool JPetOptionsGenerator::isOptionSet(const std::map<std::string, boost::any>& optionsMap, const std::string& option) const
{
  return (bool)optionsMap.count(option);
}

boost::any JPetOptionsGenerator::getOptionValue(const std::map<std::string, boost::any>& optionsMap, std::string option) const
{
  //return any_cast<boost::any>(optionsMap.at(option));
  return optionsMap.at(option);
}

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
  //std::string type = option.second;
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
std::pair <std::string, boost::any>JPetOptionsGenerator::appendSlash(boost::any option)
{
  auto path = JPetCommonTools::appendSlashToPathIfAbsent(any_cast<std::string>(option));
  return std::make_pair("outputPath_std::string", path);
}

std::pair <std::string, boost::any>JPetOptionsGenerator::getLowerEventBound(boost::any option)
{
  int firstEvent = any_cast<std::vector<int>>(option)[0];
  if (firstEvent >= 0)
  {
    return std::make_pair("firstEvent_int", firstEvent);
  } 
}

std::pair <std::string, boost::any>JPetOptionsGenerator::getHigherEventBound(boost::any option)
{
  int lastEvent = any_cast<std::vector<int>>(option)[1];
  if (lastEvent >= 0)
  {
    return std::make_pair("lastEvent_int", lastEvent);
  }
}

std::pair <std::string, boost::any>JPetOptionsGenerator::setInputFileType(boost::any option)
{
  auto inputFileType = any_cast<std::string>(option);
  return std::make_pair("inputFileType_std::string", inputFileType);
}

// std::pair <std::string, boost::any>JPetOptionsGenerator::setProgressBar(boost::any option)
// {
//   std::cout<<"Czy setProgressBar? "<<std::endl;
//   bool progressBar = any_cast<bool>(option);
//   if(progressBar == true){
//     std::cout<<"progressBar: "<< progressBar <<std::endl;
//     return std::make_pair("progressBar_bool", true);
//   }
//   else{
//     std::cout<<"progressBar: "<< progressBar <<std::endl;
//     return std::make_pair("progressBar_bool", false);
//   }
// }

std::string JPetOptionsGenerator::getTypeOfOption(const std::string nameOfOption) const
{
	std::size_t pos = nameOfOption.find("_");
    if(pos == string::npos){
    return "default";
  }
  //std::cout<<"Gettype "<<nameOfOption.substr(pos+1)<<std::endl;
	return nameOfOption.substr(pos+1);
}

std::string JPetOptionsGenerator::getNameOfOption(const std::string option) const
{
  std::size_t pos= option.find("_");
  //std::cout<<"GetName "<<option.substr(0, pos)<<std::endl;
  return option.substr(0, pos);
}

std::map<std::string, boost::any> JPetOptionsGenerator::variablesMapToOption(const po::variables_map& variablesMap) const
{
  std::map<std::string, boost::any> optionsMap;
  std::map<std::string, optionTypes> typesToSwitch = {{"int", Int},{"std::string", String},{"bool", Bool},{"std::vector<std::string>", VectorString},{"std::vector<int>", VectorInt}};
  for(auto &option : variablesMap){
  	//int typeOfOption;
  	//if (typesToSwitch.count(getTypeOfOption(option.first))>0)
  	int typeOfOption = typesToSwitch.at(getTypeOfOption(option.first));
    //else
    //  typeOfOption = 100;
  	switch(typeOfOption)
  	{
  		case Int:
  			// optionsMap[getNameOfOption(option.first)] = variablesMap[option.first].as<int>();
        optionsMap[option.first] = variablesMap[option.first].as<int>();
  			break;
  		case String:
  			optionsMap[option.first] = variablesMap[option.first].as<std::string>();
  			break;
  		case Bool:
  			optionsMap[option.first] = variablesMap[option.first].as<bool>();
  			break;
  		case VectorString:
  			optionsMap[option.first] = variablesMap[option.first].as<std::vector<std::string>>();
  			break;
  		case VectorInt:
  			optionsMap[option.first] = variablesMap[option.first].as<std::vector<int>>();
  			break;
  		// default:
  		// 	optionsMap[getNameOfOption(option.first)] = variablesMap[option.first].as<boost::any>();
  		// 	break;
  	}
  }
 // std::cout<<"Czy tu jestem?? "<<std::endl;
  return optionsMap;
}

std::map<std::string, std::string> JPetOptionsGenerator::anyMapToStringMap(const std::map<std::string, boost::any> & optionsMap) const
{

  std::map<std::string, std::string> newOptionsMap;
  std::map<std::string, optionTypes> typesToSwitch = {{"int", Int},{"std::string", String},{"bool", Bool},{"std::vector<std::string>", VectorString},{"std::vector<int>", VectorInt}, {"default", Default}};
  for(auto &option : optionsMap){
    int typeOfOption = typesToSwitch.at(getTypeOfOption(option.first));
    std::cout<< "Typ opcji: "<< getTypeOfOption(option.first)<<std::endl;
//    newOptionsMap[option.first] = std::to_string(option.second);
    switch(typeOfOption)
    {
      case Int:
        std::cout<< option.first <<std::endl;
        newOptionsMap[getNameOfOption(option.first)] = std::to_string(any_cast<int>(optionsMap.at(option.first)));
        std::cout<< newOptionsMap[getNameOfOption(option.first)] <<": anyMapToStringMap "<<std::endl;
        std::cout<<std::endl;
        break;
      case String:
        std::cout<< option.first <<std::endl;
        newOptionsMap[getNameOfOption(option.first)] = any_cast<std::string>(optionsMap.at(option.first));
        std::cout<< newOptionsMap[getNameOfOption(option.first)] <<": anyMapToStringMap "<<std::endl;
        std::cout<<std::endl;
        break;
      case Bool:
        std::cout<< option.first <<std::endl;
        if(any_cast<bool>(optionsMap.at(option.first)))
          newOptionsMap[getNameOfOption(option.first)] = "true";
        else
          newOptionsMap[getNameOfOption(option.first)] = "false";
        std::cout<< newOptionsMap[getNameOfOption(option.first)] <<": anyMapToStringMap "<<std::endl;
        std::cout<<std::endl;
        break;
      case Default:
        std::cout<< option.first <<std::endl;
        newOptionsMap[option.first] = any_cast<std::string>(optionsMap.at(option.first));
        std::cout<< newOptionsMap[option.first] <<": anyMapToStringMap "<<std::endl;
        std::cout<<std::endl;
        break;
      // case VectorString:
      //   newOptionsMap[getNameOfOption(option.first)] = std::to_string(any_cast<std::vector<std::string>>(optionsMap.at(option.first)));
      //   break;
      // case VectorInt:
      //   newOptionsMap[getNameOfOption(option.first)] = std::to_string(any_cast<std::vector<int>>(optionsMap.at(option.first)));
      //   break;
      // default:
      //  optionsMap[getNameOfOption(option.first)] = variablesMap[option.first].as<boost::any>();
      //  break;
    }
  }
  std::cout<<std::endl;
  return newOptionsMap;
}
std::map<std::string, std::vector<bool(*)(std::pair <std::string, boost::any>)> > JPetOptionsGenerator::generateValidationMap() const
{
  std::map<std::string, std::vector<bool(*)(std::pair <std::string, boost::any>)> > validationMap;
  validationMap["range_std::vector<int>"].push_back(&isNumberBoundsInRangeValid);
  validationMap["range_std::vector<int>"].push_back(&isRangeOfEventsValid);
  validationMap["type_std::string"].push_back(&isCorrectFileType);
  validationMap["file_std::vector<std::string>"].push_back(&areFilesValid);
  validationMap["runId_int"].push_back(&isRunIdValid);
  validationMap["localDB_std::string"].push_back(&isLocalDBValid);
  validationMap["outputPath_std::string"].push_back(&isOutputDirectoryValid);
  return validationMap;
}

std::map<std::string, std::vector<std::pair <std::string, boost::any>(*)(boost::any)> > JPetOptionsGenerator::generateTransformationMap() const
{
  std::map<std::string, std::vector<std::pair <std::string, boost::any>(*)(boost::any)> > transformationMap;
  transformationMap["outputPath_std::string"].push_back(&appendSlash);
  transformationMap["range_std::vector<int>"].push_back(&getLowerEventBound);
  transformationMap["range_std::vector<int>"].push_back(&getHigherEventBound);
  transformationMap["type_std::string"].push_back(&setInputFileType);
//  transformationMap["progressBar_bool"].push_back(&setProgressBar);
  return transformationMap;
}

bool JPetOptionsGenerator::areCorrectOptions(const std::map<std::string, boost::any>& optionsMap) const
{
  auto validationMap = generateValidationMap();
  for(auto &checkGroup : validationMap){
    //std::cout<<" 1.Czy tu jestem?? "<<option.first<<std::endl;
    if (optionsMap.count(checkGroup.first)>0){
      for(auto &checkFunc : checkGroup.second){
        std::cout<<"areCorrectOptions: "<<checkGroup.first<<std::endl;
        if(( !checkFunc(std::make_pair(checkGroup.first, optionsMap.at(checkGroup.first))) )){
          ERROR("ERROR VALIDATON FOR " + checkGroup.first);
          return false;
        }
      }
    }
  }
  std::cout<<std::endl;
  return true;
}

std::map<std::string, boost::any> JPetOptionsGenerator::transformOptions(std::map<std::string, boost::any>& optionsMap) const
{
  auto transformationMap = generateTransformationMap();
  for(auto &validGroup : transformationMap){
    if(optionsMap.count(validGroup.first)>0){
      for(auto &validFunct : validGroup.second){
        std::pair <std::string, boost::any> transformed = validFunct(optionsMap.at(validGroup.first));
        optionsMap[transformed.first] = transformed.second;
        //std::cout<<"Transformacja: "<<transformed.first <<std::endl;
      }
    }
  }
  return optionsMap;
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

  if (!areCorrectOptions(options)) {
    throw std::invalid_argument("Wrong user options provided! Check the log!");
  }
 
  std::cout<<std::endl;


  for(auto &option : options){
    std::cout<<"option: "<<option.first<<std::endl;
  }
  std::cout<<std::endl;
  auto files = any_cast<std::vector<std::string>>(getOptionValue(options, "file_std::vector<std::string>"));
  // for (auto a: files){
  //   std::cout<<" tu pliki:  "<< a <<std::endl;
  // }
  std::vector<JPetOptions>  optionContainer;
  /// In case of scope there is one special input file
  /// which is a json config file which must be parsed.
  /// Based on its content the set of input directories are generated.
  /// The input directories contain data files.
  /// The config input file name also should be stored in a special option field.
  if (any_cast<std::string>(getOptionValue(options, "type_std::string")) == "scope") {
  //if (options.at("type") == "scope") {
    assert(files.size() == 1); /// there should be only file which is config.
    auto configFileName = files.front();
    options["scopeConfigFile_std::string"] =  configFileName;
    //options["scopeConfigFile_std::string"] =  configFileName;
    JPetScopeConfigParser scopeConfigParser;
    /// The scope module must use a fake input file name which will be used to
    /// produce the correct output file names by the following modules.
    /// At the same time, the input directory with true input files must be
    /// also added. The container of pairs <directory, fileName> is generated
    /// based on the content of the configuration file.
    JPetScopeConfigParser::DirFileContainer dirsAndFiles = scopeConfigParser.getInputDirectoriesAndFakeInputFiles(configFileName);
    for (const auto & dirAndFile : dirsAndFiles) {
      options["scopeInputDirectory_std::string"] = dirAndFile.first;
      options["inputFile_std::string"]= dirAndFile.second;
      //stringMap["scopeInputDirectory"] = dirAndFile.first;
      //stringMap["inputFile"]= dirAndFile.second;
      std::cout<<"StringMap"<<std::endl;
      // for (auto a: stringMap){
      //   std::cout<<a.first<< " : " << a.second <<std::endl;
      // }
      // ;
      auto stringMap = anyMapToStringMap(options);
      addMissingDefaultOptions(stringMap);
      optionContainer.push_back(JPetOptions(stringMap));
    }
  } else {
    /// for every single input file we create separate JPetOptions
    for (const auto & file : files) {
      options["inputFile_std::string"] = file;
      //stringMap["inputFile"] = file;
      // std::cout<<"anyMapCheck:  " <<std::endl;
      // for (auto a: stringMap){
      //   std::cout<<a.first<< " : " << a.second <<std::endl;
      // }
      std::cout<<std::endl;
      auto stringMap = anyMapToStringMap(options);
      addMissingDefaultOptions(stringMap);
      optionContainer.push_back(JPetOptions(stringMap));
    }
  }
  return optionContainer;
}
