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
 *  @file JPetMCHit.cpp
 */

#include "./JPetLoggerInclude.h"
#include "./JPetMCHit.h"

ClassImp(JPetMCHit);

JPetMCHit::JPetMCHit() {}

JPetMCHit::JPetMCHit(UInt_t decayTreetId, UInt_t vertexId, float e, float t,
  const TVector3& pos, const TVector3& pol, const TVector3& mom):
  fMCDecayTreeIndex(decayTreetId), fMCVtxIndex(vertexId), fPolarization(pol), fMomentum(mom)
{
  setEnergy(e);
  setTime(t);
  setPos(pos.X(), pos.Y(), pos.Z());
}

UInt_t JPetMCHit::getMCDecayTreeIndex() const
{
  return fMCDecayTreeIndex;
}

UInt_t JPetMCHit::getMCVtxIndex() const
{
  return fMCVtxIndex;
}

const TVector3& JPetMCHit::getPolarization() const
{
  return fPolarization;
}

const TVector3& JPetMCHit::getMomentum() const
{
  return fMomentum;
}

void JPetMCHit::setMCDecayTreeIndex(Int_t dti)
{
  fMCDecayTreeIndex = dti;
}

void JPetMCHit::setMCVtxIndex(Int_t vi)
{
  fMCVtxIndex = vi;
}

void JPetMCHit::setPolarization(Int_t xx, Int_t yy, Int_t zz)
{
  fPolarization.SetXYZ(xx, yy, zz);
}

void JPetMCHit::setMomentum(Float_t dd, Float_t ee, Float_t ff)
{
  fMomentum.SetXYZ(dd, ee, ff);
}
