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
 *  @file JPetParamBankTools.cpp
 */

#include "./JPetParamBankTools.h"


std::map<std::tuple<int, int, JPetPM::Side, int>, int> JPetParamBankTools::getTOMBMap(const JPetParamBank& bank)
{
  auto tombChannels = bank.getTOMBChannels();
  std::map<std::tuple<int, int, JPetPM::Side, int>, int> result;
  bool errorOccured = false;
  for (const auto & el : tombChannels) {
    assert(el.second);
    assert(el.first == el.second->getChannel());
    auto tomb_id = el.first;
    auto ch = el.second;
    if (! el.second) {
      ERROR("No TOMB channel set!");
      errorOccured = true;
      break;
    }
    if (el.first != el.second->getChannel()) {
      ERROR("Mismatch in TOMB Channel numbering!");
      errorOccured = true;
      break;
    }
    if (ch->getPM().isNullObject() ||
        ch->getPM().getScin().isNullObject() ||
        ch->getPM().getScin().getBarrelSlot().isNullObject() ||
        ch->getPM().getScin().getBarrelSlot().getLayer().isNullObject()) {
      ERROR("Some parameter object is not set!");
      errorOccured = true;
      break;
    }
    auto threshold = ch->getThreshold();
    auto pm_side = ch->getPM().getSide();
    auto layer_id = ch->getPM().getScin().getBarrelSlot().getLayer().getID();
    auto barrel_slot_id = ch->getPM().getScin().getBarrelSlot().getID();
    result.insert(std::make_pair(std::make_tuple(layer_id, barrel_slot_id, pm_side, threshold), tomb_id));
  }
  if (errorOccured) {
    ERROR("Error occured while generating TOMBMap. Empty map will be returned!");
    std::map<std::tuple<int, int, JPetPM::Side, int>, int> emptyMap;
    return emptyMap;
  } else {
    return result;
  }
}
