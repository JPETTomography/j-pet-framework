#include "Unpacker_TRB2.h"
#include <iostream>

using namespace std;

ClassImp(Unpacker_TRB2);

Unpacker_TRB2::Unpacker_TRB2(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg) : UnpackingModule(bT, bA, hA, cN, o, r, mR, dec, dbg) {
  cerr<<"TRB2: Creating Unpacker_TRB2 for board type: "<<bT<<" board address "<<bA<<" hub address "<<hA<<endl;
}

void Unpacker_TRB2::ProcessEvent(UInt_t* data, Event* evt) {
  event = evt;
  
  // clear internal unpackers
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
  size_t dataSize = data_i & 0xffff;
  data += 2; // skip to the first data word
  dataSize -= 2;
  UInt_t tdcNumber = 0;
  
  
  if(debugMode == true)
    cerr<<"Unpacker_TRB2.cc: Receiving "<<dataSize<<" words to analyze"<<endl;
  
  if (dataSize > 10000) {
    cerr<<"WARNING: event size too large, skipping event"<<endl;
//     cerr<<"         Dumping first data bytes:"<<endl;
//     
//     int ctr = 50;
//     while(ctr > 0) {
//       printf("%04X\n", (*data));
//       data++;
//       ctr--;
//     }
  }
  else {
    
    // iterate through all the 32b words of the current event
    while(dataSize > 0) {
      
      if(GetInvertBytes() == true) {
	data_i = ReverseHex((*data));
      }
      else {
	data_i = (*data);
      }
      
      // read out the address and redirect data to the correct internal unpacker
      tdcNumber = (data_i >> 24) & 0xf;
      
      GetUnpacker(UIntToString(tdcNumber))->ProcessEvent(data);
      
      data++;
      dataSize--;
    }
  }
}

void Unpacker_TRB2::GetADCHits() { }

void Unpacker_TRB2::GetTDCHits() {
  map<std::string, UnpackingModule*>::iterator iter;
  
  for(iter = GetInternalUnpackersIterBegin(); iter != GetInternalUnpackersIterEnd(); iter++) {
  
    if(iter->second->GetMeasurementType() == "TDC") {
    
      for(int i = 0; i < iter->second->GetChannelNumber(); i++) {
	
	if (iter->second->GetLeadMult(i) > 0 || iter->second->GetTrailMult(i) > 0 ) {
	  
	  TDCHit* hit = event->AddTDCHit(iter->second->GetChannelOffset() + i);
	
	  if(iter->second->GetLeadMult(i) > 0) {
	    
	    if(iter->second->GetChannelOffset() + i == referenceChannel) {
	      event->SetTDCReferenceTime(iter->second->GetLeadTime(i, 0));    
	      
	      if(debugMode == true)
		cerr<<"Unpacker_TRB2.cc: Adding referenceTime"<<endl;
	    }
	    
	    for(UInt_t j = 0; j < iter->second->GetLeadMult(i); j++)
	      hit->AddLeadTime(iter->second->GetLeadTime(i, j));
	  }
	  
	  if(iter->second->GetTrailMult(i) > 0) {
	    for(UInt_t j = 0; j < iter->second->GetTrailMult(i); j++)
	      hit->AddTrailTime(iter->second->GetTrailTime(i, j));
	  }
	  
	  if(iter->second->GetFirstLeadCorrect(i) == true && iter->second->GetTrailMult(i) > 0)
	    hit->AddTot(iter->second->GetTrailTime(i, 0) - iter->second->GetLeadTime(i, 0));
	}
	
      }
    }
  }
}