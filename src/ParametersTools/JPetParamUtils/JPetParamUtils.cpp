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
 *  @file JPetParamUtils.cpp
 */

#include "JPetParamUtils/JPetParamUtils.h"

/**
 * Calculate distance between two barrel slots in XY plane,
 * (perpendicular to strips) based on JPetSlot objects
 */
double JPetParamUtils::distanceXY(const JPetSlot& slot1, const JPetSlot& slot2)
{
  double angle = TMath::Abs(slot2.getTheta() - slot1.getTheta());
  double radius1= slot1.getLayer().getRadius();
  double radius2= slot2.getLayer().getRadius();
  double radiusDiff = TMath::Abs(radius1 - radius2);
  if(radiusDiff < 0.01){
    double dist = 2*radius1*TMath::Sin(0.5*angle*TMath::DegToRad());
    return dist;
  } else {
    WARNING(Form("For PMTs with different radius distanceXY() never tested"));
    double dist1 = radius1*TMath::Sin(0.5*angle*TMath::DegToRad());
    double dist2 = radius2*TMath::Sin(0.5*angle*TMath::DegToRad());
    double xDist = dist1+dist2;
    double y1 = radius1*TMath::Cos(0.5*angle*TMath::DegToRad());
    double y2 = radius2*TMath::Cos(0.5*angle*TMath::DegToRad());
    double deltaY = TMath::Abs(y2 - y1);
    double dist = TMath::Sqrt(xDist*xDist + deltaY*deltaY);
    return dist;
  }
}

/**
 * Calculate distance between two barrel slots in XY plane,
 * (perpendicular to strips) based on JPetPM objects
 */
double JPetParamUtils::distanceXY(const JPetPM& pm1, const JPetPM& pm2)
{
  const JPetSlot& slot1 = pm1.getScin().getSlot();
  const JPetSlot& slot2 = pm2.getScin().getSlot();
  return distanceXY(slot1, slot2);
}
