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
 *  @file BarrelExtensions.cpp
 */

#include <algorithm>
#include <sstream>
#include "BarrelExtensions.h"
using namespace std;

const string Layer(const size_t layer)
{
  return "layer" + to_string(layer);
}
const string LayerSlot(const size_t layer, const size_t slot)
{
  return "layer" + to_string(layer) + "-slot" + to_string(slot);
}
const string LayerSlotThr(const size_t layer, const size_t slot, const size_t thr)
{
  return "layer" + to_string(layer) + "-slot" + to_string(slot) + "-thr" + to_string(thr);
}

const StripPos LargeBarrelMapping::getStripPos(const JPetBarrelSlot& slot)const
{
  return {.layer = getLayerNumber(slot.getLayer()), .slot = getSlotNumber(slot)};
}
const vector< size_t > LargeBarrelMapping::getLayersSizes() const
{
  vector<size_t> res;
  for (size_t i = 1, n = getLayersCount(); i <= n; i++)
    res.push_back(getSlotsCount(i));
  return res;
}
LargeBarrelMapping::LargeBarrelMapping(const JPetParamBank& paramBank)
{
  for (auto & layer : paramBank.getLayers() ) {
    double radius = layer.second->getRadius();
    fRadii.push_back(radius);
    fTheta.push_back(vector<double>());
  }
  sort( fRadii.begin(), fRadii.end(), less<double>() );
  for (const auto & slot : paramBank.getBarrelSlots()) {
    const int layer_number = getLayerNumber( slot.second->getLayer() );
    fTheta[layer_number - 1].push_back(slot.second->getTheta());
  }
  for (auto & thetas : fTheta)
    sort( thetas.begin(), thetas.end(), less<double>() );
}
LargeBarrelMapping::~LargeBarrelMapping() {}
size_t LargeBarrelMapping::getLayersCount() const
{
  return fRadii.size();
}
size_t LargeBarrelMapping::getLayerNumber(const JPetLayer& layer) const
{
  size_t res = 0;
  while (layer.getRadius() != fRadii[res])
    res++;
  return res + 1;
}
size_t LargeBarrelMapping::getSlotsCount(const size_t layer) const
{
  return fTheta[layer - 1].size();
}
size_t LargeBarrelMapping::getSlotsCount(const JPetLayer& layer) const
{
  return fTheta[getLayerNumber(layer) - 1].size();
}
size_t LargeBarrelMapping::getSlotNumber(const JPetBarrelSlot& slot) const
{
  const auto& theta = fTheta[getLayerNumber(slot.getLayer()) - 1];
  size_t res = 0;
  while (slot.getTheta() != theta[res])
    res++;
  return res + 1;
}
size_t LargeBarrelMapping::calcDeltaID(const JPetBarrelSlot& slot1, const JPetBarrelSlot& slot2) const
{
  if (slot1.getLayer().getID() == slot2.getLayer().getID()) {
    auto delta_ID = size_t(abs(int(getSlotNumber(slot1)) - int(getSlotNumber(slot2))));
    auto layer_size = getSlotsCount(slot1.getLayer());
    auto half_layer_size = layer_size / 2;
    if ( delta_ID > half_layer_size ) return layer_size - delta_ID;
    return delta_ID;
  }
  throw Exception<LargeBarrelMapping>("attempt to calc deltaID for strips from different layers");
}
size_t LargeBarrelMapping::calcGlobalPMTNumber(const JPetPM& pmt) const
{
  const size_t number_of_sides = 2;
  const auto layer_number = getLayerNumber(pmt.getBarrelSlot().getLayer());
  size_t pmt_no = 0;
  for (size_t l = 1; l < layer_number; l++)
    pmt_no += number_of_sides * fTheta[l - 1].size();
  const auto slot_number = getSlotNumber(pmt.getBarrelSlot());
  if ( pmt.getSide() == JPetPM::SideB )
    pmt_no += fTheta[layer_number - 1].size();
  pmt_no += slot_number - 1;
  return pmt_no;
}
LargeBarrelTask::LargeBarrelTask(const char* name)
  : JPetUserTask(name) {}
LargeBarrelTask::~LargeBarrelTask() {}

bool LargeBarrelTask::init()
//void LargeBarrelTask::init(const JPetTaskInterface::Options&)
{
  fBarrelMap = make_shared<LargeBarrelMapping>(getParamBank());
  return true;
}

const std::shared_ptr<LargeBarrelMapping>LargeBarrelTask::map() const
{
  return fBarrelMap;
}

bool TOT_Hists::init()
//void TOT_Hists::init(const JPetTaskInterface::Options& opts)
{
  LargeBarrelTask::init();
  return true;
}

TOT_Hists::TOT_Hists(const char* name)
  :
  LargeBarrelTask(name) {}
TOT_Hists::~TOT_Hists() {}
void TOT_Hists::createTOTHistos(const std::string& suffix, const size_t bins, const double min, const double max)
{
  for (auto & layer : getParamBank().getLayers()) {
    const auto ln = map()->getLayerNumber(*layer.second);
    for (size_t sl = 1, n = map()->getSlotsCount(ln); sl <= n; sl++)
      for (size_t thr = 1; thr <= 4; thr++) {
        getStatistics().createHistogram( new TH1F(("TOT-" + LayerSlotThr(ln, sl, thr) + "-A-" + suffix).c_str(), "", bins, min, max));
        getStatistics().createHistogram( new TH1F(("TOT-" + LayerSlotThr(ln, sl, thr) + "-B-" + suffix).c_str(), "", bins, min, max));
      }
  }
}
void TOT_Hists::fillTOTHistos(const JPetHit& hit, const std::string& suffix)
{
  const auto strip1 = map()->getStripPos(hit.getBarrelSlot());
  auto TOTA = hit.getSignalA().getRecoSignal().getRawSignal().getTOTsVsThresholdNumber(),
       TOTB = hit.getSignalB().getRecoSignal().getRawSignal().getTOTsVsThresholdNumber();
  for (size_t thr = 1; thr <= 4; thr++) {
    getStatistics().getHisto1D(("TOT-" + LayerSlotThr(strip1.layer, strip1.slot, thr) + "-A-" + suffix).c_str()).Fill(TOTA[thr]);
    getStatistics().getHisto1D(("TOT-" + LayerSlotThr(strip1.layer, strip1.slot, thr) + "-B-" + suffix).c_str()).Fill(TOTB[thr]);
  }
}

const TOTs TOT_Hists::getTOTs(const JPetHit& hit) const
{
  auto TOTA = hit.getSignalA().getRecoSignal().getRawSignal().getTOTsVsThresholdNumber(),
       TOTB = hit.getSignalB().getRecoSignal().getRawSignal().getTOTsVsThresholdNumber();
  TOTs result;
  for (size_t thr = 1; thr <= 4; thr++) {
    result.A[thr - 1] = TOTA[thr];
    result.B[thr - 1] = TOTB[thr];
  }
  return result;
}

