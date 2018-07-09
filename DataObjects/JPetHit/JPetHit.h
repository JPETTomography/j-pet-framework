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
 *  @file JPetHit.h
 */

#ifndef _JPETHIT_H_
#define _JPETHIT_H_

#include "./JPetBarrelSlot/JPetBarrelSlot.h"
#include "./JPetPhysSignal/JPetPhysSignal.h"
#include "./JPetScin/JPetScin.h"
#include "TVector3.h"
#include "TObject.h"
#include <cstddef>
#include <utility>
#include <TRef.h>

class JPetBarrelSlot;
class JPetPhysSignal;
class JPetScin;

/**
 * @brief Data class representing a reconstructed hit of a photon in the scintillator strip.
 *
 * Hit class contains two objects of type JPetPhysSignal (from "Side A" and "Side B"
 * of the Barrel) which represent signals at two ends of a scintillator strip,
 * from which the hit was reconstructed. Analyst can set the energy, time and position.
 * Agreed convention of units: energy [keV], time [ps], position [cm].
 * User can describe quality of energy, hit time and time difference
 * between the two signals in the hit.
 */
class JPetHit: public TObject
{
public:
  enum Signal {SideA, SideB};
  JPetHit();
  JPetHit(float Energy, float QualityOfEnergy, float Time, float QualityOfTime,
    TVector3& Position, JPetPhysSignal& SignalA, JPetPhysSignal& SignalB,
    JPetBarrelSlot& BarrelSlot, JPetScin& Scintillator);
  virtual ~JPetHit();
  float getEnergy() const;
  float getQualityOfEnergy() const;
  float getTime() const ;
  float getTimeDiff() const ;
  float getQualityOfTime() const;
  float getQualityOfTimeDiff() const ;
  float getPosX() const;
  float getPosY() const ;
  float getPosZ() const;
  float getPos(int index) const;
  const TVector3& getPos() const;
  const JPetPhysSignal& getSignal(Signal pos) const;
  const JPetPhysSignal& getSignalA() const;
  const JPetPhysSignal& getSignalB() const;
  const JPetScin& getScintillator() const;
  const JPetBarrelSlot& getBarrelSlot() const;
  bool isSignalASet()const;
  bool isSignalBSet()const;
  void setEnergy(float energy);
  void setQualityOfEnergy(float qualityOfEnergy);
  void setTime(float time);
  void setQualityOfTime(float qualityOfTime);
  void setTimeDiff(float td);
  void setQualityOfTimeDiff(float qtd);
  void setPosX(float x) ;
  void setPosY(float y);
  void setPosZ(float z) ;
  void setPos (float x, float y, float z) ;
  void setBarrelSlot( JPetBarrelSlot& bs) ;
  void setScintillator(JPetScin& sc) ;
  void setSignals(const JPetPhysSignal& p_sigA, const JPetPhysSignal& p_sigB);
  void setSignalA(const JPetPhysSignal& p_sig);
  void setSignalB(const JPetPhysSignal& p_sig);
  bool checkConsistency() const;
  void Clear(Option_t * opt  = "");

private:
  float fEnergy = 0.0f;
  float fQualityOfEnergy = 0.0f;
  float fTime = 0.0f;
  float fQualityOfTime = 0.0f;
  float fTimeDiff = 0.0f;
  float fQualityOfTimeDiff = 0.0f;
  bool fIsSignalAset = false;
  bool fIsSignalBset = false;
  TVector3 fPos;
  JPetPhysSignal fSignalA;
  JPetPhysSignal fSignalB;
  TRef fBarrelSlot = NULL;
  TRef fScintillator = NULL;

  ClassDef(JPetHit, 5);
};

#endif
