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
 *  @file JPetLOR.h
 *  @brief Line of Response Class
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
class JPetLOR: public TObject
{
public:
  JPetLOR();
  JPetLOR(float Time, float QualityOfTime, JPetHit& firstHit,
          JPetHit& secondHit);
  virtual ~JPetLOR();

public:
	float getTime() const;
	float getQualityOfTime() const;
	void setTime(const float time);
	void setQualityOfTime(const float qualityOfTime);
	const JPetHit& getFirstHit() const;
	const JPetHit& getSecondHit() const;

  /**
   * @brief Set both hits of this event at once.
   *
   *
   */
  void setHits(const JPetHit & firstHit,const JPetHit & secondHit);

  /**
   * @brief Set the first (earlier) hit of this event.
   *
   * Convention: "first" and "second" hits refer to their chronological order in a time slot.
   */
  void setFirstHit(const JPetHit & firstHit);

  /**
   * @brief Set the second (later) hit of this event.
   *
   * Convention: "first" and "second" hits refer to their chronological order in a time slot.
   */
  void setSecondHit(const JPetHit & secondHit);

  void setTimeDiff(const float td);
  void setQualityOfTimeDiff(const float qtd);
  float getTimeDiff() const;
  float getQualityOfTimeDiff() const;
  bool isHitSet(const unsigned int index);
  
ClassDef(JPetLOR,3);

/** @brief Checks whether both Hit objects set in this LOR object
 *  come from different barrel slots and are properly time-ordered
 *  and logs an error message if not.
 *
 *  Pairing two hits from the same Barrel Slot (i.e. from the same scintillator)
 *  into a LOR would make no physical sense. This method ensures that it is not the case.
 *  Moreover, by convention the First Hit should have and earlier time that Second Hit.
 *  This method also ensures
 * 
 *  If the signals come from the same barrel slot and opposite-side PMTs, 
 *  this method only returns true.
 *  Otherwise, false is returned and an appropriate error message is logged.
 *
 *  @return true if both signals are consistently from the same barrel slot.
 */
bool isFromSameBarrelSlot() const; 

  void Clear(Option_t * opt = "");

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
