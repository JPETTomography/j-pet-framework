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
 *  @file JPetGeantScinHits.cpp
 */

#include "JPetGeantScinHits.h"

ClassImp(JPetGeantScinHits)

JPetGeantScinHits::JPetGeantScinHits()
    :TObject(), fEvtID(0), fScinID(0), fTrackID(0), fTrackPDGencoding(0),
    fNumOfInteractions(0), fGenGammaIndex(0), fGenGammaMultiplicity(0), 
    fEneDep(0), fTime(0), fPosition(0,0,0),
    fPolarizationIn(0,0,0), fPolarizationOut(0,0,0), fMomentumIn(0,0,0), fMomentumOut(0,0,0)
{}


JPetGeantScinHits::JPetGeantScinHits(int evID, int scinID, int trkID, int trkPDG, 
        int nInter, float ene, float time, TVector3 hit )
    :TObject(), fEvtID(evID), fScinID(scinID), fTrackID(trkID), fTrackPDGencoding(trkPDG),
    fNumOfInteractions(nInter), fGenGammaIndex(0), fGenGammaMultiplicity(0),
    fEneDep(ene), fTime(time), fPosition(hit),
    fPolarizationIn(0,0,0), fPolarizationOut(0,0,0), fMomentumIn(0,0,0), fMomentumOut(0,0,0)
{}


JPetGeantScinHits::JPetGeantScinHits(int evID, int scinID, int trkID, int trkPDG, 
        int nInter, float ene, float time, TVector3 hit, 
        TVector3 polIn, TVector3 polOut,
        TVector3 momeIn, TVector3 momeOut)
    :TObject(), fEvtID(evID), fScinID(scinID), fTrackID(trkID), fTrackPDGencoding(trkPDG),
    fNumOfInteractions(nInter),  fGenGammaIndex(0), fGenGammaMultiplicity(0),
    fEneDep(ene), fTime(time), fPosition(hit),
    fPolarizationIn(polIn), fPolarizationOut(polOut), fMomentumIn(momeIn), fMomentumOut(momeOut)
{}

void JPetGeantScinHits::Fill(int evID, int scinID, int trkID, int trkPDG, 
                int nInter, float ene, float time) 
{
    this->SetEvtID(evID);
    this->SetScinID(scinID);
    this->SetTrackID(trkID);
    this->SetTrackPDG(trkPDG);
    this->SetNumOfInteractions(nInter);
    this->SetEneDepos(ene);
    this->SetTime(time);
}



void JPetGeantScinHits::Fill(int evID, int scinID, int trkID, int trkPDG, 
                int nInter, float ene, float time, TVector3 hit, 
                TVector3 polIn, TVector3 polOut,
                TVector3 momeIn, TVector3 momeOut)
{
    this->SetEvtID(evID);
    this->SetScinID(scinID);
    this->SetTrackID(trkID);
    this->SetTrackPDG(trkPDG);
    this->SetNumOfInteractions(nInter);
    this->SetEneDepos(ene);
    this->SetTime(time);
    this->SetHitPosition(hit);
    this->SetPolarizationIn(polIn);
    this->SetPolarizationOut(polOut);
    this->SetMomentumIn(momeIn);
    this->SetMomentumOut(momeOut);
}



JPetGeantScinHits::~JPetGeantScinHits()
{}

void JPetGeantScinHits::Clean()
{
    this->SetEvtID(0);
    this->SetScinID(0);
    this->SetTrackID(0);
    this->SetTrackPDG(0);
    this->SetNumOfInteractions(0);
    this->SetEneDepos(0.0);
    this->SetTime(0.0);
    this->SetHitPosition(TVector3());
    this->SetPolarizationIn(TVector3());
    this->SetPolarizationOut(TVector3());
    this->SetMomentumIn(TVector3());
    this->SetMomentumOut(TVector3());

}
