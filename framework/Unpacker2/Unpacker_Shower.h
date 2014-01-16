#ifndef Unpacker_Shower_h
#define Unpacker_Shower_h

#include "UnpackingModule.h"

class Unpacker_Shower : public UnpackingModule {
  
private:
  Event* event;
  
public:
  
  Unpacker_Shower() {}
  Unpacker_Shower(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg);
  ~Unpacker_Shower() {}
  
  void ProcessEvent(UInt_t* data, Event* evt);
  
  void GetADCHits();
  void GetTDCHits();
  
  void SayHi() { cerr<<"SHW: Hi from Shower"<<endl; }
  
  void Clear() {}
  
  ClassDef(Unpacker_Shower, 1);
  
};

#endif