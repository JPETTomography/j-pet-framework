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

#include <map>
#include <TCanvas.h>
#include "../../JPetUserTask/JPetUserTask.h"
#include "../../JPetHit/JPetHit.h"
#include "../../JPetPhysSignal/JPetPhysSignal.h"

class SDAMatchHits: public JPetUserTask
{
public:
  SDAMatchHits(const char* name);
  virtual ~SDAMatchHits();
  virtual bool init() override;
  virtual bool exec()override;
  virtual bool terminate() override;
private:
  std::vector<JPetHit> createHits(std::vector<JPetPhysSignal>& signals);
  void saveHits(std::vector<JPetHit> hits);
  std::vector<JPetHit> matchHitsWithinSlot(std::vector<JPetPhysSignal>);
  int fMatched;
  int fTSlot;
  int fCurrentEventNumber;
  std::vector<JPetPhysSignal> fSignalsArray;
};

#endif
