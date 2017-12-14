#ifndef JPETGATECONVERTER_H 
#define JPETGATECONVERTER_H
#include <TROOT.h>
#include "TNamed.h"
#include "TVector3.h"
#include "./JPetMCHit/JPetMCHit.h" 
#include "./JPetScin/JPetScin.h"

class JPetGATEConverter 
{
  
public:
  
 JPetGATEConverter();
 JPetGATEConverter(int numb_strips);  
 int checkArgument(TString inputFile);
 TString createOutput(TString inputFile);
 void converterTVector3(TString inputFile);
 int converterJPetHit(TString inputFile); 
 int converterJPetMCHit(TString inputFile); 
 int calculate_strip_ID(Float_t x,Float_t y); 

 void converter();

private:
  
  TString finputFile; 
  int fnumb_strips;  
  std::vector<JPetScin> fscins;   
};
#endif /*  !JPETGATECONVERTER_H */      
