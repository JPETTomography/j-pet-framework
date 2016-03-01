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
 *  @file PassedInformationMap.h
 */

#ifndef PASSED_INFORMATION_MAP_H
#define PASSED_INFORMATION_MAP_H

#include <utility>
#include "../HeaderFiles/SerializableMap.hpp"


namespace DB
{

namespace DATA
{

typedef int PASSED_INFORMATION_MAP_KEY_TYPE;
typedef bool PASSED_INFORMATION_MAP_VALUE_TYPE;

class PassedInformationMap : public SerializableMap<PASSED_INFORMATION_MAP_KEY_TYPE, PASSED_INFORMATION_MAP_VALUE_TYPE >
{
public:
  PassedInformationMap(SERVICES::DBHandler &l_dBHandler);
  virtual ~PassedInformationMap(void);

  virtual void fillMap(int p_run_id);
  virtual void showMap(void) const;
  virtual boost::optional<PASSED_INFORMATION_MAP_VALUE_TYPE > valueFromMap(PASSED_INFORMATION_MAP_KEY_TYPE p_key);
  virtual void saveMapToFile(std::string p_fileName);
};

} // namespace DATA

} // namespace DB

#endif // PASSED_INFORMATION_MAP_H
