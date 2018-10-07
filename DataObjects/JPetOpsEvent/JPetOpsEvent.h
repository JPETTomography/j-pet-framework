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
 *  @file JPetOpsEvent.h
 *  @brief Class representing an event from a single o-Ps->3g annihilation.
 */

#ifndef JPETOPSEVENT_H
#define JPETOPSEVENT_H

#include "./JPetEvent/JPetEvent.h"

/**
 * @brief Data class representing an event from a single o-Ps->3g annihilation.
 *
 * Extends JPetEvent to contain the reconstructed annihilation point and time.
 */

class JPetOpsEvent : public JPetEvent
{

public:
  JPetOpsEvent();
  JPetOpsEvent(const JPetEvent& event);
  JPetOpsEvent(const std::vector<JPetHit>& hits, JPetEventType eventType = JPetEventType::kUnknown, bool orderedByTime = true);

  void Clear(Option_t * opt = "");

  void setAnnihilationPoint(double x, double y, double z);
  void setAnnihilationPoint(const TVector3& point);
  void setAnnihilationTime(double t);
  
  const TVector3& getAnnihilationPoint() const;
  double getAnnihilationTime() const;
  
protected:

  TVector3 fAnnihilationPoint;
  double fAnnihilationTime;
  
  ClassDef(JPetOpsEvent, 1);
};
#endif /*  !JPETOPSEVENT_H */
