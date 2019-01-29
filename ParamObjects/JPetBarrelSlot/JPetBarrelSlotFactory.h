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
 *  @file JPetBarrelSlotFactory.h
 */

#ifndef JPET_BARREL_SLOT_FACTORY_H
#define JPET_BARREL_SLOT_FACTORY_H

#include "./JPetParamGetter/JPetParamGetter.h"
#include "./JPetLayer/JPetLayerFactory.h"
#include "JPetBarrelSlot.h"
#include <map>

/**
 * @brief A factory of JPetBarrelSlot objects.
 *
 * This class is able to create JPetBarrelSlot objects using data from the database.
 */
class JPetBarrelSlotFactory
{
public:
  JPetBarrelSlotFactory(JPetParamGetter &paramGetter, int runId, JPetLayerFactory &layerFactory):
    paramGetter(paramGetter), runId(runId), layerFactory(layerFactory), fInitialized(false) {}
  std::map<int, JPetBarrelSlot*>&getBarrelSlots();

private:
  JPetParamGetter &paramGetter;
  const int runId;
  JPetLayerFactory &layerFactory;
  bool fInitialized;
  std::map<int, JPetBarrelSlot*> fBarrelSlots;
  void initialize();
  JPetBarrelSlot* build(ParamObjectDescription data);
};

#endif /* JPET_BARREL_SLOT_FACTORY_H */
