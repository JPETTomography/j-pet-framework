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
 *  @file JPetBaseMCHit.cpp
 */

#include "JPetBaseMCHit/JPetBaseMCHit.h"
#include "JPetLoggerInclude.h"

ClassImp(JPetBaseMCHit);

JPetBaseMCHit::JPetBaseMCHit() : JPetBaseHit() {}

int JPetBaseMCHit::getMCDecayTreeIndex() const { return fMCDecayTreeIndex; }

int JPetBaseMCHit::getMCVtxIndex() const { return fMCVtxIndex; }

const TVector3& JPetBaseMCHit::getPolarization() const { return fPolarization; }

const TVector3& JPetBaseMCHit::getMomentum() const { return fMomentum; }

JPetBaseMCHit::MultiplicityTag JPetBaseMCHit::getMultiplicityTag() const { return fMultiplicityTag; }

void JPetBaseMCHit::setMCDecayTreeIndex(int decayTreeIndex) { fMCDecayTreeIndex = decayTreeIndex; }

void JPetBaseMCHit::setMCVtxIndex(int vertexIndex) { fMCVtxIndex = vertexIndex; }

void JPetBaseMCHit::setPolarization(double polX, double polY, double polZ) { fPolarization.SetXYZ(polX, polY, polZ); }

void JPetBaseMCHit::setMomentum(double momX, double momY, double momZ) { fMomentum.SetXYZ(momX, momY, momZ); }

void JPetBaseMCHit::setMultiplicityTag(JPetBaseMCHit::MultiplicityTag multiplicityTag) { fMultiplicityTag = multiplicityTag; }
