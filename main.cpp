/*
Analysis Control for J-PET
04-7-2013, M. Silarski:
v0- skeleton of AC program reading unpacked ROOT tree using exactly the same class
structure. The program is next filling a small exemplary structure Sig.
A tree TR is created and filled with this structure.

Usage after compiling and linking with Makefie:

./main filename.root (opens filename.root)
or

./main runNr_start runNr_end (opens files with run numbers between runNr_start
and runNr_end. This is however not fully implemented yet)
*/


#include <TApplication.h>
#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>
#include <TObject.h>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "framework/Event/Event.h"
#include "framework/ADCHit/ADCHit.h"
#include "framework/TDCHit/TDCHit.h"
#include "string"
#include "map"
#include "TSystem.h"
#include "framework/Sig/Sig.h"

using namespace std;
int pet_init(Event *&event,TClonesArray *&tdc, TClonesArray *&adc,TTree *&Tn,TFile *&f)
{
  //function called in main() once per run/file

  Tn = (TTree*)f->Get("T");
  TBranch *branch=Tn->GetBranch("event");
  branch->SetAddress(&event);
  tdc = event->GetTDCHitsArray();
  adc = event->GetTDCHitsArray();
  

  return 0;
}
int pet_event(Sig *signal,int i,Event *event,TClonesArray *tdc, TClonesArray *adc,TTree *Tn,TFile *f)
 {

 Int_t    nev,Tot_NADCHits,Tot_NTDCHits,TDCReferenceTime;
 Int_t    maxChannelHits,j,k,ii,nChannels; 
 Long64_t  nbytes;
 //Sig signal;

 maxChannelHits = 20; //the maximum number of hits per one channel fixed in the structure
 
       nbytes += Tn->GetEntry(i);
       //cout <<"Event nr: " <<i <<endl; 
       Tot_NADCHits = event->GetTotalNTDCHits();
       //cout <<"Total number of ADC hits=" <<Tot_NADCHits<<endl;
       Tot_NTDCHits = event->GetTotalNADCHits();
       //cout <<"Total number of TDC hits="<<Tot_NTDCHits<<endl;
       TDCReferenceTime = event->GetTDCReferenceTime();
       //cout <<"TDC reference time"<<TDCReferenceTime<<endl;

       tdc = event->GetTDCHitsArray();
       adc = event->GetADCHitsArray();
       signal->nChannel = tdc->GetEntriesFast();//Number of channels fired in event
       signal->nSig = event->GetTotalNADCHits();
     //loop over all channels
       for(ii=0;ii<signal->nSig; ii++)
      {
        TDCHit* tshit = (TDCHit*) tdc->At(ii);

          signal->channel[ii] = tshit->GetChannel();
         
        for(j=0;j<maxChannelHits;j++)
           {
	     signal->LTimes[ii][j] = tshit->GetLeadTime(j);
             signal->TTimes[ii][j] = tshit->GetTrailTime(j);
           }
      }

return 0;
}
int pet_anaEv(Sig *sig,TTree *Tn)
//This routine is called for every event in the file/run
{
  Tn->Fill();
  sig->Clear();
  return 0;
}
int pet_book(TTree *&Tr,TFile *&file,Sig *&sigp)
{
  file = new TFile("treeRaw.root","recreate");
   Tr = new TTree("TR","Raw structure");
  Tr->Branch("Str","Sig",&sigp,64000,2);
  return 0;
}
int pet_close(TFile *fm,TFile *Fr,TTree *Tr)
{
  //This function is called once per file/run and contains
  //all procedures for closing files etc.

  fm->Close();
  Tr->Write();
  Tr->Print();
  Tr->Show(100000);
  delete Tr;
  Fr->Close();
  cout<<"Files closed successfully"<<endl;
  cout<<"Do widzenia"<<endl;
  return 0;
}
# ifndef __CINT__
int main(int argc, char *argv[])
{
  gSystem->Load("libTree"); //lading ROOT libraries
  Event* eventm = new Event();
  TTree *Tnm;
  TClonesArray *tdcm;
  TClonesArray *adcm;
  //const char *cRootFile = name.c_str(); 
  string zonk;
  Int_t nEntries,i,run_first,run_last;
  Sig* sig = new Sig();
  TTree *Tr;
  TFile *Fr;
  if(argc<2)
 {
    cout<<"Wrong number of arguments: Give at least the root file name!!"<<endl;
    return 0;}
  else{
       if(argc==2){zonk = argv[1];}
       else{
            run_first = atoi(argv[1]); //string/char->int conversion
            run_last = atoi(argv[2]);  //to convert float use atof()
	    cout<<"Analysing Runs from "<<run_first<<" to "<<run_last<<endl;
	    return 0;
           }
 }
  const char *cRootFile = zonk.c_str();
  TFile *fm = new TFile(cRootFile);

  pet_init(eventm,tdcm,adcm,Tnm,fm);
  pet_book(Tr,Fr,sig);
  nEntries = Tnm->GetEntries();

  cout<<"File: "<<zonk<<endl;
  cout <<"Number of Entries: "<<nEntries<<endl;

  for ( i=0; i<nEntries; i++)
    {
      pet_event(sig,i,eventm,tdcm,adcm,Tnm,fm);
      pet_anaEv(sig,Tr);
      //getchar();
    }
  pet_close(fm,Fr,Tr);
  return 0;
}
#endif
