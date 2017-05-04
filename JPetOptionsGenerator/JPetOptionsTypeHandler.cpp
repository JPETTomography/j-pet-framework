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

JPetOptionsTypeHandler::JPetOptionsTypeHandler(const std::vector<std::string>& allowedTypes):
  fAllowedTypes(allowedTypes)
{ }

///@todo change it to use fAllowedTypes and not typesToSwitch
std::map<std::string, std::string> JPetOptionsTypeHandler::anyMapToStringMap(const std::map<std::string, boost::any>& optionsMap) const
{
  using boost::any_cast;
  std::map<std::string, std::string> newOptionsMap;
  std::map<std::string, optionTypes> typesToSwitch = {{"int", Int}, {"std::string", String}, {"bool", Bool}, {"std::vector<std::string>", VectorString}, {"std::vector<int>", VectorInt}, {"default", Default}};
  for (auto & option : optionsMap) {
    int typeOfOption = typesToSwitch.at(getTypeOfOption(option.first));
    /// @todo change switch to series of if and compare just to allowed types
    /// e.g if(bla == "int") { }
    /// else if(bla == "std::string") etc.
    switch (typeOfOption) {
    case Int:
      newOptionsMap[getNameOfOption(option.first)] = std::to_string(any_cast<int>(optionsMap.at(option.first)));
      break;
    case String:
      newOptionsMap[getNameOfOption(option.first)] = any_cast<std::string>(optionsMap.at(option.first));
      break;
    case Bool:
      if (any_cast<bool>(optionsMap.at(option.first)))
        newOptionsMap[getNameOfOption(option.first)] = "true";
      else
        newOptionsMap[getNameOfOption(option.first)] = "false";
      break;
    case Default:
      newOptionsMap[option.first] = any_cast<std::string>(optionsMap.at(option.first));
      break;
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
