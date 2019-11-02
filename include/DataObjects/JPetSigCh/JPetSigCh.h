/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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

#include "JPetChannel/JPetChannel.h"
#include "JPetLoggerInclude.h"
#include "JPetPM/JPetPM.h"
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
  enum RecoFlag { Good, Corrupted, Unknown };
  enum EdgeType { Trailing, Leading };
  const static float kUnset;

  JPetSigCh();
  JPetSigCh(EdgeType Edge, float EdgeTime);
  ~JPetSigCh();

  void setRecoFlag(JPetSigCh::RecoFlag flag);
  void setType(JPetSigCh::EdgeType type);
  void setTime(float time);
  void setChannel(const JPetChannel& channel);
  JPetSigCh::RecoFlag getRecoFlag() const;
  JPetSigCh::EdgeType getType() const;
  float getTime() const;
  const JPetChannel& getChannel() const;
  static bool compareByThresholdNumber(const JPetSigCh& a, const JPetSigCh& b);
  static bool compareByThresholdValue(const JPetSigCh& a, const JPetSigCh& b);
  void Clear(Option_t * = "");

private:
  RecoFlag fFlag = JPetSigCh::Unknown;
  EdgeType fType = JPetSigCh::Leading;
  float fTime = 0.0f;
  TRef fChannel = NULL;

  ClassDef(JPetSigCh, 10);
};

#endif /* !JPETSIGCH_H */
