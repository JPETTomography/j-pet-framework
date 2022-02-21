/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file JPetGeantScinHits.h
 */

#ifndef JPETGEANTSCINHITS_H
#define JPETGEANTSCINHITS_H

#include "TObject.h"
#include "TVector3.h"
#include <vector>

/**
 * \class JPetGeantScinHits
 * \brief class is containing the hits registered in scintillators created by Geant software
 *
 */
class JPetGeantScinHits : public TObject
{
public:
  JPetGeantScinHits();

  JPetGeantScinHits(int evID, int scinID, int trkID, int trkPDG, int nInter, float ene, float time, TVector3 hit);

  JPetGeantScinHits(int evID, int scinID, int trkID, int trkPDG, int nInter, float ene, float time, TVector3 hit, TVector3 polIn, TVector3 polOut,
                    TVector3 momeIn, TVector3 momeOut);

  void Fill(int evID, int scinID, int trkID, int trkPDG, int nInter, float ene, float time);

  void Fill(int evID, int scinID, int trkID, int trkPDG, int nInter, float ene, float time, TVector3 hit, TVector3 polIn, TVector3 polOut,
            TVector3 momeIn, TVector3 momeOut);

  ~JPetGeantScinHits();

  void Clean();

  // setters
  void SetEvtID(int x) { fEvtID = x; };
  void SetScinID(int x) { fScinID = x; };
  void SetTrackID(int x) { fTrackID = x; };
  void SetTrackPDG(int x) { fTrackPDGencoding = x; };
  void SetNumOfInteractions(int x) { fNumOfInteractions = x; };
  void SetEneDepos(float x) { fEneDep = x; };
  void SetTime(float x) { fTime = x; };

  void SetHitPosition(TVector3 x) { fPosition = x; };
  void SetHitPosition(float x, float y, float z) { fPosition.SetXYZ(x, y, z); };

  void SetPolarizationIn(TVector3 x) { fPolarizationIn = x; };
  void SetPolarizationIn(float x, float y, float z) { fPolarizationIn.SetXYZ(x, y, z); };

  void SetPolarizationOut(TVector3 x) { fPolarizationOut = x; };
  void SetPolarizationOut(float x, float y, float z) { fPolarizationOut.SetXYZ(x, y, z); };

  void SetMomentumIn(TVector3 x) { fMomentumIn = x; };
  void SetMomentumIn(float x, float y, float z) { fMomentumIn.SetXYZ(x, y, z); };

  void SetMomentumOut(TVector3 x) { fMomentumOut = x; };
  void SetMomentumOut(float x, float y, float z) { fMomentumOut.SetXYZ(x, y, z); };

  // getters
  int GetEvtID() const { return fEvtID; };
  int GetScinID() const { return fScinID; };
  int GetTrackID() const { return fTrackID; };
  int GetTrackPDG() const { return fTrackPDGencoding; };
  int GetNumOfInteractions() const { return fNumOfInteractions; };
  float GetEneDepos() const { return fEneDep; };
  float GetTime() const { return fTime; };
  const TVector3 GetHitPosition() const { return fPosition; };
  const TVector3 GetPolarizationIn() const { return fPolarizationIn; };
  const TVector3 GetPolarizationOut() const { return fPolarizationOut; };
  const TVector3 GetMomentumIn() const { return fMomentumIn; };
  const TVector3 GetMomentumOut() const { return fMomentumOut; };

  //  generated cheatsheet
  void SetGenGammaMultiplicity(int i) { fGenGammaMultiplicity = i; }
  void SetGenGammaIndex(int i) { fGenGammaIndex = i; }

  int GetGenGammaMultiplicity() const { return fGenGammaMultiplicity; }
  int GetGenGammaIndex() const { return fGenGammaIndex; }

private:
  int fEvtID;
  int fScinID;
  int fTrackID;
  int fTrackPDGencoding;
  int fNumOfInteractions; ///< number of interaction taking place in single scintillator whish was classified as single hit; it may be a big number
                          ///< since electron deposits energy in many steps
  int fGenGammaIndex;
  int fGenGammaMultiplicity;
  float fEneDep;
  float fTime;
  TVector3 fPosition;
  TVector3 fPolarizationIn;
  TVector3 fPolarizationOut;
  TVector3 fMomentumIn;
  TVector3 fMomentumOut;

  ClassDef(JPetGeantScinHits, 3)
};

#endif
