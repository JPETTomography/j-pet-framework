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
 *  @file JPetScopeConfigParser.cpp
 */

#include "JPetScopeConfigParser.h"
#include "../JPetLoggerInclude.h"

#include <boost/regex.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <TApplication.h>
#include <cstdio>
#include <iostream>
#include "../JPetCommonTools/JPetCommonTools.h"


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

scope_config::Config JPetScopeConfigParser::getConfig(std::string configName, boost::property_tree::ptree const& configContent) const
{
  using namespace scope_config;
  Config config;
  config.fName = configName;
  config.fLocation = getLocation(configContent);
  config.fCollimatorPositions = getPositions(configContent);
  config.fBSlots = getBSlots(configContent);
  config.fPMs = getPMs(configContent);
  config.fScins = getScins(configContent);
  return config;
}

std::vector<JPetScopeConfigParser::InputDirectory> JPetScopeConfigParser::getInputDirectories(const std::string& configFileLocation, const scope_config::Config& config) const
{
  std::vector<std::string> directories;
  auto path = configFileLocation + "/" + config.fLocation;
  auto currDir = generateDirectories(path, transformToNumbers(config.fCollimatorPositions));
  directories.insert(directories.end(), currDir.begin(), currDir.end());
  return directories;
}

std::vector<JPetScopeConfigParser::FakeInputFile> JPetScopeConfigParser::getFakeInputFileNames(const std::string& configFileName, const scope_config::Config& config) const
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
      directories.begin(), directories.end(), filenames.begin(), std::back_inserter(container),
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
  std::copy_if(dirsAndFiles.begin(), dirsAndFiles.end(), std::back_inserter(result),
  [](const DirFilePair dirFilePair) {
    return JPetCommonTools::isDirectory(dirFilePair.first);
  }
              );
  return result;
}


// The function takes a vector of string, each string can contain one or more integers separated by
// space and it will transform it to vector of integers.
// If some elements are non-numbers the rest of the string is ignored.
// If floats or doubles are present in the string, the will be cast to int.
// e.g. ["1 2", "3", "7 a 5", "1.2"] -> [1, 2, 3, 7, 1]
std::vector<int> JPetScopeConfigParser::transformToNumbers(const std::vector<std::string>& positions) const
{
  std::vector<int> numbers;
  for (std::vector<std::string>::const_iterator it = positions.begin(); it != positions.end(); ++it) {
    int pos;
    std::stringstream buffer(*it);
    while (buffer >> pos) {
      numbers.push_back(pos);
    }
  }
  return numbers;
}

/// The directory is generated according to the following pattern:
/// base_path/position
/// e.g. "unittests/data/1"
std::vector<std::string>  JPetScopeConfigParser::generateDirectories(
  const std::string& basePath,
  const std::vector<int>& positions) const
{
  std::vector<std::string> DirNames(positions.size());
  std::transform(positions.begin(), positions.end(), DirNames.begin(),
  [ &basePath](int number) {
    return basePath + "/" + std::to_string(number);
  }
                );
  return DirNames;
}

/// The filename is generated according to the following pattern:
/// configFileName_configName_positions
/// e.g. "example_config1_5"
std::vector<std::string>  JPetScopeConfigParser::generateFileNames(
  const std::string& configFileName,
  const std::string& configName,
  const std::vector<int>& positions) const
{
  std::vector<std::string> fileNames(positions.size());
  std::transform(positions.begin(), positions.end(), fileNames.begin(),
  [&configFileName, &configName](int number) {
    return configFileName + "_" + configName + "_" + std::to_string(number);
  }
                );
  return fileNames;
}


std::string JPetScopeConfigParser::getLocation(boost::property_tree::ptree const& content) const
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

std::vector<std::string> JPetScopeConfigParser::getPositions(boost::property_tree::ptree const& configContent) const
{
  using boost::property_tree::ptree;
  std::vector<std::string> positions;
  try {
    BOOST_FOREACH(const ptree::value_type & v, configContent.get_child("collimator")) {
      //! one element positions can contain a string of several numbers e.g. "2 3 10"
      positions.push_back(v.second.get<std::string>("positions"));
    }
  } catch (const std::runtime_error& error) {
    std::string message = "Error parsing collimator positions. Error = " + std::string(error.what());
    ERROR(message);
  }
  return positions;
}

