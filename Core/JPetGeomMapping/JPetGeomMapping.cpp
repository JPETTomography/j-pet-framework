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

const size_t JPetGeomMapping::kBadLayerNumber = 99999999;
const size_t JPetGeomMapping::kBadSlotNumber = 99999999;

void JPetGeomMapping::printTOMBMapping(
    const std::map< std::tuple< int, int, JPetPM::Side, int >, int > &tombMap)
{
  for (auto &el : tombMap)
  {
    auto key = el.first;
    auto layer = std::get< 0 >(key);
    auto slot = std::get< 1 >(key);
    auto side = std::get< 2 >(key);
    auto threshold = std::get< 3 >(key);
    auto tomb = el.second;
    std::cout << "layer:" << layer << " slot:" << slot << " side:" << side
              << " threshold:" << threshold << " tomb:" << tomb << std::endl;
  }
}

JPetGeomMapping::JPetGeomMapping(const JPetParamBank &paramBank)
{
  vector< double > layersRadii;
  vector< vector< double > > slotsTheta;
  for (auto &layer : paramBank.getLayers())
  {
    double radius = layer.second->getRadius();
    layersRadii.push_back(radius);
    fNumberOfSlotsInLayer.push_back(0);
    map< double, int > slots_map;
    fThetaToSlot.push_back(slots_map);
    vector< double > slots_theta;
    slotsTheta.push_back(slots_theta);
  }
  sort(layersRadii.begin(), layersRadii.end(), less< double >());
  int layer_counter = 1;
  for (const auto &radius : layersRadii)
  {
    fRadiusToLayer[radius] = layer_counter++;
  }
  for (const auto &slot : paramBank.getBarrelSlots())
  {
    int layer_number = getLayerNumber(slot.second->getLayer());
    fNumberOfSlotsInLayer[layer_number - 1]++;
    slotsTheta[layer_number - 1].push_back(slot.second->getTheta());
  }
  vector< int > slotCounters;
  int layerNumber = 1;
  for (auto &thetas : slotsTheta)
  {
    slotCounters.push_back(1);
    sort(thetas.begin(), thetas.end(), less< double >());
    for (const double &theta : thetas)
    {
      fThetaToSlot[layerNumber - 1][theta] = slotCounters[layerNumber - 1]++;
    }
    layerNumber++;
  }
  fTOMBs = getTOMBMap(paramBank);
}

JPetGeomMapping::~JPetGeomMapping() {}

size_t JPetGeomMapping::getLayersCount() const { return fRadiusToLayer.size(); }

size_t JPetGeomMapping::getLayerNumber(const JPetLayer &layer) const
{
  auto radius = layer.getRadius();
  if (fRadiusToLayer.find(radius) != fRadiusToLayer.end())
  {
    return fRadiusToLayer.at(radius);
  }
  else
  {
    ERROR("No layer for radius:" + std::to_string(radius) + " found.");
    return JPetGeomMapping::kBadLayerNumber;
  }
}

size_t JPetGeomMapping::getSlotsCount(const JPetLayer &layer) const
{
  auto layerNr = getLayerNumber(layer);
  if (fNumberOfSlotsInLayer.size() > layerNr)
  {
    return fNumberOfSlotsInLayer.at(layerNr - 1);
  }
  else
  {
    ERROR("No slot counts found for layer:" + std::to_string(layerNr));
    return JPetGeomMapping::kBadLayerNumber;
  }
}

size_t JPetGeomMapping::getSlotsCount(const size_t layerNr) const
{
  if ((fNumberOfSlotsInLayer.size() >= layerNr) && (layerNr > 0))
  {
    return fNumberOfSlotsInLayer.at(layerNr - 1);
  }
  else
  {
    ERROR("No slot counts found for layer:" + std::to_string(layerNr));
    return JPetGeomMapping::kBadSlotNumber;
  }
}

size_t JPetGeomMapping::getSlotNumber(const JPetBarrelSlot &slot) const
{
  auto layerNr = getLayerNumber(slot.getLayer());
  auto theta = slot.getTheta();
  if ((fNumberOfSlotsInLayer.size() < layerNr) || (layerNr <= 0))
  {
    ERROR("No slot counts found for layer:" + std::to_string(layerNr));
    return JPetGeomMapping::kBadSlotNumber;
  }
  auto index = layerNr - 1;
  if (fThetaToSlot.at(index).find(theta) == fThetaToSlot.at(index).end())
  {
    ERROR("No slot number found for theta :" + std::to_string(theta) +
          " in layer:" + std::to_string(layerNr));
    return JPetGeomMapping::kBadSlotNumber;
  }
  return fThetaToSlot.at(index).at(theta);
}

