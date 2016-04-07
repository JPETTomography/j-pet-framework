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
 *  @file ParamData.h
 */

#ifndef PARAM_DATA_H
#define PARAM_DATA_H

#include "../HeaderFiles/ParamServer.h"
#include "../HeaderFiles/TOMBInputMap.h"


namespace DB
{

namespace DATA
{

class ParamData
{
protected:
  SERVER::ParamServer &m_paramServer;

public:
  ParamData(DB::SERVER::ParamServer &p_paramServer);
  ParamData(const ParamData &p_paramData) = delete;             // do przemyslenia!
  ParamData& operator=(const ParamData &p_paramData) = delete;  // do przemyslenia!
  ParamData(ParamData &&p_paramData) = delete;                  // do przemyslenia!
  ParamData& operator=(ParamData &&p_paramData) = delete;       // do przemyslenia!
  virtual ~ParamData(void);

  virtual boost::optional<TOMB_INPUT_MAP_VALUE_TYPE > getTOMBInputIdFromTOMBInputMap(TOMB_INPUT_MAP_KEY_TYPE p_TRBIdAndTRBoutputId) const;
  virtual boost::optional<TOMB_INPUT_MAP_KEY_TYPE > getTRBIdAndTRBoutputIdFromTOMBInputMap(TOMB_INPUT_MAP_VALUE_TYPE p_TOMBInputId) const;
  virtual boost::optional<int> getTRBIdFromTOMBInputMap(TOMB_INPUT_MAP_VALUE_TYPE p_TOMBInputId) const;
  virtual boost::optional<int> getTRBOutputIdFromTOMBInputMap(TOMB_INPUT_MAP_VALUE_TYPE p_TOMBInputId) const;
};

} // namespace DATA

} // namespace DB

#endif // PARAM_DATA_H
