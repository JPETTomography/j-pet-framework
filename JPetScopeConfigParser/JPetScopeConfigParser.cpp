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
bool JPetScopeConfigParser::loadConfigFile(std::string configFileName)
{
  fLoadedConfigData = getJsonContent(configFileName);
  if (fLoadedConfigData.empty()) {
    return false;
  }
  return true;
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
    auto currFileNames =generateFileNames(configFileName, currentConfigName, transformToNumbers(positionsContainer));
    inputFileNames.insert(inputFileNames.end(), currFileNames.begin(), currFileNames.end());
  }
  return inputFileNames;
}

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

//JPetScopeConfigParser::JPetScopeConfigParser() : configName(""), location("")
//{}


//bool JPetScopeConfigParser::createFilesLocation(boost::property_tree::ptree const& conf_data, std::vector<JPetConfigData>::iterator configDataElement)
//{
//try
//{
//location = conf_data.get<std::string>("location");//TODO do usuniecia ale pod koniec jak wektor bedzie caly wypelniony
//(*configDataElement).location = location;
//}
//catch(const std::runtime_error &error)
//{
//std::string message = "No location. Error = " + std::string(error.what());
//ERROR(message);
//return false;
//}
//return true;
//}

//bool JPetScopeConfigParser::createBSlotData(boost::property_tree::ptree const& conf_data, std::vector<JPetConfigData>::iterator configDataElement)
//{
//try
//{
//int bslotid1 = conf_data.get("bslot1.id", -1);
//int bslotid2 = conf_data.get("bslot2.id", -1);

//bool bslotactive1 = conf_data.get("bslot1.active", false);
//bool bslotactive2 = conf_data.get("bslot2.active", false);

//std::string bslotname1 = conf_data.get("bslot1.name", std::string(""));
//std::string bslotname2 = conf_data.get("bslot2.name", std::string(""));

//float bslottheta1 = conf_data.get("bslot1.theta", -1.f);
//float bslottheta2 = conf_data.get("bslot2.theta", -1.f);

//int bslotframe1 = conf_data.get("bslot1.frame", -1);
//int bslotframe2 = conf_data.get("bslot2.frame", -1);

//JPetBSlotData bSlotData1(bslotid1, bslotactive1, bslotname1, bslottheta1, bslotframe1);
//JPetBSlotData bSlotData2(bslotid2, bslotactive2, bslotname2, bslottheta2, bslotframe2);
//bSlotData.push_back(bSlotData1);
//bSlotData.push_back(bSlotData2);

//(*configDataElement).bSlotData.emplace_back(bSlotData1);
//(*configDataElement).bSlotData.emplace_back(bSlotData2);

//std::cout << bslotid1 << " " << bslotid1 << std::endl;
//std::cout << bslotactive1 << " " << bslotactive2 << std::endl;
//std::cout << bslotname1 << " " << bslotname2 << std::endl;
//std::cout << bslottheta1 << " " << bslottheta1 << std::endl;
//std::cout << bslotframe1 << " " << bslotframe2 << std::endl;
//}
//catch(const std::runtime_error &error)
//{
//std::string message = "BSlot data error parsing. Error = " + std::string(error.what());
//ERROR(message);
//return false;
//}
//return true;
//}

//bool JPetScopeConfigParser::createPMData(boost::property_tree::ptree const& conf_data, std::vector<JPetConfigData>::iterator configDataElement)
//{
//try
//{
//int pmid1 = conf_data.get("pm1.id", 0);
//int pmid2 = conf_data.get("pm2.id", 0);
//int pmid3 = conf_data.get("pm3.id", 0);
//int pmid4 = conf_data.get("pm4.id", 0);

//std::string pmPrefix1 = conf_data.get<std::string>("pm1.prefix");
//std::string pmPrefix2 = conf_data.get<std::string>("pm2.prefix");
//std::string pmPrefix3 = conf_data.get<std::string>("pm3.prefix");
//std::string pmPrefix4 = conf_data.get<std::string>("pm4.prefix");

//JPetPMData pmData1(pmid1, pmPrefix1);
//JPetPMData pmData2(pmid2, pmPrefix2);
//JPetPMData pmData3(pmid3, pmPrefix3);
//JPetPMData pmData4(pmid4, pmPrefix4);

//pmData.push_back(pmData1);
//pmData.push_back(pmData2);
//pmData.push_back(pmData3);
//pmData.push_back(pmData4);

//(*configDataElement).pmData.emplace_back(pmData1);
//(*configDataElement).pmData.emplace_back(pmData2);
//(*configDataElement).pmData.emplace_back(pmData3);
//(*configDataElement).pmData.emplace_back(pmData4);

