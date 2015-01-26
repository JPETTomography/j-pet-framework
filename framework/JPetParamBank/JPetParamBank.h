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
#include <TClonesArray.h>
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
    new (fScintillators[getScintillatorsSize()]) JPetScin(scintillator);
  }
  inline const TClonesArray& getScintillators() const {
    return fScintillators;
  }
  inline JPetScin& getScintillator(int i) const {
    return *((JPetScin*)fScintillators[i]);
  }
  inline int getScintillatorsSize() const {
    return fScintillators.GetEntries();
  }

  // PMs
  inline void addPM(JPetPM& pm) {
    new (fPMs[getPMsSize()]) JPetPM(pm);
  }
  inline const TClonesArray& getPMs() const {
    return fPMs;
  }
  inline JPetPM& getPM(int i) const {
    return *((JPetPM*)fPMs[i]);
  }
  int getPMsSize() const {
    return fPMs.GetEntries();
  }

  // PMCalibs
  inline void addPMCalib(JPetPMCalib& pmCalib) {
    new (fPMCalibs[getPMCalibsSize()]) JPetPMCalib(pmCalib);
  }
  inline const TClonesArray& getPMCalibs() const {
    return fPMCalibs;
  }
  inline JPetPMCalib& getPMCalib(int i) const {
    return *((JPetPMCalib*)fPMCalibs[i]);
  }
  int getPMCalibsSize() const {
    return fPMCalibs.GetEntries();
  }
  
  // FEBs
  inline void addFEB(JPetFEB& kb) {
    new (fFEBs[getFEBsSize()]) JPetFEB(kb);
  }
  inline const TClonesArray& getFEBs() const {
    return fFEBs;
  }
  inline JPetFEB& getFEB(int i) const {
    return *((JPetFEB*)fFEBs[i]);
  }
  inline int getFEBsSize() const {
    return fFEBs.GetEntries();
  }

  // TRBs
  inline void addTRB(JPetTRB& trb) {
    new (fTRBs[getTRBsSize()]) JPetTRB(trb);
  }
  inline const TClonesArray& getTRBs() const {
    return fTRBs;
  }
  inline JPetTRB& getTRB(int i) const {
    return *((JPetTRB*)fTRBs[i]);
  }
  inline int getTRBsSize() const {
    return fTRBs.GetEntries();
  }

  // Barrel Slot
  inline void addBarrelSlot(JPetBarrelSlot& slot) {
    new (fBarrelSlots[getBarrelSlotsSize()]) JPetBarrelSlot(slot);
  }
  inline const TClonesArray& getBarrelSlots() const {
    return fBarrelSlots;
  }
  inline JPetBarrelSlot& getBarrelSlot(int i) const {
    return *((JPetBarrelSlot*)fBarrelSlots[i]);
  }
  inline int getBarrelSlotsSize() const {
    return fBarrelSlots.GetEntries();
  }

  // Layer
  inline void addLayer(JPetLayer& layer) {
    new (fLayers[getLayersSize()]) JPetLayer(layer);
  }
  inline const TClonesArray& getLayers() const {
    return fLayers;
  }
  inline JPetLayer& getLayer(int i) const {
    return *((JPetLayer*)fLayers[i]);
  }
  inline int getLayersSize() const {
    return fLayers.GetEntries();
  }
  
  // Frame
  inline void addFrame(JPetFrame& frame) {
    new (fFrames[getFramesSize()]) JPetFrame(frame);
  }
  inline const TClonesArray& getFrames() const {
    return fFrames;
  }
  inline JPetFrame& getFrame(int i) const {
    return *((JPetFrame*)fFrames[i]);
  }
  inline int getFramesSize() const {
    return fFrames.GetEntries();
  }
  
  // TOMB Channels
  inline void addTOMBChannel(JPetTOMBChannel& tombchannel) {
    new (fTOMBChannels[getTOMBChannelsSize()]) JPetTOMBChannel(tombchannel);
  }
  inline const TClonesArray& getTOMBChannels() const {
    return fTOMBChannels;
  }
  inline JPetTOMBChannel& getTOMBChannel(int i) const {
    return *((JPetTOMBChannel*)fTOMBChannels[i]);
  }
  inline int getTOMBChannelsSize() const {
    return fTOMBChannels.GetEntries();
  }

 private:
  JPetParamBank(const JPetParamBank&);
  void operator=(const JPetParamBank&);

  TClonesArray fScintillators;
  TClonesArray fPMs;
  TClonesArray fPMCalibs;
  TClonesArray fFEBs;
  TClonesArray fTRBs;
  TClonesArray fBarrelSlots;
  TClonesArray fLayers;
  TClonesArray fFrames;
  TClonesArray fTOMBChannels;
  ClassDef (JPetParamBank, 2);
};
#endif /*  !JPETPARAMBANK_H */
