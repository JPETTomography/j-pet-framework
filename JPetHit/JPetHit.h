/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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

#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetPhysSignal/JPetPhysSignal.h"
#include "../JPetTimeWindow/JPetTimeWindow.h"

#include "TNamed.h"
#include "TVector3.h"
#include <TRef.h>

#include <cstddef>
#include <utility>

class JPetBarrelSlot;
class JPetScin;
class JPetPhysSignal;
class JPetTimeWindow;

/**
 * @brief Data class representing a reconstructed hit of a photon in the scintillator strip.
 *
 * It contains two objects of type JPetPhysSignal (from "Side A" and "Side B" of the Barrel) which represent signals at two ends of a scintillator strip, from which the hit was reconstructed.
 */
class JPetHit : public TNamed {

  public:

  enum Signal {SideA,SideB};

  JPetHit();
  JPetHit(float Energy, float QualityOfEnergy, float Time, float QualityOfTime, TVector3& Position,
          JPetPhysSignal& SignalA, JPetPhysSignal& SignalB, JPetBarrelSlot& BarrelSlot, JPetScin& Scintillator);
  virtual ~JPetHit();
  const float getEnergy() const;
  const float getQualityOfEnergy() const;
  const float getTime() const ;
  const float getTimeDiff() const ;
  const float getQualityOfTime() const;
  const float getQualityOfTimeDiff() const ;
  /**
   * @brief Returns the 1-dim position of the hit along the scintillator
   *
   * @return position along the strip in cm, measured from the "Side A" end of the strip.
   */
  const float getPosAlongStrip() const ;
  const float getPosX() const;
  const float getPosY() const ;
  const float getPosZ() const;
  const float getPos(int index) const;
  const int getScinID()const;
  const TVector3& getPos() const;
  const JPetPhysSignal& getSignal(Signal pos) const;
  const JPetPhysSignal& getSignalA() const;
  const JPetPhysSignal& getSignalB() const;
  const JPetScin& getScintillator() const;
  const JPetBarrelSlot& getBarrelSlot() const;
  const bool isSignalASet()const;
  const bool isSignalBSet()const;

  void setEnergy(float energy);
  void setQualityOfEnergy(float qualityOfEnergy);
  void setTime(float time);
  void setQualityOfTime(float qualityOfTime);
  void setTimeDiff(float td);
  void setQualityOfTimeDiff(float qtd);
  /**
   * @brief Sets the 1-dim position of the hit along the scintillator
   *
   * The position should be in cm, measured from the "A Side" end of the strip. This value should be set after calculation of the position using the time difference of the two signals.
   */
  void setPosAlongStrip(const float pos);
  void setPosX(float x) ;
  void setPosY(float y);
  void setPosZ(float z) ;
  void setPos (float x,float y,float z) ;
  void setBarrelSlot( JPetBarrelSlot& bs) ;
  void setScintillator(JPetScin& sc) ;
  void setScinID (const int scinID);

  void setSignals(JPetPhysSignal & p_sigA, JPetPhysSignal & p_sigB);
  void setSignalA(JPetPhysSignal & p_sig);
  void setSignalB(JPetPhysSignal & p_sig);
  unsigned int getTimeWindowIndex()const;

  ClassDef(JPetHit,1);
  /** @brief Checks whether information contained in both Signal objects
   *  set in this Hit object is consistent and logs an error message if
   *  it is not.
   *
   *  Pairing two signals originating from photomultipliers belonging to
   *  two different barrel slots or the same barrel side (i.e. attached
   *  to different scintillators) would make no physical sense. This method
   *  ensures that it is not the case.
   *
   *  This method checks the following:
   *  - if both signals come from the same barrel slot
   *  - if the two signals come from opposite-side PMTs
   *  - if both signals belong to the same time window
   *
   *  If all the above conditions are met, this method only returns 'true'.
   *  If any of these conditions is violated, 'false' is returned and
   *  an appropriate message is written to the log file.
   *
   *  @return true if both signals are consistently from the same barrel slot.
   */
  const bool checkConsistency() const;

  private:
  float fEnergy = 0.0f; ///< reconstructed energy of the hit [keV]
  float fQualityOfEnergy = 0.0f;
  float fTime = 0.0f; ///< reconstructed time of the hit [ps]
  float fQualityOfTime = 0.0f;
  float fTimeDiff = 0.0f; ///< reconstructed time difference between signals at two ends of scintillator [ps]
  float fQualityOfTimeDiff = 0.0f;
  float fPosAlongStrip = 0.0f; ///< reconstructed position along scintillator strip (from "Side A" to "Side B") [cm]
  TVector3 fPos;
  JPetPhysSignal fSignalA;
  JPetPhysSignal fSignalB;
  bool fIsSignalAset = false;
  bool fIsSignalBset = false;

  int fScinID = 0; ///< For simple reconstruction

  // references to parametric objects
  TRef fBarrelSlot = NULL; ///< BarrelSlot in which the hit was recorded
  TRef fScintillator = NULL; ///< Scintillator strip which was hit

};

#endif
