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
 *  @file JPetParamBank.h
 */

#ifndef JPETPARAMBANK_H
#define JPETPARAMBANK_H

#include "JPetChannel/JPetChannel.h"
#include "JPetDataModule/JPetDataModule.h"
#include "JPetDataSource/JPetDataSource.h"
#include "JPetLayer/JPetLayer.h"
#include "JPetLoggerInclude.h"
#include "JPetMatrix/JPetMatrix.h"
#include "JPetPM/JPetPM.h"
#include "JPetParamGetter/JPetParamConstants.h"
#include "JPetScin/JPetScin.h"
#include "JPetSetup/JPetSetup.h"
#include "JPetSlot/JPetSlot.h"
#include <cassert>
#include <map>

class JPetParamBank : public TObject
{
public:
  JPetParamBank();
  JPetParamBank(const JPetParamBank& paramBank);
  JPetParamBank(const bool dummy);
  ~JPetParamBank();
  bool isDummy() const;
  void clear();
  int getSize(ParamObjectType type) const;

  /**
   * Adds a Setup to Param Bank. If a Setup with the same ID
   * already exists in the Param Bank, the new element will not be added.
   */
  inline void addSetup(JPetSetup setup)
  {
    if (!fSetups.insert(std::make_pair(setup.getID(), new JPetSetup(setup))).second)
    {
      WARNING("A Setup with this ID already exists in the ParamBank. It will not be added.");
    }
  }
  inline const std::map<int, JPetSetup*>& getSetups() const { return fSetups; }
  inline JPetSetup& getSetup(int i) const { return *(fSetups.at(i)); }
  inline int getSetupsSize() const { return fSetups.size(); }

  /**
   * Adds a Layer to Param Bank. If a Layer with the same ID
   * already exists in the Param Bank, the new element will not be added.
   */
  inline void addLayer(JPetLayer layer)
  {
    if (!fLayers.insert(std::make_pair(layer.getID(), new JPetLayer(layer))).second)
    {
      WARNING("A Layer with this ID already exists in the ParamBank. It will not be added.");
    }
  }
  inline const std::map<int, JPetLayer*>& getLayers() const { return fLayers; }
  inline JPetLayer& getLayer(int i) const { return *(fLayers.at(i)); }
  inline int getLayersSize() const { return fLayers.size(); }

  /**
   * Adds a Slot to Param Bank. If a Slot with the same ID
   * already exists in the Param Bank, the new element will not be added.
   */
  inline void addSlot(JPetSlot slot)
  {
    if (!fSlots.insert(std::make_pair(slot.getID(), new JPetSlot(slot))).second)
    {
      WARNING("A Slot with this ID already exists in the ParamBank. It will not be added.");
    }
  }
  inline const std::map<int, JPetSlot*>& getSlots() const { return fSlots; }
  inline JPetSlot& getSlot(int i) const { return *(fSlots.at(i)); }
  inline int getSlotsSize() const { return fSlots.size(); }

  /**
   * Adds a Scin to Param Bank. If a Scin with the same ID
   * already exists in the Param Bank, the new element will not be added.
   */
  inline void addScin(JPetScin scin)
  {
    if (!fScins.insert(std::make_pair(scin.getID(), new JPetScin(scin))).second)
    {
      WARNING("A Scin with this ID already exists in the ParamBank. It will not be added.");
    }
  }
  inline const std::map<int, JPetScin*>& getScins() const { return fScins; }
  inline JPetScin& getScin(int i) const { return *(fScins.at(i)); }
  inline int getScinsSize() const { return fScins.size(); }

  /**
   * Adds a Matrix of photomultipiers to Param Bank. If a Matrix with the same ID
   * already exists in the Param Bank, the new element will not be added.
   */
  inline void addMatrix(JPetMatrix mtx)
  {
    if (!fMatrices.insert(std::make_pair(mtx.getID(), new JPetMatrix(mtx))).second)
    {
      WARNING("A Matrix with this ID already exists in the ParamBank. It will not be added.");
    }
  }
  inline const std::map<int, JPetMatrix*>& getMatrices() const { return fMatrices; }
  inline JPetMatrix& getMatrix(int id) const { return *(fMatrices.at(id)); }
  int getMatricesSize() const { return fMatrices.size(); }

