/**
 *  @copyright Copyright (c) 2014, Wojciech Krzemien
 *  @file JPetParamBank.h
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief
 */

#ifndef JPETPARAMBANK_H
#define JPETPARAMBANK_H

#include "../JPetScin/JPetScin.h"
#include "../JPetTRB/JPetTRB.h"
#include "../JPetFEB/JPetFEB.h"
#include "../JPetPM/JPetPM.h"
#include "../JPetPMCalib/JPetPMCalib.h"
#include "../JPetLayer/JPetLayer.h"

#include "../JPetTOMBChannel/JPetTOMBChannel.h"
#include "../JPetLoggerInclude.h"
#include <map>
#include <cassert>

enum ParamObjectType {kScintillator, kPM, kPMCalib, kFEB, kTRB, kTOMBChannel, kBarrelSlot, kLayer, kFrame, SIZE};

class JPetParamBank: public TObject
{
 public:
  JPetParamBank();
  JPetParamBank(const JPetParamBank& paramBank);
  ~JPetParamBank();
  void clear();

  int getSize(ParamObjectType type) const;
  // Scintillators
  inline void addScintillator(JPetScin& scintillator) {
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
  inline void addPM(JPetPM& pm) {
    fPMs[pm.getID()] = new JPetPM(pm);
  }
  inline const std::map<int, JPetPM*>& getPMs() const {
    return fPMs;
  }
  inline JPetPM& getPM(int i) const {
    return *(fPMs.at(i));
  }
  int getPMsSize() const {
    return fPMs.size();
  }

  // PMCalibs
  inline void addPMCalib(JPetPMCalib& pmCalib) {
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
  inline void addFEB(JPetFEB& feb) {
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
  inline void addTRB(JPetTRB& trb) {
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
  inline void addBarrelSlot(JPetBarrelSlot& slot) {
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
  inline void addLayer(JPetLayer& layer) {
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
  inline void addFrame(JPetFrame& frame) {
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
  inline void addTOMBChannel(JPetTOMBChannel& tombchannel) {
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

  static int getTOMBChannelFromDescription(std::string p_desc);

 private:

  void operator=(const JPetParamBank&);

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

/**
 * @brief An interface classes can implement to return JPetParamBank objects.
 */
class JPetParamGetter
{
public:
  virtual JPetParamBank* generateParamBank(const int p_run_id) = 0;
};

#endif /*  !JPETPARAMBANK_H */