size_t JPetGeomMapping::getGlobalSlotNumber(const JPetBarrelSlot &slot) const
{
  auto layerNr = getLayerNumber(slot.getLayer());
  auto index = layerNr - 1;
  auto previousSlots = 0;
  /// We add all previously defined slots in previous layers
  for (auto i = 0u; i < fNumberOfSlotsInLayer.size(); i++)
  {
    if (index <= i)
      break; /// if we reach our layer
    previousSlots = previousSlots + fNumberOfSlotsInLayer[i];
  }
  auto slotNrInLayer = getSlotNumber(slot);
  if (slotNrInLayer == JPetGeomMapping::kBadSlotNumber)
  {
    return JPetGeomMapping::kBadSlotNumber;
  }
  else
  {
    return previousSlots + getSlotNumber(slot);
  }
}

const StripPos JPetGeomMapping::getStripPos(const JPetBarrelSlot &slot) const
{
  return {.layer = getLayerNumber(slot.getLayer()),
          .slot = getSlotNumber(slot)};
}

const vector< size_t > JPetGeomMapping::getLayersSizes() const
{
  vector< size_t > res;
  for (size_t i = 1, n = getLayersCount(); i <= n; i++)
    res.push_back(getSlotsCount(i));
  return res;
}

size_t JPetGeomMapping::calcDeltaID(const JPetBarrelSlot &slot1,
                                    const JPetBarrelSlot &slot2) const
{
  if (slot1.getLayer().getID() == slot2.getLayer().getID())
  {
    int delta_ID = abs( (int)getSlotNumber(slot1) - (int)getSlotNumber(slot2));
    int layer_size = getSlotsCount(slot1.getLayer());
    int half_layer_size = layer_size / 2;
    if (delta_ID > half_layer_size)
      return layer_size - delta_ID;
    return delta_ID;
  }
  ERROR("attempt to calc deltaID for strips from different layers");
  return -1;
}

size_t JPetGeomMapping::calcGlobalPMTNumber(const JPetPM &pmt) const
{
  return -1;
  const size_t number_of_sides = 2;
  const auto layer_number = getLayerNumber(pmt.getBarrelSlot().getLayer());
  size_t pmt_no = 0;
  for (size_t l = 1; l < layer_number; l++)
    pmt_no += number_of_sides * fThetaToSlot[l - 1].size();
  const auto slot_number = getSlotNumber(pmt.getBarrelSlot());
  if (pmt.getSide() == JPetPM::SideB)
    pmt_no += fThetaToSlot[layer_number - 1].size();
  pmt_no += slot_number - 1;
  return pmt_no;
}

std::map< std::tuple< int, int, JPetPM::Side, int >, int >
JPetGeomMapping::getTOMBMap(const JPetParamBank &bank) const
{
  auto tombChannels = bank.getTOMBChannels();
  std::map< std::tuple< int, int, JPetPM::Side, int >, int > result;
  bool errorOccured = false;
  for (const auto &el : tombChannels)
  {
    assert(el.second);
    assert(el.first == el.second->getChannel());
    auto tomb_id = el.first;
    auto ch = el.second;
    if (!el.second)
    {
      ERROR("No TOMB channel set!");
      errorOccured = true;
      break;
    }
    if (el.first != el.second->getChannel())
    {
      ERROR("Mismatch in TOMB Channel numbering!");
      errorOccured = true;
      break;
    }
    if (ch->getPM().isNullObject() || ch->getPM().getScin().isNullObject() ||
        ch->getPM().getScin().getBarrelSlot().isNullObject() ||
        ch->getPM().getScin().getBarrelSlot().getLayer().isNullObject())
    {
      ERROR("Some parameter object is not set!");
      errorOccured = true;
      break;
    }
    auto threshold = ch->getLocalChannelNumber();
    auto pm_side = ch->getPM().getSide();
    const auto &barrelSlot = ch->getPM().getScin().getBarrelSlot();
    auto LayerNr = getLayerNumber(barrelSlot.getLayer());
    auto barrel_slot_nr = getSlotNumber(barrelSlot);
    result.insert(std::make_pair(
        std::make_tuple(LayerNr, barrel_slot_nr, pm_side, threshold), tomb_id));
  }
  if (errorOccured)
  {
    ERROR(
        "Error occured while generating TOMBMap. Empty map will be returned!");
    std::map< std::tuple< int, int, JPetPM::Side, int >, int > emptyMap;
    return emptyMap;
  }
  else
  {
    return result;
  }
}

std::map< std::tuple< int, int, JPetPM::Side, int >, int >
JPetGeomMapping::getTOMBMapping() const
{
  return fTOMBs;
}

int JPetGeomMapping::getTOMB(int LayerNr, int barrel_slot_nr,
                             const JPetPM::Side &side, int threshold) const
{
  auto key = std::make_tuple(LayerNr, barrel_slot_nr, side, threshold);
  if (fTOMBs.find(key) == fTOMBs.end())
  {
    return -1;
  }
  else
  {
    return fTOMBs.at(key);
  }
}

double JPetGeomMapping::getRadiusOfLayer(int layer) const
{
  for (auto it = fRadiusToLayer.begin(); it != fRadiusToLayer.end(); it++)
  {
    if (it->second == layer)
      return it->first;
  }
  return 0.;
}
