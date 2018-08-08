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
 *  @file JPetGeantEventPack.cpp
 */

#include "JPetGeantEventPack.h"

ClassImp(JPetGeantEventPack)

JPetGeantEventPack::JPetGeantEventPack():
  fMCHits("JPetGeantScinHits", 10000), fMCDecayTrees("JPetGeantDecayTree", 1000),
  fEvtIndex(0), fHitIndex(0), fMCDecayTreesIndex(0)
{
  fGenInfo = new JPetGeantEventInformation();
}

JPetGeantScinHits* JPetGeantEventPack::ConstructNextHit()
{
  return (JPetGeantScinHits*) fMCHits.ConstructedAt(fHitIndex++);
}


JPetGeantDecayTree* JPetGeantEventPack::ConstructNextDecayTree()
{
  return (JPetGeantDecayTree*) fMCDecayTrees.ConstructedAt(fMCDecayTreesIndex++);
}


JPetGeantEventPack::~JPetGeantEventPack()
{
  fMCHits.Clear("C");
  fMCDecayTrees.Clear("C");

  fEvtIndex = 0;
  fHitIndex = 0;
  fMCDecayTreesIndex = 0;

  fGenInfo->Clear();
}

void JPetGeantEventPack::Clear()
{
  fMCHits.Clear("C");
  fMCDecayTrees.Clear("C");

  fEvtIndex = 0;
  fHitIndex = 0;
  fMCDecayTreesIndex = 0;

  fGenInfo->Clear();
}


