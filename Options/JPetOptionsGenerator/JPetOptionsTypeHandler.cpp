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
 *  @file JPetOptionsTypeHandler.cpp
 */

#include "JPetOptionsTypeHandler.h"
#include "JPetCommonTools/JPetCommonTools.h"
#include "JPetLoggerInclude.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;

std::map<std::string, std::string> JPetOptionsTypeHandler::anyMapToStringMap(const std::map<std::string, boost::any>& optionsMap) {
  using boost::any_cast;
  std::map<std::string, std::string> newOptionsMap;
  for (const auto& option : optionsMap) {
    std::string typeOfOption = getTypeOfOption(option.first);
    switch (getAllowedTypes()[typeOfOption]) {
    case JPetOptionsTypeHandler::kAllowedTypes::kInt:
      newOptionsMap[getNameOfOption(option.first)] = std::to_string(any_cast<int>(option.second));
      break;
    case JPetOptionsTypeHandler::kAllowedTypes::kFloat:
      newOptionsMap[getNameOfOption(option.first)] = std::to_string(any_cast<float>(option.second));
      break;
    case JPetOptionsTypeHandler::kAllowedTypes::kDouble:
      newOptionsMap[getNameOfOption(option.first)] = std::to_string(any_cast<double>(option.second));
      break;
    case JPetOptionsTypeHandler::kAllowedTypes::kString:
      newOptionsMap[getNameOfOption(option.first)] = any_cast<std::string>(option.second);
      break;
    case JPetOptionsTypeHandler::kAllowedTypes::kBool:
      if (any_cast<bool>(option.second))
        newOptionsMap[getNameOfOption(option.first)] = "true";
      else
        newOptionsMap[getNameOfOption(option.first)] = "false";
      break;
    case JPetOptionsTypeHandler::kAllowedTypes::kNoType:
      newOptionsMap[option.first] = any_cast<std::string>(option.second);
      break;
    case JPetOptionsTypeHandler::kAllowedTypes::kVectorString:
      newOptionsMap[option.first] = [&option]() -> std::string {
        std::string result = "[";

        for (const auto& s : any_cast<std::vector<std::string>>(option.second)) {
          result += "\"" + s + "\", ";
        }
        result += "]";
        return result;
      }();
      break;
    case JPetOptionsTypeHandler::kAllowedTypes::kVectorInt:
      newOptionsMap[option.first] = [&option]() -> std::string {
        std::string result = "";
        for (const auto& s : any_cast<std::vector<int>>(option.second)) {
          result += std::to_string(s) + " ";
        }
        return result;
      }();
      break;
    default:
      WARNING("Cant convert " + typeOfOption + " to string map, skipping it");
      break;
    }
  }
  return newOptionsMap;
}

std::string JPetOptionsTypeHandler::getTypeOfOption(const std::string& nameOfOption) {
  std::size_t pos = nameOfOption.rfind("_");
  if (pos == std::string::npos) {
    return "noType";
  }
  return nameOfOption.substr(pos + 1);
}

std::string JPetOptionsTypeHandler::getNameOfOption(const std::string& option) {
  std::size_t pos = option.rfind("_");
  return option.substr(0, pos);
}

std::map<std::string, int> JPetOptionsTypeHandler::getAllowedTypes() {
  static std::map<std::string, int> kAllowedTypesMap;
  if (kAllowedTypesMap.empty()) {
    kAllowedTypesMap["int"] = JPetOptionsTypeHandler::kAllowedTypes::kInt;
    kAllowedTypesMap["std::string"] = JPetOptionsTypeHandler::kAllowedTypes::kString;
    kAllowedTypesMap["std::vector<std::string>"] = JPetOptionsTypeHandler::kAllowedTypes::kVectorString;
    kAllowedTypesMap["std::vector<int>"] = JPetOptionsTypeHandler::kAllowedTypes::kVectorInt;
    kAllowedTypesMap["float"] = JPetOptionsTypeHandler::kAllowedTypes::kFloat;
    kAllowedTypesMap["double"] = JPetOptionsTypeHandler::kAllowedTypes::kDouble;
    kAllowedTypesMap["bool"] = JPetOptionsTypeHandler::kAllowedTypes::kBool;
    kAllowedTypesMap["noType"] = JPetOptionsTypeHandler::kAllowedTypes::kNoType;
  }
  return kAllowedTypesMap;
}
