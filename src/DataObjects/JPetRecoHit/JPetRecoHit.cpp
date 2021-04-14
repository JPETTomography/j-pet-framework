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
 *  @file JPetRecoHit.cpp
 */

#include "JPetRecoHit/JPetRecoHit.h"

ClassImp(JPetRecoHit);

JPetRecoHit::JPetRecoHit() : JPetBaseHit(), fFlag(JPetRecoHit::Unknown) {}

JPetRecoHit::JPetRecoHit(JPetRecoHit::RecoFlag flag) : JPetBaseHit(), fFlag(flag) {}

JPetRecoHit::~JPetRecoHit() {}

JPetRecoHit::RecoFlag JPetRecoHit::getRecoFlag() const { return fFlag; }

void JPetRecoHit::setRecoFlag(JPetRecoHit::RecoFlag flag) { fFlag = flag; }

void JPetRecoHit::Clear(Option_t*)
{
  JPetBaseHit::Clear("");
  fFlag = JPetRecoHit::Unknown;
}
