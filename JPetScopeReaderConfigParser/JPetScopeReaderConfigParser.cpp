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
 *  @file JPetScopeReaderConfigParser.cpp
 */

/*
 * Temporary help
 * read_json(...)
 * http://www.boost.org/doc/libs/1_55_0/doc/html/boost/property_tree/json_parser/read_json_idp102885800.html
 */

#include "JPetScopeReaderConfigParser.h"
#include "../JPetLoggerInclude.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <cstdio>


using boost::property_tree::ptree;
using namespace boost::filesystem;


JPetScopeReaderConfigParser::JPetScopeReaderConfigParser() : fileName("")
{}

void JPetScopeReaderConfigParser::readData(const string &configFileName)
{
  ptree propTree;

  string configFileExtension = path(configFileName).extension().string();
  
  if(configFileExtension.compare(".ini") == 0) 
  {
    read_ini(configFileName, propTree);
  } 
  else if(configFileExtension.compare(".info") == 0) 
  {
    read_info(configFileName, propTree);
  } 
  else if(configFileExtension.compare(".json") == 0) 
  {
    read_json(configFileName, propTree);
  } 
  else if(configFileExtension.compare(".xml") == 0) 
  {
    read_xml(configFileName, propTree);
  } 
  else 
  {
    ERROR("Cannot open config file. Exiting");
    exit(-1); 
  }
  
  for(ptree::const_iterator it = propTree.begin(); it != propTree.end(); ++it) 
  {
    const ptree& conf_data = it->second;
    
    if(fileName.empty())
    {
      fileName = it->first;
//std::cout << "fileName= " << fileName << std::endl;
    }

    string collimatorFunction = "";
    int a = 0, b = 0, c = 0, n = 0;
    
    BOOST_FOREACH(const ptree::value_type& v, conf_data.get_child("collimator")) 
    {
      if(configFileExtension.compare(".json") == 0) 
      {
	collimatorFunction = v.second.get<string>("positions");
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
	}
      }
    }
  }
}
