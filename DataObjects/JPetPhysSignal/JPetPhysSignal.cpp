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
 *  @file JPetPhysSignal.cpp
 */

#include "./JPetPhysSignal.h"

ClassImp(JPetPhysSignal);

/**
 * Constructor
 */
JPetPhysSignal::JPetPhysSignal():
  fTime(0), fQualityOfTime(0), fPhe(0), fQualityOfPhe(0) {}

/**
 * Destructor
 */
JPetPhysSignal::~JPetPhysSignal() {}

/**
 * Constructor with is null setting
 */
JPetPhysSignal::JPetPhysSignal(bool isNull): fIsNullObject(isNull) {}

/**
 * Is null check
 */
bool JPetPhysSignal::isNullObject() const
{
   return fIsNullObject;
}

/**
 * Set the Reconstructed Signal object, that this Physical Signal is based on
 */
void JPetPhysSignal::setRecoSignal(const JPetRecoSignal& recoSignal)
{
   fRecoSignal = recoSignal;
   setPM(recoSignal.getPM());
   setBarrelSlot(recoSignal.getBarrelSlot());
}

/**
 * Clear the signals values (set all to zero/null)
 */
void JPetPhysSignal::Clear(Option_t *)
{
  fTime = 0.;
  fQualityOfTime = 0.;
  fPhe = 0.;
  fQualityOfPhe = 0.;
  fRecoSignal = JPetRecoSignal();
}
