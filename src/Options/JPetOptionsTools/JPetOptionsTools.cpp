/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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

#include "JPetOptionsTools/JPetOptionsTools.h"
#include "JPetCommonTools/JPetCommonTools.h"
#include "JPetLoggerInclude.h"
#include "JPetOptionsGenerator/JPetOptionsTypeHandler.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <typeinfo>

namespace pt = boost::property_tree;
using boost::any_cast;

namespace jpet_options_tools
{
bool isOptionSet(const OptsStrAny& opts, const std::string& optionName) { return static_cast<bool>(opts.count(optionName)); }

boost::any getOptionValue(const OptsStrAny& opts, const std::string& optionName) { return opts.at(optionName); }

std::string getOptionAsString(const OptsStrAny& opts, const std::string& optionName)
{
  try
  {
    return any_cast<std::string>(getOptionValue(opts, optionName));
  }
  catch (const std::exception& excep)
  {
    ERROR("Bad option type:" + std::string(excep.what()));
    return "";
  }
}

int getOptionAsInt(const OptsStrAny& opts, const std::string& optionName)
{
  try
  {
    return any_cast<int>(getOptionValue(opts, optionName));
  }
  catch (const std::exception& excep)
  {
    ERROR("Bad option type:" + std::string(excep.what()));
    return -1;
  }
}

float getOptionAsFloat(const OptsStrAny& opts, const std::string& optionName)
{
  try
  {
    return any_cast<float>(getOptionValue(opts, optionName));
  }
  catch (const std::exception& excep)
  {
    ERROR("Bad option type:" + std::string(excep.what()));
    return -1.;
  }
}

double getOptionAsDouble(const OptsStrAny& opts, const std::string& optionName)
{
  try
  {
    return any_cast<double>(getOptionValue(opts, optionName));
  }
  catch (const std::exception& excep)
  {
    ERROR("Bad option type:" + std::string(excep.what()));
    return -1.;
  }
}

std::vector<std::string> getOptionAsVectorOfStrings(const OptsStrAny& opts, const std::string& optionName)
{
  try
  {
    return any_cast<std::vector<std::string>>(getOptionValue(opts, optionName));
  }
  catch (const std::exception& excep)
  {
    std::vector<std::string> emptyV;
    ERROR("Bad option type:" + std::string(excep.what()));
    return emptyV;
  }
}

std::vector<int> getOptionAsVectorOfInts(const OptsStrAny& opts, const std::string& optionName)
{
  try
  {
    return any_cast<std::vector<int>>(getOptionValue(opts, optionName));
  }
  catch (const std::exception& excep)
  {
    std::vector<int> emptyV;
    ERROR("Bad option type:" + std::string(excep.what()));
    return emptyV;
  }
}

std::vector<double> getOptionAsVectorOfDoubles(const OptsStrAny& opts, const std::string& optionName)
{
  try
  {
    return any_cast<std::vector<double>>(getOptionValue(opts, optionName));
  }
  catch (const std::exception& excep)
  {
    std::vector<double> emptyV;
    ERROR("Bad option type:" + std::string(excep.what()));
    return emptyV;
  }
}

bool getOptionAsBool(const OptsStrAny& opts, const std::string& optionName)
{
  try
  {
    return any_cast<bool>(getOptionValue(opts, optionName));
  }
  catch (const std::exception& excep)
  {
    ERROR("Bad option type:" + std::string(excep.what()));
    return false;
  }
}

/**
 * Specialized getter functions to extract option values with predefined names
 * This function returns a valid result only if the inputFile option is given
 * in the untransformed form: std::vector<std::string>
 */
std::vector<std::string> getInputFiles(const std::map<std::string, boost::any>& opts)
{
  std::vector<std::string> dummy;
  if (!isOptionSet(opts, "file_std::vector<std::string>"))
  {
    ERROR("key:file_std::vector<std::string> not found in options");
    return dummy;
  }
  return any_cast<std::vector<std::string>>(opts.at("file_std::vector<std::string>"));
}

/**
 * This function returns a valid result only if the inputFile option is given
 * in the transformed form with _std::string suffix
 */
std::string getInputFile(const std::map<std::string, boost::any>& opts) { return any_cast<std::string>(opts.at("inputFile_std::string")); }

std::string getScopeConfigFile(const std::map<std::string, boost::any>& opts)
{
  return any_cast<std::string>(opts.at("scopeConfigFile_std::string"));
}

std::string getScopeInputDirectory(const std::map<std::string, boost::any>& opts)
{
  return any_cast<std::string>(opts.at("scopeInputDirectory_std::string"));
}

// cppcheck-suppress unusedFunction
std::string getOutputFile(const std::map<std::string, boost::any>& opts) { return any_cast<std::string>(opts.at("outputFile_std::string")); }

std::string getOutputPath(const std::map<std::string, boost::any>& opts) { return any_cast<std::string>(opts.at("outputPath_std::string")); }

long long getFirstEvent(const std::map<std::string, boost::any>& opts) { return any_cast<int>(opts.at("firstEvent_int")); }

long long getLastEvent(const std::map<std::string, boost::any>& opts) { return any_cast<int>(opts.at("lastEvent_int")); }

/**
 * It returns the total number of events calculated from the first and the last
 * event given in the range of events to calculate. If first or last event is
 * set to -1 then the -1 is returned. If last - first < 0 then -1 is returned.
 * Otherwise last - first +1 is returned.
 */
long long getTotalEvents(const std::map<std::string, boost::any>& opts)
{
  long long first = getFirstEvent(opts);
  long long last = getLastEvent(opts);
  long long diff = -1;
  if ((first >= 0) && (last >= 0) && ((last - first) >= 0))
  {
    diff = last - first + 1;
  }
  return diff;
}

int getRunNumber(const std::map<std::string, boost::any>& opts) { return any_cast<int>(opts.at("runID_int")); }

bool isProgressBar(const std::map<std::string, boost::any>& opts)
{
  if (opts.find("progressBar_bool") != opts.end())
  {
    return any_cast<bool>(opts.at("progressBar_bool"));
  }
  return false;
}

bool isDirectProcessing(const std::map<std::string, boost::any>& opts)
{
  if (opts.find("directProcessing_bool") != opts.end())
  {
    return any_cast<bool>(opts.at("directProcessing_bool"));
  }
  return false;
}

bool isLocalDB(const std::map<std::string, boost::any>& opts) { return (bool)opts.count("localDB_std::string"); }

std::string getLocalDB(const std::map<std::string, boost::any>& opts)
{
  std::string result("");
  if (isLocalDB(opts))
  {
    result = any_cast<std::string>(opts.at("localDB_std::string"));
  }
  return result;
}
bool isLocalDBCreate(const std::map<std::string, boost::any>& opts) { return (bool)opts.count("localDBCreate_std::string"); }

std::string getLocalDBCreate(const std::map<std::string, boost::any>& opts)
{
  std::string result("");
  if (isLocalDBCreate(opts))
  {
    result = any_cast<std::string>(opts.at("localDBCreate_std::string"));
  }
  return result;
}

// cppcheck-suppress unusedFunction
std::string getUnpackerConfigFile(const std::map<std::string, boost::any>& opts)
{
  return any_cast<std::string>(opts.at("unpackerConfigFile_std::string"));
}

std::string getConfigFileName(const std::map<std::string, boost::any>& optsMap)
{
  if (optsMap.count("userCfg_std::string"))
  {
    return any_cast<std::string>(optsMap.at("userCfg_std::string"));
  }
  else
  {
    return "";
  }
}

// cppcheck-suppress unusedFunction
void printOptions(const OptsStrAny& opts)
{
  std::cout << "Current options:" << std::endl;
  auto stringOptions = JPetOptionsTypeHandler::anyMapToStringMap(opts);
  for (const auto& el : stringOptions)
  {
    std::cout << el.first + "=" + el.second << std::endl;
  }
}

void printOptionsToLog(const OptsStrAny& opts, const std::string& firstLine)
{
  if (!firstLine.empty())
  {
    INFO(firstLine.c_str());
  }
  INFO("Current options:");
  auto stringOptions = JPetOptionsTypeHandler::anyMapToStringMap(opts);
  for (const auto& el : stringOptions)
  {
    INFO(el.first + "=" + el.second);
  }
}

/**
 * Creates json file based on given options.
 */
bool createConfigFileFromOptions(const OptsStrStr& options, const std::string& outFile)
{
  pt::ptree optionsTree;
  for (auto& entry : options)
    optionsTree.put(entry.first, entry.second);
  try
  {
    pt::write_json(outFile, optionsTree);
  }
  catch (const pt::json_parser_error&)
  {
    ERROR("ERROR IN WRITING OPTIONS TO JSON FILE");
    return false;
  }
  return true;
}

/**
 * Creates option map based on the content of the json file.
 */
std::map<std::string, boost::any> createOptionsFromConfigFile(const std::string& filename)
{
  pt::ptree optionsTree;
  std::map<std::string, boost::any> mapOptions, emptyMap;
  if (JPetCommonTools::ifFileExisting(filename))
  {
    try
    {
      pt::read_json(filename, optionsTree);
      for (auto& item : optionsTree)
      {
        auto key = item.first;
        std::string typeOfOption = JPetOptionsTypeHandler::getTypeOfOption(key);
        auto allowedTypes = JPetOptionsTypeHandler::getAllowedTypes();
        switch (allowedTypes[typeOfOption])
        {
        case JPetOptionsTypeHandler::kAllowedTypes::kInt:
          mapOptions.insert(std::make_pair(key, item.second.get_value<int>()));
          break;
        case JPetOptionsTypeHandler::kAllowedTypes::kString:
          mapOptions.insert(std::make_pair(key, item.second.get_value<std::string>()));
          break;
        case JPetOptionsTypeHandler::kAllowedTypes::kFloat:
          mapOptions.insert(std::make_pair(key, item.second.get_value<float>()));
          break;
        case JPetOptionsTypeHandler::kAllowedTypes::kDouble:
          mapOptions.insert(std::make_pair(key, item.second.get_value<double>()));
          break;
        case JPetOptionsTypeHandler::kAllowedTypes::kBool:
          mapOptions.insert(std::make_pair(key, item.second.get_value<bool>()));
          break;
        case JPetOptionsTypeHandler::kAllowedTypes::kVectorString:
          mapOptions.insert(std::make_pair(key, [&optionsTree, &key]() -> std::vector<std::string> {
            std::vector<std::string> values;
            for (pt::ptree::value_type& value : optionsTree.get_child(key))
            {
              values.push_back(value.second.get_value<std::string>());
            }
            return values;
          }()));
          break;
        case JPetOptionsTypeHandler::kAllowedTypes::kVectorInt:
          mapOptions.insert(std::make_pair(key, [&optionsTree, &key]() -> std::vector<int> {
            std::vector<int> values;
            for (pt::ptree::value_type& value : optionsTree.get_child(key))
            {
              values.push_back(value.second.get_value<int>());
            }
            return values;
          }()));
          break;
        case JPetOptionsTypeHandler::kAllowedTypes::kVectorDouble:
          mapOptions.insert(std::make_pair(key, [&optionsTree, &key]() -> std::vector<double> {
            std::vector<double> values;
            for (pt::ptree::value_type& value : optionsTree.get_child(key))
            {
              values.push_back(value.second.get_value<double>());
            }
            return values;
          }()));
          break;
        default:
          WARNING("Unknow option type: " + typeOfOption + " skipping option: " + key);
          break;
        }
      }
    }
    catch (const pt::json_parser_error&)
    {
      ERROR("ERROR IN READINIG OPTIONS FROM JSON FILE! FILENAME:" + filename);
      throw std::invalid_argument("ERROR parsing json user params file! Aborting execution!");
    }
  }
  else
  {
    ERROR("JSON CONFIG FILE DOES NOT EXIST! FILENAME:" + filename);
    throw std::invalid_argument("ERROR parsing json user params file, file does not exist! Aborting execution!");
  }
  return mapOptions;
}

void handleErrorMessage(const std::string& errorMessage, const std::out_of_range& outOfRangeException)
{
  std::cerr << errorMessage << outOfRangeException.what() << '\n';
  ERROR(errorMessage);
}

file_type_checker::FileType file_type_checker::getFileType(const std::map<std::string, boost::any>& opts, const std::string& fileTypeName)
{
  std::map<std::string, file_type_checker::FileType> fileTypeMap = {{"", kNoType}, {"root", kRoot},       {"mcGeant", kMCGeant}, {"scope", kScope},
                                                                    {"hld", kHld}, {"hldRoot", kHldRoot}, {"zip", kZip}};

  try
  {
    auto option = any_cast<std::string>(opts.at(fileTypeName));
    try
    {
      return fileTypeMap.at(option);
    }
    catch (const std::out_of_range& outOfRangeFileTypeException)
    {
      std::string errorMessage = "Provided file type option was not found - out of range in getFileType() ";
      handleErrorMessage(errorMessage, outOfRangeFileTypeException);
    }
  }
  catch (const std::out_of_range& outOfRangeOptionException)
  {
    std::string errorMessage = "Provided option was not found - out of range error in options container ";
    handleErrorMessage(errorMessage, outOfRangeOptionException);
  }
  return file_type_checker::FileType::kUndefinedFileType;
}

file_type_checker::FileType file_type_checker::getInputFileType(const std::map<std::string, boost::any>& opts)
{
  return file_type_checker::getFileType(opts, "inputFileType_std::string");
}

file_type_checker::FileType file_type_checker::getOutputFileType(const std::map<std::string, boost::any>& opts)
{
  return file_type_checker::getFileType(opts, "outputFileType_std::string");
}

/**
 * Method returns the detector type based on the provided options:
 * if the "-k" option for the is worng or not used, then by default
 * the detector type is the Big Barrel - kBarrel.
 */
detector_type_checker::DetectorType detector_type_checker::getDetectorType(const std::map<std::string, boost::any>& opts)
{
  std::map<std::string, detector_type_checker::DetectorType> detectorTypeMap = {
      {"bar", kBarrel}, {"barrel", kBarrel}, {"mod", kModular}, {"modular", kModular}};

  try
  {
    auto option = any_cast<std::string>(opts.at("detectorType_std::string"));
    try
    {
      return detectorTypeMap.at(option);
    }
    catch (const std::out_of_range& outOfRangeDetectorTypeException)
    {
      std::string errorMessage = "Provided detector type option was not found - out of range in getDetectorType() ";
      handleErrorMessage(errorMessage, outOfRangeDetectorTypeException);
    }
  }
  catch (const std::out_of_range& outOfRangeOptionException)
  {
    std::string errorMessage = "Provided option was not found - out of range error in options container ";
    handleErrorMessage(errorMessage, outOfRangeOptionException);
  }
  return detector_type_checker::DetectorType::kBarrel;
}

} // namespace jpet_options_tools
