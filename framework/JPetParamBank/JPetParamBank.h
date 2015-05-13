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
#include "../../JPetLoggerInclude.h"
#include <vector>
#include <cassert>

class JPetParamBank: public TObject
{
 public:
  enum ParamObjectType {kScintillator, kPM, kPMCalib, kFEB, kTRB, kTOMBChannel, kBarrelSlot, kLayer, kFrame, SIZE};

  JPetParamBank();
  ~JPetParamBank();
  void clear();


  int getSize(ParamObjectType type) const;
  // Scintillators
  inline void addScintillator(JPetScin& scintillator) {
    fScintillators.push_back(new JPetScin(scintillator));
  }
  inline const std::vector<JPetScin*>& getScintillators() const {
    return fScintillators;
  }
  inline JPetScin& getScintillator(int i) const {
    return *fScintillators[i];
  }
  inline int getScintillatorsSize() const {
    return fScintillators.size();
  }

  // PMs
  inline void addPM(JPetPM& pm) {
    fPMs.push_back(new JPetPM(pm));
  }
  inline const std::vector<JPetPM*>& getPMs() const {
    return fPMs;
  }
  inline JPetPM& getPM(int i) const {
    return *fPMs[i];
  }
  int getPMsSize() const {
    return fPMs.size();
  }

  // PMCalibs
  inline void addPMCalib(JPetPMCalib& pmCalib) {
    fPMCalibs.push_back(new JPetPMCalib(pmCalib));
  }
  inline const std::vector<JPetPMCalib*>& getPMCalibs() const {
    return fPMCalibs;
  }
  inline JPetPMCalib& getPMCalib(int i) const {
    return *fPMCalibs[i];
  }
  int getPMCalibsSize() const {
    return fPMCalibs.size();
  }
  
  // FEBs
  inline void addFEB(JPetFEB& feb) {
    fFEBs.push_back(new JPetFEB(feb));
  }
  inline const std::vector<JPetFEB*>& getFEBs() const {
    return fFEBs;
  }
  inline JPetFEB& getFEB(int i) const {
    return *fFEBs[i];
  }
  inline int getFEBsSize() const {
    return fFEBs.size();
  }

  // TRBs
  inline void addTRB(JPetTRB& trb) {
    fTRBs.push_back(new JPetTRB(trb));
  }
  inline const std::vector<JPetTRB*>& getTRBs() const {
    return fTRBs;
  }
  inline JPetTRB& getTRB(int i) const {
    return *fTRBs[i];
  }
  inline int getTRBsSize() const {
    return fTRBs.size();
  }

  // Barrel Slot
  inline void addBarrelSlot(JPetBarrelSlot& slot) {
    fBarrelSlots.push_back(new JPetBarrelSlot(slot));
  }
  inline const std::vector<JPetBarrelSlot*>& getBarrelSlots() const {
    return fBarrelSlots;
  }
  inline JPetBarrelSlot& getBarrelSlot(int i) const {
    return *fBarrelSlots[i];
  }
  inline int getBarrelSlotsSize() const {
    return fBarrelSlots.size();
  }

  // Layer
  inline void addLayer(JPetLayer& layer) {
    fLayers.push_back(new JPetLayer(layer));
  }
  inline const std::vector<JPetLayer*>& getLayers() const {
    return fLayers;
  }
  inline JPetLayer& getLayer(int i) const {
    return *fLayers[i];
  }
  inline int getLayersSize() const {
    return fLayers.size();
  }
  
  // Frame
  inline void addFrame(JPetFrame& frame) {
    fFrames.push_back(new JPetFrame(frame));
  }
  inline const std::vector<JPetFrame*>& getFrames() const {
    return fFrames;
  }
  inline JPetFrame& getFrame(int i) const {
    return *fFrames[i];
  }
  inline int getFramesSize() const {
    return fFrames.size();
  }
  
  // TOMB Channels
  inline void addTOMBChannel(JPetTOMBChannel& tombchannel) {
    fTOMBChannels.push_back(new JPetTOMBChannel(tombchannel));
  }
  inline const std::vector<JPetTOMBChannel*>& getTOMBChannels() const {
    return fTOMBChannels;
  }
  inline JPetTOMBChannel& getTOMBChannel(int i) const {
    return *fTOMBChannels[i];
  }
  inline int getTOMBChannelsSize() const {
    return fTOMBChannels.size();
  }

 private:
  JPetParamBank(const JPetParamBank&);
  void operator=(const JPetParamBank&);

  std::vector<JPetScin*> fScintillators;
  std::vector<JPetPM*> fPMs;
  std::vector<JPetPMCalib*> fPMCalibs;
  std::vector<JPetFEB*> fFEBs;
  std::vector<JPetTRB*> fTRBs;
  std::vector<JPetBarrelSlot*> fBarrelSlots;
  std::vector<JPetLayer*> fLayers;
  std::vector<JPetFrame*> fFrames;
  std::vector<JPetTOMBChannel*> fTOMBChannels;
  ClassDef (JPetParamBank, 3);
};
#endif /*  !JPETPARAMBANK_H */
