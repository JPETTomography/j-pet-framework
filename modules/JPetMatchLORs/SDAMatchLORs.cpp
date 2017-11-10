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
 *  @file SDAMatchLORs.cpp
 */

#include "SDAMatchLORs.h"
using namespace std;
SDAMatchLORs::SDAMatchLORs(const char* name) : 
  JPetUserTask(name),
  fMatched(0),
  fCurrentEventNumber(0)
{
}

SDAMatchLORs::~SDAMatchLORs(){}

bool SDAMatchLORs::init()
{
  fMatched=0;
  fCurrentEventNumber=0;  
  return true;
}

bool SDAMatchLORs::exec(){
	if(auto currHit = dynamic_cast<const JPetHit*const>(fEvent)){
		if (fHitsArray.empty()) {
			fHitsArray.push_back(*currHit);
		} else {
			if (fHitsArray[0].getTimeWindowIndex() == currHit->getTimeWindowIndex()) {
				fHitsArray.push_back(*currHit);
			} else {
				saveLORs(createLORs(fHitsArray)); //create LORs from Hits from the same Time Window
				fHitsArray.clear();
				fHitsArray.push_back(*currHit);
			}
		}
		fCurrentEventNumber++;
	}
	return true;
}


bool SDAMatchLORs::terminate()
{
  int fEventNb = fCurrentEventNumber;
  INFO(Form("Matching complete \nAmount of LORs mathed: %d out of %d hits" , fMatched, fEventNb) );
  double goodPercent = fMatched* 100.0 /fEventNb ;
  INFO(Form("%f %% of data was matched \n " , goodPercent) );
  return true;
}

vector<JPetLOR> SDAMatchLORs::createLORs(vector<JPetHit>& hits){
  vector<JPetLOR> lors;
  for (auto i = hits.begin(); i != hits.end(); ++i) {
    for (auto j = i + 1; j != hits.end(); ++j ) {
      JPetHit & hit1 = *i;
      JPetHit & hit2 = *j;
      // @ todo: add more strict rules for deciding whether two hits constitute a LOR
      if (hit1.getScintillator() != hit2.getScintillator()) {
	// found 2 hits in different scintillators -> an event!
	
	// create an event object
	JPetLOR event;
	// convention: "first hit" is the one with earlier time
	if (hit1.getTime() < hit2.getTime()) {
	  event.setFirstHit(hit1);
	  event.setSecondHit(hit2);
	} else {
	  event.setFirstHit(hit2);
	  event.setSecondHit(hit1);
	}
	lors.push_back(event);
      }
    }
  }
  return lors;
}


void SDAMatchLORs::saveLORs(std::vector<JPetLOR> lors){
  fMatched += lors.size();
  for (auto&lor : lors) {
    // @todo: replace with fOutputEvents
    //    fWriter->write(lor);
  }
}

