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
#include "../JPetAnalysisTools/JPetAnalysisTools.h"

ClassImp(JPetEvent);

JPetEvent::JPetEvent(): TObject()
{
  /**/
}

JPetEvent::JPetEvent(const std::vector<JPetHit>& hits, JPetEventType eventType, bool orderedByTime):
  TObject(),
  fType(eventType)
{
  setHits(hits, orderedByTime);
}

void JPetEvent::setHits(const std::vector<JPetHit>& hits, bool orderedByTime)
{
  if (orderedByTime) {
    fHits = JPetAnalysisTools::getHitsOrderedByTime(hits);
  } else {
    fHits = hits;
  }
}

void JPetEvent::addHit(const JPetHit& hit)
{
  fHits.push_back(hit);
}

std::vector<JPetHit> JPetEvent::getHits() const
{
  return fHits;
}

JPetEventType JPetEvent::getEventType() const
{
  return fType;
}

void JPetEvent::setEventType(JPetEventType type)
{
  fType = type;
}

bool JPetEvent::isTypeOf(JPetEventType type) const
{
  return (fType & type) == type;
}

bool JPetEvent::isOnlyTypeOf(JPetEventType type) const
{
  return fType == type;
}

void JPetEvent::addEventType(JPetEventType type)
{
  if (isOnlyTypeOf(JPetEventType::kUnknown)) {
    setEventType(type);
  } else {
    fType = static_cast<JPetEventType>(fType | type); /// adding flag to the existing one
  }
}

void JPetEvent::Clear(Option_t *){
  fType = kUnknown;
  fHits.clear();
}
