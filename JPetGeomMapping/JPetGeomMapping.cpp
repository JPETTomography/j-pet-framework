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
 *  @file JPetGeomMapping.cpp
 */

#include "./JPetGeomMapping.h"

using namespace std;

JPetGeomMapping::JPetGeomMapping(const JPetParamBank& paramBank)
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

JPetGeomMapping::~JPetGeomMapping() {}
const size_t JPetGeomMapping::getLayersCount() const
{
  return fRadii.size();
}
const size_t JPetGeomMapping::getLayerNumber(const JPetLayer& layer) const
{
  size_t res = 0;
  while (layer.getRadius() != fRadii[res])
    res++;
  return res + 1;
}

const size_t JPetGeomMapping::getSlotsCount(const size_t layer) const
{
  return fTheta[layer - 1].size();
}

const size_t JPetGeomMapping::getSlotsCount(const JPetLayer& layer) const
{
  return fTheta[getLayerNumber(layer) - 1].size();
}

const size_t JPetGeomMapping::getSlotNumber(const JPetBarrelSlot& slot) const
{
  const auto& theta = fTheta[getLayerNumber(slot.getLayer()) - 1];
  size_t res = 0;
  while (slot.getTheta() != theta[res])
    res++;
  return res + 1;
}

const StripPos JPetGeomMapping::getStripPos(const JPetBarrelSlot& slot)const
{
  return {.layer = getLayerNumber(slot.getLayer()), .slot = getSlotNumber(slot)};
}

const vector< size_t > JPetGeomMapping::getLayersSizes() const
{
  vector<size_t> res;
  for (size_t i = 1, n = getLayersCount(); i <= n; i++)
    res.push_back(getSlotsCount(i));
  return res;
}

const size_t JPetGeomMapping::calcDeltaID(const JPetBarrelSlot& slot1, const JPetBarrelSlot& slot2) const
{
  if (slot1.getLayer().getID() == slot2.getLayer().getID()) {
    auto delta_ID = size_t(abs(int(getSlotNumber(slot1)) - int(getSlotNumber(slot2))));
    auto layer_size = getSlotsCount(slot1.getLayer());
    auto half_layer_size = layer_size / 2;
    if ( delta_ID > half_layer_size ) return layer_size - delta_ID;
    return delta_ID;
  }
  ERROR("attempt to calc deltaID for strips from different layers");
  return -1;
}

const size_t JPetGeomMapping::calcGlobalPMTNumber(const JPetPM& pmt) const
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
