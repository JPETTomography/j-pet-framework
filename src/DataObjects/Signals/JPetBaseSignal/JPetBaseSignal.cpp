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
 *  @file JPetBaseSignal.cpp
 */

#include "Signals/JPetBaseSignal/JPetBaseSignal.h"

ClassImp(JPetBaseSignal);

JPetBaseSignal::JPetBaseSignal() : TObject(), fTime(0.0) {}

JPetBaseSignal::JPetBaseSignal(bool isNull) : fIsNullObject(isNull) {}

JPetBaseSignal::JPetBaseSignal(double time) : TObject(), fTime(time) {}

JPetBaseSignal::~JPetBaseSignal() {}

void JPetBaseSignal::setTime(double time) { fTime = time; }

const double JPetBaseSignal::getTime() const { return fTime; }

bool JPetBaseSignal::isNullObject() const { return fIsNullObject; }

JPetBaseSignal& JPetBaseSignal::getDummyResult()
{
  static JPetBaseSignal dummyResult(true);
  return dummyResult;
}

void JPetBaseSignal::Clear(Option_t*) { fTime = 0.0; }
