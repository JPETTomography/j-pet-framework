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
 *  @file JPetParamUtils.h
 */

#ifndef JPETPARAMUTILS_H
#define JPETPARAMUTILS_H

#include "./JPetBarrelSlot/JPetBarrelSlot.h"
#include "./JPetLayer/JPetLayer.h"
#include "./JPetLoggerInclude.h"
#include "./JPetPM/JPetPM.h"
#include "TMath.h"

/**
 * @brief Helper class to calculate several things based on parameter objects.
 * @todo Add tests for this class. Any.
 */
class JPetParamUtils
{
public:
  static double distanceXY(const JPetBarrelSlot& slot1, const JPetBarrelSlot& slot2);
  static double distanceXY(const JPetPM& PM1, const JPetPM& PM2);

private:
  JPetParamUtils(const JPetParamUtils&) {}
  void operator=(const JPetParamUtils&) {}
};

#endif /* !JPETPARAMUTILS_H */
