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
 *  @file JPetRecoSignal.cpp
 */

#include "Signals/JPetRecoSignal/JPetRecoSignal.h"

ClassImp(JPetRecoSignal);

JPetRecoSignal::JPetRecoSignal() : JPetBaseSignal(), fFlag(JPetRecoSignal::Unknown) {}

JPetRecoSignal::JPetRecoSignal(JPetRecoSignal::RecoFlag flag) : JPetBaseSignal(), fFlag(flag) {}

JPetRecoSignal::JPetRecoSignal(float time) : JPetBaseSignal(time), fFlag(JPetRecoSignal::Unknown) {}

JPetRecoSignal::JPetRecoSignal(JPetRecoSignal::RecoFlag flag, float time) : JPetBaseSignal(time), fFlag(flag) {}

JPetRecoSignal::~JPetRecoSignal() {}

void JPetRecoSignal::setRecoFlag(JPetRecoSignal::RecoFlag flag) { fFlag = flag; }

JPetRecoSignal::RecoFlag JPetRecoSignal::getRecoFlag() const { return fFlag; }

void JPetRecoSignal::Clear(Option_t*)
{
  JPetBaseSignal::Clear("");
  fFlag = JPetRecoSignal::Unknown;
}
