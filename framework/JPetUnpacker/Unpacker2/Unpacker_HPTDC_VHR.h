#ifndef Unpacker_HPTDC_VHR_h
#define Unpacker_HPTDC_VHR_h

#include "UnpackingModule.h"
#include <TClonesArray.h>
#include "inlCorrector.h"

class Unpacker_HPTDC_VHR : public UnpackingModule {
  
private:
  int channelNumber;

  float **leadTimes; //!
  float **trailTimes; //!
  UInt_t* leadMult; //!  
  UInt_t* trailMult; //!
  
  bool useInlCorrections;
  InlCorrector* inlCorrector;
    
public:
  
  Unpacker_HPTDC_VHR() {}
  Unpacker_HPTDC_VHR(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg);
  ~Unpacker_HPTDC_VHR();
  
  void ProcessEvent(UInt_t* data);
  
  void SayHi() { cerr<<"HTPDC_VHR: Hi from HPTDC_VHR"<<endl; }
  
  float GetLeadTime(int channel, int mult) { return leadTimes[channel][mult]; }
  UInt_t GetLeadMult(int channel) { return leadMult[channel]; }
  float GetTrailTime(int channel, int mult) { return trailTimes[channel][mult]; }
  UInt_t GetTrailMult(int channel) { return trailMult[channel]; }
  
  void SetInlCorrection(const char* correctionsFile);
  
  void Clear();
  
  ClassDef(Unpacker_HPTDC_VHR, 1);
  
};

#endif
