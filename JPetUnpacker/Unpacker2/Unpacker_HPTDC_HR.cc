#include "Unpacker_HPTDC_HR.h"
#include <iostream>
#include "Event.h"
#include "Hit.h"

using namespace std;

ClassImp(Unpacker_HPTDC_HR);

Unpacker_HPTDC_HR::Unpacker_HPTDC_HR(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg) : UnpackingModule(bT, bA, hA, cN, o, r, mR, dec, dbg) {
  
  channelNumber = cN;
  
  leadTimes = new float*[channelNumber];
  trailTimes = new float*[channelNumber];
  leadMult = new UInt_t[channelNumber];
  trailMult = new UInt_t[channelNumber];
  
  firstLeadCorrect = new bool[channelNumber];
  
  for(int i = 0; i < channelNumber; i++) {
    leadTimes[i] = new float[1000];
    trailTimes[i] = new float[1000];
    leadMult[i] = 0;
    trailMult[i] = 0;
    firstLeadCorrect[i] = false;
  }
  
  
  cerr<<"HPTDC_HR: Creating Unpacker_HPTDC_HR for board type: "<<bT<<" board address "<<bA<<" hub address "<<hA<<" number of channels "<<channelNumber<<endl;
}

Unpacker_HPTDC_HR::~Unpacker_HPTDC_HR() {
  for(int i = 0; i < channelNumber; i++) {
    delete [] leadTimes[i];
    delete [] trailTimes[i];
  }
  
  delete [] leadMult;
  delete [] trailMult;
  delete [] leadTimes;
  delete [] trailTimes;
  delete [] firstLeadCorrect;
}

void Unpacker_HPTDC_HR::Clear() {
  
  for(int i = 0; i < channelNumber; i++) {
    delete [] leadTimes[i];
    delete [] trailTimes[i];
    leadTimes[i] = new float[1000];
    trailTimes[i] = new float[1000];
    leadMult[i] = 0;
    trailMult[i] = 0;
    firstLeadCorrect[i] = false;
  }
}

void Unpacker_HPTDC_HR::ProcessEvent(UInt_t* data) {
  
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
    
    case 2:
      break;
      
    case 3:
      break;
      
    case 4:
      channel = (data_i >> 19) & 0x1f;
      time = data_i & 0x7ffff;
      leadTimes[channel][leadMult[channel]] = time;
      
      if (leadMult[channel] == 0 && trailMult[channel] == 0)
	firstLeadCorrect[channel] = true;
      
      //if(debugMode == true)
	//cerr<<"HPTDC_HR: LeadTime found on channel "<<channel<<" with value "<<time<<endl;
      leadMult[channel]++;
      break;
      
    case 5:
      channel = (data_i >> 19) & 0x1f;
      time = data_i & 0x7ffff;
      trailTimes[channel][trailMult[channel]] = time;
      //if(debugMode == true)
	//cerr<<"HPTDC_HR: TrailTime found on channel "<<channel<<" with value "<<time<<endl;
      trailMult[channel]++;
      break;
    
  }
}