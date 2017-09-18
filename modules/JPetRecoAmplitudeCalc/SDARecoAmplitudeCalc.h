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
 *  @file SDARecoAmplitudeCalc.h
 *  @brief Producer of charge for JPetRecoSignals
 *  Reads a TTree of Reco Signals and calculates charges for each of them.
 *  For more details look into README
 */

#ifndef _JPETANALYSISMODULE_SDAAMPLITIDE_H_
#define _JPETANALYSISMODULE_SDAAMPLITIDE_H_

#include "../../JPetUserTask/JPetUserTask.h"

class SDARecoAmplitudeCalc: public JPetUserTask
{
public:
  SDARecoAmplitudeCalc(const char* name);
  virtual ~SDARecoAmplitudeCalc();
  virtual bool init() override;
  virtual bool exec() override;
  virtual bool terminate() override;
private:
  int fBadSignals;
  int fCurrentEventNumber;
};

#endif