  /**
   * Adds a PM to Param Bank. If a PM with the same ID
   * already exists in the Param Bank, the new element will not be added.
   */
  inline void addPM(JPetPM pm)
  {
    if (!fPMs.insert(std::make_pair(pm.getID(), new JPetPM(pm))).second)
    {
      WARNING("A PM with this ID already exists in the ParamBank. It will not be added.");
    }
  }
  inline const std::map<int, JPetPM*>& getPMs() const { return fPMs; }
  inline JPetPM& getPM(int id) const { return *(fPMs.at(id)); }
  int getPMsSize() const { return fPMs.size(); }

  /**
   * Adds a Channel to Param Bank. If a Channel with the same ID
   * already exists in the Param Bank, the new element will not be added.
   */
  inline void addChannel(JPetChannel channel)
  {
    if (!fChannels.insert(std::make_pair(channel.getID(), new JPetChannel(channel))).second)
    {
      WARNING("A Channel with this ID already exists in the ParamBank. It will not be added.");
    }
  }
  inline const std::map<int, JPetChannel*>& getChannels() const { return fChannels; }
  inline JPetChannel& getChannel(int i) const { return *(fChannels.at(i)); }
  inline int getChannelsSize() const { return fChannels.size(); }

  Int_t Write(const char* name, Int_t option, Int_t bufsize) const { return TObject::Write(name, option, bufsize); }
  Int_t Write(const char* name, Int_t option, Int_t bufsize) { return ((const JPetParamBank*)this)->Write(name, option, bufsize); }

  /**
   * Adds Data Source to Param Bank. If the data source with the same ID
   * already exists in the Param Bank, the new element will not be added.
   */
  inline void addDataSource(JPetDataSource dataSource)
  {
    if (fDataSources.insert(std::make_pair(dataSource.getID(), new JPetDataSource(dataSource))).second == false)
    {
      WARNING("The Data Source with this id already exists in the ParamBank. It will not be added.");
    }
  }
  inline const std::map<int, JPetDataSource*>& getDataSources() const { return fDataSources; }
  inline JPetDataSource& getDataSource(int i) const { return *(fDataSources.at(i)); }
  inline int getDataSourcesSize() const { return fDataSources.size(); }

  /**
   * Adds Data Module to Param Bank. If the data source with the same ID
   * already exists in the Param Bank, the new element will not be added.
   */
  inline void addDataModule(JPetDataModule dataModule)
  {
    if (fDataModules.insert(std::make_pair(dataModule.getID(), new JPetDataModule(dataModule))).second == false)
    {
      WARNING("The Data Module with this id already exists in the ParamBank. It will not be added.");
    }
  }
  inline const std::map<int, JPetDataModule*>& getDataModules() const { return fDataModules; }
  inline JPetDataModule& getDataModule(int i) const { return *(fDataModules.at(i)); }
  inline int getDataModulesSize() const { return fDataModules.size(); }

private:
  void operator=(const JPetParamBank&);
  bool fDummy;
  std::map<int, JPetSetup*> fSetups;
  std::map<int, JPetLayer*> fLayers;
  std::map<int, JPetSlot*> fSlots;
  std::map<int, JPetScin*> fScins;
  std::map<int, JPetMatrix*> fMatrices;
  std::map<int, JPetPM*> fPMs;
  std::map<int, JPetChannel*> fChannels;
  std::map<int, JPetDataSource*> fDataSources;
  std::map<int, JPetDataModule*> fDataModules;

  template <typename T>
  void copyMapValues(std::map<int, T*>& target, const std::map<int, T*>& source)
  {
    for (auto& c : source)
    {
      target[c.first] = new T(*c.second);
    }
  }

  ClassDef(JPetParamBank, 8);
};

#endif /* !JPETPARAMBANK_H */
