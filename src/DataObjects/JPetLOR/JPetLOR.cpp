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
 *  @file JPetLOR.cpp
 */

#include "JPetLOR/JPetLOR.h"

ClassImp(JPetLOR);

JPetLOR::JPetLOR():
  TObject(), fFlag(JPetLOR::Unknown), fTime(0.0f), fQualityOfTime(0.0f),
  fTimeDiff(0.0f), fQualityOfTimeDiff(0.0f)
{
  fIsHitSet[0] = false;
  fIsHitSet[1] = false;
}

JPetLOR::JPetLOR(
  float time, float qualityOfTime, JPetHit& firstHit, JPetHit& secondHit):
  TObject(), fFlag(JPetLOR::Unknown), fTime(time), fQualityOfTime(qualityOfTime),
  fTimeDiff(0.0), fQualityOfTimeDiff(0.0),
  fFirstHit(firstHit), fSecondHit(secondHit)
{
  fIsHitSet[0] = true;
  fIsHitSet[1] = true;
}

JPetLOR::JPetLOR(
  float time, float qualityOfTime, float timeDiff, float qualityOfTimeDiff,
  JPetHit& firstHit, JPetHit& secondHit, JPetLOR::RecoFlag flag):
  TObject(), fFlag(flag), fTime(time), fQualityOfTime(qualityOfTime),
  fTimeDiff(timeDiff), fQualityOfTimeDiff(qualityOfTimeDiff),
  fFirstHit(firstHit), fSecondHit(secondHit)
{
  fIsHitSet[0] = true;
  fIsHitSet[1] = true;
}

JPetLOR::~JPetLOR(){}

void JPetLOR::setRecoFlag(JPetLOR::RecoFlag flag)
{
  fFlag = flag;
}

/**
 * Set LOR time in [ps]
 */
void JPetLOR::setTime(const float time) {
	fTime = time;
}

/**
 * Set the value, that describes quality of reconstructed LOR time
 */
void JPetLOR::setQualityOfTime(const float qualityOfTime) {
	fQualityOfTime = qualityOfTime;
}

/**
 * Set LOR time difference [ps]
 */
void JPetLOR::setTimeDiff(const float td) {
	fTimeDiff = td;
}

/**
 * Set the value, that describes quality of LOR time difference.
 */
void JPetLOR::setQualityOfTimeDiff(const float qtd) {
	fQualityOfTimeDiff = qtd;
}

/**
 * Set both hits of this event at once.
 */
void JPetLOR::setHits(const JPetHit& firstHit, const JPetHit& secondHit) {
	fFirstHit = firstHit;
	fSecondHit = secondHit;
	fIsHitSet[0] = true;
	fIsHitSet[1] = true;
}

/**
 * Set the hit, that is first in time.
 */
void JPetLOR::setFirstHit(const JPetHit& firstHit) {
	fFirstHit = firstHit;
	fIsHitSet[0] = true;
}

/**
 * Set the hit, that is second in time.
 */
void JPetLOR::setSecondHit(const JPetHit& secondHit) {
	fSecondHit = secondHit;
	fIsHitSet[1] = true;
}

JPetLOR::RecoFlag JPetLOR::getRecoFlag() const
{
  return fFlag;
}

/**
 * Get LOR time in [ps].
 */
float JPetLOR::getTime() const {
	return fTime;
}

/**
 * Get the value, that describes time reconstruction quality.
 */
float JPetLOR::getQualityOfTime() const {
	return fQualityOfTime;
}

/**
 * Get LOR time difference.
 */
float JPetLOR::getTimeDiff() const {
	return fTimeDiff;
}

/**
 * Get the value, that describes quality of LOR time difference.
 */
float JPetLOR::getQualityOfTimeDiff() const{
	return fQualityOfTimeDiff;
}

/**
 * Get the hit, that is first in time.
 */
const JPetHit& JPetLOR::getFirstHit() const {
	return fFirstHit;
}

/**
 * Get the hit, that is second in time
 */
const JPetHit& JPetLOR::getSecondHit() const {
	return fSecondHit;
}

/**
 * Check if one of two hits, as indicated by index, is set or not.
 */
bool JPetLOR::isHitSet(const unsigned int index){
	switch(index){
		case 0:
			return fIsHitSet[0];
		case 1:
			return fIsHitSet[1];
		default:
			return false;
	};
}

/**
 * @brief Checks whether both hits set in this LOR object come from
 * the different scintillators and are properly time-ordered.
 *
 * @return true if the checks are successful or the LOR does not have both hits set,
 * false if scins are of the same ID, or time ordering is incorrect. Also logs an error message.
 */
bool JPetLOR::checkConsistency() const {
	if(fIsHitSet[0] && fIsHitSet[1]){
		const int scinAID = getFirstHit().getScin().getID();
		const int scinBID = getSecondHit().getScin().getID();
		if(scinAID == scinBID) {
			ERROR(Form("Hits added to LOR come from the same slots: %d." , scinAID));
			return false;
		}
		if(getFirstHit().getTime() > getSecondHit().getTime()){
			ERROR("Hits added to LOR are not in chronological order.");
			return false;
		}
	}
	return true;
}

/**
 * Resets LOR values to zero/false.
 */
void JPetLOR::Clear(Option_t *){
  fFlag = JPetLOR::Unknown;
  fTime = 0.0;
  fQualityOfTime = 0.0;
  fTimeDiff = 0.0;
  fQualityOfTimeDiff = 0.0;
  fIsHitSet[0] = false;
  fIsHitSet[1] = false;
}
