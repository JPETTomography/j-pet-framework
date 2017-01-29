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
 *  @file JPetParamBankTools.h
 */

#ifndef JPETPARAMBANKTOOLS_H
#define JPETPARAMBANKTOOLS_H

#include <vector>
#include "../JPetParamBank/JPetParamBank.h"

/// Set of tools that precomputes some relations between the parameter objects.
class JPetParamBankTools
{
public:
  /// Function returns a map which reflects the relation:
  /// layer id, barrel slot id, photomultiplier side, threshold -->  TOMB channel number.
  /// TOMB channel is a unique identifier that corresponds a single front-end electronic channel or
  /// equivalently a set of parameter objects Layer-BarrelSlot-Scintillator-PM-threshold.
  /// TOMB channels are used as internal identifiers in internal parameter DB.
  /// The map is created based on the JPetParamBank content.
  /// If any of param objects needed to create the map is not set in JPetParamBank, the empty map will be returned.
  static std::map<std::tuple<int, int, JPetPM::Side, int>, int> getTOMBMap(const JPetParamBank& bank);
private:
  JPetParamBankTools(const JPetParamBankTools&);
  JPetParamBankTools& operator=(const JPetParamBankTools&);

};
#endif /*  !JPETPARAMBANKTOOLS_H */
