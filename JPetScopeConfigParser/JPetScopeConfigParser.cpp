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

/*
 * Temporary help
 * read_json(...)
 * http://www.boost.org/doc/libs/1_55_0/doc/html/boost/property_tree/json_parser/read_json_idp102885800.html
 */

#include "JPetScopeConfigParser.h"
#include "../JPetLoggerInclude.h"

//#include <boost/property_tree/ptree.hpp>
#include <boost/regex.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <TApplication.h>
#include <cstdio>



/*
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <utility>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <TApplication.h>
*/

#include <iostream>
//using namespace std;

//using boost::property_tree::ptree;
using namespace boost::filesystem;


JPetScopeConfigParser::JPetScopeConfigParser() : fileName(""), filesLocation("")
{}

bool JPetScopeConfigParser::getFilesLocation(ptree const& conf_data)
{
  filesLocation = conf_data.get<std::string>("location");
  return true;
}

bool JPetScopeConfigParser::createParamObject(ptree const& conf_data) 
{
    int bslotid1, bslotid2;
    bool bslotactive1, bslotactive2;
    std::string bslotname1, bslotname2;
    float bslottheta1, bslottheta2;
    int bslotframe1, bslotframe2;

    bslotid1 = conf_data.get("bslot1.id", -1);
    bslotid2 = conf_data.get("bslot2.id", -1);

    bslotactive1 = conf_data.get("bslot1.active", false);
    bslotactive2 = conf_data.get("bslot2.active", false);

    bslotname1 = conf_data.get("bslot1.name", std::string(""));
    bslotname2 = conf_data.get("bslot2.name", std::string(""));

    bslottheta1 = conf_data.get("bslot1.theta", -1.f);
    bslottheta2 = conf_data.get("bslot2.theta", -1.f);

    bslotframe1 = conf_data.get("bslot1.frame", -1);
    bslotframe2 = conf_data.get("bslot2.frame", -1);
    
    JPetBSlotData bSlotData1(bslotid1, bslotactive1, bslotname1, bslottheta1, bslotframe1);
    JPetBSlotData bSlotData2(bslotid2, bslotactive2, bslotname2, bslottheta2, bslotframe2);
    bSlotData.push_back(bSlotData1);
    bSlotData.push_back(bSlotData2);

    int pmid1, pmid2, pmid3, pmid4;

    pmid1 = conf_data.get("pm1.id", 0);
    pmid2 = conf_data.get("pm2.id", 0);
    pmid3 = conf_data.get("pm3.id", 0);
    pmid4 = conf_data.get("pm4.id", 0);
    
    std::string pmPrefix1 = conf_data.get<std::string>("pm1.prefix");
    std::string pmPrefix2 = conf_data.get<std::string>("pm2.prefix");
    std::string pmPrefix3 = conf_data.get<std::string>("pm3.prefix");
    std::string pmPrefix4 = conf_data.get<std::string>("pm4.prefix");
    
    JPetPMData pmData1(pmid1, pmPrefix1);
    JPetPMData pmData2(pmid1, pmPrefix2);
    JPetPMData pmData3(pmid1, pmPrefix3);
    JPetPMData pmData4(pmid1, pmPrefix4);
    
    pmData.push_back(pmData1);
    pmData.push_back(pmData2);
    pmData.push_back(pmData3);
    pmData.push_back(pmData4);

    int scinid1, scinid2;

    scinid1 = conf_data.get("scin1.id", 0);
    scinid2 = conf_data.get("scin2.id", 0);
    
    JPetScinData scinData1(scinid1);
    JPetScinData scinData2(scinid2);
    
    scinData.push_back(scinData1);
    scinData.push_back(scinData2);
    
std::cout << bslotid1 << " " << bslotid1 << std::endl;
std::cout << bslotactive1 << " " << bslotactive2 << std::endl;
std::cout << bslotname1 << " " << bslotname2 << std::endl;
std::cout << bslottheta1 << " " << bslottheta1 << std::endl;
std::cout << bslotframe1 << " " << bslotframe2 << std::endl;
std::cout << pmid1 << " " << pmid2 << " " << pmid3 << " " << pmid4 << std::endl;
std::cout << scinid1 << " " << scinid2 << std::endl;
    
    return true;
}

bool JPetScopeConfigParser::createOutputFileNames(const std::string &configFileName, const int position)
{
  std::string starting_loc  = path(configFileName).parent_path().string();
	  starting_loc += "/";
	  starting_loc += filesLocation;
	  starting_loc += "/";
	  starting_loc += std::to_string(position);

  path current_dir(starting_loc);
  std::string prefix = pmData.front().prefix;
  boost::regex pattern(Form("%s_\\d*.txt", prefix.c_str()));
std::cout << "current_dir= " << current_dir << std::endl;	  
  if (exists(current_dir))
  {
std::cout << "if" << std::endl;
    for (recursive_directory_iterator iter(current_dir), end; iter != end; ++iter) 
    {
      std::string name = iter->path().leaf().string();
std::cout << "name= " << name << std::endl;
      std::string dir = "";
      if (regex_match(name, pattern)) 
      {
	name[1] = prefix[1];
	dir = iter->path().parent_path().string();
	dir += "/";
	dir += name;
	//(*current_config).pFiles.insert(dir);
	outputFileNames.push_back(dir);
std::cout << "dir= " << dir << std::endl;
      }
    }
  }
  else 
  {
    std::string msg  = "Directory: \"";
    msg += current_dir.string();
    msg += "\" does not exist.";
std::cout << "msg= " << msg << std::endl;
    ERROR(msg.c_str());
  }
  return true;
}

bool JPetScopeConfigParser::readData(const std::string &configFileName)
{
  ptree propTree;

  
  std::string configFileExtension = path(configFileName).extension().string();
/// wk mozna zostawic tylko json, inne nie ma sensu ?
  if(configFileExtension.compare(".json") == 0) 
  {
    read_json(configFileName, propTree);
  }
  else 
  {
    ERROR("Cannot open config file. Exiting");
  /// wk exit(-1) to trzeba inaczej obsluzyc a nie exit(-1)
  // np. zwrocic boola i sprawdzic w funkcjach powyzej
  // 
    return false;
  }
  
  for(ptree::const_iterator it = propTree.begin(); it != propTree.end(); ++it) 
  {
    //string files_location;
    
    const ptree& conf_data = it->second;
    
    //files_location = conf_data.get<string>("location");
    getFilesLocation(conf_data);
    
    createParamObject(conf_data);
    
    if(fileName.empty())
    {
      fileName = it->first;
//std::cout << "fileName= " << fileName << std::endl;
    }

    std::string collimatorFunction = "";
    int a = 0, b = 0, c = 0, n = 0;
    
    BOOST_FOREACH(const ptree::value_type& v, conf_data.get_child("collimator")) 
    {
      if(configFileExtension.compare(".json") == 0) 
      {
	collimatorFunction = v.second.get<std::string>("positions");
      }
      else 
      {
	collimatorFunction = v.second.data();
      }

      n = sscanf(collimatorFunction.c_str(), "%d %d %d", &a, &b, &c);

      if(n > 0) 
      {
        if(n == 1) {b = a; c = 1;}
	if(n == 2) {c = 1;}
	
	for(int j = a; j <=b; j+= c) 
	{
	  positions.emplace_back(j);
//std::cout << "pCollPosition= " << j << std::endl;
	  
	  createOutputFileNames(configFileName, j);
	}
      }
    }
  }
  return true;
}
