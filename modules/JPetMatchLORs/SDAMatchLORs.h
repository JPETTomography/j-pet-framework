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
 *  @file SDAMatchLORs.h
 *  @brief Producer of JPetLOR
 *  Reads a TTree of JPetHit and transforms them into JPetLOR objects
 */

#ifndef _JPETANALYSISMODULE_SDAMATCHLORS_H_
#define _JPETANALYSISMODULE_SDAMATCHLORS_H_

#include <TCanvas.h>
#include "../../JPetUserTask/JPetUserTask.h"
#include "../../JPetLOR/JPetLOR.h"
#include "../../JPetHit/JPetHit.h"

class SDAMatchLORs: public JPetUserTask
{

public:

  SDAMatchLORs(const char* name);
  virtual ~SDAMatchLORs();
  virtual bool init() override;
  virtual bool exec()override;
  virtual bool terminate() override;
private:
  std::vector<JPetLOR> createLORs(std::vector<JPetHit>& hits);
  void saveLORs(std::vector<JPetLOR> lors);
  std::vector<JPetHit> fHitsArray;
  int fTSlot;
  int fMatched;
  int fCurrentEventNumber;
};

#endif
