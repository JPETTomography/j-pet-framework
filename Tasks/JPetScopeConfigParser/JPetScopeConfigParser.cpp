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
 *  @file JPetScopeConfigParser.cpp
 */

#include "./JPetCommonTools/JPetCommonTools.h"
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "JPetScopeConfigParser.h"
#include "./JPetLoggerInclude.h"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/regex.hpp>
#include <TApplication.h>
#include <iostream>
#include <cstdio>

scope_config::Config JPetScopeConfigParser::getConfig(const std::string& configFileName) const
{
  using namespace scope_config;
  using boost::property_tree::ptree;
  Config config;
  auto prop_tree = getJsonContent(configFileName);
  if (prop_tree.size() > 1 ) {
    ERROR("More than one config found in the configuration file! Only the last set will be used!");
  }
  for (ptree::const_iterator it = prop_tree.begin(); it != prop_tree.end(); ++it) {
    auto currConfigName = it->first;
    auto currConfigContent = it->second;
    config = getConfig(currConfigName, currConfigContent);
  }
  return config;
}

scope_config::Config JPetScopeConfigParser::getConfig(
  std::string configName, boost::property_tree::ptree const& configContent) const
{
  using namespace scope_config;
  Config config;
  config.fName = configName;
  config.fLocation = getLocation(configContent);
  config.fCollimatorPositions = getPositions(configContent);
  return config;
}

std::vector<JPetScopeConfigParser::InputDirectory> JPetScopeConfigParser::getInputDirectories(
  const std::string& configFileLocation, const scope_config::Config& config) const
{
  std::vector<std::string> directories;
  auto path = configFileLocation + "/" + config.fLocation;
  auto currDir = generateDirectories(path, transformToNumbers(config.fCollimatorPositions));
  directories.insert(directories.end(), currDir.begin(), currDir.end());
  return directories;
}

std::vector<JPetScopeConfigParser::FakeInputFile> JPetScopeConfigParser::getFakeInputFileNames(
  const std::string& configFileName, const scope_config::Config& config) const
{
  std::vector<std::string> positionsContainer = config.fCollimatorPositions;
  return generateFileNames(JPetCommonTools::stripFileNameSuffix(configFileName), config.fName,  transformToNumbers(positionsContainer));
}

JPetScopeConfigParser::DirFileContainer JPetScopeConfigParser::getInputDirectoriesAndFakeInputFiles(
  const std::string& configFileWithPath) const
{
  auto config  = getConfig(configFileWithPath);
  auto filenames = getFakeInputFileNames(configFileWithPath, config);
  auto directories =  getInputDirectories(JPetCommonTools::extractPathFromFile(configFileWithPath), config);
  JPetScopeConfigParser::DirFileContainer  container;
  if (filenames.size() != directories.size()) {
    ERROR("filenames.size() != directories.size()");
  } else {
    container.reserve(filenames.size());
    std::transform(
      directories.begin(),
      directories.end(),
      filenames.begin(),
      std::back_inserter(container),
      [](InputDirectory dir, FakeInputFile file) {
        return std::make_pair(dir, file);
      }
    );
  }
  return getElementsWithExistingDirs(container);
}

JPetScopeConfigParser::DirFileContainer JPetScopeConfigParser::getElementsWithExistingDirs(
  const JPetScopeConfigParser::DirFileContainer& dirsAndFiles) const
{
  JPetScopeConfigParser::DirFileContainer result;
  std::copy_if(
    dirsAndFiles.begin(),
    dirsAndFiles.end(),
    std::back_inserter(result),
    [](const DirFilePair dirFilePair) {
      return JPetCommonTools::isDirectory(dirFilePair.first);
    }
  );
  return result;
}

/**
 * Parsing function that takes a vector of strings, each string can contain
 * one or more integers separated by space and it will transform it to
 * a vector of integers. If a non-number element is encountered,
 * the rest of the string is ignored. Floats and doubles are cast to integers.
 * e.g. ["1 2", "3", "7 a 5", "1.2"] -> [1, 2, 3, 7, 1]
 */
std::vector<int> JPetScopeConfigParser::transformToNumbers(const std::vector<std::string>& positions) const
{
  std::vector<int> numbers;
  for (std::vector<std::string>::const_iterator it = positions.begin(); it != positions.end(); ++it) {
    int pos;
    std::stringstream buffer(*it);
    while (buffer >> pos) { numbers.push_back(pos); }
  }
  return numbers;
}

/**
 * The directory is generated according to the following pattern:
 * base_path/position
 * e.g. 'unittests/data/1'
 */
std::vector<std::string>  JPetScopeConfigParser::generateDirectories(
  const std::string& basePath,
  const std::vector<int>& positions) const
{
  std::vector<std::string> DirNames(positions.size());
  std::transform(
    positions.begin(),
    positions.end(),
    DirNames.begin(),
    [&basePath](int number) {
      return basePath + "/" + std::to_string(number);
    }
  );
  return DirNames;
}

/**
 * The filename is generated according to the following pattern:
 * configFileName_configName_positions
 * e.g. 'example_config1_5'
 */
std::vector<std::string>  JPetScopeConfigParser::generateFileNames(
  const std::string& configFileName,
  const std::string& configName,
  const std::vector<int>& positions) const
{
  std::vector<std::string> fileNames(positions.size());
  std::transform(
    positions.begin(),
    positions.end(),
    fileNames.begin(),
    [&configFileName, &configName](int number) {
      return configFileName + "_" + configName + "_" + std::to_string(number);
    }
  );
  return fileNames;
}

std::string JPetScopeConfigParser::getLocation(
  boost::property_tree::ptree const& content) const
{
  std::string location;
  try {
    location = content.get<std::string>("location");
  } catch (const std::runtime_error& error) {
    std::string message = "No location found in config file. Error = " + std::string(error.what());
    ERROR(message);
  }
  return location;
}

std::vector<std::string> JPetScopeConfigParser::getPositions(
  boost::property_tree::ptree const& configContent) const
{
  using boost::property_tree::ptree;
  std::vector<std::string> positions;
  try {
    BOOST_FOREACH(const ptree::value_type & v, configContent.get_child("collimator")) {
      positions.push_back(v.second.get<std::string>("positions"));
    }
  } catch (const std::runtime_error& error) {
    std::string message = "Error parsing collimator positions. Error = " + std::string(error.what());
    ERROR(message);
  }
  return positions;
}

boost::property_tree::ptree JPetScopeConfigParser::getJsonContent(const std::string& configFileName) const
{
  boost::property_tree::ptree propTree;
  try {
    read_json(configFileName, propTree);
  } catch (const std::runtime_error& error) {
    std::string message = "Error opening config file. Error = " + std::string(error.what());
    ERROR(message);
  }
  return propTree;
}
