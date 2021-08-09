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
 *  @file JPetGeantScinHits.h
 */

#ifndef JPETGEANTSCINHITS_H
#define JPETGEANTSCINHITS_H

#include <TObject.h>
#include <TVector3.h>
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
  JPetGeantScinHits(int evID, int scinID, int trkID, int trkPDG, int nInter, double ene, double time, const TVector3& position);
  JPetGeantScinHits(int evID, int scinID, int trkID, int trkPDG, int nInter, double ene, double time, const TVector3& position, const TVector3& polIn,
                    const TVector3& polOut, const TVector3& momIn, const TVector3& momOut);
  ~JPetGeantScinHits();
  void Clear(Option_t*) override;

  int getEvtID() const { return fEvtID; };
  int getScinID() const { return fScinID; };
  int getTrackID() const { return fTrackID; };
  int getTrackPDG() const { return fTrackPDGencoding; };
  int getNumOfInteractions() const { return fNumOfInteractions; };
  double getEneDepos() const { return fEneDep; };
  double getTime() const { return fTime; };

  const TVector3& getHitPosition() const { return fPosition; };
  const TVector3& getPolarizationIn() const { return fPolarizationIn; };
  const TVector3& getPolarizationOut() const { return fPolarizationOut; };
  const TVector3& getMomentumIn() const { return fMomentumIn; };
  const TVector3& getMomentumOut() const { return fMomentumOut; };

  int getGenGammaMultiplicity() const { return fGenGammaMultiplicity; }
  int getGenGammaIndex() const { return fGenGammaIndex; }

  void set(int evtID, int scinID, int trkID, int trkPDG, int nInter, double ene, double time);
  void set(int evtID, int scinID, int trkID, int trkPDG, int nInter, double ene, double time, const TVector3& position, const TVector3& polIn,
           const TVector3& polOut, const TVector3& momIn, const TVector3& momOut);

  void setEvtID(int evtID) { fEvtID = evtID; };
  void setScinID(int scinID) { fScinID = scinID; };
  void setTrackID(int trkID) { fTrackID = trkID; };
  void setTrackPDG(int trkPDG) { fTrackPDGencoding = trkPDG; };
  void setNumOfInteractions(int nInter) { fNumOfInteractions = nInter; };
  void setEneDepos(double ene) { fEneDep = ene; };
  void setTime(double time) { fTime = time; };
  void setHitPosition(const TVector3& position) { fPosition = position; };
  void setHitPosition(double x, double y, double z) { fPosition.SetXYZ(x, y, z); };
  void setPolarizationIn(const TVector3& polIn) { fPolarizationIn = polIn; };
  void setPolarizationIn(double x, double y, double z) { fPolarizationIn.SetXYZ(x, y, z); };
  void setPolarizationOut(const TVector3& polOut) { fPolarizationOut = polOut; };
  void setPolarizationOut(double x, double y, double z) { fPolarizationOut.SetXYZ(x, y, z); };
  void setMomentumIn(const TVector3& momIn) { fMomentumIn = momIn; };
  void setMomentumIn(double x, double y, double z) { fMomentumIn.SetXYZ(x, y, z); };
  void setMomentumOut(const TVector3& momOut) { fMomentumOut = momOut; };
  void setMomentumOut(double x, double y, double z) { fMomentumOut.SetXYZ(x, y, z); };

  void setGenGammaMultiplicity(int i) { fGenGammaMultiplicity = i; }
  void setGenGammaIndex(int i) { fGenGammaIndex = i; }

private:
  int fEvtID = 0;
  int fScinID = 0;
  int fTrackID = 0;
  int fTrackPDGencoding = 0;
  //! Number of interaction taking place in single scintillator,
  //! which were classified as a single hit;
  //! it may be a big number since electron deposits energy in many steps
  int fNumOfInteractions = 0;
  //! unequivocal number identifying gamma quanta
  int fGenGammaIndex = 0;
  //! 2 - back-to-back; 3 - 3gamma annihilation
  int fGenGammaMultiplicity = 0;
  //! deposited energy (a sum if more than one gamma quanta interacted)
  double fEneDep = 0.0;
  //! Time of interaction in the scintillator with respect to the beta+ decay (start of simulation)
  double fTime = 0.0;

  TVector3 fPosition;
  TVector3 fPolarizationIn;
  TVector3 fPolarizationOut;
  TVector3 fMomentumIn;
  TVector3 fMomentumOut;

  ClassDef(JPetGeantScinHits, 4)
};

#endif
