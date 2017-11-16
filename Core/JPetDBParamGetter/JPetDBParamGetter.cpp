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
 *  @file JPetDBParamGetter.cpp
 */

#include "./JPetDBParamGetter.h"
#include <boost/lexical_cast.hpp>
#include <TThread.h>
#include "../DBHandler/HeaderFiles/DBHandler.h"
#include <cstdint>

const std::map<ParamObjectType, std::map<std::string, std::string>> fieldTranslations {
  {
    ParamObjectType::kScintillator,
    {
      {"scintillator_id", "id"},
      {"scintillator_length", "length"},
      {"scintillator_width", "width"},
      {"scintillator_height", "height"}
    }
  },
  {
    ParamObjectType::kPM,
    {
      {"photomultiplier_id", "id"},
      {"hvpmconnection_isrightside", "is_right_side"}
    }
  },
  {
    ParamObjectType::kPMCalib,
    {
      {"pm_calibration_id", "id"},
      {"pm_calibration_name", "name"},
      {"pm_calibration_opthv", "opthv"},
      {"pm_calibration_c2e_1", "c2e1"},
      {"pm_calibration_c2e_2", "c2e2"},
      {"pm_calibration_gainalpha", "gain_alpha"},
      {"pm_calibration_gainbeta", "gain_beta"},
      {"pm_calibration_assignment_id", "assignment_id"},
      {"pm_calibration_assignment_photomuliplier_id", "assignment_photomultiplier_id"}
    }
  },
  {
    ParamObjectType::kBarrelSlot,
    {
      {"slot_id", "id"},
      {"slot_isActive", "active"},
      {"slot_name", "name"},
      {"slot_theta1", "theta1"},
      {"slot_inFrameId", "frame_id"}
    }
  },
  {
    ParamObjectType::kLayer,
    {
      {"layer_id", "id"},
      {"layer_isActive", "active"},
      {"layer_name", "name"},
      {"layer_radius", "radius"}
    }
  },
  {
    ParamObjectType::kFrame,
    {
      {"frame_id", "id"},
      {"frame_isActive", "active"},
      {"frame_status", "status"},
      {"frame_description", "description"},
      {"frame_version", "version"},
      {"frame_creator_id", "creator_id"}
    }
  },
  {
    ParamObjectType::kFEB,
    {
      {"konradboard_id", "id"},
      {"konradboard_isactive", "active"},
      {"konradboard_status", "status"},
      {"konradboard_description", "description"},
      {"konradboard_version", "version"},
      {"konradboard_creator_id", "creator_id"},
      {"time_outputs_per_input", "time_outputs_per_input"},
      {"notime_outputs_per_input", "no_time_outputs_per_input"}
    }
  },
  {
    ParamObjectType::kTRB,
    {
      {"TRB_id", "id"}
    }
  },
  {
    ParamObjectType::kTOMBChannel,
    {
      {"tomb", "channel"},
      {"thr_num", "local_number"},
      {"threshold", "threshold"},
      {"feb_input", "FEB"},
      {"trb_id", "trb_id"},
      {"konradboard_id", "konradboard_id"},
      {"photomultiplier_id", "photomultiplier_id"}
    }
  },
};
const std::map<ParamObjectType, std::string> dbFunctionName {
  {ParamObjectType::kScintillator, "getDataFromScintillators"},
  {ParamObjectType::kPM, "getDataFromPhotoMultipliers"},
  {ParamObjectType::kPMCalib, "getPmCalibration"},
  {ParamObjectType::kBarrelSlot, "getBarrelSlot"},
  {ParamObjectType::kLayer, "getLayer"},
  {ParamObjectType::kFrame, "getFrame"},
  {ParamObjectType::kFEB, "getDataFromKonradBoards"},
  {ParamObjectType::kTRB, "getDataFromTRBs"},
  {ParamObjectType::kTOMBChannel, "getEverythingVsTOMB"},
};
const std::map<ParamObjectType, std::map<ParamObjectType, std::string>> dbRelationFunctionName {
  {
    ParamObjectType::kPM, {
      {ParamObjectType::kFEB, "getKonradBoardsForPhotoMultiplier"},
      {ParamObjectType::kScintillator, "getScintillatorsForPhotoMultiplier"},
      {ParamObjectType::kBarrelSlot, "getbarrelslotforphotomultiplier"}
    }
  },
  {
    ParamObjectType::kFEB, {
      {ParamObjectType::kTRB, "getTRBsForKonradBoard"}
    }
  },
  {
    ParamObjectType::kBarrelSlot, {
      {ParamObjectType::kLayer, "getLayerForBarrelSlot"}
    }
  },
  {
    ParamObjectType::kLayer, {
      {ParamObjectType::kFrame, "getFrameForLayer"}
    }
  },
  {
    ParamObjectType::kScintillator, {
      {ParamObjectType::kBarrelSlot, "getbarrelslotforscintillator"}
    }
  },
};
const std::map<ParamObjectType, std::map<ParamObjectType, std::string>> dbRelationFieldName {
  {
    ParamObjectType::kPM, {
      {ParamObjectType::kFEB, "KonradBoard_id"},
      {ParamObjectType::kScintillator, "Scintillator_id"},
      {ParamObjectType::kBarrelSlot, "hvpmconnection_slot_id"}
    }
  },
  {
    ParamObjectType::kFEB, {
      {ParamObjectType::kTRB, "TRB_id"}
    }
  },
  {
    ParamObjectType::kBarrelSlot, {
      {ParamObjectType::kLayer, "layer_id"}
    }
  },
  {
    ParamObjectType::kLayer, {
      {ParamObjectType::kFrame, "frame_id"}
    }
  },
  {
    ParamObjectType::kScintillator, {
      {ParamObjectType::kBarrelSlot, "slscconnection_slot_id"}
    }
  },
};

