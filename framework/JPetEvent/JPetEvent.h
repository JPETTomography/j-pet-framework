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

  typedef std::pair<JPetHit*,JPetHit*> JPetHits;
  
  JPetEvent();
  JPetEvent(float Time, float QualityOfTime, JPetHits& Hits);
  virtual ~JPetEvent();
  inline const float GetTime() const {return fTime;};
  inline const float GetQualityOfTime() const {return fQualityOfTime;};
  inline void SetTime(float time) {fTime = time;};
  inline void SetQualityOfTime(float qualityOfTime) {fQualityOfTime = qualityOfTime;};
  inline const JPetHit& GetHitFirst() const {return *fHits->first;};
  inline const JPetHit& GetHitSecond() const {return *fHits->second;};
  inline const JPetHits& GetHits() const {return *fHits;};
  inline void SetHits(JPetHits* hits) {fHits = hits;};
  inline void SetHits(JPetHits& hits) {fHits = &hits;};
  inline void SetHits(JPetHit* firstHit, JPetHit* secondHit) {
              fHits->first = firstHit;
	      fHits->second = secondHit;};
  
  ClassDef(JPetEvent,1);

  private:
  
  float fTime;
  float fQualityOfTime;
  JPetHits* fHits;
  
};

#endif
