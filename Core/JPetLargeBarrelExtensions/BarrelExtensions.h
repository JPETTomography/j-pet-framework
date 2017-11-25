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
 *  @file BarrelExtensions.h
 */

#ifndef _LARGE_BARREL_EXTENSIONS_
#define _LARGE_BARREL_EXTENSIONS_

#include <map>
#include <vector>
#include <string>
#include "./JPetGeomMappingInterface/JPetGeomMappingInterface.h"
#include "./JPetHit/JPetHit.h"
#include "./JPetUserTask/JPetUserTask.h"
#include "PetDict.h"
const std::string Layer(const size_t layer);
const std::string LayerSlot(const size_t layer, const size_t slot);
inline const std::string LayerSlot(const StripPos& pos)
{
  return LayerSlot(pos.layer, pos.slot);
}
const std::string LayerSlotThr(const size_t layer, const size_t slot, const size_t thr);

class LargeBarrelMapping: public JPetGeomMappingInterface
{
public:
  LargeBarrelMapping(const JPetParamBank& paramBank);
  virtual ~LargeBarrelMapping();
  virtual size_t getLayersCount()const override;
  virtual size_t getLayerNumber(const JPetLayer& layer)const override;
  virtual size_t getSlotsCount(const JPetLayer& layer)const override;
  virtual size_t getSlotsCount(const size_t layer)const override;
  virtual size_t getSlotNumber(const JPetBarrelSlot& slot) const override;
  size_t calcDeltaID(const JPetBarrelSlot& slot1, const JPetBarrelSlot& slot2) const;
  size_t calcGlobalPMTNumber(const JPetPM& pmt) const;
  const StripPos getStripPos(const JPetBarrelSlot& slot) const;
  const std::vector<size_t> getLayersSizes()const;
private:
  std::vector<double> fRadii;
  std::vector<std::vector<double>> fTheta;
};

class LargeBarrelTask: public JPetUserTask
{
protected:
  LargeBarrelTask(const char* name);
public:
  virtual ~LargeBarrelTask();
  virtual bool init()override;
protected:
  const std::shared_ptr<LargeBarrelMapping>map()const;
private:
  std::shared_ptr<LargeBarrelMapping>fBarrelMap;
};

struct TOTs {
  double A[4], B[4];
};

inline std::istream& operator>>(std::istream& str, TOTs& item)
{
  return str >> item.A[0] >> item.A[1] >> item.A[2] >> item.A[3]
         >> item.B[0] >> item.B[1] >> item.B[2] >> item.B[3];
}

inline std::ostream& operator<<(std::ostream& str, const TOTs& item)
{
  return str << item.A[0] << " " << item.A[1] << " " << item.A[2] << " " << item.A[3] << " "
         << item.B[0] << " " << item.B[1] << " " << item.B[2] << " " << item.B[3] << " ";
}

class TOT_Hists: public LargeBarrelTask
{
protected:
  TOT_Hists(const char* name);
public:
  virtual ~TOT_Hists();
  virtual bool init()override;
  //virtual void init(const JPetTaskInterface::Options& opts)override;
protected:
  void createTOTHistos(const std::string& suffix, const size_t bins, const double min, const double max);
  void fillTOTHistos(const JPetHit& hit, const std::string& suffix);
  const TOTs getTOTs(const JPetHit& hit)const;
};

#endif
