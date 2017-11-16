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
 *  @file JPetLOR.cpp
 */

#include "./JPetLOR.h"

ClassImp(JPetLOR);

JPetLOR::JPetLOR() :
    TObject(),
    fTime(0.0f), 
    fQualityOfTime(0.0f),
    fTimeDiff(0.0f), 
    fQualityOfTimeDiff(0.0f)
{
  fIsHitSet[0] = false;
  fIsHitSet[1] = false;
}

JPetLOR::JPetLOR(float Time, float QualityOfTime, JPetHit& firstHit,
                 JPetHit& secondHit) :
    TObject(), 
    fTime(Time),
    fQualityOfTime(QualityOfTime),
    fTimeDiff(0.0f),
    fQualityOfTimeDiff(0.0f),
    fFirstHit(firstHit), 
    fSecondHit(secondHit)
{
  fIsHitSet[0] = true;
  fIsHitSet[1] = true;
}

JPetLOR::~JPetLOR(){}

float JPetLOR::getTime() const {
	return fTime;
}
float JPetLOR::getQualityOfTime() const{
	return fQualityOfTime;
}
void JPetLOR::setTime(const float time){
	fTime = time;
}
void JPetLOR::setQualityOfTime(const float qualityOfTime) {
	fQualityOfTime = qualityOfTime;
}
const JPetHit& JPetLOR::getFirstHit() const {
	return fFirstHit;
}
const JPetHit& JPetLOR::getSecondHit() const {
	return fSecondHit;
}
void JPetLOR::setHits(const JPetHit& firstHit, const JPetHit& secondHit) {
	fFirstHit = firstHit;
	fSecondHit = secondHit;
	fIsHitSet[0] = true;
	fIsHitSet[1] = true;
}
void JPetLOR::setFirstHit(const JPetHit& firstHit) {
	fFirstHit = firstHit;
	fIsHitSet[0] = true;
}
void JPetLOR::setSecondHit(const JPetHit& secondHit) {
	fSecondHit = secondHit;
	fIsHitSet[1] = true;
}
void JPetLOR::setTimeDiff(const float td) {
	fTimeDiff = td;
}
void JPetLOR::setQualityOfTimeDiff(const float qtd) {
	fQualityOfTime = qtd;
}
float JPetLOR::getTimeDiff() const {
	return fTimeDiff;
}
float JPetLOR::getQualityOfTimeDiff() const{
	return fQualityOfTimeDiff;
}
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

bool JPetLOR::isFromSameBarrelSlot() const {  
	if(fIsHitSet[0]&&fIsHitSet[1] ){// do not claim inconsistency if signals are not set yet
		const int slot_a = getFirstHit().getBarrelSlot().getID();
		const int slot_b = getSecondHit().getBarrelSlot().getID();
		if( slot_a == slot_b ){
			ERROR( Form("Hits added to LOR come from the same barrel slots: %d." ,slot_a) );
			return false; 
		}
		
		if( getFirstHit().getTime() > getSecondHit().getTime() ){
			ERROR( "Hits added to LOR are not in chronological order." );
			return false; 
		}
	}
	return true;
}

void JPetLOR::Clear(Option_t *){
  fTime = 0.0f;
  fQualityOfTime = 0.0f;
  fTimeDiff = 0.0f;
  fQualityOfTimeDiff = 0.0f;
  fIsHitSet[0] = false;
  fIsHitSet[1] = false;  
}
