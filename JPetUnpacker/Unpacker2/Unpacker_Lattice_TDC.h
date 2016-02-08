#ifndef Unpacker_Lattice_TDC_h
#define Unpacker_Lattice_TDC_h

#include "UnpackingModule.h"
#include "Event.h"
//#include "Hit.h"
#include <TH1F.h>
#include <TFile.h>

class Unpacker_Lattice_TDC : public UnpackingModule {
  
private:
	int* leadMult;
	int** leadFineTimes;
	int** leadCoarseTimes;
	int** leadEpochs;
  
	int* trailMult;
	int** trailFineTimes;
	int** trailCoarseTimes;
	int** trailEpochs;

  int channelNumber;
  int offset;
  
  TH1F** corrections;
  bool useCorrections;

  int actualEpoch;
  
  UInt_t errorBits;
  
public:
  
  Unpacker_Lattice_TDC() { }
  Unpacker_Lattice_TDC(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg, string cF);
  ~Unpacker_Lattice_TDC();
  
  void ProcessEvent(UInt_t* data);
  void ProcessEvent(UInt_t* /* data */, Event* /* evt */);
  
  void SayHi() { cerr<<"Lattice_TDC: Hi from Lattice_TDC"<<endl; }
  
  int GetLeadMult(int channel) { return leadMult[channel]; }
  int GetLeadFineTime(int channel, int mult) { return leadFineTimes[channel][mult]; }
  int GetLeadCoarseTime(int channel, int mult) { return leadCoarseTimes[channel][mult]; }
  int GetLeadEpoch(int channel, int mult) { return leadEpochs[channel][mult]; }

  int GetTrailMult(int channel) { return trailMult[channel]; }
  int GetTrailFineTime(int channel, int mult) { return trailFineTimes[channel][mult]; }
  int GetTrailCoarseTime(int channel, int mult) { return trailCoarseTimes[channel][mult]; }
  int GetTrailEpoch(int channel, int mult) { return trailEpochs[channel][mult]; }

  UInt_t GetErrorBits() { return errorBits; }
  
  void Clear();
  
  //  ClassDef(Unpacker_Lattice_TDC, 1);
  
};

#endif
