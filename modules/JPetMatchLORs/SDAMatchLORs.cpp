#include "./SDAMatchLORs.h"

SDAMatchLORs::SDAMatchLORs(const char* name, const char* description) : 
  JPetTask(name, description),
  fMatched(0),
  fCurrentEventNumber(0)
{
}

SDAMatchLORs::~SDAMatchLORs()
{
	
}

void SDAMatchLORs::init(const JPetTaskInterface::Options& /* opts */)
{
  fMatched=0;
  fCurrentEventNumber=0;  
}

void SDAMatchLORs::exec()
{

  JPetHit currHit = (JPetHit&)(*getEvent());
  
  if (fHitsArray.empty()) {
    fHitsArray.push_back(currHit);
  } else {
    if (fHitsArray[0].getTimeWindowIndex() == currHit.getTimeWindowIndex()) {
      fHitsArray.push_back(currHit);
    } else {
      saveLORs(createLORs(fHitsArray)); //create LORs from Hits from the same Time Window
      fHitsArray.clear();
      fHitsArray.push_back(currHit);
    }
  }
  
  fCurrentEventNumber++;

}


void SDAMatchLORs::terminate()
{
  int fEventNb = fCurrentEventNumber;
  INFO(
       Form("Matching complete \nAmount of LORs mathed: %d out of %d hits" , fMatched, fEventNb) );
  double goodPercent = fMatched* 100.0 /fEventNb ;
  INFO(
       Form("%f %% of data was matched \n " , goodPercent) );
}


std::vector<JPetLOR> SDAMatchLORs::createLORs(std::vector<JPetHit>& hits){

  std::vector<JPetLOR> lors;
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
  assert(fWriter);
  fMatched += lors.size();
  for (auto lor : lors) {
    fWriter->write(lor);
  }
}
