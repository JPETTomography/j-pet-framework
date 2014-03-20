#ifndef Event_h
#define Event_h

#include <fstream>
#include <TObject.h>
#include <TClonesArray.h>
#include "TDCHit.h"
#include "ADCHit.h"
#include <iostream>

using namespace std;

class TDCHit;
class ADCHit;

class Event : public TObject {
  
private:
  Int_t totalNTDCHits;
  Int_t totalNADCHits;
  float TDCReferenceTime;
  UInt_t errorBits;
  
public:
  TClonesArray* TDCHits;
  TClonesArray* ADCHits;
  
  Event();
  virtual ~Event() { Clear(); }
  
  TDCHit* AddTDCHit(int channel);
  ADCHit* AddADCHit(int channel);
  
  void SetTDCReferenceTime(float t) { TDCReferenceTime = t; }
  void SetErrorBits(UInt_t err) { errorBits = err; }
  
  Int_t GetTotalNADCHits() { return totalNADCHits; }
  Int_t GetTotalNTDCHits() { return totalNTDCHits; }
  float GetTDCReferenceTime() { return TDCReferenceTime; }
  UInt_t GetErrorBits() { return errorBits; }
  
  TClonesArray* GetTDCHitsArray() {return TDCHits;}
  TClonesArray* GetADCHitsArray() {return ADCHits;}
  
  void Clear(void);
  
  ClassDef(Event,1);
  
};


#endif
