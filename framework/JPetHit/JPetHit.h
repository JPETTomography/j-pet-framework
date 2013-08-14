#ifndef _JPETHIT_H_
#define _JPETHIT_H_

#include "../JPetBarrelSlot/JPetBarrelSlot.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetTSlot/JPetTSlot.h"

//#include "TVector3.h"

#include <cstddef>

class JPetBarrelSlot;
class JPetScin;
class JPetSignal;
class JPetTSlot;

class Vector3 {
  
  public:
  
  Vector3 ();
  Vector3 (float x, float y, float z);
  virtual ~Vector3 ();
  
  float operator() (int index) const {return fCords[index];};
  
  inline float X() const {return fCords[0];};
  inline float Y() const {return fCords[1];};
  inline float Z() const {return fCords[2];};
  
  private:
  
  float fCords[3];
};

class JPetSignals {
  
  public:
  
  enum SignalPosition {kLeft, kRight};
 
  JPetSignals ();
  JPetSignals (JPetSignal& leftSignal, JPetSignal& rightSignal);
  virtual ~JPetSignals();
  inline JPetSignal& Left() const {return *fLeft;};
  inline JPetSignal& Right() const {return *fRight;};
  inline JPetSignal& GetSignal(SignalPosition pos) const {
    if (pos==kLeft) return *fLeft;
    return *fRight;
  };
   
  private:
  
  JPetSignal* fLeft;
  JPetSignal* fRight;
};

class JPetHit {

  public:
  
  JPetHit();
  JPetHit(float Energy, float QualityOfEnergy, float Time, float QualityOfTime, Vector3& Position, 
          JPetSignals& Signals, JPetBarrelSlot& BarrelSlot, JPetScin& Scintillator, JPetTSlot& TSlot);
  virtual ~JPetHit();
  inline float GetEnergy() const {return fEnergy;};
  inline float GetQualityOfEnergy() const {return fQualityOfEnergy;};
  inline float GetTime() const {return fTime;};
  inline float GetQualityOfTime() const {return fQualityOfTime;};
  inline float GetPosX() const {return fPos->X();};
  inline float GetPosY() const  {return fPos->Y();};
  inline float GetPosZ() const  {return fPos->Z();};
  inline float GetPos (int index) const {return (*fPos)(index);};
  inline Vector3& GetPos() const {return *fPos;};
  inline JPetSignal& GetSignal(JPetSignals::SignalPosition pos) const {return *&fSignals->GetSignal(pos);};
  inline JPetSignals& GetSignals() const {return *fSignals;};
  inline JPetScin& GetScintillator() const {return *fScintillator;};
  inline JPetBarrelSlot& GetBarrelSlot() const {return *fBarrelSlot;};
  //data members:
  //must contain 2 signals, and reference/pointer to JPetScinitllator and JPetSlot,
  
  private:
   
  float fEnergy;
  float fQualityOfEnergy;
  float fTime;
  float fQualityOfTime;
  Vector3* fPos;
  JPetSignals* fSignals;
  JPetBarrelSlot* fBarrelSlot;
  JPetScin* fScintillator;
  JPetTSlot* fTSlot;

};
  
#endif
