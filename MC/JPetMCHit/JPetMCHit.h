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
 *  @file JPetMCHit.h
 */

#ifndef _JPETMCHIT_H_
#define _JPETMCHIT_H_

#include "./JPetHit/JPetHit.h"

/**
 * @brief Data class representing a hit of a photon in the scintillator strip
 * based on Monte Carlo simulation.
 */
class JPetMCHit : public JPetHit
{
public:
  JPetMCHit();
  JPetMCHit(UInt_t MCDecayTreeIndex, UInt_t MCVtxIndex, float Energy, float Time,
    const TVector3& Position, const TVector3& Polarization, const TVector3& Momentum);
  UInt_t getMCDecayTreeIndex() const;
  UInt_t getMCVtxIndex() const;
  const TVector3& getPolarization() const;
  const TVector3& getMomentum() const;
  void setMCDecayTreeIndex(Int_t dti);
  void setMCVtxIndex(Int_t vi);
  void setPolarization(Int_t xx, Int_t yy, Int_t zz);
  void setMomentum(Float_t dd, Float_t ee, Float_t ff);

  //  generated cheatsheet
  void setGenGammaMultiplicity(UInt_t i){fGenGammaMultiplicity=i;} ///< 1-prompt gamma; 2-gamma from back-to-bak; 3-gamma from oPs
  UInt_t getGenGammaMultiplicity(){return fGenGammaMultiplicity;}


private:
  UInt_t fMCDecayTreeIndex = 0u;
  UInt_t fMCVtxIndex = 0u;
  TVector3 fPolarization;
  TVector3 fMomentum;
  UInt_t fGenGammaMultiplicity = 0u; ///< generated gamma cheat sheet: 1- prompt; 2- back-to-back; 3- 3gamma annihilation

  ClassDef(JPetMCHit, 2);
};

#endif /* !_JPETMCHIT_H_ */
