/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetOptionsGeneratorTools.cpp
 */

#include "./JPetCommonTools/JPetCommonTools.h"
#include "./JPetOptionsGeneratorTools.h"

using namespace jpet_options_tools;

namespace jpet_options_generator_tools
{
std::map<std::string, boost::any> kDefaultOptions = {
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

std::map<std::string, std::string> kOptCmdLineNameToExtendedName = {
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

std::map<std::string, boost::any> transformOptions(
  const TransformersMap& transformationMap,
  const std::map<std::string,
  boost::any>& oldOptionsMap)
{
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

/**
 * Method returns a set of Options based on the input set and the control settings
 * If no special options are present in the control settings, the inOptions
 * are just passed further. Currenty if controlSettings contain option:
 * 1. "resetEventRange_bool"->true then, the generated inOptions will contain
 * the first and the last event values set to -1, which means
 * 'process all available events'.
 * 2. option 'outputFileType_std::string'->value set, then the generated
 * inOptions will contain inputFileType_str::string set to value
 * 3.'outputPath_std::string'-> path then the generated inOptions will contain
 * 'inputFile_std::string' ->path/nameOfFile
 */
OptsStrAny generateOptionsForTask(const OptsStrAny& inOptions, const OptsStrAny& controlSettings)
{
  auto newOpts(inOptions);
  if (isOptionSet(controlSettings, "resetEventRange_bool")) {
    if (getOptionAsBool(controlSettings, "resetEventRange_bool")) {
      newOpts = resetEventRange(newOpts);
    }
  }
  if (isOptionSet(controlSettings, "outputFileType_std::string")) {
    newOpts["inputFileType_std::string"] = getOptionAsString(controlSettings,
      "outputFileType_std::string");
  }
  if (isOptionSet(controlSettings, "outputFile_std::string")) {
    newOpts["inputFile_std::string"] = getOptionAsString(controlSettings,
      "outputFile_std::string");
  }
  if (isOptionSet(controlSettings, "outputPath_std::string")) {
    auto outPath  = std::string(getOutputPath(controlSettings));
    if (!outPath.empty()) {
      newOpts.at("inputFile_std::string") = outPath
        + JPetCommonTools::extractFileNameFromFullPath(getInputFile(newOpts));
    }
  }
  return newOpts;
}

std::map<std::string, boost::any> transformToStrAnyMap(const po::variables_map& inMap)
{
  std::map<std::string, boost::any> outMap;
  for (auto& option : inMap) {
    outMap[option.first] = option.second.value();
  }
  return outMap;
}

std::map<std::string, boost::any>  addMissingDefaultOptions(
  const std::map<std::string, boost::any>& oldOptions)
{
  std::map<std::string, boost::any> newOptions(oldOptions);
  auto defaultOptions = getDefaultOptions();
  newOptions.insert(defaultOptions.begin(), defaultOptions.end());
  return newOptions;
}

/**
 * The keys usedin this method correspond to the keys defined in the CmdArgMap
 */
std::map<std::string, std::vector<Transformer> > generateTransformationMap(OptsStrAny& options)
{
  std::map<std::string, std::vector<Transformer> > transformationMap;
  transformationMap["outputPath_std::string"].push_back(appendSlash);
  transformationMap["range_std::vector<int>"].push_back(generateLowerEventBound);
  transformationMap["range_std::vector<int>"].push_back(generateHigherEventBound);
  addTransformFunction(transformationMap, "type_std::string",
    jpet_options_tools::generateSetFileTypeTransformator(options));
  return transformationMap;
}

OptsStrAny resetEventRange(const OptsStrAny& srcOpts)
{
  OptsStrAny opts(srcOpts);
  opts.at("firstEvent_int") = -1;
  opts.at("lastEvent_int") = -1;
  return opts;
}

/**
 * Methods add type suffixes to the elements of the map according to the key name.
 */
OptsStrAny addTypeSuffixes(const std::map<std::string, boost::any>& oldMap)
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

std::map<std::string, boost::any> getDefaultOptions()
{
  return kDefaultOptions;
}

void addTransformFunction(TransformersMap& map,
  const std::string& name,
  Transformer transformFunction)
{
  map[name].push_back(transformFunction);
}

/**
 * Adding an option to already existing ones. If the key already exists the element
 * will not be updated.
 */
void addNewOptionsFromCfgFile(const std::string& cfgFile, std::map<std::string, boost::any>& options)
{
  std::map<std::string, boost::any> optionsFromJson = jpet_options_tools::createOptionsFromConfigFile(cfgFile);
  options.insert(optionsFromJson.begin(), optionsFromJson.end());
}

void setOutputFileType(OptsStrAny& options, const std::string& fileType)
{
  options["outputFileType_std::string"] = fileType;
}

/**
 * Please note that those methods change the input options. If the key does not
 * exist, it will be created, if it exists the value will be overwritten
 */
void setResetEventRangeOption(OptsStrAny& options, bool isReset)
{
  options["resetEventRange_bool"] = isReset;
}

void setOutputFile(OptsStrAny& options, const std::string& file)
{
  options["outputFile_std::string"] = file;
}

void setOutputPath(OptsStrAny& options, const std::string& path)
{
  options["outputPath_std::string"] = path;
}

}
