#include "Unpacker_Shower.h"
#include <iostream>
#include "Unpacker_Ecal_ADC.h"

using namespace std;

ClassImp(Unpacker_Shower);

Unpacker_Shower::Unpacker_Shower(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg) : UnpackingModule(bT, bA, hA, cN, o, r, mR, dec, dbg) {
  cerr<<"SHW: Creating Unpacker_Shower for board type: "<<bT<<" board address "<<bA<<" hub address "<<hA<<endl;
}

void Unpacker_Shower::ProcessEvent(UInt_t* data, Event* evt) {
  event = evt;
  
  // clear internal unpackers
  map<std::string, UnpackingModule*>::iterator iter;
  for(iter = GetInternalUnpackersIterBegin(); iter != GetInternalUnpackersIterEnd(); iter++) {
    iter->second->Clear();
  }
  
  size_t dataSize = GetEntireEventSize();
  
  // iterate through all the 32b words of the current event
  while(dataSize > 0) {
    
    UInt_t data_i = 0;
    if(GetInvertBytes() == true) {
      data_i = ReverseHex((*data));
    }
    else {
      data_i = (*data);
    }

    UInt_t internalSize = data_i >> 16;
    UInt_t addr = data_i & 0xffff;  

    UnpackingModule* u = GetUnpacker(UIntToString(addr));
    if (u != NULL) {
      GetUnpacker(UIntToString(addr))->SetEntireEventSize(internalSize + 1);
      GetUnpacker(UIntToString(addr))->ProcessEvent(data, evt);
    }

    data += internalSize + 1;
    dataSize -= (internalSize + 1) * 4;
  }
}

void Unpacker_Shower::GetADCHits() {
  map<std::string, UnpackingModule*>::iterator iter;
  
  for(iter = GetInternalUnpackersIterBegin(); iter != GetInternalUnpackersIterEnd(); iter++) {
  
    if(iter->second->GetMeasurementType() == "ADC") {
    
      for(int i = 0; i < iter->second->GetChannelNumber(); i++) {
	  
	ADCHit* hit = event->AddADCHit(iter->second->GetChannelOffset() + i);
	
// 	if(debugMode == true) {
// 	  cerr<<"SHW: Adding a hit on channel "<<(iter->second->GetChannelOffset() + i);
// 	  cerr<<"                    with values "<<((Unpacker_Ecal_ADC*)(iter->second))->GetDspSum(i)<<" "<<iter->second->GetDspMean(i)<<endl;
// 	}
	  
	for(int j = 0; j < ((Unpacker_Ecal_ADC*)(iter->second))->GetNumberOfSamples(); j++) {
	    hit->AddSample(((Unpacker_Ecal_ADC*)(iter->second))->GetSample(i, j));
	}
	hit->SetDspSum(((Unpacker_Ecal_ADC*)(iter->second))->GetDspSum(i));
	hit->SetDspMean(((Unpacker_Ecal_ADC*)(iter->second))->GetDspMean(i));
	hit->SetDspCfA(((Unpacker_Ecal_ADC*)(iter->second))->GetDspCfA(i));
	hit->SetDspCfB(((Unpacker_Ecal_ADC*)(iter->second))->GetDspCfB(i));
	hit->SetDspCfT(((Unpacker_Ecal_ADC*)(iter->second))->GetDspCfT(i));
      }
    }
  }
}

void Unpacker_Shower::GetTDCHits() { }