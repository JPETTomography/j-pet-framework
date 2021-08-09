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
 *  @file JPetChannelSignal.cpp
 */

#include "Signals/JPetChannelSignal/JPetChannelSignal.h"
#include "JPetLoggerInclude.h"

ClassImp(JPetChannelSignal);

JPetChannelSignal::JPetChannelSignal() : JPetRecoSignal(), fEdge(JPetChannelSignal::Leading) {}

JPetChannelSignal::JPetChannelSignal(EdgeType edge, double time) : JPetRecoSignal(JPetRecoSignal::Unknown, time), fEdge(edge) {}

JPetChannelSignal::JPetChannelSignal(JPetRecoSignal::RecoFlag flag, EdgeType edge, double time) : JPetRecoSignal(flag, time), fEdge(edge) {}

JPetChannelSignal::~JPetChannelSignal() {}

void JPetChannelSignal::setEdgeType(JPetChannelSignal::EdgeType edge) { fEdge = edge; }

void JPetChannelSignal::setChannel(const JPetChannel& channel) { fChannel = const_cast<JPetChannel*>(&channel); }

JPetChannelSignal::EdgeType JPetChannelSignal::getEdgeType() const { return fEdge; }

const JPetChannel& JPetChannelSignal::getChannel() const
{
  if (fChannel.GetObject())
  {
    return static_cast<JPetChannel&>(*(fChannel.GetObject()));
  }
  else
  {
    ERROR("No JPetChannel set, null object will be returned");
    return JPetChannel::getDummyResult();
  }
}

bool JPetChannelSignal::compareByThresholdNumber(std::pair<const JPetChannelSignal, const JPetChannelSignal> pair1,
                                                 std::pair<const JPetChannelSignal, const JPetChannelSignal> pair2)
{
  return pair1.first.getChannel().getThresholdNumber() < pair2.first.getChannel().getThresholdNumber();
}

bool JPetChannelSignal::compareByThresholdValue(std::pair<const JPetChannelSignal, const JPetChannelSignal> pair1,
                                                std::pair<const JPetChannelSignal, const JPetChannelSignal> pair2)
{
  return pair1.first.getChannel().getThresholdValue() < pair2.first.getChannel().getThresholdValue();
}

void JPetChannelSignal::Clear(Option_t*)
{
  JPetRecoSignal::Clear("");
  fEdge = JPetChannelSignal::Leading;
  fChannel = nullptr;
}
