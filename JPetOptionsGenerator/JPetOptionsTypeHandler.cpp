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
 *  @file JPetOptionsTypeHandler.cpp
 */

#include "JPetOptionsTypeHandler.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../JPetCommonTools/JPetCommonTools.h"
#include "../JPetLoggerInclude.h"
namespace pt = boost::property_tree;


JPetOptionsTypeHandler::JPetOptionsTypeHandler(const std::vector<std::string>& allowedTypes): 
  fAllowedTypes(allowedTypes)
{ }

JPetOptionsTypeHandler::JPetOptionsTypeHandler(const std::string& allowedTypes):
  fAllowedTypes(getAllowedTypesFromFile(allowedTypes))
{ }

std::map<std::string, std::string> JPetOptionsTypeHandler::anyMapToStringMap(const std::map<std::string, boost::any>& optionsMap) const
{
  using boost::any_cast;
  std::map<std::string, std::string> newOptionsMap;
  for (auto & option : optionsMap) {
    std::string typeOfOption = getTypeOfOption(option.first);
    if(std::find(fAllowedTypes.begin(), fAllowedTypes.end(), typeOfOption) != fAllowedTypes.end()){
      if(typeOfOption == "int"){
        newOptionsMap[getNameOfOption(option.first)] = std::to_string(any_cast<int>(optionsMap.at(option.first)));
      }
      else if(typeOfOption == "float"){
        newOptionsMap[getNameOfOption(option.first)] = std::to_string(any_cast<float>(optionsMap.at(option.first)));
      }
      else if(typeOfOption == "double"){
        newOptionsMap[getNameOfOption(option.first)] = std::to_string(any_cast<double>(optionsMap.at(option.first)));
      }
      else if(typeOfOption == "std::string"){
        newOptionsMap[getNameOfOption(option.first)] = any_cast<std::string>(optionsMap.at(option.first));
      }
      else if(typeOfOption == "bool"){
        if (any_cast<bool>(optionsMap.at(option.first)))
          newOptionsMap[getNameOfOption(option.first)] = "true";
        else
          newOptionsMap[getNameOfOption(option.first)] = "false";
      }
      else if(typeOfOption == "default"){
        newOptionsMap[option.first] = any_cast<std::string>(optionsMap.at(option.first));
      }
    }
  }
  return newOptionsMap;
}

std::string JPetOptionsTypeHandler::getTypeOfOption(const std::string& nameOfOption) const
{
  std::size_t pos = nameOfOption.find("_");
  if (pos == std::string::npos) {
    return "default";
  }
  return nameOfOption.substr(pos + 1);
}

std::string JPetOptionsTypeHandler::getNameOfOption(const std::string& option) const
{
  std::size_t pos = option.find("_");
  return option.substr(0, pos);
}

std::vector<std::string> JPetOptionsTypeHandler::getAllowedTypes() const
{
  return fAllowedTypes;
}

std::vector<std::string> JPetOptionsTypeHandler::getAllowedTypesFromFile(const std::string& filename)
{
  pt::ptree optionsTree;
  std::vector<std::string> types, emptyTypes;
  if (JPetCommonTools::ifFileExisting(filename)) {
    try {
      pt::read_json(filename, optionsTree);
      for (auto & item : optionsTree) {
        if(item.first == "allowedTypes"){
          for(pt::ptree::value_type & value : optionsTree.get_child(item.first)){
            types.push_back(value.second.get_value<std::string>());
          }
        }
      }
    } catch (pt::json_parser_error) {
      ERROR("ERROR IN READINIG TYPES FROM JSON FILE! FILENAME:" + filename );
      return emptyTypes;
    }
  } else {
    ERROR("JSON TYPES FILE DOES NOT EXIST! FILENAME:" + filename);
  }
  return types;
}