#ifndef Unpacker_HUB2_h
#define Unpacker_HUB2_h

#include "UnpackingModule.h"

class Unpacker_HUB2 : public UnpackingModule {
  
private:
  Event* event;
  
public:
  
  Unpacker_HUB2() {}
  Unpacker_HUB2(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg);
  ~Unpacker_HUB2() {}
  
  void ProcessEvent(UInt_t* data, Event* evt);
  
  void GetADCHits();
  void GetTDCHits();
  
  void SayHi() { cerr<<"HUB2: Hi from HUB2"<<endl; }
  
  void Clear() {}
  
  ClassDef(Unpacker_HUB2, 1);
  
};

#endif