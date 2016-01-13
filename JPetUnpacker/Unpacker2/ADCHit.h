#ifndef ADCHit_h
#define ADCHit_h

#include <TObject.h>

#define MAX_SAMPLES 128

class ADCHit : public TObject {
  
private:
  Int_t channel;
  Int_t ADC;
  Int_t nHits;
  Int_t samples[MAX_SAMPLES];
  Int_t dspSum;
  Int_t dspMean;
  Int_t dspCfA;
  Int_t dspCfB;
  Int_t dspCfT;
  
  Int_t localPtr;
  
public:
  ADCHit();
  ~ADCHit();
  
  void SetChannel(int ch) { channel = ch; }
  void SetADC(Int_t a) { ADC = a; }
  void SetNHits(Int_t n) { nHits = n; }
  void SetDspSum(Int_t d) { dspSum = d; }
  void SetDspMean(Int_t d) { dspMean = d; }
  void SetDspCfA(Int_t d) { dspCfA = d; }
  void SetDspCfB(Int_t d) { dspCfB = d; }
  void SetDspCfT(Int_t d) { dspCfT = d; }
  void AddSample(Int_t s) { if(localPtr < MAX_SAMPLES) samples[localPtr] = s; localPtr++; }
  
  Int_t GetChannel() { return channel; }
  Int_t GetADC() { return ADC; }
  Int_t GetNHits() { return nHits;}
  Int_t GetSample(int i) { return samples[i]; }
  Int_t* GetSamples() { return samples; }
  Int_t GetDspSum() { return dspSum; }
  Int_t GetDspMean() { return dspMean; }
  Int_t GetDspCfA() { return dspCfA; }
  Int_t GetDspCfB() { return dspCfB; }
  Int_t GetDspCfT() { return dspCfT; }
  Int_t GetMaxSamples() { return MAX_SAMPLES; }
  
  void Clear();
  
  ClassDef(ADCHit,1);
};

#endif