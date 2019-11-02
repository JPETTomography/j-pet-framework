/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetParamGetterAscii.cpp
 */

#include "JPetParamGetterAscii/JPetParamAsciiConstants.h"
#include "JPetParamGetterAscii/JPetParamGetterAscii.h"
#include <boost/property_tree/json_parser.hpp>
#include "JPetParamBank/JPetParamBank.h"
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

ParamObjectsDescriptions JPetParamGetterAscii::getAllBasicData(ParamObjectType type, const int runID)
{
  std::string runNumberS = boost::lexical_cast<std::string>(runID);
  std::string objectsName = objectsNames.at(type);
  ParamObjectsDescriptions result;
  if (boost::filesystem::exists(fFilename)) {
    boost::property_tree::ptree dataFromFile;
    boost::property_tree::read_json(fFilename, dataFromFile);
    if (auto possibleRunContents = dataFromFile.get_child_optional(runNumberS)) {
      auto runContents = *possibleRunContents;
      if (auto possibleInfos = runContents.get_child_optional(objectsName)) {
        auto infos = * possibleInfos;
        for (auto infoRaw : infos) {
          auto info = infoRaw.second;
          ParamObjectDescription description = toDescription(info);
          int id = boost::lexical_cast<int>(description["id"]);
          result[id] = description;
        }
      } else { ERROR(Form("No %s in the specified run.", objectsName.c_str())); }
    } else { ERROR(Form("No run with such id: %i", runID)); }
  } else { ERROR(Form("Input file does not exist: %s", fFilename.c_str())); }
  return result;
}

ParamRelationalData JPetParamGetterAscii::getAllRelationalData(
  ParamObjectType type1, ParamObjectType type2, const int runID
) {
  std::string runNumberS = boost::lexical_cast<std::string>(runID);
  std::string objectsName = objectsNames.at(type1);
  std::string fieldName = objectsNames.at(type2) + "_id";
  ParamRelationalData result;
  if (boost::filesystem::exists(fFilename)) {
    boost::property_tree::ptree dataFromFile;
    boost::property_tree::read_json(fFilename, dataFromFile);
    if (auto possibleRunContents = dataFromFile.get_child_optional(runNumberS)) {
      auto runContents = *possibleRunContents;
      if (auto possibleInfos = runContents.get_child_optional(objectsName)) {
        auto infos = * possibleInfos;
        for (auto infoRaw : infos) {
          auto info = infoRaw.second;
          ParamObjectDescription description = toDescription(info);
          if (description.count(fieldName)) {
            int id = boost::lexical_cast<int>(description["id"]);
            int otherID = boost::lexical_cast<int>(description[fieldName]);
            result[id] = otherID;
          }
        }
      } else { ERROR(Form("No %s in the specified run.", objectsName.c_str())); }
    } else { ERROR(Form("No run with such id: %i", runID)); }
  } else { ERROR(Form("Input file does not exist: %s", fFilename.c_str())); }
  return result;
}

ParamObjectDescription JPetParamGetterAscii::toDescription(boost::property_tree::ptree& info)
{
  ParamObjectDescription description;
  for (auto value : info) {
    std::string val = value.second.get_value<std::string>();
    description[value.first] = val;
  }
  return description;
}
