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

/**
 * @brief A class representing an event with two photon hits recorded in the barrel.
 *
 * An event consists of two hits (JPetHit objects) in two barel slots.
 */
class JPetEvent: public TNamed {
  
  public:

  //typedef std::pair<JPetHit*,JPetHit*> JPetHits;
  
  JPetEvent();
  JPetEvent(float Time, float QualityOfTime, JPetHit& firstHit, JPetHit& secondHit);
  virtual ~JPetEvent();
  /// Get the reconstructed absolute time of the event wrt beginning of the run
  inline const float GetTime() const {return fTime;};
  inline const float GetQualityOfTime() const {return fQualityOfTime;};
  /// Set the reconstructed absolute time of the event wrt beginning of the run
  inline void SetTime(float time) {fTime = time;};
  inline void SetQualityOfTime(float qualityOfTime) {fQualityOfTime = qualityOfTime;};
  inline const JPetHit& GetFirstHit() const {return fFirstHit;};
  inline const JPetHit& GetSecondHit() const {return fSecondHit;};
  /**
   * @brief Access the hits of the event as elements if an array
   *
   * @param i should be either 0 or 1 as the event can have 0-2 hits
   */
  const JPetHit & operator[](int i) const;
  //inline const JPetHits& GetHits() const {return *fHits;};
  // inline void SetHits(JPetHits* hits) {fHits = hits;};
  // inline void SetHits(JPetHits& hits) {fHits = &hits;};
  /**
   * @brief Set both hits of this event at once.
   */
  inline void SetHits(JPetHit & firstHit, JPetHit & secondHit) {
    fFirstHit = firstHit;
    fSecondHit = secondHit;
    fNhits = 2;
  }
  /**
   * @brief Set the first hit of this event.
   *
   * Using this method the user is responsible for controlling which hit is first and second and ensuring that both hits of the events are set. 
   */
  inline void SetFirstHit(JPetHit & firstHit) {fFirstHit = firstHit; }
  /**
   * @brief Set the second hit of this event.
   *
   * Using this method the user is responsible for controlling which hit is first and second and ensuring that both hits of the events are set.
   */
  inline void SetSecondHit(JPetHit & secondHit) {fSecondHit = secondHit; };
  /**
   * @brief Add a JPetHit object to this event
   *
   * Use this method and the [] operator rather than Set(Get)FirstHit and Set(Get)SecondHit if you don't want to manually control which hit is first and which second. Just call AddHit twice to set the hits in the event. They can be later accessed as event[0] and event[1].
   *
   * @return number of hits set in this event after adding the provided hit (i.e. 1 or 2), or 0 if the event already had two set hits (and the new hit was not added).
   */
  int AddHit(JPetHit & hit);
  /// Set the reconstructed time difference between the two hits of the event
  inline void SetTimeDiff(float td) {fTimeDiff = td;}
  inline void SetQualityOfTimeDiff(float qtd) {fQualityOfTime = qtd;}

  ClassDef(JPetEvent,1);

  private:
  
  float fTime; ///< reconstructed absolute time of the event wrt to beginning of the run
  float fQualityOfTime;
  
  float fTimeDiff; ///< reconstructed time difference between the two hits of the event
  float fQualityOfTimeDiff;

  JPetHit fFirstHit;
  JPetHit fSecondHit;
  float fNhits;

};

#endif
