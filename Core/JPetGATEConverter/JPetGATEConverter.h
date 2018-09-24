#ifndef JPETGATECONVERTER_H 
#define JPETGATECONVERTER_H
#include <TROOT.h>
#include "TNamed.h"
#include "TVector3.h"
#include "./JPetMCHit/JPetMCHit.h" 
#include "./JPetScin/JPetScin.h"
#include "./JPetParamManager/JPetParamManager.h"    
#include "./JPetParamGetterAscii/JPetParamGetterAscii.h" 
#include "./JPetParamBank/JPetParamBank.h" 
#include <vector> 

using namespace std;

class JPetGATEConverter 
{
  
public:
  
 JPetGATEConverter();   
 JPetGATEConverter(std::string json_file,int run_id);   
 int checkArgument(TString inputFile);
 TString createOutputFileName(TString inputFile);  //it creates output root file name
 int converterJPetHit(TString inputFile); 
 int converterJPetMCHit(TString inputFile); 


private:
  
  TString finputFile; 
  int fnumb_strips;  
  std::vector<JPetScin> fscins;  
  JPetParamManager fManager; 
  std::vector<std::string> fTreeName = {"Hits", "gosia"};
            
};

#endif /*  !JPETGATECONVERTER_H */      