std::vector<scope_config::BSlot> JPetScopeConfigParser::getBSlots(boost::property_tree::ptree const& content) const
{
  using namespace scope_config;
  std::vector<BSlot> bslots;
  try {
    int bslotid1 = content.get("bslot1.id", -1);
    int bslotid2 = content.get("bslot2.id", -1);

    bool bslotactive1 = content.get("bslot1.active", false);
    bool bslotactive2 = content.get("bslot2.active", false);

    std::string bslotname1 = content.get("bslot1.name", std::string(""));
    std::string bslotname2 = content.get("bslot2.name", std::string(""));

    float bslottheta1 = content.get("bslot1.theta", -1.f);
    float bslottheta2 = content.get("bslot2.theta", -1.f);

    int bslotframe1 = content.get("bslot1.frame", -1);
    int bslotframe2 = content.get("bslot2.frame", -1);

    bslots.push_back(BSlot(bslotid1, bslotactive1, bslotname1, bslottheta1, bslotframe1));
    bslots.push_back(BSlot(bslotid2, bslotactive2, bslotname2, bslottheta2, bslotframe2));
  } catch (const std::runtime_error& error) {
    std::string message = "BSlot data error parsing. Error = " + std::string(error.what());
    ERROR(message);
  }
  return bslots;
}

std::vector<scope_config::PM> JPetScopeConfigParser::getPMs(boost::property_tree::ptree const& content) const
{
  using namespace scope_config;
  std::vector<PM> pms;
  try {
    int pmid1 = content.get("pm1.id", -1);
    int pmid2 = content.get("pm2.id", -1);
    int pmid3 = content.get("pm3.id", -1);
    int pmid4 = content.get("pm4.id", -1);

    std::string pmPrefix1 = content.get<std::string>("pm1.prefix");
    std::string pmPrefix2 = content.get<std::string>("pm2.prefix");
    std::string pmPrefix3 = content.get<std::string>("pm3.prefix");
    std::string pmPrefix4 = content.get<std::string>("pm4.prefix");

    pms.push_back(PM(pmid1, pmPrefix1));
    pms.push_back(PM(pmid2, pmPrefix2));
    pms.push_back(PM(pmid3, pmPrefix3));
    pms.push_back(PM(pmid4, pmPrefix4));

  } catch (const std::runtime_error& error) {
    std::string message = "PM data error parsing. Error = " + std::string(error.what());
    ERROR(message);
  }
  return pms;
}

std::vector<scope_config::Scin> JPetScopeConfigParser::getScins(boost::property_tree::ptree const& content) const
{
  using namespace scope_config;
  std::vector<Scin> scins;
  try {
    int scinid1 = content.get("scin1.id", 0);
    int scinid2 = content.get("scin2.id", 0);
    scins.push_back(Scin(scinid1));
    scins.push_back(Scin(scinid2));
  } catch (const std::runtime_error& error) {
    std::string message = "Scin data error parsing. Error = " + std::string(error.what());
    ERROR(message);
  }
  return scins;
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



/// We store id of given types in a set. Set can contain only unique id, therefore in case of
/// duplication the set size will be smaller that orginal vector size.
bool JPetScopeConfigParser::areObjectsWithDuplicatedIds(const scope_config::Config& config) const
{
  using namespace scope_config;
  std::set<int> bSlotIdSet;
  for (const auto &  bslot : config.fBSlots) {
    bSlotIdSet.insert(bslot.fId);
  }
  if (bSlotIdSet.size() < config.fBSlots.size()) return true;

  std::set<int> pmIdSet;
  for (const auto &  pm : config.fPMs) {
    pmIdSet.insert(pm.fId);
  }
  if (pmIdSet.size() < config.fPMs.size()) return true;

  std::set<int> scinIdSet;
  for (const auto &  scin : config.fScins) {
    scinIdSet.insert(scin.fId);
  }
  if (scinIdSet.size() < config.fScins.size()) return true;

  return false;
}
