#include "./SDAMatchHits.h"

SDAMatchHits::SDAMatchHits(const char* name, const char* description)
  : JPetTask(name, description),
    fMatched(0),
    fCurrentEventNumber(0)
{
}

SDAMatchHits::~SDAMatchHits()
{
}

void SDAMatchHits::init(const JPetTaskInterface::Options& /* opts */)
{
  fMatched = 0; 
  fCurrentEventNumber=0;
}

void SDAMatchHits::exec()
{
  
  JPetPhysSignal currSignal = (JPetPhysSignal&) (*getEvent());
  
  if (fSignalsArray.empty()) {
    fSignalsArray.push_back(currSignal);
  } else {
    if (fSignalsArray[0].getTimeWindowIndex() == currSignal.getTimeWindowIndex()) {
      fSignalsArray.push_back(currSignal);
    } else {
      saveHits(createHits(fSignalsArray)); //create Hits from previously saved signals
      fSignalsArray.clear();
      fSignalsArray.push_back(currSignal);
    }
  }
  
  fCurrentEventNumber++;
}


void SDAMatchHits::terminate()
{
  int fEventNb = fCurrentEventNumber;
  INFO(
       Form("Matching complete \nAmount of fMatched hits: %d out of initial %d signals" , fMatched, fEventNb) );
}

std::vector<JPetHit> SDAMatchHits::createHits(std::vector<JPetPhysSignal>& signals){

  std::vector<JPetHit> hits;
  
  // group the signals by barrel slot ID
  std::map<int, std::vector<JPetPhysSignal>> signalsBySlot;
  for(auto const & signal : signals){
    int barrelSlotID = signal.getBarrelSlot().getID();
    signalsBySlot[barrelSlotID].push_back(signal);
  }

  // discard entries for PMTs with smalller number of signals than two for each barrel slot
  // since they cannot be merged into JPetHit and later for JPetLOR
  for(std::map<int, std::vector<JPetPhysSignal>>::iterator it = signalsBySlot.begin();
      it != signalsBySlot.end(); ++it){
    if( it->second.size() < 2 ){
      signalsBySlot.erase( it );
    }
  }

  // iterate over barrel slots which had a sufficient number
  // of signals to match a hit
  for(std::map<int, std::vector<JPetPhysSignal>>::iterator it = signalsBySlot.begin();
      it != signalsBySlot.end(); ++it){  
      std::vector<JPetHit> hitsFromSingleSlot = matchHitsWithinSlot(it->second);
      // append the hits found for one specific barrel slot to all hits from this time window
      hits.insert(hits.end(), hitsFromSingleSlot.begin(), hitsFromSingleSlot.end());
  }

  return hits;
}

std::vector<JPetHit> matchHitsWithinSlot(std::vector<JPetPhysSignal> signals){

  std::vector<JPetHit> hits;
  
  for(int i=0;i<signals.size()-1;++i){
    for(int j=i+1;j<signals.size();++j){
      JPetPhysSignal & sig1 = signals.at(i);
      JPetPhysSignal & sig2 = signals.at(j);
      if( sig1.getPM().getSide() == sig2.getPM().getSide() ){
	// @ todo: add more strict rules for deciding whether two signals constitute a hit
	continue;
      }else{
	// ha wave a hit
	JPetHit hit;
	if (sig1.getPM().getSide() == JPetPM::SideA){
	  hit.setSignalA(sig1);
	  hit.setSignalB(sig2);
	}else{
	  hit.setSignalA(sig2);
	  hit.setSignalB(sig1);
	}
	hits.push_back(hit);
      }
    }
  }
  
  return hits;
}

void SDAMatchHits::saveHits(std::vector<JPetHit> hits){
  assert(fWriter);
  fMatched += hits.size();
  for (auto hit : hits) {
    fWriter->write(hit);
  }
}
