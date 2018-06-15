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

TString JPetGATEConverter::createOutput(TString inputFile)    
{
  TString b;
  TRegexp re = "root";        
  inputFile(re) = "gate";
  inputFile = inputFile + ".root";
  b = inputFile;
  return b;
}

void JPetGATEConverter::converterTVector3(TString inputFile)                       
{ 
  TVector3 zmienne;       
  Float_t m, n, o;
  int st; 
  st=checkArgument(inputFile); 
  if(st==-1)               
  {
    cout<<" argument is incorrect"<<endl;
    return;                             
  }
  TFile *f = new TFile(inputFile);
  TTree *g = (TTree*)f->Get("Hits"); 
  TString b;
  b = createOutput(inputFile);              
  TFile *nf = new TFile(b,"recreate");              
  cout<< b << endl;                                                                                                                                                              
  TTree *tree = new TTree("tree","description");   
  g->SetBranchAddress("posX",&m);   
  g->SetBranchAddress("posY",&n);
  g->SetBranchAddress("posZ",&o); 
       
  tree->Branch("TVector3","TVector3", &zmienne, 16000,0);    
  
  Long64_t nentries = g->GetEntries();					
  
  for (Long64_t i=0; i < nentries; i=i+1)
  {
     g->GetEntry(i);                            
     zmienne.SetX(m);     
     zmienne.SetY(n);     
     zmienne.SetZ(o);                               
     tree->Fill();
  }
   tree->Write();
   tree->Print();
   delete f;
   delete nf;
}

int JPetGATEConverter::converterJPetHit(TString inputFile)                  
{  
   Float_t m, n, o;
   Float_t u,r,s;    
   Double_t p;
   int st; 
   int id_strip;                   
   st=checkArgument(inputFile); 
  
   if(st==-1)                 
   {
     cout<<" argument is incorrect"<<endl;    
     return -1;                                 
  }
  finputFile = inputFile;   
  TFile *f = new TFile(inputFile);
  TTree *g = (TTree*)f->Get("Hits"); 
  TString b;
  b = createOutput(inputFile);              
  TFile *nf = new TFile(b,"recreate");                  
  TTree *tree = new TTree("tree","description");
  
  JPetHit hit;    
  g->SetBranchAddress("posX",&m);   
  g->SetBranchAddress("posY",&n);
  g->SetBranchAddress("posZ",&o); 
  g->SetBranchAddress("time",&p);  	
  g->SetBranchAddress("edep",&r);   
  g->SetBranchAddress("axialPos",&s); 	//float axialPos in file Hits  (= PosAlongStrip in object JPetHit)
  tree->Branch("JPetHit","JPetHit", &hit, 16000,0);      
  
  Long64_t nentries = g->GetEntries();
  for (Long64_t i=0; i < nentries; i=i+1)
  {
     g->GetEntry(i);  
     u= (Float_t)(p);  
     hit.setPos(m,n,o);
     hit.setTime(u);
     hit.setEnergy(r);  
   //  hit.setPosAlongStrip(s);

    id_strip = calculate_strip_ID(m,n);  
    
    JPetScin sci;
    sci = fscins[id_strip];
    hit.setScintillator(sci);
    tree->Fill();         
  }
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
  Float_t en,ti,m,n,o; 
  Double_t tim; 
  int ch;
  int id_strip;
  int idStripTab[10]; 
                     
  const JPetParamBank& bank = fManager.getParamBank();  

  ch=checkArgument(inputFile); 
  
  JPetMCHit MChit;                                           

  if(ch==-1)                 
   {
     cout<<" argument is incorrect"<<endl;    
     return -1;                                 
   }
  finputFile = inputFile;                     				
  TFile *fm = new TFile(inputFile);						
  TTree *gm = (TTree*)fm->Get("Hits"); 					
  TString bmc;
  bmc = createOutput(inputFile);             
  TFile *nfm = new TFile(bmc,"recreate");                 
  TTree *treemc = new TTree("treemc","description"); 
  
  gm->SetBranchAddress("edep",&en);         	
  gm->SetBranchAddress("time",&tim);		
  gm->SetBranchAddress("posX",&m);
  gm->SetBranchAddress("posY",&n);
  gm->SetBranchAddress("posZ",&o);
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
    MChit.setPos(m,n,o);

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

int JPetGATEConverter::calculate_strip_ID(Float_t x,Float_t y)    
{  
  int ID;  
  Float_t b; 
  Float_t result;
  Float_t alfa;
  alfa = (2*3.14)/fnumb_strips;        
  
  result = atan2(y,x);  
  result = result + 3.14;
  
  b = result/alfa;
  ID = (int)(b);  
  
  if(ID < 0)
   {
      cout<< "ERROR"<<endl;
      return ID;
   }
   return ID;
}
  
void JPetGATEConverter::converter(){                                               
  JPetHit hit;
   TString input = "output_192str_3lay_L050.root";        
  TString output = "test_selected.root";                    
}
