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
 *  @file JPetRawMCHit.cpp
 */

#include "JPetRawMCHit/JPetRawMCHit.h"
#include "JPetLoggerInclude.h"

ClassImp(JPetRawMCHit);

JPetRawMCHit::JPetRawMCHit() : JPetBaseHit() {}

JPetRawMCHit* JPetRawMCHit::clone() const { return new JPetRawMCHit(*this); }

int JPetRawMCHit::getMCDecayTreeIndex() const { return fMCDecayTreeIndex; }

int JPetRawMCHit::getMCVtxIndex() const { return fMCVtxIndex; }

const TVector3& JPetRawMCHit::getPolarization() const { return fPolarization; }

const TVector3& JPetRawMCHit::getMomentum() const { return fMomentum; }

int JPetRawMCHit::getGammaTag() const { return fGammaTag; }

void JPetRawMCHit::setMCDecayTreeIndex(int decayTreeIndex) { fMCDecayTreeIndex = decayTreeIndex; }

void JPetRawMCHit::setMCVtxIndex(int vertexIndex) { fMCVtxIndex = vertexIndex; }

void JPetRawMCHit::setPolarization(float polX, float polY, float polZ) { fPolarization.SetXYZ(polX, polY, polZ); }

void JPetRawMCHit::setPolarization(const TVector3& polarization) { fPolarization = polarization; }

void JPetRawMCHit::setMomentum(float momX, float momY, float momZ) { fMomentum.SetXYZ(momX, momY, momZ); }

void JPetRawMCHit::setMomentum(const TVector3& momentum) { fMomentum = momentum; }

void JPetRawMCHit::setGammaTag(int i) { fGammaTag = i; }

void JPetRawMCHit::Clear(Option_t*)
{
  JPetBaseHit::Clear("");
  fMCDecayTreeIndex = 0;
  fMCVtxIndex = 0;
  fGammaTag = 0;
  fPolarization = TVector3();
  fMomentum = TVector3();
}