std::map<int, std::map<ParamObjectType, ParamObjectsDescriptions>> JPetDBParamGetter::gBasicDataCache;
std::map<int, std::map<ParamObjectType, std::map<ParamObjectType, ParamRelationalData>>> JPetDBParamGetter::gRelationalDataCache;

void JPetDBParamGetter::clearParamCache()
{
  TThread::Lock();
  WARNING("JPetDBParamGetter cached data will be cleared");
  JPetDBParamGetter::gBasicDataCache.clear();
  JPetDBParamGetter::gRelationalDataCache.clear();
  TThread::UnLock();
}

ParamObjectsDescriptions JPetDBParamGetter::getAllBasicData(ParamObjectType type, const int runId)
{
  if (runId < 0) {
    ERROR("Run number is less than 0!");
    return ParamObjectsDescriptions();
  }
  auto& thisCache = gBasicDataCache[runId][type];
  if (thisCache.size() == 0) {
    TThread::Lock();
    std::string runIdS = boost::lexical_cast<std::string>(runId);
    auto dbResult = getDataFromDB(dbFunctionName.at(type), runIdS);
    if (dbResult.size() == 0) {
      printErrorMessageDB(dbFunctionName.at(type), runId);
      return thisCache;
    }
    for (auto row : dbResult) {
      ParamObjectDescription description;
      for (auto& translation : fieldTranslations.at(type)) {
        description[translation.second] = row[translation.first].as<std::string>();
        // Workaround to fix booleans.
        if (description[translation.second] == "t") {
          description[translation.second] = "1";
        }
        if (description[translation.second] == "f") {
          description[translation.second] = "0";
        }
      }
      // Fix id for TOMBChannel
      if (type == ParamObjectType::kTOMBChannel) {
        description["channel"] = boost::lexical_cast<std::string>(JPetParamGetter::getTOMBChannelFromDescription(description["channel"]));
        //The id field is needed for caching
        description["id"] = description["channel"];
      }
      // Workarounds because of missing stuff in DB.
      // Scintillator -- no attenuation_length
      if (type == ParamObjectType::kScintillator) {
        description["attenuation_length"] = "0";
      }
      // TRB -- no type and channel
      if (type == ParamObjectType::kTRB) {
        description["type"] = "0";
        description["channel"] = "0";
      }
      // PM -- probably no description TODO: check
      if (type == ParamObjectType::kPM) {
        description["description"] = "";
      }
      thisCache[boost::lexical_cast<int>(description["id"])] = description;
    }
    TThread::UnLock();
  }
  return thisCache;
}

