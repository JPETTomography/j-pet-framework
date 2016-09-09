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
 *  @file JPetParamBank.h
 */

#ifndef JPETPARAMBANK_H
#define JPETPARAMBANK_H

#include "../JPetScin/JPetScin.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetPMCalib/JPetPMCalib.h"
#include "../JPetFEB/JPetFEB.h"
#include "../JPetTRB/JPetTRB.h"
#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetLayer/JPetLayer.h"
#include "../JPetFrame/JPetFrame.h"
#include "../JPetTOMBChannel/JPetTOMBChannel.h"

#include "../JPetParamGetter/JPetParamConstants.h"
#include "../JPetLoggerInclude.h"
#include <map>
#include <cassert>

class JPetParamBank: public TObject
{
 public:
  JPetParamBank();
  JPetParamBank(const JPetParamBank& paramBank);
  ~JPetParamBank();
  void clear();

  JPetParamBank(const bool dummy);
  const bool isDummy()const;

  int getSize(ParamObjectType type) const;

  // Scintillators
  inline void addScintillator(JPetScin scintillator) {
    fScintillators[scintillator.getID()] = new JPetScin(scintillator);
  }
  inline const std::map<int, JPetScin*>& getScintillators() const {
    return fScintillators;
  }
  inline JPetScin& getScintillator(int i) const {
    return *(fScintillators.at(i));
  }
  inline int getScintillatorsSize() const {
    return fScintillators.size();
  }

  // PMs
  inline void addPM(JPetPM pm) {
    fPMs[pm.getID()] = new JPetPM(pm);
  }
  inline const std::map<int, JPetPM*>& getPMs() const {
    return fPMs;
  }
  inline JPetPM& getPM(int id) const {
    return *(fPMs.at(id));
  }
  int getPMsSize() const {
    return fPMs.size();
  }

  // PMCalibs
  inline void addPMCalib(JPetPMCalib pmCalib) {
    fPMCalibs[pmCalib.GetId()] = new JPetPMCalib(pmCalib);
  }
  inline const std::map<int, JPetPMCalib*>& getPMCalibs() const {
    return fPMCalibs;
  }
  inline JPetPMCalib& getPMCalib(int i) const {
    return *(fPMCalibs.at(i));
  }
  int getPMCalibsSize() const {
    return fPMCalibs.size();
  }

  // FEBs
  inline void addFEB(JPetFEB feb) {
    fFEBs[feb.getID()] = new JPetFEB(feb);
  }
  inline const std::map<int, JPetFEB*>& getFEBs() const {
    return fFEBs;
  }
  inline JPetFEB& getFEB(int i) const {
    return *(fFEBs.at(i));
  }
  inline int getFEBsSize() const {
    return fFEBs.size();
  }

  // TRBs
  inline void addTRB(JPetTRB trb) {
    fTRBs[trb.getID()] = new JPetTRB(trb);
  }
  inline const std::map<int, JPetTRB*>& getTRBs() const {
    return fTRBs;
  }
  inline JPetTRB& getTRB(int i) const {
    return *(fTRBs.at(i));
  }
  inline int getTRBsSize() const {
    return fTRBs.size();
  }

  // Barrel Slot
  inline void addBarrelSlot(JPetBarrelSlot slot) {
    fBarrelSlots[slot.getID()] = new JPetBarrelSlot(slot);
  }
  inline const std::map<int, JPetBarrelSlot*>& getBarrelSlots() const {
    return fBarrelSlots;
  }
  inline JPetBarrelSlot& getBarrelSlot(int i) const {
    return *(fBarrelSlots.at(i));
  }
  inline int getBarrelSlotsSize() const {
    return fBarrelSlots.size();
  }

  // Layer
  inline void addLayer(JPetLayer layer) {
    fLayers[layer.getId()] = new JPetLayer(layer);
  }
  inline const std::map<int, JPetLayer*>& getLayers() const {
    return fLayers;
  }
  inline JPetLayer& getLayer(int i) const {
    return *(fLayers.at(i));
  }
  inline int getLayersSize() const {
    return fLayers.size();
  }

  // Frame
  inline void addFrame(JPetFrame frame) {
    fFrames[frame.getId()] = new JPetFrame(frame);
  }
  inline const std::map<int, JPetFrame*>& getFrames() const {
    return fFrames;
  }
  inline JPetFrame& getFrame(int i) const {
    return *(fFrames.at(i));
  }
  inline int getFramesSize() const {
    return fFrames.size();
  }

  // TOMB Channels
  inline void addTOMBChannel(JPetTOMBChannel tombchannel) {
    fTOMBChannels[tombchannel.getChannel()] = new JPetTOMBChannel(tombchannel);
  }
  inline const std::map<int, JPetTOMBChannel*>& getTOMBChannels() const {
    return fTOMBChannels;
  }
  inline JPetTOMBChannel& getTOMBChannel(int i) const {
    return *(fTOMBChannels.at(i));
  }
  inline int getTOMBChannelsSize() const {
    return fTOMBChannels.size();
  }

 private:
  void operator=(const JPetParamBank&);
  bool fDummy;
  std::map<int, JPetScin*> fScintillators;
  std::map<int, JPetPM*> fPMs;
  std::map<int, JPetPMCalib*> fPMCalibs;
  std::map<int, JPetFEB*> fFEBs;
  std::map<int, JPetTRB*> fTRBs;
  std::map<int, JPetBarrelSlot*> fBarrelSlots;
  std::map<int, JPetLayer*> fLayers;
  std::map<int, JPetFrame*> fFrames;
  std::map<int, JPetTOMBChannel*> fTOMBChannels;
  ClassDef (JPetParamBank, 3);

  template <typename T>
  void copyMapValues(std::map<int, T*>& target, const std::map<int, T*>& source)
  {
      for (auto & c : source) {
          target[c.first] = new T(*c.second);
      }
  }
};

#endif /*  !JPETPARAMBANK_H */
