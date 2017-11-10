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
 *  @file SDAMatchHits.cpp
 */

#include "SDAMatchHits.h"
using namespace std;
SDAMatchHits::SDAMatchHits(const char* name)
  : JPetUserTask(name),
    fMatched(0),
    fCurrentEventNumber(0)
{
}

SDAMatchHits::~SDAMatchHits()
{
}

bool SDAMatchHits::init()
{
  fMatched = 0;
  fCurrentEventNumber = 0;

  return true;
}

bool SDAMatchHits::exec()
{
  if (auto currSignal = dynamic_cast<const JPetPhysSignal* const>(fEvent)) {
    if (fSignalsArray.empty()) {
      fSignalsArray.push_back(*currSignal);
    } else {
      if (fSignalsArray[0].getTimeWindowIndex() == currSignal->getTimeWindowIndex()) {
        fSignalsArray.push_back(*currSignal);
      } else {
        saveHits(createHits(fSignalsArray)); //create Hits from previously saved signals
        fSignalsArray.clear();
        fSignalsArray.push_back(*currSignal);
      }
    }
    fCurrentEventNumber++;
  }
  return true;
}

bool SDAMatchHits::terminate()
{
  int fEventNb = fCurrentEventNumber;
  INFO(Form("Matching complete \nAmount of fMatched hits: %d out of initial %d signals" , fMatched, fEventNb) );
  return true;
}

vector<JPetHit> SDAMatchHits::createHits(vector<JPetPhysSignal>& signals)
{
  vector<JPetHit> hits;

  // group the signals by barrel slot ID
  map<int, vector<JPetPhysSignal>> signalsBySlot;
  for (auto const& signal : signals) {
    int barrelSlotID = signal.getRecoSignal().getBarrelSlot().getID();
    signalsBySlot[barrelSlotID].push_back(signal);
  }

  // discard entries for PMTs with smalller number of signals than two for each barrel slot
  // since they cannot be merged into JPetHit and later for JPetLOR
  for (auto it = signalsBySlot.begin(); it != signalsBySlot.end(); ++it) {
    if ( it->second.size() < 2 ) {
      signalsBySlot.erase( it );
    }
  }

  // iterate over barrel slots which had a sufficient number
  // of signals to match a hit
  for (auto it = signalsBySlot.begin(); it != signalsBySlot.end(); ++it) {
    vector<JPetHit> hitsFromSingleSlot = matchHitsWithinSlot(it->second);
    // append the hits found for one specific barrel slot to all hits from this time window
    hits.insert(hits.end(), hitsFromSingleSlot.begin(), hitsFromSingleSlot.end());
  }
  return hits;
}

std::vector<JPetHit> SDAMatchHits::matchHitsWithinSlot(std::vector<JPetPhysSignal> signals)
{
  vector<JPetHit> hits;

  for (size_t i = 0; i < signals.size() - 1; ++i) {
    for (size_t j = i + 1; j < signals.size(); ++j) {
      JPetPhysSignal& sig1 = signals.at(i);
      JPetPhysSignal& sig2 = signals.at(j);
      if ( sig1.getPM().getSide() == sig2.getPM().getSide() ) {
        // @ todo: add more strict rules for deciding whether two signals constitute a hit
        continue;
      } else {
        // ha wave a hit
        JPetHit hit;
        if (sig1.getPM().getSide() == JPetPM::SideA) {
          hit.setSignalA(sig1);
          hit.setSignalB(sig2);
        } else {
          hit.setSignalA(sig2);
          hit.setSignalB(sig1);
        }
        hit.setBarrelSlot(sig1.getPM().getBarrelSlot());
        hit.setScintillator(sig1.getPM().getScin());
        hits.push_back(hit);
      }
    }
  }
  return hits;
}

void SDAMatchHits::saveHits(std::vector<JPetHit> hits)
{
  fMatched += hits.size();
  for (auto hit : hits)
    // @todo: replace with fOutputEvents
    ;
    //    fWriter->write(hit);
}
