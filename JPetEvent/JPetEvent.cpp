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
 *  @file JPetEvent.cpp
 */

#include "./JPetEvent.h"

ClassImp(JPetEvent);

JPetEvent::JPetEvent()
{
  /**/
}

JPetEvent::JPetEvent(float time, float qualityOfTime, const std::vector<JPetHit>& hits):
  fTime(time),
  fQualityOfTime(qualityOfTime),
  fHits(hits)
{
  /**/
}

void JPetEvent::setHits(const std::vector<JPetHit>& hits)
{
  fHits = hits;
}

void JPetEvent::addHit(const JPetHit& hit)
{
  fHits.push_back(hit);
}

void JPetEvent::setTimeAndQuality(float time, float qualityOfTime)
{
  fTime = time;
  fQualityOfTime = qualityOfTime;
}

const std::vector<JPetHit> JPetEvent::getHits() const
{
  return fHits;
}

const std::vector<JPetHit> JPetEvent::getHitsOrderedByTime() const
{
  auto hits = getHits();
  std::sort(hits.begin(), hits.end(),
  [] (const JPetHit & h1, const JPetHit & h2) {
    return h1.getTime() < h2.getTime();
  });
  return hits;
}

float JPetEvent::getTime() const
{
  return fTime;
}

float JPetEvent::getQualityOfTime() const
{
  return fQualityOfTime;
}
