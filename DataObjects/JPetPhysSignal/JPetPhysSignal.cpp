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
 *  @file JPetPhysSignal.cpp
 */

#include "./JPetPhysSignal.h"

ClassImp(JPetPhysSignal);

JPetPhysSignal::JPetPhysSignal() :
  fTime(0),
  fQualityOfTime(0),
  fPhe(0),
  fQualityOfPhe(0)
{
}


JPetPhysSignal::~JPetPhysSignal()
{ }

JPetPhysSignal::JPetPhysSignal(bool isNull):
  fIsNullObject(isNull)
{}

bool JPetPhysSignal::isNullObject() const
{
   return fIsNullObject;
}
void JPetPhysSignal::setRecoSignal(const JPetRecoSignal& recoSignal){
   fRecoSignal = recoSignal;
   setPM( recoSignal.getPM() );
   setBarrelSlot( recoSignal.getBarrelSlot() );
}

void JPetPhysSignal::Clear(Option_t *){
  fTime = 0.;
  fQualityOfTime = 0.;
  fPhe = 0.; 
  fQualityOfPhe = 0.;
  fRecoSignal = JPetRecoSignal();
}
