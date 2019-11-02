/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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

#ifndef JPETLOR_H
#define JPETLOR_H

#include "JPetHit/JPetHit.h"
#include <cstddef>
#include <utility>

class JPetHit;

/**
 * @brief Line of Response data class is a representation of an event
 * with two photon hits recorded in the barrel.
 *
 * LOR is an event that consists of two hits (JPetHit objects) in two slots,
 * referred to as "first" and "second" according to their chronological order
 * in a time slot. The user is responsible for setting the first and second hit
 * in the appropriate order. The LOR reconstructed absolute time is to be set
 * with respect to beginning of the run in [ps].
 */
class JPetLOR: public TObject
{
public:
  enum RecoFlag { Good, Corrupted, Unknown };

  JPetLOR();
  JPetLOR(
    float time, float qualityOfTime, JPetHit& firstHit, JPetHit& secondHit
  );
  JPetLOR(
    float time, float qualityOfTime, float timeDiff, float qualityOfTimeDiff,
    JPetHit& firstHit, JPetHit& secondHit, JPetLOR::RecoFlag flag
  );
  virtual ~JPetLOR();

  void setRecoFlag(JPetLOR::RecoFlag flag);
  void setTime(const float time);
  void setQualityOfTime(const float qualityOfTime);
  void setTimeDiff(const float td);
  void setQualityOfTimeDiff(const float qtd);
  void setHits(const JPetHit& firstHit, const JPetHit& secondHit);
  void setFirstHit(const JPetHit& firstHit);
  void setSecondHit(const JPetHit& secondHit);

  JPetLOR::RecoFlag getRecoFlag() const;
  float getTime() const;
  float getQualityOfTime() const;
  float getTimeDiff() const;
  float getQualityOfTimeDiff() const;
  const JPetHit& getFirstHit() const;
  const JPetHit& getSecondHit() const;

  bool isHitSet(const unsigned int index);
  bool checkConsistency() const;
  void Clear(Option_t* opt = "");

private:
  RecoFlag fFlag = JPetLOR::Unknown;
  float fTime;
  float fQualityOfTime;
  float fTimeDiff;
  float fQualityOfTimeDiff;
  bool fIsHitSet[2];
  JPetHit fFirstHit;
  JPetHit fSecondHit;

  ClassDef(JPetLOR, 6);
};

#endif /* !JPETLOR_H */
