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
 *  @file JPetGeantEventPack.h
 */

#ifndef JPETGEANTEVENTPACK_H
#define JPETGEANTEVENTPACK_H

#include <TObject.h>
#include <TVector3.h>
#include <TClonesArray.h>
#include <TBits.h>
#include <JPetGeantScinHits/JPetGeantScinHits.h>
#include <JPetGeantDecayTree/JPetGeantDecayTree.h>
#include <JPetGeantEventInformation/JPetGeantEventInformation.h>


class JPetGeantEventPack : public TObject
{
public:
  JPetGeantEventPack();
  ~JPetGeantEventPack();
  void Clear();


  JPetGeantScinHits* ConstructNextHit();
  JPetGeantDecayTree* ConstructNextDecayTree();

  JPetGeantScinHits* GetHit(int i)
  {
    return dynamic_cast<JPetGeantScinHits*>(fMCHits[i]);
  }
  JPetGeantDecayTree* GetDecayTree(int i)
  {
    return dynamic_cast<JPetGeantDecayTree*>(fMCDecayTrees[i]);
  }

  JPetGeantEventInformation* GetEventInformation()
  {
    return fGenInfo;
  }

  unsigned int GetNumberOfHits() const
  {
    return fHitIndex;
  }
  unsigned int GetNumberOfDecayTrees() const
  {
    return fMCDecayTreesIndex;
  }
  unsigned int GetEventNumber() const
  {
    return fEvtIndex;
  }

  void SetEventNumber(int x)
  {
    fEvtIndex = x;
  }

private:
  TClonesArray fMCHits;
  TClonesArray fMCDecayTrees;
  JPetGeantEventInformation* fGenInfo;

  unsigned int fEvtIndex;
  unsigned int fHitIndex;
  unsigned int fMCDecayTreesIndex;

  ClassDef(JPetGeantEventPack, 2)
};
#endif
