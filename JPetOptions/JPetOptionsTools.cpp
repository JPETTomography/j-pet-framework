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
#include "../JPetOptions/JPetOptions.h"
#include "../JPetCommonTools/JPetCommonTools.h"
#include "../JPetLoggerInclude.h"
#include "../JPetOptionsGenerator/JPetOptionsTypeHandler.h"
#include <typeinfo>

namespace pt = boost::property_tree;

namespace jpet_options_tools
{
// const std::string kFileWithAllowedOptionType= "allowedUserOptionTypes.json";

bool createConfigFileFromOptions(const Options& options, const std::string& outFile)
{
  pt::ptree optionsTree;
  for (auto & entry : options)
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
      //std::vector<std::string> allowedTypes = { "int", "std::string", "bool", "std::vector<std::string>", "std::vector<int>"};
      JPetOptionsTypeHandler typeHandler(kFileWithAllowedOptionType);
     // std::cout << "After creating object of typeHandler"<< std::endl;
      for (auto & item : optionsTree) {
      //  std::cout << "Option tree: "<< item.first << std::endl;
        auto key = item.first;
        std::string typeOfOption = typeHandler.getTypeOfOption(key);
        if(std::find(typeHandler.getAllowedTypes().begin(), typeHandler.getAllowedTypes().end(), typeOfOption) != typeHandler.getAllowedTypes().end()){
          if(typeOfOption == "int"){
            auto value = item.second.get_value<int>();
      //      std::cout << "value: "<< value << std::endl;
            mapOptions.insert(std::make_pair(key, value));
          }
          else if(typeOfOption == "std::string"){
            auto value = item.second.get_value<std::string>();
      //      std::cout << "value: "<< value << std::endl;
            mapOptions.insert(std::make_pair(key, value));
          }
          else if(typeOfOption == "float"){
            auto value = item.second.get_value<float>();
      //      std::cout << "value: "<< value << std::endl;
            mapOptions.insert(std::make_pair(key, value));
          }
          else if(typeOfOption == "double"){
            auto value = item.second.get_value<double>();
      //      std::cout << "value: "<< value << std::endl;
            mapOptions.insert(std::make_pair(key, value));
          }
          else if(typeOfOption == "bool"){
            auto value = item.second.get_value<bool>();
      //      std::cout << "value: "<< value << std::endl;
            mapOptions.insert(std::make_pair(key, value));
          }
          else if(typeOfOption == "std::vector<std::string>"){
            std::vector<std::string> values;
            for(pt::ptree::value_type & value : optionsTree.get_child(key)){
    //          std::cout << "value: "<< value.second.get_value<std::string>() << std::endl;
              values.push_back(value.second.get_value<std::string>());
            }
            mapOptions.insert(std::make_pair(key, values));
           }
          else if(typeOfOption == "std::vector<int>"){
            std::vector<int> values;
            for(pt::ptree::value_type & value : optionsTree.get_child(key)){
    //          std::cout << "value: "<< value.second.get_value<int>() << std::endl;
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
}
