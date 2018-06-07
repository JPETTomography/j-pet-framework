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
 *  @file JPetEvent.cpp
 */

#include "./JPetAnalysisTools/JPetAnalysisTools.h"
#include "./JPetEvent.h"

ClassImp(JPetEvent);

JPetEvent::JPetEvent(): TObject() {}

JPetEvent::JPetEvent(const std::vector<JPetHit>& hits,
  JPetEventType eventType, bool orderedByTime): TObject(), fType(eventType)
{
  setHits(hits, orderedByTime);
}

/**
 * Set the whole vector of hits to this event, with boolean argument
 * to decide if hits should additionally be ordered by time.
 */
void JPetEvent::setHits(const std::vector<JPetHit>& hits, bool orderedByTime)
{
  if (orderedByTime) {
    fHits = JPetAnalysisTools::getHitsOrderedByTime(hits);
  } else {
    fHits = hits;
  }
}

/**
 * Adding hit to the event, this method does not sort nor order added hits by time.
 */
void JPetEvent::addHit(const JPetHit& hit)
{
  fHits.push_back(hit);
}

/**
 * Get vector of hits from this event.
 */
const std::vector<JPetHit>& JPetEvent::getHits() const
{
  return fHits;
}

/**
 * Get all the event types.
 */
JPetEventType JPetEvent::getEventType() const
{
  return fType;
}

/**
 * Setting the type, that can be a combination of several types, set like:
 * setEventType(JPetEventType::kGamma2|JPetEventType::kScattered)
 */
void JPetEvent::setEventType(JPetEventType type)
{
  fType = type;
}

/**
 * Check if the event is of a given type. Event can belong to more than one category.
 */
bool JPetEvent::isTypeOf(JPetEventType type) const
{
  return (fType & type) == type;
}

/**
 * Check if the event is of only given type e.g. isOnlyTypeOf(k2Gamma).
 * It will return false if the type is k2Gamma|kScattered.
 */
bool JPetEvent::isOnlyTypeOf(JPetEventType type) const
{
  return fType == type;
}

/**
* AddEventType adds the next event type to existing types e.g.
* if type is set to k2Gamma and we call event.addEventType(kPrompt),
* the type will be set to k2Gamma|K2Prompt. If the event type was only kUnknown,
* it is reset to the new type.
*/
void JPetEvent::addEventType(JPetEventType type)
{
  if (isOnlyTypeOf(JPetEventType::kUnknown)) {
    setEventType(type);
  } else {
    fType = static_cast<JPetEventType>(fType | type);
  }
}

void JPetEvent::Clear(Option_t *){
  fType = kUnknown;
  fHits.clear();
}
