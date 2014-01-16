#include "UnpackingModule.h"

ClassImp(UnpackingModule);

UnpackingModule::UnpackingModule(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg) {
  boardType = bT;
  boardAddress = bA;
  hubAddress = hA;
  channelNumber = cN;
  channelOffset = o;
  resolution = r;
  measurementType = mR;
  invertBytes = dec;
  
  debugMode = dbg;
}

void UnpackingModule::ProcessEvent(UInt_t* data) { }

void UnpackingModule::ProcessEvent(UInt_t* data, Event* evt) { cerr<<"Doin shit"<<endl; }

void UnpackingModule::SayHi() { cerr<<"Hi from Unpacking Module"<<endl; }

void UnpackingModule::Clear() { cerr<<"Clearing nothing"<<endl; }

void UnpackingModule::GetADCHits() { }
void UnpackingModule::GetTDCHits() { }

UInt_t UnpackingModule::ReverseHex(UInt_t n) {
  UInt_t a, b, c, d, e;
  a = n & 0x000000ff;
  b = n & 0x0000ff00;
  c = n & 0x00ff0000;
  d = n & 0xff000000;
  
  a <<= 24;
  b <<= 8;
  c >>= 8;
  d >>=24 ;
  
  e = a|b|c|d;
  
  return e;
}

string UnpackingModule::UIntToString(UInt_t t) {
  string s = "0000";
  stringstream sstream;
  sstream<<hex<<t;
  
  s = s.replace(4 - sstream.str().length(), sstream.str().length(), sstream.str());
  
  return s;  
}
