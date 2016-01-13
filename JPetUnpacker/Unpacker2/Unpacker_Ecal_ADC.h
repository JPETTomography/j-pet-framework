#ifndef Unpacker_Ecal_ADC_h
#define Unpacker_Ecal_ADC_h

#include "UnpackingModule.h"

#define MAX_CHANNELS 8
#define MAX_SAMPLES 128

class Unpacker_Ecal_ADC : public UnpackingModule {
  
private:
  Event* event;
  
public:
  
  Int_t samples[MAX_CHANNELS][MAX_SAMPLES];
  Int_t dspSums[MAX_CHANNELS];
  Int_t dspMeans[MAX_CHANNELS];
  Int_t dspCfA[MAX_CHANNELS];
  Int_t dspCfB[MAX_CHANNELS];
  Int_t dspCfT[MAX_CHANNELS];
  
  Unpacker_Ecal_ADC() {}
  Unpacker_Ecal_ADC(string bT, string bA, string hA, int cN, int o, int r, string mR, bool dec, bool dbg);
  ~Unpacker_Ecal_ADC() {}
  
  void ProcessEvent(UInt_t* data, Event* evt);
  
  void GetADCHits();
  void GetTDCHits();
  
  void SayHi() { cerr<<"Ecal_ADC: Hi from Ecal_ADC"<<endl; }
  
  void Clear();
  
  void AddSample(Int_t channel, Int_t sampleNr, Int_t sample) { samples[channel][sampleNr] = sample;}
  void SetDspSum(Int_t channel, Int_t sum) { dspSums[channel] = sum; }
  void SetDspMean(Int_t channel, Int_t mean) { dspMeans[channel] = mean; }
  void SetDspCfA(Int_t channel, Int_t cfa) { dspCfA[channel] = cfa; }
  void SetDspCfB(Int_t channel, Int_t cfb) { dspCfB[channel] = cfb; }
  void SetDspCfT(Int_t channel, Int_t cft) { dspCfT[channel] = cft; }
  
  Int_t GetSample(Int_t channel, Int_t sampleNr) const;
  Int_t GetDspSum(Int_t channel) const;
  Int_t GetDspMean(Int_t channel) const;
  Int_t GetDspCfA(Int_t channel) const;
  Int_t GetDspCfB(Int_t channel) const;
  Int_t GetDspCfT(Int_t channel) const;  
  Int_t GetNumberOfSamples() { return MAX_SAMPLES; }
  
  ClassDef(Unpacker_Ecal_ADC, 1);
  
};

#endif