//std::cout << pmid1 << " " << pmid2 << " " << pmid3 << " " << pmid4 << std::endl;
//}
//catch(const std::runtime_error &error)
//{
//std::string message = "PM data error parsing. Error = " + std::string(error.what());
//ERROR(message);
//return false;
//}
//return true;
//}

//bool JPetScopeConfigParser::createScinData(boost::property_tree::ptree const& conf_data, std::vector<JPetConfigData>::iterator configDataElement)
//{
//try
//{
//int scinid1 = conf_data.get("scin1.id", 0);
//int scinid2 = conf_data.get("scin2.id", 0);

//JPetScinData scinData1(scinid1);
//JPetScinData scinData2(scinid2);

//scinData.push_back(scinData1);
//scinData.push_back(scinData2);

//(*configDataElement).scinData.emplace_back(scinData1);
//(*configDataElement).scinData.emplace_back(scinData2);

//std::cout << scinid1 << " " << scinid2 << std::endl;
//}
//catch(const std::runtime_error &error)
//{
//std::string message = "Scin data error parsing. Error = " + std::string(error.what());
//ERROR(message);
//return false;
//}
//return true;
//}

//bool JPetScopeConfigParser::createParamObjects(boost::property_tree::ptree const& conf_data, std::vector<JPetConfigData>::iterator configDataElement)
//{
//bool createBSlotDataSuccessfully = createBSlotData(conf_data, configDataElement);
//bool createPMDataSuccessfully = createPMData(conf_data, configDataElement);
//bool createScinDataSuccessfully = createScinData(conf_data, configDataElement);
//bool createParamObjectsSuccessfully = createBSlotDataSuccessfully && createPMDataSuccessfully && createScinDataSuccessfully;

//return createParamObjectsSuccessfully;
//}

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

//bool JPetScopeConfigParser::readData(const std::string &configFileName)
//{
//boost::property_tree::ptree propTree;

//const std::string configFileExtension = boost::filesystem::path(configFileName).extension().string();
//const std::string requiredFileExtension = ".json";

//if(getJsonContent(configFileExtension, requiredFileExtension, configFileName, propTree))
//{
//for(boost::property_tree::ptree::const_iterator it = propTree.begin(); it != propTree.end(); ++it)
//{
//const boost::property_tree::ptree& conf_data = it->second;

////proof of concept
//JPetConfigData configData;
//configDataContainer.emplace_back(configData);
//std::vector<JPetConfigData>::iterator lastElementFromConfigData = configDataContainer.end() - 1;

//bool createFilesLocationSuccessfully = createFilesLocation(conf_data, lastElementFromConfigData);
//bool createParamObjectsSuccessfully = createParamObjects(conf_data, lastElementFromConfigData);

//std::cout << "configDataContainer.front().location = " << configDataContainer.front().location << std::endl;
//for(unsigned i=0; i<configDataContainer.front().bSlotData.size(); ++i) std::cout << "A = " << configDataContainer.front().bSlotData[i] << std::endl;
//for(unsigned i=0; i<configDataContainer.front().pmData.size(); ++i) std::cout << "B = " << configDataContainer.front().pmData[i] << std::endl;
//for(unsigned i=0; i<configDataContainer.front().scinData.size(); ++i) std::cout << "C = " << configDataContainer.front().scinData[i] << std::endl;

//if(createFilesLocationSuccessfully && createParamObjectsSuccessfully)
//{
////if(configName.empty())
//{
//configName = it->first;
////std::cout << "configName= " << configName << std::endl;
//(*lastElementFromConfigData).configName = configName;

//std::cout << "configDataContainer.front().configName = " << configDataContainer.front().configName << std::endl;
//}

//std::string collimatorFunction = "";
//int a = 0, b = 0, c = 0, n = 0;

//BOOST_FOREACH(const boost::property_tree::ptree::value_type& v, conf_data.get_child("collimator"))
//{
//collimatorFunction = v.second.get<std::string>("positions");

//n = sscanf(collimatorFunction.c_str(), "%d %d %d", &a, &b, &c);

//if(n > 0)
//{
//if(n == 1) {b = a; c = 1;}
//if(n == 2) {c = 1;}

//for(int j = a; j <=b; j+= c)
//{
//positions.emplace_back(j);
////j - pozycja z pliku json
////std::cout << "pCollPosition= " << j << std::endl;
//(*lastElementFromConfigData).positions.emplace_back(j);

//std::cout << "configDataContainer.front().positions.size() = " << configDataContainer.front().positions.size() << std::endl;
//for(unsigned i=0; i<configDataContainer.front().positions.size(); ++i) std::cout << "D = " << configDataContainer.front().positions[i] << std::endl;

//createOutputFileNames(configFileName, j);
//}
//}
//}
//}
//}
//}
//return true;
//}
