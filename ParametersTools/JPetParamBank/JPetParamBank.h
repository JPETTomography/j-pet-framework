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
 *  @file JPetParamBank.h
 */

#ifndef JPETPARAMBANK_H
#define JPETPARAMBANK_H

#include "./JPetParamGetter/JPetParamConstants.h"
#include "./JPetTOMBChannel/JPetTOMBChannel.h"
#include "./JPetBarrelSlot/JPetBarrelSlot.h"
#include "./JPetLayer/JPetLayer.h"
#include "./JPetFrame/JPetFrame.h"
#include "./JPetScin/JPetScin.h"
#include "./JPetLoggerInclude.h"
#include "./JPetFEB/JPetFEB.h"
#include "./JPetTRB/JPetTRB.h"
#include "./JPetPM/JPetPM.h"
#include <cassert>
#include <map>

class JPetParamBank: public TObject
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
   * Adds scintillator to Param Bank. If the scintillator with the same ID
   * already exists in the Param Bank, the new element will not be added.
   */
  inline void addScintillator(JPetScin scintillator)
  {
    if (fScintillators.insert(std::make_pair(scintillator.getID(), new JPetScin(scintillator))).second == false) {
      WARNING("the scintillator with this id already exists in the ParamBank. It will not be added.");
    }
  }
  inline const std::map<int, JPetScin*>& getScintillators() const
  {
    return fScintillators;
  }
  inline JPetScin& getScintillator(int i) const
  {
    return *(fScintillators.at(i));
  }
  inline int getScintillatorsSize() const
  {
    return fScintillators.size();
  }

  /**
   * Adds photomultipliers(PM) to Param Bank. If the scintillator with the same ID
   * already exists in the Param Bank, the new element will not be added.
   */
  inline void addPM(JPetPM pm)
  {
    if (fPMs.insert(std::make_pair(pm.getID(), new JPetPM(pm))).second == false) {
      WARNING("the pm with this id already exists in the ParamBank. It will not be added.");
    }
  }
  inline const std::map<int, JPetPM*>& getPMs() const
  {
    return fPMs;
  }
  inline JPetPM& getPM(int id) const
  {
    return *(fPMs.at(id));
  }
  int getPMsSize() const
  {
    return fPMs.size();
  }

  /**
   * Adds FEB to Param Bank. If the scintillator with the same ID
   * already exists in the Param Bank, the new element will not be added.
   */
  inline void addFEB(JPetFEB feb)
  {
    if (fFEBs.insert(std::make_pair(feb.getID(), new JPetFEB(feb))).second == false) {
      WARNING("the feb with this id already exists in the ParamBank. It will not be added.");
    }
  }
  inline const std::map<int, JPetFEB*>& getFEBs() const
  {
    return fFEBs;
  }
  inline JPetFEB& getFEB(int i) const
  {
    return *(fFEBs.at(i));
  }
  inline int getFEBsSize() const
  {
    return fFEBs.size();
  }

  /**
   * Adds TRB to Param Bank. If the scintillator with the same ID
   * already exists in the Param Bank, the new element will not be added.
   */
  inline void addTRB(JPetTRB trb)
  {
    if (fTRBs.insert(std::make_pair(trb.getID(), new JPetTRB(trb))).second == false) {
      WARNING("the trb with this id already exists in the ParamBank. It will not be added.");
    }
  }
  inline const std::map<int, JPetTRB*>& getTRBs() const
  {
    return fTRBs;
  }
  inline JPetTRB& getTRB(int i) const
  {
    return *(fTRBs.at(i));
  }
  inline int getTRBsSize() const
  {
    return fTRBs.size();
  }

  /**
   * Adds BarrelSlot to Param Bank. If the scintillator with the same ID
   * already exists in the Param Bank, the new element will not be added.
   */
  inline void addBarrelSlot(JPetBarrelSlot slot)
  {
    if (fBarrelSlots.insert(std::make_pair(slot.getID(), new JPetBarrelSlot(slot))).second == false) {
      WARNING("the barrelslot with this id already exists in the ParamBank. It will not be added.");
    }
  }
  inline const std::map<int, JPetBarrelSlot*>& getBarrelSlots() const
  {
    return fBarrelSlots;
  }
  inline JPetBarrelSlot& getBarrelSlot(int i) const
  {
    return *(fBarrelSlots.at(i));
  }
  inline int getBarrelSlotsSize() const
  {
    return fBarrelSlots.size();
  }

  /**
   * Adds Layer to Param Bank. If the scintillator with the same ID
   * already exists in the Param Bank, the new element will not be added.
   */
  inline void addLayer(JPetLayer layer)
  {
    if (fLayers.insert(std::make_pair(layer.getID(), new JPetLayer(layer))).second == false) {
      WARNING("the layer with this id already exists in the ParamBank. It will not be added.");
    }
  }
  inline const std::map<int, JPetLayer*>& getLayers() const
  {
    return fLayers;
  }
  inline JPetLayer& getLayer(int i) const
  {
    return *(fLayers.at(i));
  }
  inline int getLayersSize() const
  {
    return fLayers.size();
  }

  /**
   * Adds Frame to Param Bank. If the scintillator with the same ID
   * already exists in the Param Bank, the new element will not be added.
   */
  inline void addFrame(JPetFrame frame)
  {
    if (fFrames.insert(std::make_pair(frame.getID(), new JPetFrame(frame))).second == false) {
      WARNING("the frame with this id already exists in the ParamBank. It will not be added.");
    }
  }
  inline const std::map<int, JPetFrame*>& getFrames() const
  {
    return fFrames;
  }
  inline JPetFrame& getFrame(int i) const
  {
    return *(fFrames.at(i));
  }
  inline int getFramesSize() const
  {
    return fFrames.size();
  }

  /**
   * Adds TOMB to Param Bank. If the scintillator with the same ID
   * already exists in the Param Bank, the new element will not be added.
   */
  inline void addTOMBChannel(JPetTOMBChannel tombchannel)
  {
    if (fTOMBChannels.insert(std::make_pair(tombchannel.getChannel(), new JPetTOMBChannel(tombchannel))).second == false) {
      WARNING("the tombchannel with this id already exists in the ParamBank. It will not be added.");
    }
  }
  inline const std::map<int, JPetTOMBChannel*>& getTOMBChannels() const
  {
    return fTOMBChannels;
  }
  inline JPetTOMBChannel& getTOMBChannel(int i) const
  {
    return *(fTOMBChannels.at(i));
  }
  inline int getTOMBChannelsSize() const
  {
    return fTOMBChannels.size();
  }

private:
  void operator=(const JPetParamBank&);
  bool fDummy;
  std::map<int, JPetTOMBChannel*> fTOMBChannels;
  std::map<int, JPetBarrelSlot*> fBarrelSlots;
  std::map<int, JPetScin*> fScintillators;
  std::map<int, JPetLayer*> fLayers;
  std::map<int, JPetFrame*> fFrames;
  std::map<int, JPetFEB*> fFEBs;
  std::map<int, JPetTRB*> fTRBs;
  std::map<int, JPetPM*> fPMs;

  template <typename T>
  void copyMapValues(std::map<int, T*>& target, const std::map<int, T*>& source)
  {
    for (auto& c : source) {
      target[c.first] = new T(*c.second);
    }
  }

  ClassDef (JPetParamBank, 4);

};

#endif /* !JPETPARAMBANK_H */
