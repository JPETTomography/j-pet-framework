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
 *  @file JPetGeomMapping.h
 */

#ifndef JPETGEOMMAPPING_H
#define JPETGEOMMAPPING_H
#include <cstddef>
#include <vector>
#include <map>
#include "../JPetLayer/JPetLayer.h"
#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetParamBank/JPetParamBank.h"
#include "../JPetGeomMappingInterface/JPetGeomMappingInterface.h"

class JPetGeomMapping: public JPetGeomMappingInterface
{
public:
  explicit JPetGeomMapping(const JPetParamBank& paramBank);
  virtual ~JPetGeomMapping();
  virtual const size_t getLayersCount()const override;
  virtual const size_t getLayerNumber(const JPetLayer& layer)const override;
  virtual const size_t getSlotsCount(const JPetLayer& layer)const override;
  virtual const size_t getSlotsCount(const size_t layer)const override;
  virtual const size_t getSlotNumber(const JPetBarrelSlot& slot) const override;
  virtual const StripPos getStripPos(const JPetBarrelSlot& slot) const override;
  virtual const std::vector<size_t> getLayersSizes() const override;
  const size_t calcDeltaID(const JPetBarrelSlot& slot1, const JPetBarrelSlot& slot2) const;
  const size_t calcGlobalPMTNumber(const JPetPM& pmt) const;
  static const size_t kBadLayerNumber;
  static const size_t kBadSlotNumber;
private:
  std::map<double, int> fRadiusToLayer;
  std::vector<std::map<double, int> > fThetaToSlot;
  std::vector<int> fNumberOfSlotsInLayer;
};

#endif /*  !JPETGEOMMAPPING_H */
