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
 *  @file JPetSigCh.cpp
 */

#include "JPetSigCh/JPetSigCh.h"
#include <limits>

ClassImp(JPetSigCh);

const float JPetSigCh::kUnset = std::numeric_limits<float>::infinity();

JPetSigCh::JPetSigCh():
  TObject(), fFlag(JPetSigCh::Unknown), fType(JPetSigCh::Leading), fTime(kUnset) {}

JPetSigCh::JPetSigCh(EdgeType edge, float time):
  TObject(), fFlag(JPetSigCh::Unknown), fType(edge), fTime(time) {}

JPetSigCh::~JPetSigCh(){}

/**
 * Get the reconstruction flag
 */
JPetSigCh::RecoFlag JPetSigCh::getRecoFlag() const
{
  return fFlag;
}

/**
 * Get the edge type
 */
JPetSigCh::EdgeType JPetSigCh::getType() const
{
  return fType;
}

/**
 * Get the value of time in [ps]
 */
float JPetSigCh::getTime() const
{
  return fTime;
}

/**
 * Get the Channel associated with this SigCh
 */
const JPetChannel & JPetSigCh::getChannel() const {
  if(fChannel.GetObject()) {
    return (JPetChannel&) *fChannel.GetObject();
  } else {
    ERROR("No JPetChannel slot set, Null object will be returned");
    return JPetChannel::getDummyResult();
  }
}

/**
 * Set the reconstruction flag with enum
 */
void JPetSigCh::setRecoFlag(JPetSigCh::RecoFlag flag)
{
  fFlag = flag;
}

/**
 * Set the edge type for this Signal Channel
 */
void JPetSigCh::setType(JPetSigCh::EdgeType type)
{
  fType = type;
}

/**
 * Set the time value for this Signal Channel
 */
void JPetSigCh::setTime(float time)
{
  fTime = time;
}

/**
 * Set the Channel associated with this SigCh
 */
void JPetSigCh::setChannel(const JPetChannel & channel)
{
  fChannel = const_cast<JPetChannel*>(&channel);
}

/**
 * Compares two SigChs by their threshold numbers
 */
bool JPetSigCh::compareByThresholdNumber(const JPetSigCh& sigA, const JPetSigCh& sigB)
{
  return sigA.getChannel().getThresholdNumber() < sigB.getChannel().getThresholdNumber();
}

/**
 * Compares two SigChs by their threshold value
 */
bool JPetSigCh::compareByThresholdValue(const JPetSigCh& sigA, const JPetSigCh& sigB)
{
  return sigA.getChannel().getThresholdValue() < sigB.getChannel().getThresholdValue();
}

void JPetSigCh::Clear(Option_t *){
  fType = JPetSigCh::Leading;
  fFlag = JPetSigCh::Unknown;
  fTime = 0.0f;
  fChannel = NULL;
}
