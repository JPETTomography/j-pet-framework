/**
 * @file JPetEvent.h
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2013, Damian Trybek
 * @brief Event Class
 */

#ifndef _JPETEVENT_H_
#define _JPETEVENT_H_

#include "../JPetHit/JPetHit.h"

#include <cstddef>
#include <utility>

class JPetHit;

class JPetEvent: public TNamed {
  
  public:

  //typedef std::pair<JPetHit*,JPetHit*> JPetHits;
  
  JPetEvent();
  JPetEvent(float Time, float QualityOfTime, JPetHit& firstHit, JPetHit& secondHit);
  virtual ~JPetEvent();
  inline const float GetTime() const {return fTime;};
  inline const float GetQualityOfTime() const {return fQualityOfTime;};
  inline void SetTime(float time) {fTime = time;};
  inline void SetQualityOfTime(float qualityOfTime) {fQualityOfTime = qualityOfTime;};
  inline const JPetHit& GetfirstHit() const {return *fFirstHit;};
  inline const JPetHit& GetsecondHit() const {return *fSecondHit;};
 //inline const JPetHits& GetHits() const {return *fHits;};
 // inline void SetHits(JPetHits* hits) {fHits = hits;};
 // inline void SetHits(JPetHits& hits) {fHits = &hits;};
  inline void SetHits(JPetHit* firstHit, JPetHit* secondHit) {
              fFirstHit = firstHit;
	      fSecondHit = secondHit;};
  inline void SetFirstHit(JPetHit* firstHit) {fFirstHit=firstHit;};
  inline void SetSecondHit(JPetHit* secondHit) {fSecondHit=secondHit;};

  
  ClassDef(JPetEvent,1);

  private:
  
  float fTime;
  float fQualityOfTime;
  JPetHit* fFirstHit;
  JPetHit* fSecondHit;
  
};

#endif
