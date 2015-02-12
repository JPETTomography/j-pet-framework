/**
 * @file JPetLOR.h
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2013, Damian Trybek
 * @brief Line of Response Class
 */

#ifndef _JPETLOR_H_
#define _JPETLOR_H_

#include "../JPetHit/JPetHit.h"

#include <cstddef>
#include <utility>

class JPetHit;

/**
 * @brief Data class representing an event with two photon hits recorded in the barrel.
 *
 * An event consists of two hits (JPetHit objects) in two barel slots, referred to as "first" and "second" according to their chronological order in a time slot.
 * The user is responsible for setting the first and second hit in the appropriate order
 */
class JPetLOR: public TNamed
{
public:
  JPetLOR();
  JPetLOR(float Time, float QualityOfTime, JPetHit& firstHit,
          JPetHit& secondHit);
  virtual ~JPetLOR();

public:
  /// Get the reconstructed absolute time of the event wrt beginning of the run [ps]
  inline const float getTime() const {
    return fTime;
  }
  ;
  inline const float getQualityOfTime() const {
    return fQualityOfTime;
  }
  ;
  /// Set the reconstructed absolute time of the event wrt beginning of the run [ps]
  inline void setTime(float time) {
    fTime = time;
  }
  ;
  inline void setQualityOfTime(float qualityOfTime) {
    fQualityOfTime = qualityOfTime;
  }
  ;
  inline const JPetHit& getFirstHit() const {
    return fFirstHit;
  }
  ;
  inline const JPetHit& getSecondHit() const {
    return fSecondHit;
  }
  ;

  /**
   * @brief Set both hits of this event at once.
   *
   *
   */
  inline void setHits(JPetHit & firstHit, JPetHit & secondHit) {
    fFirstHit = firstHit;
    fSecondHit = secondHit;
    fIsHitSet[0] = true;
    fIsHitSet[1] = true;
  }

  /**
   * @brief Set the first (earlier) hit of this event.
   *
   * Convention: "first" and "second" hits refer to their chronological order in a time slot.
   */
  inline void setFirstHit(JPetHit & firstHit) {
    fFirstHit = firstHit;
    fIsHitSet[0] = true;
  }

  /**
   * @brief Set the second (later) hit of this event.
   *
   * Convention: "first" and "second" hits refer to their chronological order in a time slot.
   */
  inline void setSecondHit(JPetHit & secondHit) {
    fSecondHit = secondHit;
    fIsHitSet[1] = true;
  }

  /// Set the reconstructed time difference between the two hits of the event [ps]
  inline void setTimeDiff(float td) {
    fTimeDiff = td;
  }
  inline void setQualityOfTimeDiff(float qtd) {
    fQualityOfTime = qtd;
  }
  inline float getTimeDiff() const {
    return fTimeDiff;
  }

ClassDef(JPetLOR,1);

private:

  float fTime; ///< reconstructed absolute time of the event wrt to beginning of the run [ps]
  float fQualityOfTime;

  float fTimeDiff; ///< reconstructed time difference between the two hits of the event [ps]
  float fQualityOfTimeDiff;

  JPetHit fFirstHit;
  JPetHit fSecondHit;
  bool fIsHitSet[2]; ///< true if first (0) or second (1) hit was set; if false, the respective hit object will be existent but empty.

};

#endif
