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
 *  @file JPetHitUtils.h
 */

#ifndef JPETHITUTILS_H
#define JPETHITUTILS_H

#include "./JPetBarrelSlot/JPetBarrelSlot.h"
#include "./JPetLayer/JPetLayer.h"
#include "./JPetLoggerInclude.h"
#include "./JPetHit/JPetHit.h"
#include "./JPetPM/JPetPM.h"
#include <map>

/**
 * @brief Helper class to calculate properties of JPetHit objects.
 */
class JPetHitUtils
{
public:
  static double getTimeDiffAtThr(const JPetHit& hit, int threshold);
  static double getTimeAtThr(const JPetHit& hit, int threshold);
  const static double Unset;

private:
  JPetHitUtils(const JPetHitUtils&){}
  void operator=(const JPetHitUtils&){}
};

#endif /* !JPETHITUTILS_H */
