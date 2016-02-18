/**
 * @file SDAMatchHits.h
 * @author Szymon Niedzwiecki, szymon.niedzwiecki@googlemail.com
 * @copyright Copyright (c) 2015, Szymon Niedzwiecki
 * @brief Producer of JPetHit objects for SDA signals
 * Reads a TTree of PhysSignals matches the ones with the same TSlot 
 * and joins the ones from the same scintillator into JPetHit object
  */

#ifndef _JPETANALYSISMODULE_SDAMATCHHITS_H_
#define _JPETANALYSISMODULE_SDAMATCHHITS_H_

#include "TCanvas.h"
#include "../../JPetTask/JPetTask.h"
#include "../../JPetHit/JPetHit.h"
#include "../../JPetPhysSignal/JPetPhysSignal.h"
#include <map>

class SDAMatchHits: public JPetTask
{

public:

  SDAMatchHits(const char* name, const char* description);
  virtual ~SDAMatchHits();
  virtual void exec();
  virtual void init(const JPetTaskInterface::Options& /* opts */);
  virtual void terminate();
  
 private:
  std::vector<JPetHit> createHits(std::vector<JPetPhysSignal>& signals);
  void saveHits(std::vector<JPetHit> hits);
  std::vector<JPetHit> matchHitsWithinSlot(std::vector<JPetPhysSignal>);
  
  // put any custom variables (e.g. histograms) here:
  int fMatched;
  int fTSlot;
  int fCurrentEventNumber;
  std::vector<JPetPhysSignal> fSignalsArray;
};

#endif
