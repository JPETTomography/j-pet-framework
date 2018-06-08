/**
 *  @copyright Copyright 2017 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetOptionsTools.cpp
 */

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "./JPetOptionsTools.h"
#include "./JPetCommonTools/JPetCommonTools.h"
#include "./JPetLoggerInclude.h"
#include "./JPetOptionsGenerator/JPetOptionsTypeHandler.h"
#include <typeinfo>

namespace pt = boost::property_tree;
using boost::any_cast;

namespace jpet_options_tools
{

std::map<std::string, FileTypeChecker::FileType> FileTypeChecker::fStringToFileType = {
  {"", kNoType},
  {"root", kRoot},
  {"mcGeant", kMCGeant},
  {"scope", kScope},
  {"hld", kHld},
  {"hldRoot", kHldRoot},
  {"zip", kZip}
};

bool isOptionSet(const OptsStrAny& opts, const std::string& optionName)
{
  return static_cast<bool>(opts.count(optionName));
}

boost::any getOptionValue(const OptsStrAny& opts, std::string optionName)
{
  return opts.at(optionName);
}

std::string getOptionAsString(const OptsStrAny& opts, std::string optionName)
{
  try {
    return any_cast<std::string>(getOptionValue(opts, optionName));
  } catch (const std::exception& excep) {
    ERROR("Bad option type:" + std::string(excep.what()));
    return "";
  }
}

int getOptionAsInt(const OptsStrAny& opts, std::string optionName)
{
  try {
    return any_cast<int>(getOptionValue(opts, optionName));
  } catch (const std::exception& excep) {
    ERROR("Bad option type:" + std::string(excep.what()));
    return -1;
  }
}

float getOptionAsFloat(const OptsStrAny& opts, std::string optionName)
{
  try {
    return any_cast<float>(getOptionValue(opts, optionName));
  } catch (const std::exception& excep) {
    ERROR("Bad option type:" + std::string(excep.what()));
    return -1.;
  }
}

double getOptionAsDouble(const OptsStrAny& opts, std::string optionName)
{
  try {
    return any_cast<double>(getOptionValue(opts, optionName));
  } catch (const std::exception& excep) {
    ERROR("Bad option type:" + std::string(excep.what()));
    return -1.;
  }
}

std::vector<std::string> getOptionAsVectorOfStrings(const OptsStrAny& opts, std::string optionName)
{
  try {
    return any_cast<std::vector<std::string>>(getOptionValue(opts, optionName));
  } catch (const std::exception& excep) {
    std::vector<std::string> emptyV;
    ERROR("Bad option type:" + std::string(excep.what()));
    return emptyV;
  }
}

bool getOptionAsBool(const OptsStrAny& opts, std::string optionName)
{
  try {
    return any_cast<bool>(getOptionValue(opts, optionName));
  } catch (const std::exception& excep) {
    ERROR("Bad option type:" + std::string(excep.what()));
    return false;
  }
}



std::vector<std::string> getInputFiles(const std::map<std::string, boost::any>& opts)
{
  std::vector<std::string> dummy;
  if (!isOptionSet(opts, "file_std::vector<std::string>")) {
    ERROR("key:file_std::vector<std::string> not found in options");
    return dummy;
  }
  return any_cast<std::vector<std::string>>(opts.at("file_std::vector<std::string>"));
}

std::string getInputFile(const std::map<std::string, boost::any>& opts)
{
  return any_cast<std::string>(opts.at("inputFile_std::string"));
}

std::string getScopeConfigFile(const std::map<std::string, boost::any>& opts)
{
  return any_cast<std::string>(opts.at("scopeConfigFile_std::string"));
}

std::string getScopeInputDirectory(const std::map<std::string, boost::any>& opts)
{
  return any_cast<std::string>(opts.at("scopeInputDirectory_std::string"));
}

std::string getOutputFile(const std::map<std::string, boost::any>& opts)
{
  return any_cast<std::string>(opts.at("outputFile_std::string"));
}

std::string getOutputPath(const std::map<std::string, boost::any>& opts)
{
  return any_cast<std::string>(opts.at("outputPath_std::string"));
}

long long getFirstEvent(const std::map<std::string, boost::any>& opts)
{
  return any_cast<int>(opts.at("firstEvent_int"));
}

long long getLastEvent(const std::map<std::string, boost::any>& opts)
{
  return any_cast<int>(opts.at("lastEvent_int"));
}

long long getTotalEvents(const std::map<std::string, boost::any>& opts)
{
  long long first = getFirstEvent(opts);
  long long last = getLastEvent(opts);
  long long diff = -1;
  if ((first >= 0) && (last >= 0) && ((last - first) >= 0)) {
    diff = last - first + 1;
  }
  return diff;
}

int getRunNumber(const std::map<std::string, boost::any>& opts)
{
  return any_cast<int>(opts.at("runId_int"));
}

bool isProgressBar(const std::map<std::string, boost::any>& opts)
{
  return any_cast<bool>(opts.at("progressBar_bool"));
}

bool isLocalDB(const std::map<std::string, boost::any>& opts)
{
  return (bool)opts.count("localDB_std::string");
}

std::string getLocalDB(const std::map<std::string, boost::any>& opts)
{
  std::string result("");
  if (isLocalDB(opts)) {
    result = any_cast<std::string>(opts.at("localDB_std::string"));
  }
  return result;
}
bool isLocalDBCreate(const std::map<std::string, boost::any>& opts)
{
  return (bool)opts.count("localDBCreate_std::string");
}

std::string getLocalDBCreate(const std::map<std::string, boost::any>& opts)
{
  std::string result("");
  if (isLocalDBCreate(opts)) {
    result = any_cast<std::string>(opts.at("localDBCreate_std::string"));
  }
  return result;
}

std::string getUnpackerConfigFile(const std::map<std::string, boost::any>& opts)
{
  return any_cast<std::string>(opts.at("unpackerConfigFile_std::string"));
}

std::string getUnpackerCalibFile(const std::map<std::string, boost::any>& opts)
{
  return any_cast<std::string>(opts.at("unpackerCalibFile_std::string"));
}

std::string getConfigFileName(const std::map<std::string, boost::any>& optsMap)
{
  if (optsMap.count("userCfg_std::string")) {
    return any_cast<std::string>(optsMap.at("userCfg_std::string"));
  } else {
    return "";
  }
}

void printOptions(const OptsStrAny& opts)
{
  std::cout << "Current options:" << std::endl;
  auto stringOptions = JPetOptionsTypeHandler::anyMapToStringMap(opts);
  for (const auto& el : stringOptions) {
    std::cout << el.first + "=" + el.second << std::endl;
  }
}

void printOptionsToLog(const OptsStrAny& opts, const std::string& firstLine)
{
  if (!firstLine.empty()) {
    INFO(firstLine.c_str());
  }
  INFO("Current options:");
  auto stringOptions = JPetOptionsTypeHandler::anyMapToStringMap(opts);
  for (const auto& el : stringOptions) {
    INFO(el.first + "=" + el.second);
  }
}

bool createConfigFileFromOptions(const OptsStrStr& options, const std::string& outFile)
{
  pt::ptree optionsTree;
  for (auto& entry : options)
    optionsTree.put(entry.first, entry.second);
  try {
    pt::write_json(outFile, optionsTree);
  } catch (pt::json_parser_error) {
    ERROR("ERROR IN WRITING OPTIONS TO JSON FILE");
    return false;
  }
  return true;
}

std::map<std::string, boost::any> createOptionsFromConfigFile(const std::string& filename)
{
  pt::ptree optionsTree;
  std::map<std::string, boost::any> mapOptions, emptyMap;
  if (JPetCommonTools::ifFileExisting(filename)) {
    try {
      pt::read_json(filename, optionsTree);
      for (auto& item : optionsTree) {
        auto key = item.first;
        std::string typeOfOption = JPetOptionsTypeHandler::getTypeOfOption(key);
        auto allowedTypes = JPetOptionsTypeHandler::getAllowedTypes();
        if (std::find(allowedTypes.begin(), allowedTypes.end(), typeOfOption) != allowedTypes.end()) {
          if (typeOfOption == "int") {
            auto value = item.second.get_value<int>();
            mapOptions.insert(std::make_pair(key, value));
          } else if (typeOfOption == "std::string") {
            auto value = item.second.get_value<std::string>();
            mapOptions.insert(std::make_pair(key, value));
          } else if (typeOfOption == "float") {
            auto value = item.second.get_value<float>();
            mapOptions.insert(std::make_pair(key, value));
          } else if (typeOfOption == "double") {
            auto value = item.second.get_value<double>();
            mapOptions.insert(std::make_pair(key, value));
          } else if (typeOfOption == "bool") {
            auto value = item.second.get_value<bool>();
            mapOptions.insert(std::make_pair(key, value));
          } else if (typeOfOption == "std::vector<std::string>") {
            std::vector<std::string> values;
            for (pt::ptree::value_type& value : optionsTree.get_child(key)) {
              values.push_back(value.second.get_value<std::string>());
            }
            mapOptions.insert(std::make_pair(key, values));
          } else if (typeOfOption == "std::vector<int>") {
            std::vector<int> values;
            for (pt::ptree::value_type& value : optionsTree.get_child(key)) {
              values.push_back(value.second.get_value<int>());
            }
            mapOptions.insert(std::make_pair(key, values));
          }
        }
      }
    } catch (pt::json_parser_error) {
      ERROR("ERROR IN READINIG OPTIONS FROM JSON FILE! FILENAME:" + filename );
      return emptyMap;
    }
  } else {
    ERROR("JSON CONFIG FILE DOES NOT EXIST! FILENAME:" + filename);
  }
  return mapOptions;
}

FileTypeChecker::FileType FileTypeChecker::getInputFileType(const std::map<std::string, boost::any>& opts)
{
  return getFileType(opts, "inputFileType_std::string");
}

FileTypeChecker::FileType FileTypeChecker::getOutputFileType(const std::map<std::string, boost::any>& opts)
{
  return getFileType(opts, "outputFileType_std::string");
}

void FileTypeChecker::handleErrorMessage(const std::string& errorMessage, const std::out_of_range& outOfRangeException)
{
  std::cerr << errorMessage << outOfRangeException.what() << '\n';
  ERROR(errorMessage);
}

FileTypeChecker::FileType FileTypeChecker::getFileType(const std::map<std::string, boost::any>& opts, const std::string& fileTypeName)
{
  try {
    auto option = any_cast<std::string>(opts.at(fileTypeName));
    try {
      return fStringToFileType.at(option);
    } catch (const std::out_of_range& outOfRangeFileTypeException) {
    }
  } catch (const std::out_of_range& outOfRangeOptionException) {
    std::string errorMessage = "Out of range error in Options container ";
    handleErrorMessage(errorMessage, outOfRangeOptionException);
  }
  return FileType::kUndefinedFileType;
}

}
