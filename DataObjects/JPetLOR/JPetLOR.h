/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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
 */

#ifndef _JPETLOR_H_
#define _JPETLOR_H_

#include "./JPetHit/JPetHit.h"
#include <cstddef>
#include <utility>

class JPetHit;

/**
 * @brief Line of Response data class is a representation of an event
 * with two photon hits recorded in the barrel.
 *
 * LOR is an event that consists of two hits (JPetHit objects) in two barel slots,
 * referred to as "first" and "second" according to their chronological order
 * in a time slot. The user is responsible for setting the first and second hit
 * in the appropriate order. The LOR reconstructed absolute time is to be set
 * with respect to beginning of the run in [ps].
 */
class JPetLOR: public TObject
{
public:
  JPetLOR();
  JPetLOR(float time, float qualityOfTime, JPetHit& firstHit, JPetHit& secondHit);
  virtual ~JPetLOR();

	float getTime() const;
	float getQualityOfTime() const;
	void setTime(const float time);
	void setQualityOfTime(const float qualityOfTime);
	const JPetHit& getFirstHit() const;
	const JPetHit& getSecondHit() const;
  void setHits(const JPetHit& firstHit,const JPetHit& secondHit);
  void setFirstHit(const JPetHit& firstHit);
  void setSecondHit(const JPetHit& secondHit);
  void setTimeDiff(const float td);
  void setQualityOfTimeDiff(const float qtd);
  float getTimeDiff() const;
  float getQualityOfTimeDiff() const;
  bool isHitSet(const unsigned int index);
  bool isFromSameBarrelSlot() const;
  void Clear(Option_t * opt = "");

  ClassDef(JPetLOR,3);

private:
  float fTime;
  float fQualityOfTime;
  float fTimeDiff;
  float fQualityOfTimeDiff;
  bool fIsHitSet[2];
  JPetHit fFirstHit;
  JPetHit fSecondHit;
};

#endif
