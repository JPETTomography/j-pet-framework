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

JPetGATEConverter::JPetGATEConverter(int numb_strips)      
{
 fnumb_strips = numb_strips;    
 for( int i = 0; i < numb_strips; i = i + 1)
   { 
     JPetScin objectscin(i);  
     fscins.push_back(objectscin);  
   } 
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
    cout<<" argument is not good"<<endl;
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
     cout<<" argument is not good"<<endl;    
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
  g->SetBranchAddress("axialPos",&s); 	//float axialPos w pliku Hits  (= PosAlongStrip w JPetHit)
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
  Int_t pda,tr,pa,ncc,eID;
  Float_t lx,ly,lz,en,ti,m,n,o; 
  Double_t tim; 
  Char_t prn; 
  int che;
  int id_strip; 
  //Int_t la,nc,npr,ncr,sID,rID;     
 // Float_t sx,sy,sz;
  
  che=checkArgument(inputFile); 
  
  JPetMCHit MChit;                                           

   if(che==-1)                 
   {
     cout<<" argument is not good"<<endl;    
     return -1;                                 
   }
  finputFile = inputFile;                     
  TFile *fm = new TFile(inputFile);
  TTree *gm = (TTree*)fm->Get("Hits"); 
  TString bmc;
  bmc = createOutput(inputFile);             
  TFile *nfm = new TFile(bmc,"recreate");                 
  TTree *treemc = new TTree("treemc","description");  
  char pd=0; 
  gm->SetBranchAddress("PDGEncoding",&pd); 
  gm->SetBranchAddress("trackID",&tr);     
  gm->SetBranchAddress("parentID",&pa);
  gm->SetBranchAddress("localPosX",&lx);
  gm->SetBranchAddress("localPosY",&ly);
  gm->SetBranchAddress("localPosZ",&lz);
  gm->SetBranchAddress("nCrystalCompton",&ncc);
  gm->SetBranchAddress("eventID",&eID);
  gm->SetBranchAddress("edep",&en);         
  gm->SetBranchAddress("time",&tim);
  gm->SetBranchAddress("processName",&prn);
  gm->SetBranchAddress("posX",&m);
  gm->SetBranchAddress("posY",&n);
  gm->SetBranchAddress("posZ",&o);
  //gm->SetBranchAddress("layerID",&la);         //Mean=0 i RMS =0 w pliku Hits w histogramie, wiec odtad zakomentowalam
  //gm->SetBranchAddress("nPhantomCompton",&nc);
  //gm->SetBranchAddress("nPhantomRayleigh",&npr);
 // gm->SetBranchAddress("nCrystalRayleigh",&ncr);
 // gm->SetBranchAddress("sourcePosX",&sx);
 // gm->SetBranchAddress("sourcePosY",&sy);
 // gm->SetBranchAddress("sourcePosZ",&sz);
 // gm->SetBranchAddress("sourceID",&sID);
  //gm->SetBranchAddress("runID",&rID);
      
  treemc->Branch("JPetMCHit","JPetMCHit", &MChit, 16000,0);    
  Long64_t numbentries = gm->GetEntries();
      
  for (Long64_t i=0; i < numbentries; i=i+1)   
  {
    gm->GetEntry(i);    
    
    ti= (Float_t)(tim); 
 
    MChit.setPDGEncoding(pd); 
    MChit.setTrackID(tr);           
    MChit.setParentID(pa);
    MChit.setEventID(eID);
    MChit.setNumCrystalCompton(ncc);
    MChit.setProcessName(prn);  
    MChit.setEnergy(en);  
    MChit.setTime(ti);  
    MChit.setLocalPosX(lx);
    MChit.setLocalPosY(ly);
    MChit.setLocalPosZ(lz);
    MChit.setPos(m,n,o);
      
    id_strip = calculate_strip_ID(m,n);  
    
    JPetScin sc;
    sc = fscins[id_strip];
    MChit.setScintillator(sc);  

   treemc->Fill();      
  }
       
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
  TString input = "test_384strips.root";          
  TString output = "test_selected.root";                    
  //Long64_t d = checkArgument(input); 
}
