#include "JPetGATEConverter.h"
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "TRegexp.h"
#include "./JPetHit/JPetHit.h"
#include "./JPetMCHit/JPetMCHit.h" 
#include "./JPetScin/JPetScin.h"
#include <math.h> /*atan*/  

using namespace std;

JPetGATEConverter::JPetGATEConverter() 
{    
}

JPetGATEConverter::JPetGATEConverter(string json_file,int run_id): fManager(new JPetParamGetterAscii(json_file))  
{  
  fManager.fillParameterBank(run_id);      
}


int JPetGATEConverter::checkArgument(TString inputFile)                   
{
  TString ss = ".root";        
                                                                                       
  Long64_t dl = inputFile.Length();
  
  if(inputFile.Index(ss) + 5 == dl)
  {
    return 1; 
  }
  return -1;
}

TString JPetGATEConverter::createOutputFileName(TString inputFile)    
{
  TString b;
  TRegexp re = "root";        
  inputFile(re) = "gate";
  inputFile = inputFile + ".root";
  b = inputFile;
  return b;
}	

int JPetGATEConverter::converterJPetHit(TString inputFile)                  
{  
   Float_t x, y, z;  //mno-> xyz
   Float_t u,r,s;    
   Double_t p;
   int id_strip;  
   int idStripTab[10]; 
                     
  const JPetParamBank& bank = fManager.getParamBank();   

  if (bank.isDummy()) {
	ERROR("Param bank is not correct, we cannot convert JPetHit.");
	return -1;
	}             



  if (checkArgument(inputFile)==-1) { 
   ERROR("argument is incorrect");
   return -1;
   }

  finputFile = inputFile;   
  TFile *f = new TFile(inputFile);
  TTree *g = (TTree*)f->Get(fTreeName[0].c_str()); 
  TString b;

  b = createOutputFileName(inputFile);              
  TFile *nf = new TFile(b,"recreate");                  
  TTree *tree = new TTree("tree","description");
  
  JPetHit hit;    
  g->SetBranchAddress("posX",&x);   
  g->SetBranchAddress("posY",&y);
  g->SetBranchAddress("posZ",&z); 
  g->SetBranchAddress("time",&p);  	
  g->SetBranchAddress("edep",&r);   
  g->SetBranchAddress("axialPos",&s); 	//float axialPos in file Hits  (= PosAlongStrip in object JPetHit)
  tree->Branch("JPetHit","JPetHit", &hit, 16000,0);      
  
  Long64_t nentries = g->GetEntries();
  for (Long64_t i=0; i < nentries; i=i+1)
  {
     g->GetEntry(i);  
     u= (Float_t)(p);  
     hit.setPos(x,y,z);
     hit.setTime(u);
     hit.setEnergy(r);  
   //  hit.setPosAlongStrip(s);

    //a) volumeID variable is a 10 elements int table. For our purpose, to get index of the strip, we use only second element of the table[1] 
  //b) the number of strip ID in framework is given as the strip Id defined in gate + 1
    id_strip = idStripTab[1]+ 1;  
    JPetScin& sc = bank.getScintillator(id_strip);
    
    hit.setScintillator(sc);    

    tree->Fill();         
  }
   nf->WriteObject(&bank, "ParamBank"); 
   tree->Write();
   tree->Print();
   
   delete f;
   delete nf;  
   
   return 1; 
}

int JPetGATEConverter::converterJPetMCHit(TString inputFile) 
{  
  Int_t dti = -1;  	//MCDecayTreeIndex
  Int_t vi  = -1;   	//MCVtxIndex
  Float_t en,ti,x,y,z; 
  Double_t tim; 
  int id_strip;
  int idStripTab[10]; 
                     
  const JPetParamBank& bank = fManager.getParamBank();  
  
  JPetMCHit MChit; 
  if (checkArgument(inputFile)==-1) { 
   ERROR("argument is incorrect");
   return -1;
   }                                          

  finputFile = inputFile;                     				
  TFile *fm = new TFile(inputFile);						
  TTree *gm = (TTree*)fm->Get(fTreeName[0].c_str()); 					
  TString bmc;
  bmc = createOutputFileName(inputFile);             
  TFile *nfm = new TFile(bmc,"recreate");                 
  TTree *treemc = new TTree("treemc","description"); 
  
  gm->SetBranchAddress("edep",&en);         	
  gm->SetBranchAddress("time",&tim);		
  gm->SetBranchAddress("posX",&x);
  gm->SetBranchAddress("posY",&y);
  gm->SetBranchAddress("posZ",&z);
  gm->SetBranchAddress("volumeID",&idStripTab); 
  treemc->Branch("JPetMCHit","JPetMCHit", &MChit, 16000,0);    
  Long64_t numbentries = gm->GetEntries();
      
  for (Long64_t i=0; i < numbentries; i=i+1)   
  {
    gm->GetEntry(i);    

    ti= (Float_t)(tim); 
    MChit.setMCDecayTreeIndex(dti);           
    MChit.setMCVtxIndex(vi);       
    MChit.setEnergy(en);  
    MChit.setTime(ti);  
    MChit.setPos(x,y,z);

  //a) volumeID variable is a 10 elements int table. For our purpose, to get index of the strip, we use only second element of the table[1] 
  //b) the number of strip ID in framework is given as the strip Id defined in gate + 1
    id_strip = idStripTab[1]+ 1;  

    JPetScin& sc = bank.getScintillator(id_strip);
    
    MChit.setScintillator(sc);  

    treemc->Fill();      
     
  }
  
  nfm->WriteObject(&bank, "ParamBank"); 
  
  treemc->Write();   
  treemc->Print(); 

  delete fm;
  delete nfm; 
   
  return 1;  
}

					
