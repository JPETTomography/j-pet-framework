#ifndef Unpacker_TRB2_Standalone_h
#define Unpacker_TRB2_Standalone_h

#include "UnpackingModule.h"

class Unpacker_TRB2_Standalone : public UnpackingModule {
  
private:
  Event* event;
  
public:
  
  Unpacker_TRB2_Standalone() {}
  Unpacker_TRB2_Standalone(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec);
  ~Unpacker_TRB2_Standalone() {}
  
  void ProcessEvent(UInt_t* data, Event* evt);
  
  void GetADCHits();
  void GetTDCHits();
  
  void SayHi() { cerr<<"Hi from TRB2_Standalone"<<endl; }
  
  ClassDef(Unpacker_TRB2_Standalone, 1);
  
};

#endif