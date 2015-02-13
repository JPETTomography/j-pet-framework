/**
 * @file JPetHit.h
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2013, Damian Trybek
 * @brief Hit Class
 */

#ifndef _JPETHIT_H_
#define _JPETHIT_H_

#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetPhysSignal/JPetPhysSignal.h"
#include "../JPetTSlot/JPetTSlot.h"

#include "TNamed.h"
#include "TVector3.h"
#include <TRef.h>

#include <cstddef>
#include <utility>

class JPetBarrelSlot;
class JPetScin;
class JPetPhysSignal;
class JPetTSlot;

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
  /// Returns the reconstructed energy of this hit [keV]
  inline const float getEnergy() const {return fEnergy;}
  /// Returns a quantitative measure of the hit energy reconstruction quality
  inline const float getQualityOfEnergy() const {return fQualityOfEnergy;}
  /// Returns the absolute time reconstructed for this hit [ps]
  inline const float getTime() const {return fTime;}
  /// Returns the reconstructed time difference between signals on two ends of scintillator (difference "Side A" - "Side B") 
  inline const float getTimeDiff() const {return fTimeDiff;}
  /// Returns a quantitative measure of the hit time reconstruction quality
  inline const float getQualityOfTime() const {return fQualityOfTime;}
  inline const float getQualityOfTimeDiff() const {return fQualityOfTimeDiff;}
  /**
   * @brief Returns the 1-dim position of the hit along the scintillator
   *
   * @return position along the strip in cm, measured from the "Side A" end of the strip.
   */
  inline const float getPosAlongStrip() const {return fPosAlongStrip;}
  inline const float getPosX() const {return fPos.X();}
  inline const float getPosY() const  {return fPos.Y();}
  inline const float getPosZ() const  {return fPos.Z();}
  inline const float getPos(int index) const {return fPos(index);}
  inline const TVector3& getPos() const {return fPos;}
  inline const JPetPhysSignal& getSignal(Signal pos) const {
                     if(pos==SideA) return fSignalA;
		     else return fSignalB;}
  inline const JPetPhysSignal& getSignalA() const {return fSignalA;}
  inline const JPetPhysSignal& getSignalB() const {return fSignalB;}

  inline const JPetScin& getScintillator() const {return (JPetScin&)*fScintillator.GetObject();}
  inline const JPetBarrelSlot& getBarrelSlot() const {return (JPetBarrelSlot&)*fBarrelSlot.GetObject();}

  /// Sets the reconstructed energy of the hit [keV]
  inline void setEnergy(float energy) {fEnergy = energy;}
  inline void setQualityOfEnergy(float qualityOfEnergy) {fQualityOfEnergy = qualityOfEnergy;}
  /// Sets the reconstructed time of the hit into scintillator [ps]
  inline void setTime(float time) {fTime = time;}
  inline void setQualityOfTime(float qualityOfTime) {fQualityOfTime = qualityOfTime;}
  /// Sets the reconstructed time difference between two signals at ends of the scintillator (difference "Side A" - "Side B") [ps]
  inline void setTimeDiff(float td) {fTimeDiff = td;}
  inline void setQualityOfTimeDiff(float qtd) {fQualityOfTimeDiff = qtd;}
  /**
   * @brief Sets the 1-dim position of the hit along the scintillator
   *
   * The position should be in cm, measured from the "A Side" end of the strip. This value should be set after calculation of the position using the time difference of the two signals.
   */
  inline void setPosAlongStrip(float pos) {fPosAlongStrip = pos;}
  inline void setPosX(float x) {fPos.SetX(x);}
  inline void setPosY(float y) {fPos.SetY(y);}
  inline void setPosZ(float z) {fPos.SetZ(z);}
  inline void setPos (float x,float y,float z) {fPos.SetXYZ(x,y,z);}
  inline void setSignals (JPetPhysSignal & p_sigA, JPetPhysSignal & p_sigB) {
              fSignalA = p_sigA;
	      fSignalB = p_sigB;}
  inline void setSignalA(JPetPhysSignal & p_sig) {fSignalA=p_sig;}
  inline void setSignalB(JPetPhysSignal & p_sig) {fSignalB=p_sig;}
  inline void setBarrelSlot(JPetBarrelSlot& bs) {fBarrelSlot = &bs;}
  inline void setScintillator(JPetScin& sc) {fScintillator = &sc;}

  inline int getScinID () const {return fScinID;}
  inline void setScinID (int scinID) {fScinID = scinID;}

  ClassDef(JPetHit,1);
  
  private:
   
  float fEnergy; ///< reconstructed energy of the hit [keV]
  float fQualityOfEnergy;
  float fTime; ///< reconstructed time of the hit [ps]
  float fQualityOfTime;
  float fTimeDiff; ///< reconstructed time difference between signals at two ends of scintillator [ps]
  float fQualityOfTimeDiff;
  float fPosAlongStrip; ///< reconstructed position along scintillator strip (from "Side A" to "Side B") [cm]
  TVector3 fPos;
  JPetPhysSignal fSignalA;
  JPetPhysSignal fSignalB;

  int fScinID; ///< For simple reconstruction

  // references to parametric objects
  TRef fBarrelSlot; ///< BarrelSlot in which the hit was recorded
  TRef fScintillator; ///< Scintillator strip which was hit

};
  
#endif
