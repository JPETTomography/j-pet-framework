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
#include "../JPetSignal/JPetSignal.h"
#include "../JPetTSlot/JPetTSlot.h"

#include "TNamed.h"
#include "TVector3.h"
#include <TRef.h>

#include <cstddef>
#include <utility>

class JPetBarrelSlot;
class JPetScin;
class JPetSignal;
class JPetTSlot;

/**
 * @brief A class representing a reconstructed hit of a photon in the scintillator strip.
 *
 * It contains two objects of type JPetSignal ("left" and "right") which represent signals at two ends of a scintillator strip, from which the hit was reconstructed.
 */
class JPetHit : public TNamed {

  public:
  
  //typedef std::pair<JPetSignal*,JPetSignal*> JPetSignals;
  enum Signal {kLeft,kRight};
  
  JPetHit();
  JPetHit(float Energy, float QualityOfEnergy, float Time, float QualityOfTime, TVector3& Position, 
          JPetSignal& LeftSignal, JPetSignal& RightSignal, JPetBarrelSlot& BarrelSlot, JPetScin& Scintillator);
  virtual ~JPetHit();
  /// Returns the reconstructed energy of this hit
  inline const float GetEnergy() const {return fEnergy;}
  /// Returns a quantitative measure of the hit energy reconstruction quality
  inline const float GetQualityOfEnergy() const {return fQualityOfEnergy;}
  /// Returns the time reconstructed for this hit
  inline const float GetTime() const {return fTime;}
  /// Returns the reconstructed time difference between signals on two ends of scintillator (difference "left" - "right") 
  inline const float GetTimeDiff() const {return fTimeDiff;}
  /// Returns a quantitative measure of the hit time reconstruction quality
  inline const float GetQualityOfTime() const {return fQualityOfTime;}
  /**
   * @brief Returns the 1-dim position of the hit along the scintillator
   *
   * @return position along the strip in cm, measured from the "left" end of the strip.
   */
  inline const float GetPosAlongStrip() const {return fPosAlongStrip;}
  inline const float GetPosX() const {return fPos.X();}
  inline const float GetPosY() const  {return fPos.Y();}
  inline const float GetPosZ() const  {return fPos.Z();}
  inline const float GetPos (int index) const {return fPos(index);}
  inline const TVector3& GetPos() const {return fPos;}
  inline const JPetSignal& GetSignal(Signal pos) const {
                     if(pos==kLeft) return fLeftSignal;
		     else return fRightSignal;}
  inline const JPetSignal& GetLeftSignal() const {return fLeftSignal;}
  inline const JPetSignal& GetRightSignal() const {return fRightSignal;}
  //inline const JPetSignals& GetSignals() const {return *fSignals;};
  inline JPetScin * GetScintillator() const {return (JPetScin*)fScintillator.GetObject();}
  inline const JPetBarrelSlot * GetBarrelSlot() const {return (JPetBarrelSlot*)fBarrelSlot.GetObject();}

  /// Sets the reconstructed energy of the hit
  inline void SetEnergy(float energy) {fEnergy = energy;}
  inline void SetQualityOfEnergy(float qualityOfEnergy) {fQualityOfEnergy = qualityOfEnergy;}
  /// Sets the reconstructed time of the hit into scintillator
  inline void SetTime(float time) {fTime = time;}
  inline void SetQualityOfTime(float qualityOfTime) {fQualityOfTime = qualityOfTime;}
  /// Sets the reconstructed time difference between two signals at ends of the scintillator (difference "left" - "right")
  inline void SetTimeDiff(float td) {fTimeDiff = td;}
  inline void SetQualityOfTimeDiff(float qtd) {fQualityOfTime = qtd;}
  /**
   * @brief Sets the 1-dim position of the hit along the scintillator
   *
   * The position should be in cm, measured from the "left" end of the strip. This value should be set after calculation of the position using the time difference of the two signals.
   */
  inline void SetPosAlongStrip(float pos) {fPosAlongStrip = pos;}
  inline void SetPosX(float x) {fPos.SetX(x);}
  inline void SetPosY(float y) {fPos.SetY(y);}
  inline void SetPosZ(float z) {fPos.SetZ(z);}
  inline void SetPos (float x,float y,float z) {fPos.SetXYZ(x,y,z);}
  //inline void SetSignals (JPetSignals* signals) {fSignals = signals;};
  //inline void SetSignals (JPetSignals& signals) {fSignals = &signals;};
  inline void SetSignals (JPetSignal & leftSignal, JPetSignal & rightSignal) {
              fLeftSignal = leftSignal;
	      fRightSignal = rightSignal;}
  inline void SetLeftSignal(JPetSignal LeftSignal) {fLeftSignal=LeftSignal;}
  inline void SetRightSignal(JPetSignal RightSignal) {fRightSignal=RightSignal;}
  //inline const JPetSignals& GetSignals() const {return *fSignals;};
  //inline void SetScintillator(TRef fScintillator) {fScintillator=Scintillator;}
  inline void SetBarrelSlot(JPetBarrelSlot* bs) {fBarrelSlot.SetObject(bs);}
  inline void SetScintillator(JPetScin* sc) {fScintillator.SetObject(sc);}

  ClassDef(JPetHit,1);
  
  private:
   
  float fEnergy; ///< reconstructed energy of the hit
  float fQualityOfEnergy;
  float fTime; ///< reconstructed time of the hit
  float fQualityOfTime;
  float fTimeDiff; ///< reconstructed time difference between signals at two ends of scintillator
  float fQualityOfTimeDiff;
  float fPosAlongStrip; ///< reconstructed position along scintillator strip (from "left" to "right") [cm]
  TVector3 fPos;
  JPetSignal fLeftSignal;
  JPetSignal fRightSignal;

  // references to parametric objects
  TRef fBarrelSlot; ///< BarrelSlot in which the hit was recorded
  TRef fScintillator; ///< Scintillator strip which was hit

};
  
#endif
