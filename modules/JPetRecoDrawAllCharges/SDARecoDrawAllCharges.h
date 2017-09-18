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
 *  @file SDARecoDrawAllCharges.h
 *  @brief Draws charges spectra for PMT
 *  Reads a TTree of JPetRecoSignals and fills charge values from PMTs to the histo.
 */

#ifndef _JPETANALYSISMODULE_DRAWALLCHARGES_H_
#define _JPETANALYSISMODULE_DRAWALLCHARGES_H_

#include <map>
#include <TCanvas.h>
#include "../../JPetUserTask/JPetUserTask.h"

class SDARecoDrawAllCharges: public JPetUserTask
{
public:
  SDARecoDrawAllCharges(const char* name);
  virtual ~SDARecoDrawAllCharges();
  virtual bool init() override;
  virtual bool exec()override;
  virtual bool terminate() override;
private:
  std::map<int, TH1F*> fChargeHistos;
  std::map<int, std::vector<double> > fCharges;
  double fCharge;
  std::vector<int> fIDs;
  unsigned int fNumberOfPMTs;
  std::string fFileName;
};
#endif
