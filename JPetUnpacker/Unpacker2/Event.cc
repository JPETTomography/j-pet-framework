#include <iostream>
#include "Event.h"

using namespace std;

ClassImp(Event);

Event::Event() {   
  TDCHits = new TClonesArray("TDCHitExtended", 2100);
//TDCHits = new TClonesArray("TDCHit", 1000);
//  ADCHits = new TClonesArray("ADCHit", 1000);
  
  TDCHits->Delete();
//  ADCHits->Delete();
  
  totalNTDCHits = 0;
//  totalNADCHits = 0;
  
  TDCReferenceTime = 0;
  
  errorBits = 0;
}

TDCHit* Event::AddTDCHit(int channel) {
  //cerr<<"Event: adding TDC hit on channel "<<channel<<endl;
  TClonesArray& thits = *TDCHits;
  TDCHit* hit = new (thits[totalNTDCHits++]) TDCHit();
  hit->SetChannel(channel);
  return hit;
}

TDCHitExtended* Event::AddTDCHitExtended(int channel) {
  //cerr<<"Event: adding TDC hit on channel "<<channel<<endl;
  TClonesArray& thits = *TDCHits;
  TDCHitExtended* hit = new (thits[totalNTDCHits++]) TDCHitExtended();
  hit->SetChannel(channel);
  return hit;
}

/*ADCHit* Event::AddADCHit(int channel) {
  //cerr<<"Event: adding ADC hit"<<endl;
  TClonesArray& ahits = *ADCHits;
  ADCHit* hit = new (ahits[totalNADCHits++]) ADCHit();
  hit->SetChannel(channel);
  return hit;
}*/

void Event::Clear(void) {  
  TDCHits->Delete();
//  ADCHits->Delete();
  
  totalNTDCHits = 0;
//  totalNADCHits = 0;  
  
  TDCReferenceTime = 0;
}
