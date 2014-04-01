#ifndef Unpacker_TRB3_h
#define Unpacker_TRB3_h

#include "UnpackingModule.h"

class Unpacker_TRB3 : public UnpackingModule {
  
private:
  Event* event;
  int referenceChannel;
  
public:
  
  Unpacker_TRB3() {}
  Unpacker_TRB3(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg);
  ~Unpacker_TRB3() {}
  
  void ProcessEvent(UInt_t* data, Event* evt);
  
  void GetADCHits();
  void GetTDCHits();
  
  void SetReferenceChannel(int t) { referenceChannel = t; }
  
  void SayHi() { cerr<<"Hi from TRB3"<<endl; }
  
  void Clear() {}
  
  ClassDef(Unpacker_TRB3, 1);
  
};

#endif