/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetSlotFactory.h
 */

#ifndef JPET_SLOT_FACTORY_H
#define JPET_SLOT_FACTORY_H

#include "JPetLayer/JPetLayerFactory.h"
#include "JPetParamGetter/JPetParamGetter.h"
#include "JPetSlot/JPetSlot.h"
#include <map>

/**
 * @brief A factory of JPetSlot objects.
 *
 * This class is able to create JPetSlot objects using data from the database.
 */
class JPetSlotFactory
{
public:
  JPetSlotFactory(JPetParamGetter& paramGetter, int runID, JPetLayerFactory& layerFactory)
      : fParamGetter(paramGetter), fRunID(runID), fLayerFactory(layerFactory), fInitialized(false)
  {
  }
  std::map<int, JPetSlot*>& getSlots();

private:
  JPetParamGetter& fParamGetter;
  const int fRunID;
  JPetLayerFactory& fLayerFactory;
  bool fInitialized;
  std::map<int, JPetSlot*> fSlots;
  void initialize();
  JPetSlot* build(ParamObjectDescription data);
};

#endif /* JPET_BARREL_SLOT_FACTORY_H */
