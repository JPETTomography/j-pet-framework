#ifndef _JPETEVENT_H_
#define _JPETEVENT_H_

#include "../JPetHit/JPetHit.h"

class JPetHit;

class JPetHits {
  
  public:
  
  enum HitsSequence {kFirst, kSecond};
 
  JPetHits ();
  JPetHits (JPetHit& firstHit, JPetHit& secondHit);
  virtual ~JPetHits();
  inline JPetHit& First() const {return *fFirst;};
  inline JPetHit& Second() const {return *fSecond;};
  inline JPetHit& GetHit(HitsSequence seq) const {
    if (seq==kFirst) return *fFirst;
    return *fSecond;
  };
  JPetHit& operator() (int index) const {
    if(index==0) return *fFirst;
    return *fSecond;  
  };
   
  private:
  
  JPetHit* fFirst;
  JPetHit* fSecond;
};

class JPetEvent {
  
  public:
  
  JPetEvent();
  virtual ~JPetEvent();
  inline float GetTime() const {return fTime;};
  inline float GetQualityOfTime() const {return fQualityOfTime;};
  inline void SetTime(float time) {fTime = time;};
  inline void SetQualityOfTime(float qualityOfTime) {fQualityOfTime = qualityOfTime;};
  inline JPetHit& GetHit(JPetHits::HitsSequence seq) const {return fHits->GetHit(seq);};
  inline JPetHit& GetHit(int index) const {return (*fHits)(index);};
  inline JPetHits& GetHits() const {return *fHits;};
  
  private:
  
  float fTime;
  float fQualityOfTime;
  JPetHits* fHits;
  
};

#endif
