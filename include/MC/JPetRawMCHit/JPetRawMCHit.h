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
 *  @file JPetRawMCHit.h
 */

#ifndef JPETRAWMCHIT_H
#define JPETRAWMCHIT_H

#include "Hits/JPetBaseHit/JPetBaseHit.h"

/**
 * @brief Representation of a Monte Carlo simulation of a interaction of a photon
 * with a scintillating strip in a form of a raw hit, before application of any
 * reconstruction, i.e. time and spatial smearing.
 */
class JPetRawMCHit : public JPetBaseHit
{
public:
  JPetRawMCHit();
  int getMCDecayTreeIndex() const;
  int getMCVtxIndex() const;
  const TVector3& getPolarization() const;
  const TVector3& getMomentum() const;
  int getGammaTag() const;
  void setMCDecayTreeIndex(int decayTreeIndex);
  void setMCVtxIndex(int vertexIndex);
  void setPolarization(float polX, float polY, float polZ);
  void setPolarization(const TVector3& polarization);
  void setMomentum(float momX, float momY, float momZ);
  void setMomentum(const TVector3& momentum);
  void setGammaTag(int i);
  void Clear(Option_t*) override;

private:
  TVector3 fPolarization;
  TVector3 fMomentum;
  int fMCDecayTreeIndex = 0;
  int fMCVtxIndex = 0;
  /**
   * Gamma tag is a number with encoded information about generated photon,
   * the convention is described in the manual of j-pet-geant4 project
   * in section 3. results of simulation, available i.e. here
   * https://github.com/JPETTomography/J-PET-geant4/blob/master/docs/
   */
  int fGammaTag = 0;

  ClassDef(JPetRawMCHit, 1);
};

#endif /* !JPETRAWMCHIT_H */
