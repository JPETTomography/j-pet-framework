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
#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetGeomMappingInterface/JPetGeomMappingInterface.h"
#include "../JPetLayer/JPetLayer.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetParamBank/JPetParamBank.h"
#include <cstddef>
#include <map>
#include <vector>

class JPetGeomMapping : public JPetGeomMappingInterface
{
public:
  static const size_t kBadLayerNumber;
  static const size_t kBadSlotNumber;

  static void
  printTOMBMapping(const std::map< std::tuple< int, int, JPetPM::Side, int >,
                                   int > &tombMap);

  explicit JPetGeomMapping(const JPetParamBank &paramBank);
  virtual ~JPetGeomMapping();
  virtual size_t getLayersCount() const override;
  virtual size_t getLayerNumber(const JPetLayer &layer) const override;
  virtual size_t getSlotsCount(const JPetLayer &layer) const override;
  virtual size_t getSlotsCount(const size_t layer) const override;
  virtual size_t getSlotNumber(const JPetBarrelSlot &slot)
      const override; /// Slot number within a given layer !!!
  virtual const StripPos getStripPos(const JPetBarrelSlot &slot) const override;
  virtual const std::vector< size_t > getLayersSizes() const override;
  size_t calcDeltaID(const JPetBarrelSlot &slot1,
                     const JPetBarrelSlot &slot2) const;
  size_t calcGlobalPMTNumber(const JPetPM &pmt) const;
  double getRadiusOfLayer(int layer) const;

  /// Function returns a map which reflects the relation:
  /// layer id, barrel slot id, photomultiplier side, threshold -->  TOMB
  /// channel number.
  /// TOMB channel is a unique identifier that corresponds a single front-end
  /// electronic channel or
  /// equivalently a set of parameter objects
  /// Layer-BarrelSlot-Scintillator-PM-threshold.
  /// TOMB channels are used as internal identifiers in internal parameter DB.
  /// The map is created based on the JPetParamBank content.
  /// If any of param objects needed to create the map is not set in
  /// JPetParamBank, the empty map will be returned.
  std::map< std::tuple< int, int, JPetPM::Side, int >, int >
  getTOMBMapping() const;
  int getTOMB(int LayerNr, int slotNr, const JPetPM::Side &side,
              int threshold) const;
  size_t getGlobalSlotNumber(const JPetBarrelSlot &slot) const; /// Slot number
                                                                /// calculated
                                                                /// for all
                                                                /// layers e.g,
                                                                /// 1-48 for
                                                                /// layer 1 and
                                                                /// 49-... for
                                                                /// layers 2 and
                                                                /// so on

private:
  std::map< std::tuple< int, int, JPetPM::Side, int >, int >
  getTOMBMap(const JPetParamBank &bank) const;

  std::map< double, int > fRadiusToLayer;
  std::vector< std::map< double, int > > fThetaToSlot;
  std::vector< int > fNumberOfSlotsInLayer;

  std::map< std::tuple< int, int, JPetPM::Side, int >, int > fTOMBs;
};

#endif /*  !JPETGEOMMAPPING_H */
