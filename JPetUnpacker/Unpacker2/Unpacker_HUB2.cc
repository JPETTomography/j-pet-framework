#include "Unpacker_HUB2.h"
#include <iostream>

using namespace std;

ClassImp(Unpacker_HUB2);

Unpacker_HUB2::Unpacker_HUB2(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg) : UnpackingModule(bT, bA, hA, cN, o, r, mR, dec, dbg) {
  cerr<<"HUB2: Creating Unpacker_HUB2 for board type: "<<bT<<" board address "<<bA<<" hub address "<<hA<<endl;
}

void Unpacker_HUB2::ProcessEvent(UInt_t* data, Event* evt) {
  event = evt;
  
  // clear internal unpackers
  map<std::string, UnpackingModule*>::iterator iter;
  for(iter = GetInternalUnpackersIterBegin(); iter != GetInternalUnpackersIterEnd(); iter++) {
    iter->second->Clear();
  }
  
  while(true) {
    
    UInt_t data_i = 0;
    if(GetInvertBytes() == true) {
      data_i = ReverseHex((*data));
    }
    else {
      data_i = (*data);
    }
    
    
    UInt_t dataSize = data_i >> 16;
    UInt_t addr = data_i & 0xffff;
    
    if (dataSize > 0) {
      
      data++;
      
      GetUnpacker(UIntToString(addr))->ProcessEvent(data, evt);
      
      data += dataSize;
      
      break;
    }
    else {
      data++;
    }
  }
}

void Unpacker_HUB2::GetADCHits() { }

void Unpacker_HUB2::GetTDCHits() {
  map<std::string, UnpackingModule*>::iterator iter;
  for(iter = GetInternalUnpackersIterBegin(); iter != GetInternalUnpackersIterEnd(); iter++) {
    iter->second->GetTDCHits();
  }
}