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
 *  @file JPetMCRecoHit.cpp
 */

#include "Hits/JPetMCRecoHit/JPetMCRecoHit.h"

ClassImp(JPetMCRecoHit);

JPetMCRecoHit::JPetMCRecoHit() : JPetRecoHit(JPetRecoHit::MC) {}

JPetMCRecoHit::JPetMCRecoHit(int mcIndex) : JPetRecoHit(JPetRecoHit::MC), fMCindex(mcIndex) {}

JPetMCRecoHit::~JPetMCRecoHit() {}

unsigned int JPetMCRecoHit::getMCindex() const { return fMCindex; }

void JPetMCRecoHit::setMCindex(unsigned int i) { fMCindex = i; }

void JPetMCRecoHit::Clear(Option_t*)
{
  JPetRecoHit::Clear("");
  fMCindex = kMCindexError;
  this->setRecoFlag(JPetRecoHit::MC);
}
