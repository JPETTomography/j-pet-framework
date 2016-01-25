#ifndef Unpacker_HPTDC_HR_h
#define Unpacker_HPTDC_HR_h

#include "UnpackingModule.h"

class Unpacker_HPTDC_HR : public UnpackingModule {
  
private:  
  int channelNumber;
  float **leadTimes; //!
  float **trailTimes; //!
  UInt_t* leadMult; //[channelNumber]
  UInt_t* trailMult; //[channelNumber]
  
  
  bool* firstLeadCorrect; //[channelNumber]
  
public:
  
  Unpacker_HPTDC_HR() { }
  Unpacker_HPTDC_HR(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg);
  ~Unpacker_HPTDC_HR();
  
  void ProcessEvent(UInt_t* data);
  
  void SayHi() { cerr<<"HTPDC_HR: Hi from HPTDC_HR"<<endl; }
  
  float GetLeadTime(int channel, int mult) { return leadTimes[channel][mult]; }
  UInt_t GetLeadMult(int channel) { return leadMult[channel]; }
  float GetTrailTime(int channel, int mult) { return trailTimes[channel][mult]; }
  UInt_t GetTrailMult(int channel) { return trailMult[channel]; }
  bool GetFirstLeadCorrect(int channel) { return firstLeadCorrect[channel]; }
  
  void Clear();
  
  ClassDef(Unpacker_HPTDC_HR, 1);
  
};

#endif
