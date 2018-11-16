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

enum FileInputType {kFirstGate,kSecondGate};   

class JPetGATEConverter 
{
  
public:
  
 JPetGATEConverter();   
 JPetGATEConverter(std::string json_file,int run_id); 
 std::string getfTreeName(int a);   
 bool checkArgument(const TString& inputFile);  
 TString createOutputFileName(TString inputFile);  //it creates output root file name
 bool checkSimulationType(const TString& inputFile);  
 bool converterJPetHit(const TString& inputFile); 
 bool converterJPetMCHit(const TString& inputFile); 
 FileInputType finputType = kFirstGate;     

private:
  
  TString finputFile; 
  int fnumb_strips;  
  std::vector<JPetScin> fscins;  
  JPetParamManager fManager; 
  std::vector<std::string> fTreeName = {"Hits","GateGlobalActorTree"}; 
            
};

#endif /*  !JPETGATECONVERTER_H */      
