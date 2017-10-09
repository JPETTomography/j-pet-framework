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
 *  @file JPetEvent.h
 *  @brief Class representing an event from a single emission.
 */

#ifndef JPETEVENT_H
#define JPETEVENT_H

#include "../JPetHit/JPetHit.h"
#include <TObject.h>
#include <vector>
#include "../JPetEventType/JPetEventType.h"

/**
 * @brief Data class representing an event from a single emission.
 *
 * An event consists of one or more  hits (JPetHit objects) registered in barrel slots.
 * The class constructor and setHits by default order hits in the ascending time order.
 * This behaviour can be turned off by the orderedByTime flag.
 * Also, when using addHit method the order is not guaranteed anymore.
 * It Is the user responsability to assure it when using addHit method.
 * The event type corresponds to the category of physical process e.g. 2 gamma or 3 gamma decay
 * A given type can be a logical combination of several types by using bit OR operators
 * e.g. static_cast<JPetEventType>(JPetEventType::kGamma2|JPetEventType::kScattered).
 * This means, that at given moment we don't know to which type it belongs.
 */

class JPetEvent : public TObject
{

public:
  JPetEvent();
  JPetEvent(const std::vector<JPetHit>& hits, JPetEventType eventType = JPetEventType::kUnknown, bool orderedByTime = true);

  std::vector<JPetHit> getHits() const;
  void setHits(const std::vector<JPetHit>& hits, bool orderedByTime = true);
  void addHit(const JPetHit& hit);

  JPetEventType getEventType() const; /// The event type can be a combination of several types
  void setEventType(JPetEventType type);
  /** AddEventType Adds next event type to existing types e.g. if type is set to k2Gamma
  *   and we call event.addEventType(kPrompt) the type will be set to k2Gamma|K2Prompt.
  *   If the event type was only kUnknown then it is reset to the new type
  */
  void addEventType(JPetEventType type);
  bool isTypeOf(JPetEventType type) const; /// check if the event is of a given type. Event can belong to more than one category e.g. k2Gamma|kScattered.
  bool isOnlyTypeOf(JPetEventType type) const;/// check if the event is of only given type e.g. isOnlyTypeOf(k2Gamma) will return false if the type is k2Gamma|kScattered.

  void Clear(Option_t * opt = "");
  
protected:
  std::vector<JPetHit> fHits;
#ifndef __CINT__
  JPetEventType fType = JPetEventType::kUnknown;
#else
  JPetEventType fType;
#endif

  ClassDef(JPetEvent, 4);
};
#endif /*  !JPETEVENT_H */
