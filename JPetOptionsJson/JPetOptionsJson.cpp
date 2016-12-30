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
 *  @file JPetOptionsJson.cpp
 */

#include "./JPetOptionsJson.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <set>
#include <exception>
#include <iostream>
#include "../JPetLoggerInclude.h"

namespace pt = boost::property_tree;

JPetOptionsJson::JPetOptionsJson(){	
}
static void JPetOptionsJson::createFileFromOptions(const JPetOptions& options){
	JPetOptions::Options optionsToJson = options.getOptions(); 
	pt::ptree optionsTree;
  	for (auto& entry: optionsToJson) 
    		optionsTree.put (entry.first, entry.second);
 	try{
		pt::write_json("options.json", optionsTree); 
	}catch(json_parser_error){
		ERROR("ERROR IN WRITING OPTIONS TO JSON FILE");
	}
}

static JPetOptions JPetOptionsJson::createOptionsFromFile(const std::string& filename){
	pt::ptree optionsTree;
	auto mapOptions = JPetOptions:: getDefaultOptions().getOptions();
	if(JPetCommonTools::ifFileExisting(filename)){
		try{
			pt::read_json(filename, optionsTree);
			for(pt::ptree::const_iterator it = optionsTree.begin(); it != optionsTree.end(); ++it){
				std::string stringIt = it->first;
				mapOptions.at( (stringIt))=optionsTree.get<std::string>(stringIt,0);
			}
		}catch(json_parser_error){
			ERROR("ERROR IN READINIG OPTIONS FROM JSON FILE! Dofault options will be returned" );
		}
	}else{
		ERROR("JSON FILE DO NOT EXISTS! Dofault options will be returned ");
	}
	return JPetOptions( mapOptions);
}
