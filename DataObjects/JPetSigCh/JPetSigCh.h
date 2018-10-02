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
 *  @file JPetSigCh.h
 */

#ifndef JPETSIGCH_H
#define JPETSIGCH_H

#include "./JPetTOMBChannel/JPetTOMBChannel.h"
#include "./JPetLoggerInclude.h"
#include "./JPetFEB/JPetFEB.h"
#include "./JPetTRB/JPetTRB.h"
#include "./JPetPM/JPetPM.h"
#include <TClass.h>
#include <cassert>
#include <vector>
#include <TRef.h>

/**
 * @brief Data class representing a Signal from a single tdc Channel.
 *
 * Represents time of signal from one PMT crossing a certain voltage threshold
 * at either leading or trailing edge of the signal.
 */
class JPetSigCh: public TObject
{
public:
  enum RecoFlag { Good, Bad, Unknown };
  enum EdgeType { Trailing, Leading };
  const static float kUnset;

  JPetSigCh();
  JPetSigCh(EdgeType Edge, float EdgeTime);
  ~JPetSigCh();

  JPetSigCh::RecoFlag getRecoFlag() const;
  JPetSigCh::EdgeType getType() const;
  float getValue() const;
  float getThreshold() const;
  unsigned int getThresholdNumber() const;
  int getDAQch() const;
  const JPetPM & getPM() const;
  const JPetFEB & getFEB() const;
  const JPetTRB & getTRB() const;
  const JPetTOMBChannel & getTOMBChannel() const;
  int getChannel() const;
  void setRecoFlag(JPetSigCh::RecoFlag flag);
  void setType(JPetSigCh::EdgeType type);
  void setValue(float value);
  void setThreshold(float thrValue);
  void setThresholdNumber(unsigned int thrNumber);
  void setDAQch(int daqCh);
  void setPM(const JPetPM & pm);
  void setFEB(const JPetFEB & feb);
  void setTRB(const JPetTRB & trb);
  void setTOMBChannel(const JPetTOMBChannel & channel);
  static bool compareByThresholdValue(const JPetSigCh & a, const JPetSigCh & b);
  static bool compareByThresholdNumber(const JPetSigCh & a, const JPetSigCh & b);
  void Clear(Option_t * = "");

private:
  RecoFlag fFlag;
  EdgeType fType;
  float fValue = 0.0f;
  float fThreshold = 0.0f;
  unsigned int fThresholdNumber = 0;
  int fDAQch = 0;
  TRef fPM = NULL;
  TRef fFEB = NULL;
  TRef fTRB = NULL;
  TRef fTOMBChannel = NULL;

  ClassDef(JPetSigCh, 8);
};

#endif /* !JPETSIGCH_H */
