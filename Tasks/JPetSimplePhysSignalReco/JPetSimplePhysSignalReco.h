/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetSimplePhysSignalReco.h
 */

#ifndef _JPETSIMPLEPHYSSIGNALRECO_H_
#define _JPETSIMPLEPHYSSIGNALRECO_H_

#include "./JPetPhysSignal/JPetPhysSignal.h"
#include "./JPetRecoSignal/JPetRecoSignal.h"
#include "./JPetUserTask/JPetUserTask.h"

class JPetWriter;

class JPetSimplePhysSignalReco: public JPetUserTask
{
public:
  JPetSimplePhysSignalReco();
  virtual ~JPetSimplePhysSignalReco();
  virtual bool exec() override;
  inline int getAlpha() const { return fAlpha; }
  inline float getThresholdSel() const { return fThresholdSel; }
  inline void setAlpha(int val) { fAlpha = val; }
  inline void setThresholdSel(float val) { fThresholdSel = val; }
  void readConfigFileAndSetAlphaAndThreshParams(const char* filename);

private:
  JPetPhysSignal createPhysSignal(JPetRecoSignal& signals);
  void savePhysSignal( JPetPhysSignal signal);
  int fAlpha;
  float fThresholdSel;
};

#endif /* !_JPETSIMPLEPHYSSIGNALRECO_H_ */