ParamRelationalData JPetDBParamGetter::getAllRelationalData(ParamObjectType type1, ParamObjectType type2, const int runId)
{
  if (runId < 0) {
    ERROR("Run number is less than 0!");
    return ParamRelationalData();
  }
  auto& thisCache = gRelationalDataCache[runId][type1][type2];
  if (thisCache.size() == 0) {
    TThread::Lock();
    std::string runIdS = boost::lexical_cast<std::string>(runId);
    auto dbResult = getDataFromDB(dbFunctionName.at(type1), runIdS);
    if (dbResult.size() == 0) {
      printErrorMessageDB(dbFunctionName.at(type1), runId);
      return thisCache;
    }
    for (auto row : dbResult) {
      ParamObjectDescription description;
      for (auto& translation : fieldTranslations.at(type1)) {
        description[translation.second] = row[translation.first].as<std::string>();
      }
      if (type1 == ParamObjectType::kTOMBChannel) {
        description["channel"] = boost::lexical_cast<std::string>(JPetParamGetter::getTOMBChannelFromDescription(description["channel"]));
        //The id field is needed for caching
        description["id"] = description["channel"];
        switch (type2) {
        case ParamObjectType::kTRB:
          thisCache[boost::lexical_cast<int>(description["id"])] = boost::lexical_cast<int>(description["trb_id"]);
          break;
        case ParamObjectType::kFEB:
          thisCache[boost::lexical_cast<int>(description["id"])] = boost::lexical_cast<int>(description["konradboard_id"]);
          break;
        case ParamObjectType::kPM:
          thisCache[boost::lexical_cast<int>(description["id"])] = boost::lexical_cast<int>(description["photomultiplier_id"]);
          break;
        default:
          break;
        }
      } else {
        auto dbRelationResult = getDataFromDB(dbRelationFunctionName.at(type1).at(type2), description["id"] + "," + runIdS);
        for (auto relationRow : dbRelationResult) {
          thisCache[boost::lexical_cast<int>(description["id"])] = relationRow[dbRelationFieldName.at(type1).at(type2)].as<int>();
        }
      }
    }
    TThread::UnLock();
  }
  return thisCache;
}

std::string JPetDBParamGetter::generateSelectQuery(const std::string& sqlFun, const std::string& arguments)
{
  std::string sqlQuerry = "SELECT * FROM ";
  sqlQuerry += sqlFun;
  sqlQuerry += "(" + arguments + ");";
  return sqlQuerry;
}

/// @brief method calls the remote PostgreSQL function sqlfunction with the id argument and returns results from database
pqxx::result JPetDBParamGetter::getDataFromDB(const std::string& sqlfunction, const  std::string& arguments)
{
  //std::string l_run_id = boost::lexical_cast<std::string>(id);
  std::string l_sqlQuerry = generateSelectQuery(sqlfunction, arguments);
  DB::SERVICES::DBHandler& l_dbHandlerInstance = DB::SERVICES::DBHandler::getInstance();
  return  l_dbHandlerInstance.querry(l_sqlQuerry);
}

void JPetDBParamGetter::printErrorMessageDB(std::string sqlFunction, int p_run_id)
{
  std::string l_error(sqlFunction);
  l_error += "() query with run_id = ";
  l_error += boost::lexical_cast<std::string>(p_run_id) + " returned 0 records.";
  ERROR(l_error.c_str());
}
