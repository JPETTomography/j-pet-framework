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
 *  @file JPetParamUtils.h
 *  @brief Helper class to calculate several things based on parameter objects.
 */

#ifndef JPETPARAMUTILS_H
#define JPETPARAMUTILS_H

#include "./JPetBarrelSlot/JPetBarrelSlot.h"
#include "./JPetPM/JPetPM.h"
#include "./JPetLayer/JPetLayer.h"
#include "./JPetLoggerInclude.h"
#include "TMath.h"

class JPetParamUtils
{
public:
  /**
     @brief Function for calculation distance between two barrel slots in XY plane (perpendicular to strips) based on JPetBarrelSlot objects
   **/
  static double distanceXY(const JPetBarrelSlot& slot1, const JPetBarrelSlot& slot2);

  /**
     @brief Function for calculation distance between two photomultipliers  in XY plane (perpendicular to strips) based on JPetPM object

     It does not take into account photomultipliers side of the barrel. For photomultipliers from different sides the function calculate the distance as if they were at the same side (only XY plane).
  **/
  static double distanceXY(const JPetPM& PM1, const JPetPM& PM2);

private:
  JPetParamUtils(const JPetParamUtils&) {}
  void operator=(const JPetParamUtils&) {}
};

#endif /*  !JPETPARAMUTILS_H */
