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
#include "JPetPM/JPetPM.h"
#include "Signals/JPetRecoSignal/JPetRecoSignal.h"
#include <TRef.h>

/**
 * @brief Data class representing a Signal from a single TDC Channel.
 *
 * Represents time of signal from one PMT crossing a certain voltage threshold
 * at either leading or trailing edge.
 */
class JPetChannelSignal : public JPetRecoSignal
{
public:
  enum EdgeType
  {
    Trailing,
    Leading
  };

  JPetChannelSignal();
  JPetChannelSignal(EdgeType edge, float time);
  JPetChannelSignal(JPetRecoSignal::RecoFlag flag, EdgeType edge, float time);
  ~JPetChannelSignal();
  void setEdgeType(JPetChannelSignal::EdgeType edge);
  void setChannel(const JPetChannel& channel);
  JPetChannelSignal::EdgeType getEdgeType() const;
  const JPetChannel& getChannel() const;
  static bool compareByThresholdNumber(std::pair<const JPetChannelSignal, const JPetChannelSignal> pair1,
                                       std::pair<const JPetChannelSignal, const JPetChannelSignal> pair2);
  static bool compareByThresholdValue(std::pair<const JPetChannelSignal, const JPetChannelSignal> pair1,
                                      std::pair<const JPetChannelSignal, const JPetChannelSignal> pair2);
  void Clear(Option_t*) override;

private:
  EdgeType fEdge = JPetChannelSignal::Leading;
  TRef fChannel = nullptr;

  ClassDef(JPetChannelSignal, 1);
};

#endif /* !JPETCHANNELSIGNAL_H */
