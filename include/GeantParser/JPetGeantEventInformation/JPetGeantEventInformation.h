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
 *  @file JPetGeantEventInformation.h
 */

#ifndef JPET_GEANT_EVENT_INFORMATION_H
#define JPET_GEANT_EVENT_INFORMATION_H 1

#include "TBits.h"
#include "TObject.h"
#include "TVector3.h"
#include <vector>

/**
 * @brief keeps information about initial simulation parameters
 * e.g. vertices and times distributions for annihilation
 * and prompt gamma photons
 */
class JPetGeantEventInformation : public TObject
{
public:
  JPetGeantEventInformation();
  ~JPetGeantEventInformation();
  void Clear();

  void setThreeGammaGen(bool tf) { fGenGammaNum.SetBitNumber(2, tf); };
  void setTwoGammaGen(bool tf) { fGenGammaNum.SetBitNumber(1, tf); };
  void setPromptGammaGen(bool tf) { fGenGammaNum.SetBitNumber(0, tf); };
  void setRunNr(int x) { fnRun = x; };
  void setVtxPosition(double x, double y, double z) { fVtxPosition.SetXYZ(x, y, z); };
  void setVtxPromptPosition(double x, double y, double z) { fVtxPromptPosition.SetXYZ(x, y, z); };
  void setLifetime(double x) { fLifetime = x; };
  void setPromptLifetime(double x) { fPromptLifetime = x; };

  bool getThreeGammaGen() const { return fGenGammaNum.TestBitNumber(2); };
  bool getTwoGammaGen() const { return fGenGammaNum.TestBitNumber(1); };
  bool getPromptGammaGen() const { return fGenGammaNum.TestBitNumber(0); };
  int getRunNr() const { return fnRun; };
  double getVtxPositionX() const { return fVtxPosition.X(); };
  double getVtxPositionY() const { return fVtxPosition.Y(); };
  double getVtxPositionZ() const { return fVtxPosition.Z(); };
  double getVtxPromptPositionX() const { return fVtxPromptPosition.X(); };
  double getVtxPromptPositionY() const { return fVtxPromptPosition.Y(); };
  double getVtxPromptPositionZ() const { return fVtxPromptPosition.Z(); };

  double getLifetime() const { return fLifetime; };
  double getPromptLifetime() const { return fPromptLifetime; };

  TVector3 getVtxPromptPosition() const { return fVtxPromptPosition; }
  TVector3 getVtxPosition() const { return fVtxPosition; }

  void setMomentumGamma(int index, double x, double y, double z) { fMomentumGamma[index].SetXYZ(x, y, z); }

  TVector3 getMomentumGamma(int index) const { return fMomentumGamma[index]; }

private:
  const unsigned int fMaxGammaNumberIndex = 3;
  TVector3 fVtxPosition;         ///< xyz annihilation coordinated
  TVector3 fVtxPromptPosition;   ///< xyz of prompt photon emmision
  TBits fGenGammaNum;            ///< bitNR 0-prompt; 1-back-to-back; 2- oPs
  int fnRun = -1;                ///< number should follow the JPet run numbering scheme
  double fLifetime = -1.0;       ///< lifetime of generated bound state or direct annihilation; see specific simulation details
  double fPromptLifetime = -1.0; ///< generated lifetime of emmited prompt photon; filled only if prompt gamma is generated
  std::vector<TVector3> fMomentumGamma;

private:
  ClassDef(JPetGeantEventInformation, 7)
};

#endif
