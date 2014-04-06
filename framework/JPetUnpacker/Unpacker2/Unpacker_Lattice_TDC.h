#ifndef Unpacker_Lattice_TDC_h
#define Unpacker_Lattice_TDC_h

#include "UnpackingModule.h"
#include "Event.h"
#include "Hit.h"
#include <TH1F.h>
#include <TFile.h>

class Unpacker_Lattice_TDC : public UnpackingModule {
  
private:  
  Int_t channelNumber;

  float** leadTimes; //!
  float** trailTimes; //!
  UInt_t* leadMult; //[channelNumber]
  UInt_t* trailMult; //[channelNumber]
  float** fineTimes; //!
  float** coarseTimes; //!

  
  int offset;
  
  TH1F** corrections;  //! 
  bool useCorrections;
  
  UInt_t errorBits;
  
public:
  
  Unpacker_Lattice_TDC() { }
  Unpacker_Lattice_TDC(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg, string cF);
  ~Unpacker_Lattice_TDC();
  
  void ProcessEvent(UInt_t* data);
  void ProcessEvent(UInt_t* data, Event* evt);
  
  void SayHi() { cerr<<"Lattice_TDC: Hi from Lattice_TDC"<<endl; }
  
  float GetLeadTime(int channel, int mult) { return leadTimes[channel][mult]; }
  UInt_t GetLeadMult(int channel) { return leadMult[channel]; }
  float GetTrailTime(int channel, int mult) { return trailTimes[channel][mult]; }
  UInt_t GetTrailMult(int channel) { return trailMult[channel]; }

  float GetFineTime(int channel, int mult) { return fineTimes[channel][mult]; }
  float GetCoarseTime(int channel, int mult) { return coarseTimes[channel][mult]; }
  
  UInt_t GetErrorBits() { return errorBits; }
  
  void Clear();
  
  ClassDef(Unpacker_Lattice_TDC, 1);
  
};

#endif
