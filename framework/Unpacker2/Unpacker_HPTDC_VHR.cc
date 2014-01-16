#include "Unpacker_HPTDC_VHR.h"
#include <iostream>

using namespace std;

ClassImp(Unpacker_HPTDC_VHR);

Unpacker_HPTDC_VHR::Unpacker_HPTDC_VHR(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg) : UnpackingModule(bT, bA, hA, cN, o, r, mR, dec, dbg) {
  
  channelNumber = cN;
  
  useInlCorrections = false;
  
  leadTimes = new float*[channelNumber];
  trailTimes = new float*[channelNumber];
  leadMult = new UInt_t[channelNumber];
  trailMult = new UInt_t[channelNumber];
  
  for(int i = 0; i < channelNumber; i++) {
    leadTimes[i] = new float[1000];
    trailTimes[i] = new float[1000];
    leadMult[i] = 0;
    trailMult[i] = 0;
  }
  
  cerr<<"HPTDC_VHR: Creating Unpacker_HPTDC_VHR for board type: "<<bT<<" board address "<<bA<<" hub address "<<hA<<endl;
}

Unpacker_HPTDC_VHR::~Unpacker_HPTDC_VHR() {
  for(int i = 0; i < channelNumber; i++) {
    delete leadTimes[i];
    delete trailTimes[i];
  }
  
  delete [] leadMult;
  delete [] trailMult;
  delete [] leadTimes;
  delete [] trailTimes;
}

void Unpacker_HPTDC_VHR::Clear() {
  for(int i =0; i < channelNumber; i++) {
    delete [] leadTimes[i];
    delete [] trailTimes[i];
    leadTimes[i] = new float[1000];
    trailTimes[i] = new float[1000];
    leadMult[i] = 0;
    trailMult[i] = 0;
  }
}

void Unpacker_HPTDC_VHR::ProcessEvent(UInt_t* data) { 
  
    UInt_t data_i = 0;
    if(GetInvertBytes() == true) {
      data_i = ReverseHex((*data));
    }
    else {
      data_i = (*data);
    }
  
    UInt_t header = (data_i >> 28) & 0xf;
    UInt_t channel;
    UInt_t time;
    
    switch (header) {
      
      case 4:
	channel = (data_i >> 21) & 0x7;
	time = (((data_i & 0x7ffff) << 2) | ((data_i >> 19) & 0x3));
	
	if(useInlCorrections == false) {
	  leadTimes[channel][leadMult[channel]] = time;
	}
	else {
	  leadTimes[channel][leadMult[channel]] = inlCorrector->getCorrectedValue(channel, time);
	}
	
	if(debugMode == true)
	  cerr<<"Unpacker_HPTDC_VHR.cc: LeadTime found on channel "<<channel<<endl;
	
	leadMult[channel]++;
	break;
      
      case 5:
	channel = (data_i >> 21) & 0x7;
	time = (((data_i & 0x7ffff) << 2) | ((data_i >> 19) & 0x3));
	
	if(useInlCorrections == false) {
	  trailTimes[channel][trailMult[channel]] = time;
	}
	else {
	  trailTimes[channel][trailMult[channel]] = inlCorrector->getCorrectedValue(channel, time);
	}
	
	if(debugMode == true)
	  cerr<<"Unpacker_HPTDC_VHR.cc: TrailTime found on channel "<<channel<<endl;
	
	trailMult[channel]++;
	break;
      
      default:
	break;
    }
}

void Unpacker_HPTDC_VHR::SetInlCorrection(const char* correctionsFile) {
  inlCorrector = new InlCorrector(true, correctionsFile);
  useInlCorrections = true;
}