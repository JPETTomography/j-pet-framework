#include "Unpacker_TRB3.h"
#include <iostream>

using namespace std;

//ClassImp(Unpacker_TRB3);

Unpacker_TRB3::Unpacker_TRB3(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg) : UnpackingModule(bT, bA, hA, cN, o, r, mR, dec, dbg) {
  if(VERBOSE) cerr<<"TRB3: Creating Unpacker_TRB3 for board type: "<<bT<<" board address "<<bA<<" hub address "<<hA<<endl;
}

void Unpacker_TRB3::ProcessEvent(UInt_t* data, Event* evt) {
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
  //size_t dataSize = data_i >> 16;
  size_t dataSize = GetEntireEventSize();
  //data += 2; // skip to the first data word
  //dataSize -= 2;
  UInt_t tdcNumber = 0;
  
  if(debugMode == true)
    if(VERBOSE) cerr<<"Unpacker_TRB3.cc: Receiving "<<dataSize<<" words to analyze"<<endl;
  
//  if (dataSize > 10000) {
//    cerr<<"WARNING: event size too large, skipping event"<<endl;
//     cerr<<"         Dumping first data bytes:"<<endl;
//     
//     int ctr = 50;
//     while(ctr > 0) {
//       printf("%04X\n", (*data));
//       data++;
//       ctr--;
//     }
//  }
 // else {
    
    // iterate through all the 32b words of the current event
    while(dataSize > 0) {
      
      if(GetInvertBytes() == true) {
	data_i = ReverseHex((*data));
      }
      else {
	data_i = (*data);
      }
      
      // read out the address and redirect data to the correct internal unpacker
      //tdcNumber = (data_i >> 24) & 0xf;
      tdcNumber = data_i & 0xffff;
      
      size_t internalSize = data_i >> 16;     
      
      UnpackingModule* u = GetUnpacker(UIntToString(tdcNumber));
      if (u != NULL) {
	if(debugMode == true)
		if(VERBOSE) cerr<<"Unpacker_TRB3.cc: Calling Lattice_TDC for module "<<UIntToString(tdcNumber)<<" passing "<<internalSize<<" bytes"<<endl;
	GetUnpacker(UIntToString(tdcNumber))->SetEntireEventSize(internalSize + 1);
	GetUnpacker(UIntToString(tdcNumber))->ProcessEvent(data);
      }
      else {
	if(debugMode == true)
		if(VERBOSE) cerr<<"Unpacker_TRB3.cc: No Unpacker found for module "<<UIntToString(tdcNumber)<<" skipping "<<internalSize<<" bytes"<<endl;
      }
      
      data += internalSize + 1;
      dataSize -= (internalSize + 1) * 4;
    }
  //}
}

//void Unpacker_TRB3::GetADCHits() { }

void Unpacker_TRB3::GetTDCHits() {
  map<std::string, UnpackingModule*>::iterator iter;  
  
  for(iter = GetInternalUnpackersIterBegin(); iter != GetInternalUnpackersIterEnd(); iter++) {
    if(iter->second->GetMeasurementType() == "TDC") {
	  
      event->SetErrorBits(iter->second->GetErrorBits());
    
      for(int i = 0; i < iter->second->GetChannelNumber(); i++) {
	
				if (iter->second->GetLeadMult(i) > 0 || iter->second->GetTrailMult(i) > 0 ) {
			
					TDCHit* hit = event->AddTDCHit(iter->second->GetChannelOffset() + i);
	
					if(iter->second->GetLeadMult(i) > 0) {
					
						if(iter->second->GetChannelOffset() + i == referenceChannel) {
							
//							if(debugMode == true)
//								cerr<<"Unpacker_TRB3.cc: Adding referenceTime at position "<<(iter->second->GetChannelOffset() + i)<<endl;
						}
					
						for(Int_t j = 0; j < iter->second->GetLeadMult(i); j++){
							hit->AddLeadTime(iter->second->GetLeadFineTime(i, j), iter->second->GetLeadCoarseTime(i, j), iter->second->GetLeadEpoch(i, j));
						}
					}
			
					if(iter->second->GetTrailMult(i) > 0) {
						for(Int_t j = 0; j < iter->second->GetTrailMult(i); j++) {
							hit->AddTrailTime(iter->second->GetTrailFineTime(i, j), iter->second->GetTrailCoarseTime(i, j), iter->second->GetTrailEpoch(i, j));
						}
					}
				}
	
      }
    }
  }
}
