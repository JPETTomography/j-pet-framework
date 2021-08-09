/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetGeantScinHits.cpp
 */

#include "JPetGeantScinHits/JPetGeantScinHits.h"

ClassImp(JPetGeantScinHits);

JPetGeantScinHits::JPetGeantScinHits()
    : TObject(), fEvtID(0), fScinID(0), fTrackID(0), fTrackPDGencoding(0), fNumOfInteractions(0), fGenGammaIndex(0), fGenGammaMultiplicity(0),
      fEneDep(0), fTime(0), fPosition(0, 0, 0), fPolarizationIn(0, 0, 0), fPolarizationOut(0, 0, 0), fMomentumIn(0, 0, 0), fMomentumOut(0, 0, 0)
{
}

JPetGeantScinHits::JPetGeantScinHits(int evID, int scinID, int trkID, int trkPDG, int nInter, double ene, double time, const TVector3& position)
    : TObject(), fEvtID(evID), fScinID(scinID), fTrackID(trkID), fTrackPDGencoding(trkPDG), fNumOfInteractions(nInter), fGenGammaIndex(0),
      fGenGammaMultiplicity(0), fEneDep(ene), fTime(time), fPosition(position), fPolarizationIn(0, 0, 0), fPolarizationOut(0, 0, 0),
      fMomentumIn(0, 0, 0), fMomentumOut(0, 0, 0)
{
}

JPetGeantScinHits::JPetGeantScinHits(int evID, int scinID, int trkID, int trkPDG, int nInter, double ene, double time, const TVector3& position,
                                     const TVector3& polIn, const TVector3& polOut, const TVector3& momeIn, const TVector3& momeOut)
    : TObject(), fEvtID(evID), fScinID(scinID), fTrackID(trkID), fTrackPDGencoding(trkPDG), fNumOfInteractions(nInter), fGenGammaIndex(0),
      fGenGammaMultiplicity(0), fEneDep(ene), fTime(time), fPosition(position), fPolarizationIn(polIn), fPolarizationOut(polOut), fMomentumIn(momeIn),
      fMomentumOut(momeOut)
{
}

JPetGeantScinHits::~JPetGeantScinHits() {}

void JPetGeantScinHits::Clear(Option_t*)
{
  TObject::Clear("");
  fEvtID = 0;
  fScinID = 0;
  fTrackID = 0;
  fTrackPDGencoding = 0;
  fNumOfInteractions = 0;
  fGenGammaIndex = 0;
  fGenGammaMultiplicity = 0;
  fEneDep = 0.0;
  fTime = 0.0;
  fPosition = TVector3();
  fPolarizationIn = TVector3();
  fPolarizationOut = TVector3();
  fMomentumIn = TVector3();
  fMomentumOut = TVector3();
}

void JPetGeantScinHits::set(int evID, int scinID, int trkID, int trkPDG, int nInter, double ene, double time)
{
  this->setEvtID(evID);
  this->setScinID(scinID);
  this->setTrackID(trkID);
  this->setTrackPDG(trkPDG);
  this->setNumOfInteractions(nInter);
  this->setEneDepos(ene);
  this->setTime(time);
}

void JPetGeantScinHits::set(int evID, int scinID, int trkID, int trkPDG, int nInter, double ene, double time, const TVector3& position,
                            const TVector3& polIn, const TVector3& polOut, const TVector3& momeIn, const TVector3& momeOut)
{
  this->setEvtID(evID);
  this->setScinID(scinID);
  this->setTrackID(trkID);
  this->setTrackPDG(trkPDG);
  this->setNumOfInteractions(nInter);
  this->setEneDepos(ene);
  this->setTime(time);
  this->setHitPosition(position);
  this->setPolarizationIn(polIn);
  this->setPolarizationOut(polOut);
  this->setMomentumIn(momeIn);
  this->setMomentumOut(momeOut);
}
