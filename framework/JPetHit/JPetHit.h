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
#include "../JPetTSlot/JPetTSlot.h"

#include "TNamed.h"
#include "TVector3.h"

#include <cstddef>
#include <utility>

class JPetBarrelSlot;
class JPetScin;
class JPetSignal;
class JPetTSlot;

class JPetHit : public TNamed {

  public:
  
  typedef std::pair<JPetSignal*,JPetSignal*> JPetSignals;
  enum Signal {kLeft,kRight};
  
  JPetHit();
  JPetHit(float Energy, float QualityOfEnergy, float Time, float QualityOfTime, TVector3& Position, 
          JPetSignals& Signals, JPetBarrelSlot& BarrelSlot, JPetScin& Scintillator, JPetTSlot& TSlot);
  virtual ~JPetHit();
  inline const float GetEnergy() const {return fEnergy;};
  inline const float GetQualityOfEnergy() const {return fQualityOfEnergy;};
  inline const float GetTime() const {return fTime;};
  inline const float GetQualityOfTime() const {return fQualityOfTime;};
  inline const float GetPosX() const {return fPos->X();};
  inline const float GetPosY() const  {return fPos->Y();};
  inline const float GetPosZ() const  {return fPos->Z();};
  inline const float GetPos (int index) const {return (*fPos)(index);};
  inline const TVector3& GetPos() const {return *fPos;};
  inline const JPetSignal& GetSignal(Signal pos) const {
                     if(pos==kLeft) return *fSignals->first;
		     else return *fSignals->second;};
  inline const JPetSignal& GetSignalLeft() const {return *fSignals->first;};
  inline const JPetSignal& GetSignalRight() const {return *fSignals->second;};
  inline const JPetSignals& GetSignals() const {return *fSignals;};
  inline const JPetScin& GetScintillator() const {return *fScintillator;};
  inline const JPetBarrelSlot& GetBarrelSlot() const {return *fBarrelSlot;};
  inline void SetEnergy(float energy) {fEnergy = energy;};
  inline void SetQualityOfEnergy(float qualityOfEnergy) {fQualityOfEnergy = qualityOfEnergy;};
  inline void SetTime(float time) {fTime = time;};
  inline void SetQualityOfTime(float qualityOfTime) {fQualityOfTime = qualityOfTime;};
  inline void SetPosX(float x) {fPos->SetX(x);};
  inline void SetPosY(float y) {fPos->SetY(y);};
  inline void SetPosZ(float z) {fPos->SetZ(z);};
  inline void SetPos (float x,float y,float z) {fPos->SetXYZ(x,y,z);};
  inline void SetSignals (JPetSignals* signals) {fSignals = signals;};
  inline void SetSignals (JPetSignals& signals) {fSignals = &signals;};
  inline void SetSignals (JPetSignal* leftSignal, JPetSignal* rightSignal) {
              fSignals->first = leftSignal;
	      fSignals->second = rightSignal;};
  
  ClassDef(JPetHit,1);
  
  private:
   
  float fEnergy;
  float fQualityOfEnergy;
  float fTime;
  float fQualityOfTime;
  TVector3* fPos;
  JPetSignals* fSignals;
  JPetBarrelSlot* fBarrelSlot;
  JPetScin* fScintillator;
  JPetTSlot* fTSlot;

};
  
#endif
