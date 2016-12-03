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
#include <TNamed.h>
#include <vector>

/**
 * @brief Data class representing an event from a single emission.
 *
 * An event consists of one or more  hits (JPetHit objects) registered in barel slots.
 * The appropriate time order of the hits is not guaranteed! Special methods are provided for it.
 */
class JPetEvent : public TNamed
{

public:
  JPetEvent();
  JPetEvent(float time, float qualityOfTime, const std::vector<JPetHit>& hits);

  void setHits(const std::vector<JPetHit>& hits);
  void addHit(const JPetHit& hit);
  void setTimeAndQuality(float time, float qualityOfTime);
  const std::vector<JPetHit> getHits() const;
  /// Returns the vector of hits ordered by the hit time. Ascending time.
  const std::vector<JPetHit> getHitsOrderedByTime() const;
  float getTime() const;
  float getQualityOfTime() const;

  ClassDef(JPetEvent, 1);

private:
  float fTime = 0.0f; /// < reconstructed absolute time of the event wrt to beginning of the run [ps]
  float fQualityOfTime = 0.0f;
  std::vector<JPetHit> fHits;

};
#endif /*  !JPETEVENT_H */
