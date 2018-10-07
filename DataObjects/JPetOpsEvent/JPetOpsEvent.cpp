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
 *  @file JPetOpsEvent.cpp
 */

#include "./JPetOpsEvent.h"

ClassImp(JPetOpsEvent);

JPetOpsEvent::JPetOpsEvent(): JPetEvent()
{
  /**/
}

JPetOpsEvent::JPetOpsEvent(const JPetEvent& event): JPetEvent(event)
{
  /**/
}

JPetOpsEvent::JPetOpsEvent(const std::vector<JPetHit>& hits, JPetEventType eventType, bool orderedByTime):
  JPetEvent(hits, eventType, orderedByTime)
{
}


void JPetOpsEvent::Clear(Option_t*)
{
  fType = kUnknown;
  fHits.clear();
}

void JPetOpsEvent::setAnnihilationPoint(double x, double y, double z)
{
  setAnnihilationPoint(TVector3(x, y, z));
}

void JPetOpsEvent::setAnnihilationPoint(const TVector3& point)
{
  fAnnihilationPoint = point;
}

const TVector3& JPetOpsEvent::getAnnihilationPoint() const
{
  return fAnnihilationPoint;
}

void JPetOpsEvent::setAnnihilationTime(double t)
{
  fAnnihilationTime = t;
}

double JPetOpsEvent::getAnnihilationTime() const
{
  return fAnnihilationTime;
}
