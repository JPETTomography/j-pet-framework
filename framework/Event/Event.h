#ifndef Event_h
#define Event_h

#include <fstream>
#include <TObject.h>
#include <TTree.h>
#include <TFile.h>
#include <TClonesArray.h>
#include "../TDCHit/TDCHit.h"
#include "../ADCHit/ADCHit.h"
#include <iostream>

using namespace std;

class TDCHit;
class ADCHit;

class Event : public TObject {
  
private:
  Int_t totalNTDCHits;
  Int_t totalNADCHits;
  Int_t TDCReferenceTime;
  
public:
  TClonesArray* TDCHits;
  TClonesArray* ADCHits;
  
  Event();
  virtual ~Event() { Clear(); }
  
  TDCHit* AddTDCHit(int channel);
  ADCHit* AddADCHit(int channel);
  
  void SetTDCReferenceTime(Int_t t) { TDCReferenceTime = t; }
  
  Int_t GetTotalNADCHits() { return totalNTDCHits; }
  Int_t GetTotalNTDCHits() { return totalNADCHits; }
  Int_t GetTDCReferenceTime() { return TDCReferenceTime; }
  
  TClonesArray* GetTDCHitsArray() {return TDCHits;}
  TClonesArray* GetADCHitsArray() {return ADCHits;}
  
  void Clear(void);
  
  ClassDef(Event,1);
  
};


#endif
