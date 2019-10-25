/**
7*  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetGeomMappingInterface.h
 */

#ifndef JPETGEOMMAPPINGINTERFACE_H
#define JPETGEOMMAPPINGINTERFACE_H

#include "./JPetBarrelSlot/JPetBarrelSlot.h"
#include "./JPetLayer/JPetLayer.h"
#include <cstddef>
#include <vector>

struct StripPos {
  size_t layer, slot;
};

/**
 * @brief Interface with methods for Big Barrel Mapping. 
 */
class JPetGeomMappingInterface
{
public:
  virtual const StripPos getStripPos(const JPetBarrelSlot& slot) const = 0;
  virtual size_t getSlotNumber(const JPetBarrelSlot& slot) const = 0;
  virtual size_t getLayerNumber(const JPetLayer& layer) const = 0;
  virtual size_t getSlotsCount(const JPetLayer& layer) const = 0;
  virtual const std::vector<size_t> getLayersSizes() const = 0 ;
  virtual size_t getSlotsCount(const size_t layer) const = 0;
  virtual size_t getLayersCount() const = 0;
};

#endif /* !JPETGEOMMAPPINGINTERFACE_H */
