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
 *  @file JPetBaseMCHit.h
 */

#ifndef JPETBASEMCHIT_H
#define JPETBASEMCHIT_H

#include "JPetBaseHit/JPetBaseHit.h"

/**
 * @brief Representation of a "true" Monte Carlo simulation of a interaction of a photon
 * with a scintillating strip in a form of a hit.
 */
class JPetBaseMCHit : public JPetBaseHit
{
public:
  enum MultiplicityTag
  {
    kPrompt,
    k2gBack2Back,
    k3gOPS,
    kUnknown
  };

  JPetBaseMCHit();
  int getMCDecayTreeIndex() const;
  int getMCVtxIndex() const;
  const TVector3& getPolarization() const;
  const TVector3& getMomentum() const;
  MultiplicityTag getMultiplicityTag() const;
  void setMCDecayTreeIndex(int decayTreeIndex);
  void setMCVtxIndex(int vertexIndex);
  void setPolarization(double polX, double polY, double polZ);
  void setMomentum(double momX, double momY, double momZ);
  void setMultiplicityTag(MultiplicityTag multiplicityTag);

private:
  TVector3 fPolarization;
  TVector3 fMomentum;
#ifndef __CINT__
  int fMCDecayTreeIndex = 0;
  int fMCVtxIndex = 0;
  MultiplicityTag fMultiplicityTag = JPetBaseMCHit::kUnknown;
#else
  int fMCDecayTreeIndex;
  int fMCVtxIndex;
  MultiplicityTag fMultiplicityTag;
#endif

  ClassDef(JPetBaseMCHit, 1);
};

#endif /* !JPETBASEMCHIT_H */
