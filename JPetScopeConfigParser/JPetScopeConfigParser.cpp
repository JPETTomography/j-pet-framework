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
#include "../CommonTools/CommonTools.h"


std::vector<scope_config::Config> JPetScopeConfigParser::getConfigs(const std::string& configFileName) const
{
  using namespace scope_config;
  using boost::property_tree::ptree;
  std::vector<Config> configs;
  auto prop_tree = getJsonContent(configFileName);
  for (ptree::const_iterator it = prop_tree.begin(); it != prop_tree.end(); ++it) {
    auto currConfigName = it->first;
    auto currConfigContent = it->second;
    configs.push_back(getConfig(currConfigName, currConfigContent));
  }
  return configs;
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

std::vector<std::string> JPetScopeConfigParser::getInputDirectories(const std::string& configFileLocation, const std::vector<scope_config::Config>& configs) const
{
  std::vector<std::string> directories;
  for(const auto& config: configs) 
  {
    auto path = configFileLocation + "/" +config.fLocation;
    auto currDir = generateDirectories(path, transformToNumbers(config.fCollimatorPositions));
    directories.insert(directories.end(), currDir.begin(), currDir.end());
  }
  return directories;
}


std::vector<std::string> JPetScopeConfigParser::getInputFileNames(std::string configFileName) const
{
  std::vector<std::string> inputFileNames;
  using boost::property_tree::ptree;
  auto prop_tree = getJsonContent(configFileName);
  ///loop over all config sets.
  for (ptree::const_iterator it = prop_tree.begin(); it != prop_tree.end(); ++it) {
    auto currentConfigName = it->first;
    auto currentConfigContent = it->second;
    std::vector<std::string> positionsContainer;
    BOOST_FOREACH(const ptree::value_type & v, currentConfigContent.get_child("collimator")) {
      //! one element positions can contain a string of several numbers e.g. "2 3 10"
      positionsContainer.push_back(v.second.get<std::string>("positions"));
    }
    auto currFileNames = generateFileNames(configFileName, CommonTools::stripFileNameSuffix(currentConfigName), transformToNumbers(positionsContainer));
    inputFileNames.insert(inputFileNames.end(), currFileNames.begin(), currFileNames.end());
  }
  return inputFileNames;
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

//std::string JPetScopeConfigParser::createPath(const std::string &configFileName, const int position)
//{
//std::string starting_loc  = boost::filesystem::path(configFileName).parent_path().string();
//starting_loc += "/";
//starting_loc += location;
//starting_loc += "/";
//starting_loc += std::to_string(position);
//return starting_loc;
//}

//bool JPetScopeConfigParser::createOutputFileNames(const std::string &configFileName, const int position)
//{
//std::string starting_loc = createPath(configFileName, position);

//boost::filesystem::path current_dir(starting_loc);
//std::cout << "starting_loc = " << starting_loc << std::endl;
//std::string prefix = pmData.front().prefix; //o co tu chodzi to jest niejasne dla mnie
//boost::regex pattern(Form("%s_\\d*.txt", prefix.c_str()));
//std::cout << "current_dir= " << current_dir << std::endl;
//if (exists(current_dir))
//{
//std::cout << "if" << std::endl;
//for (boost::filesystem::recursive_directory_iterator iter(current_dir), end; iter != end; ++iter)
//{
//std::string name = iter->path().leaf().string();
//std::cout << "name= " << name << std::endl;
//std::string dir = "";
//if (regex_match(name, pattern))
//{
//name[1] = prefix[1];
//dir = iter->path().parent_path().string();
//dir += "/";
//dir += name;
////(*current_config).pFiles.insert(dir);
//outputFileNames.push_back(dir);
//std::cout << "dir= " << dir << std::endl;
//}
//}
//}
//else
//{
//std::string msg  = "Directory: \"";
//msg += current_dir.string();
//msg += "\" does not exist.";
////std::cout << "msg= " << msg << std::endl;
//ERROR(msg.c_str());
//return false;
//}
//return true;
//}


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
