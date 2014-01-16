#ifndef Unpacker_TRB2_h
#define Unpacker_TRB2_h

#include "UnpackingModule.h"

class Unpacker_TRB2 : public UnpackingModule {
  
private:
  Event* event;
  int referenceChannel;
  
public:
  
  Unpacker_TRB2() {}
  Unpacker_TRB2(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg);
  ~Unpacker_TRB2() {}
  
  void ProcessEvent(UInt_t* data, Event* evt);
  
  void GetADCHits();
  void GetTDCHits();
  
  void SetReferenceChannel(int t) { referenceChannel = t; }
  
  void SayHi() { cerr<<"Hi from TRB2"<<endl; }
  
  void Clear() {}
  
  ClassDef(Unpacker_TRB2, 1);
  
};

#endif