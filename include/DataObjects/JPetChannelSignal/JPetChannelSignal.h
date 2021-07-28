/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetChannelSignal.h
 */

#ifndef JPETCHANNELSIGNAL_H
#define JPETCHANNELSIGNAL_H

#include "JPetChannel/JPetChannel.h"
#include "JPetLoggerInclude.h"
#include "JPetPM/JPetPM.h"
#include <TClass.h>
#include <TRef.h>
#include <cassert>
#include <vector>

/**
 * @brief Data class representing a Signal from a single TDC Channel.
 *
 * Represents time of signal from one PMT crossing a certain voltage threshold
 * at either leading or trailing edge of the signal.
 */
class JPetChannelSignal : public JPetRecoSignal
{
public:
  enum EdgeType
  {
    Trailing,
    Leading
  };
  // const static double kUnset;

  JPetChannelSignal();
  JPetChannelSignal(EdgeType Edge, double EdgeTime);
  ~JPetChannelSignal();
  void setType(JPetChannelSignal::EdgeType type);
  void setChannel(const JPetChannel& channel);
  JPetChannelSignal::EdgeType getType() const;
  const JPetChannel& getChannel() const;
  // static bool compareByThresholdNumber(const JPetChannelSignal& a, const JPetChannelSignal& b);
  // static bool compareByThresholdValue(const JPetChannelSignal& a, const JPetChannelSignal& b);
  void Clear(Option_t*) override;

private:
  EdgeType fType = JPetChannelSignal::Leading;
  TRef fChannel = nullptr;

  ClassDef(JPetChannelSignal, 1);
};

#endif /* !JPETCHANNELSIGNAL_H */
