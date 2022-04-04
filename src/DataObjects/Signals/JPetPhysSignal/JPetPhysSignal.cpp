/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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

#include "Signals/JPetPhysSignal/JPetPhysSignal.h"

ClassImp(JPetPhysSignal);

JPetPhysSignal::JPetPhysSignal() : JPetRecoSignal(), fQualityOfTime(0.0), fPhe(0.0), fQualityOfPhe(0.0) {}

JPetPhysSignal::JPetPhysSignal(float time, float qTime, float phe, float qPhe)
    : JPetRecoSignal(time), fQualityOfTime(qTime), fPhe(phe), fQualityOfPhe(qPhe)
{
}

JPetPhysSignal::~JPetPhysSignal() {}

void JPetPhysSignal::setQualityOfTime(float qualityOfTime) { fQualityOfTime = qualityOfTime; }

void JPetPhysSignal::setPhe(float phe) { fPhe = phe; }

void JPetPhysSignal::setQualityOfPhe(float qualityOfPhe) { fQualityOfPhe = qualityOfPhe; }

float JPetPhysSignal::getQualityOfTime() const { return fQualityOfTime; }

float JPetPhysSignal::getPhe() const { return fPhe; }

float JPetPhysSignal::getQualityOfPhe() const { return fQualityOfPhe; }

void JPetPhysSignal::Clear(Option_t*)
{
  fQualityOfTime = 0.;
  fPhe = 0.;
  fQualityOfPhe = 0.;
  JPetRecoSignal::Clear("");
}
