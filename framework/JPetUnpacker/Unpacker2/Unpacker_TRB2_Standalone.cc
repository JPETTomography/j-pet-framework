#include "Unpacker_TRB2_Standalone.h"
#include <iostream>

using namespace std;

ClassImp(Unpacker_TRB2_Standalone);

Unpacker_TRB2_Standalone::Unpacker_TRB2_Standalone(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec) : UnpackingModule(bT, bA, hA, cN, o, r, mR, dec) {
  cerr<<"TRB2_STND: Creating Unpacker_TRB2_Standalone for board type: "<<bT<<" board address "<<bA<<" hub address "<<hA<<endl;
}

void Unpacker_TRB2_Standalone::ProcessEvent(UInt_t* data, Event* evt) {
  event = evt;
  
  // clear internal unpackers
  //cerr<<"TRB2_STND: clearing internals"<<endl;
  map<std::string, UnpackingModule*>::iterator iter;
  for(iter = GetInternalUnpackersIterBegin(); iter != GetInternalUnpackersIterEnd(); iter++) {
    iter->second->Clear();
  }
  
  UInt_t data_i = 0;
  if(GetInvertBytes() == true) {
    data_i = ReverseHex((*data));
  }
  else {
    data_i = (*data);
  }
  
  // get the size of the data in the event
  //size_t dataSize = (*data) & 0xffff;
  size_t dataSize = data_i & 0xffff;
  data += 2; // skip to the first data word
  dataSize -= 2;
  UInt_t tdcNumber = 0;
  
  // iterate through all the 32b words of the current event
  while(dataSize > 0) {
    
    if(GetInvertBytes() == true) {
      data_i = ReverseHex((*data));
    }
    else {
      data_i = (*data);
    }
    
    // read out the address and redirect data to the correct internal unpacker
    //tdcNumber = ((*data) >> 24) & 0xf;
    tdcNumber = (data_i >> 24) & 0xf;
    GetUnpacker(UIntToString(tdcNumber))->ProcessEvent(data);
    
    data++;
    dataSize--;
  }  
}

void Unpacker_TRB2_Standalone::GetADCHits() { }

void Unpacker_TRB2_Standalone::GetTDCHits() {
  map<std::string, UnpackingModule*>::iterator iter;
  
  for(iter = GetInternalUnpackersIterBegin(); iter != GetInternalUnpackersIterEnd(); iter++) {
  
    if(iter->second->GetMeasurementType() == "TDC") {
    
      for(int i = 0; i < iter->second->GetChannelNumber(); i++) {
	
	if (iter->second->GetLeadMult(i) > 0 || iter->second->GetTrailMult(i) > 0 ) {
	  
	  TDCHit* hit = event->AddTDCHit(iter->second->GetChannelOffset() + i);
	
	  if(iter->second->GetLeadMult(i) > 0) {
	    for(UInt_t j = 0; j < iter->second->GetLeadMult(i); j++)
	      hit->AddLeadTime(iter->second->GetLeadTime(i, j));
	  }
	  
	  if(iter->second->GetTrailMult(i) > 0) {
	    for(UInt_t j = 0; j < iter->second->GetTrailMult(i); j++)
	      hit->AddTrailTime(iter->second->GetTrailTime(i, j));
	  }
	  
	  if(iter->second->GetFirstLeadCorrect(i) == true)
	    hit->AddTot(10); //iter->second->GetTrailTime(i, 0) - iter->second->GetLeadTime(i, 0));
	}
	
      }
    }
  }
}