#include "Unpacker_Ecal_ADC.h"
#include <iostream>

using namespace std;

ClassImp(Unpacker_Ecal_ADC);

Unpacker_Ecal_ADC::Unpacker_Ecal_ADC(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg) : UnpackingModule(bT, bA, hA, cN, o, r, mR, dec, dbg) {
  cerr<<"ECAL_ADC: Creating Unpacker_Ecal_ADC for board type: "<<bT<<" board address "<<bA<<" hub address "<<hA<<endl;
}

void Unpacker_Ecal_ADC::ProcessEvent(UInt_t* data, Event* evt) {
  UInt_t data_i = 0;
  if(GetInvertBytes() == true) {
    data_i = ReverseHex((*data));
  }
  else {
    data_i = (*data);
  }
  
  // get the size of the data in the event
  size_t dataSize = (data_i >> 16) & 0xffff;
  
  data++;
  dataSize--;
  
  while(true) {
    
    if(GetInvertBytes() == true) {
      data_i = ReverseHex((*data));
    }
    else {
      data_i = (*data);
    }
    
    Int_t channel, sample, sampleNr;
    channel = (data_i >> 24) & 0xf;
    sampleNr = (data_i >> 16) & 0xff;
    sample = data_i & 0xfff;
    
    if (sampleNr <= MAX_SAMPLES) {
      AddSample(channel, sampleNr, sample);
      
      if(debugMode == true)
	cerr<<"ECAL_ADC: adding a sample: on channel "<<channel<<" nr "<<sampleNr<<" with value "<<sample<<endl;      
    }
    else if (sampleNr > MAX_SAMPLES && sampleNr <= MAX_SAMPLES + 6)
    {
      if(debugMode == true)
	cerr<<"ECAL_ADC: adding a calc value: on channel "<<channel<<" nr "<<(sampleNr - MAX_SAMPLES)<<" with value "<<sample<<endl;
      
      switch(sampleNr)
      {
	case MAX_SAMPLES + 1:
	  SetDspSum(channel, data_i & 0xffff);
	  break;
	  
	case MAX_SAMPLES + 2:
	  SetDspSum(channel, GetDspSum(channel) + (data_i & 0xffff) * 65525);
	  break;
	  
	case MAX_SAMPLES + 3:
	  SetDspMean(channel, data_i & 0xfff);
	  break;
	  
	case MAX_SAMPLES + 4:
	  SetDspCfA(channel, data_i & 0xfff);
	  break;
	
	case MAX_SAMPLES + 5:
	  SetDspCfB(channel, data_i & 0xfff);
	  break;
	  
	case MAX_SAMPLES + 6:
	  SetDspCfT(channel, data_i & 0xfff);
	  break;
	  
	default:
	  break;
      }
    }
   
    dataSize--;
    data++;
    
    if(dataSize == 0)
      break;
  } 
}

void Unpacker_Ecal_ADC::GetADCHits() { }

void Unpacker_Ecal_ADC::GetTDCHits() { }

void Unpacker_Ecal_ADC::Clear() {
  for(int i = 0; i < MAX_CHANNELS; i++) {
    for(int j = 0; j < MAX_SAMPLES; j++) {
      samples[i][j] = -1;
    }
    dspSums[i] = -1;
    dspMeans[i] = -1;
    dspCfA[i] = -1;
    dspCfB[i] = -1;
    dspCfT[i] = -1;
  }
}

Int_t Unpacker_Ecal_ADC::GetSample(Int_t channel, Int_t sampleNr) const {
  return samples[channel][sampleNr];
}

Int_t Unpacker_Ecal_ADC::GetDspSum(Int_t channel) const {
  return dspSums[channel]; 
}
  
Int_t Unpacker_Ecal_ADC::GetDspMean(Int_t channel) const {
 return dspMeans[channel]; 
}
  
Int_t Unpacker_Ecal_ADC::GetDspCfA(Int_t channel) const {
 return dspCfA[channel]; 
}
  
Int_t Unpacker_Ecal_ADC::GetDspCfB(Int_t channel) const {
 return dspCfB[channel]; 
}
  
Int_t Unpacker_Ecal_ADC::GetDspCfT(Int_t channel) const {
 return dspCfT[channel]; 
}