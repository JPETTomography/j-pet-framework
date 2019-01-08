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
 *  @file JPetGeomMapping.h
 */

#ifndef JPETGEOMMAPPING_H
#define JPETGEOMMAPPING_H
#include "./JPetGeomMappingInterface/JPetGeomMappingInterface.h"
#include "./JPetBarrelSlot/JPetBarrelSlot.h"
#include "./JPetParamBank/JPetParamBank.h"
#include "./JPetLayer/JPetLayer.h"
#include "./JPetPM/JPetPM.h"
#include <cstddef>
#include <vector>
#include <map>

/**
 * @brief Implementation of methods for Big Barrel Mapping.
 *
 * Created mapping is to be used in the analyses for application of various
 * parameters i.e. from calibrations. In general, use only for measurements
 * conducted with the Big Barrel detector.
 */
class JPetGeomMapping : public JPetGeomMappingInterface
{
public:
  explicit JPetGeomMapping(const JPetParamBank &paramBank);
  virtual ~JPetGeomMapping();
  virtual size_t getLayersCount() const override;
  virtual size_t getLayerNumber(const JPetLayer &layer) const override;
  virtual size_t getSlotsCount(const JPetLayer &layer) const override;
  virtual size_t getSlotsCount(const size_t layer) const override;
  virtual size_t getSlotNumber(const JPetBarrelSlot &slot) const override;
  virtual const StripPos getStripPos(const JPetBarrelSlot &slot) const override;
  virtual const std::vector<size_t> getLayersSizes() const override;
  static void printTOMBMapping(
    const std::map<std::tuple<int, int, JPetPM::Side, int>, int> &tombMap);
  std::map<std::tuple<int, int, JPetPM::Side, int>, int> getTOMBMapping() const;
  int getTOMB(int layerNr, int slotNr, const JPetPM::Side &side, int threshold) const;
  double getRadiusOfLayer(int layer) const;
  size_t calcDeltaID(const JPetBarrelSlot &slot1, const JPetBarrelSlot &slot2) const;
  static const size_t kBadLayerNumber;
  static const size_t kBadSlotNumber;

private:
  std::map<std::tuple<int, int, JPetPM::Side, int>, int> getTOMBMap(
    const JPetParamBank &bank) const;
  std::map<std::tuple<int, int, JPetPM::Side, int>, int> fTOMBs;
  std::vector<std::map<double, int>> fThetaToSlot;
  std::vector<int> fNumberOfSlotsInLayer;
  std::map<double, int> fRadiusToLayer;
};

#endif /* !JPETGEOMMAPPING_H */
