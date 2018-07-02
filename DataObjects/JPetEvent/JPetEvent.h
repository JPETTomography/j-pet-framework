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
 *  @file JPetEvent.h
 */

#ifndef JPETEVENT_H
#define JPETEVENT_H

#include "./JPetEventType/JPetEventType.h"
#include "./JPetHit/JPetHit.h"
#include <TObject.h>
#include <vector>

/**
 * @brief Data class representing an event, that took place during
 * the measurement with J-PET detector.
 *
 * An event consists of one or more JPetHits, registered in barrel slots.
 * The class constructor and setHits method by default order the hits
 * in the ascending time order. This behaviour can be turned off by
 * the orderedByTime flag. Also, when using addHit method the order
 * is NOT guaranteed anymore. It is the users responsibility to sort it in
 * (or not) during the reconstrution/analysis procedures.
 * The JPetEvent can be flagged with a type (JPetEventType enum),
 * that corresponds to the category of physical process e.g. 2, 3 gamma decay.
 * A given type can be a logical combination of several types by using
 * bit OR operators. This option can be used for instatnce to flag that
 * the final type of the event is yet undecided or it contains hits
 * from several separate physical events.
 */

class JPetEvent: public TObject
{

public:
  JPetEvent();
  JPetEvent(const std::vector<JPetHit>& hits,
    JPetEventType eventType = JPetEventType::kUnknown,
    bool orderedByTime = true);
  const std::vector<JPetHit>& getHits() const;
  void setHits(const std::vector<JPetHit>& hits, bool orderedByTime = true);
  void addHit(const JPetHit& hit);
  JPetEventType getEventType() const;
  void setEventType(JPetEventType type);
  void addEventType(JPetEventType type);
  bool isTypeOf(JPetEventType type) const;
  bool isOnlyTypeOf(JPetEventType type) const;
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
#endif /* !JPETEVENT_H */
