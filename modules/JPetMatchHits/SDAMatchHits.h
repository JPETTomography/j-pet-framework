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
 *  @file SDAMatchHits.h
 *  @brief Producer of JPetHit objects for SDA signals
 *  Reads a TTree of PhysSignals matches the ones with the same TSlot 
 *  and joins the ones from the same scintillator into JPetHit object
 */

#ifndef _JPETANALYSISMODULE_SDAMATCHHITS_H_
#define _JPETANALYSISMODULE_SDAMATCHHITS_H_

#include "TCanvas.h"
#include "../../JPetTask/JPetTask.h"
#include "../../JPetHit/JPetHit.h"
#include "../../JPetPhysSignal/JPetPhysSignal.h"
#include "../../JPetWriter/JPetWriter.h"
#include <map>

class SDAMatchHits: public JPetTask
{

public:

  SDAMatchHits(const char* name, const char* description);
  virtual ~SDAMatchHits();
  virtual void exec();
  virtual void init(const JPetTaskInterface::Options& /* opts */);
  virtual void terminate();
  virtual void setWriter(JPetWriter* writer) {
    fWriter = writer;
  }
  
 private:
  std::vector<JPetHit> createHits(std::vector<JPetPhysSignal>& signals);
  void saveHits(std::vector<JPetHit> hits);
  std::vector<JPetHit> matchHitsWithinSlot(std::vector<JPetPhysSignal>);

  JPetWriter* fWriter;
  
  // put any custom variables (e.g. histograms) here:
  int fMatched;
  int fTSlot;
  int fCurrentEventNumber;
  std::vector<JPetPhysSignal> fSignalsArray;
};

#endif
