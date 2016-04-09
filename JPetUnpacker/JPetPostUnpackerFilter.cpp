/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file JPetPostUnpackerFilter.cpp
 */

#include "JPetPostUnpackerFilter.h"

#include "Unpacker2/EventIII.h"
//#include "Unpacker2/TDCHitIII.h"
#include "Unpacker2/Event.h"
#include "Unpacker2/TDCHit.h"
#include "Unpacker2/TDCHitExtended.h"
#include "Unpacker2/TDCChannel.h"
#include "Unpacker2/Unpacker2.h"
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <TH2F.h>
#include <TTree.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TFile.h>
#include <string.h>
#include <TIterator.h>
#include <TCollection.h>
#include <unistd.h>

using namespace std;

#define REF_CHANNELS_NUMBER 50

int JPetPostUnpackerFilter::calculate_hits(int eventsNum, const char* fileName)
{
  TChain chain("T");
  chain.Add(fileName);
    
  Event* pEvent = 0;
  TDCHitExtended* pHit = 0;
  TClonesArray* pArray = 0;
  chain.SetBranchAddress("event", &pEvent);

  string newFileName = "";
  newFileName = string(fileName);
  cerr<<"HITS:"<<newFileName<<endl;
  newFileName = newFileName.substr(0, newFileName.size() - 5);
  newFileName += "_hits.root";
  
  TFile* new_file = new TFile(newFileName.c_str(), "RECREATE");
  TTree* new_tree = new TTree("T", "Times converted into hit units");
  EventIII* new_event = 0;
  Int_t split = 2;
  Int_t bsize = 64000;
  TBranch* event_branch = new_tree->Branch("eventIII", "EventIII", &new_event, bsize, split);
  
  Int_t entries = (Int_t)chain.GetEntries();

  double actualLead = -100000;
  bool firstLeadFound = false;
  
  TIter * iter;
  
  for(Int_t i = 0; i < entries; i++){

    //if (i % 10000 == 0) cerr<<i<<" of "<<entries<<"\r";
    if (i == eventsNum) break;
    chain.GetEntry(i);
    pArray = pEvent->GetTDCHitsArray();
    if (pArray == 0) continue;
    iter = new TIter(pArray);
    
    
    while( pHit = (TDCHitExtended*) iter->Next() ){
      TDCChannel* new_ch = new_event->AddTDCChannel(pHit->GetChannel());
      
      // hit construction logic
      actualLead = -100000;
      firstLeadFound = false;
	
      for (int j = 0; j < pHit->GetTimeLineSize(); j++) {
	if (pHit->GetRisingEdge(j) == true && firstLeadFound == false) {
	  actualLead = pHit->GetAbsoluteTimeLine(j);
	  firstLeadFound = true;
	}
	else if (pHit->GetRisingEdge(j) == false && firstLeadFound == true) {
	  new_ch->AddHit(actualLead, pHit->GetAbsoluteTimeLine(j));
	  firstLeadFound = false;	    
	}
      }
    }
    
    new_tree->Fill();
    new_event->Clear();
    delete iter;
  }
  
  new_tree->Write();
  
  new_file->Close();
  
  return 0;
}


int JPetPostUnpackerFilter::calculate_times(int eventsNum, const char* fileName, int refChannelOffset, const char* calibFile)
{
  TH1F* calibHist;
  TH1F* tmp;
  
  // load zero offsets in case no file is specified
  string calibFileName = string(calibFile);
  if (calibFileName.find(".root") == string::npos) {
    calibHist = new TH1F("stretcher_offsets", "stretcher_offsets", REF_CHANNELS_NUMBER * refChannelOffset, 0, REF_CHANNELS_NUMBER * refChannelOffset);
    for (int i = 0; i < REF_CHANNELS_NUMBER * refChannelOffset; i++) {
      calibHist->SetBinContent(i + 1, 0);
    }
    cerr<<"Zero offsets and calib loaded"<<endl;
  }
  // load the stretcher offsets calibration
  else {
    TFile* file = new TFile();
    ifstream my_file(calibFileName.c_str());
    file = new TFile(calibFileName.c_str(), "READ");
    TDirectory* dir = gDirectory->GetDirectory("Rint:/");
    tmp = (TH1F*)file->Get("stretcher_offsets");
    
    cerr<<"Calculated  calib loadedasdasd"<<endl;
    
    calibHist = (TH1F*)(tmp->Clone("stretcher_offsets"));
    calibHist->SetDirectory(dir);
    
    cerr<<"Calculated  calib loaded"<<endl;
    
    file->Close();
  }
  
  //int localTrailIndex = 0;
  double lastTime = -1;
  int localIndex = 0;
  
  TChain chain("T");
  chain.Add(fileName);
  
  Event* pEvent = 0;
  TDCHit* pHit = 0;
  TClonesArray* pArray = 0;
  chain.SetBranchAddress("event", &pEvent);
  
  string newFileName = string(fileName);
  cerr<<"TIMES:"<<newFileName<<endl;
  newFileName = newFileName.substr(0, newFileName.size() - 5);
  newFileName += "_times.root";
  
  TFile* new_file = new TFile(newFileName.c_str(), "RECREATE");
  TTree* new_tree = new TTree("T", "Normalized times tree");
  Event* new_event = 0;
  Int_t split = 2;
  Int_t bsize = 64000;
  new_tree->Branch("event", "Event", &new_event, bsize, split);
  
  Int_t entries = (Int_t)chain.GetEntries();
  cout<<"Entries = " <<entries<<endl;
  

 int refTimeEpoch[REF_CHANNELS_NUMBER];
 int refTimeCoarse[REF_CHANNELS_NUMBER];
 int refTimeFine[REF_CHANNELS_NUMBER];
 
 TIter * iter;

 for(Int_t i = 0; i < entries; i++){

   if (i == eventsNum) break;
   chain.GetEntry(i);
   pArray = pEvent->GetTDCHitsArray();
   if (pArray == 0) continue;
   iter = new TIter(pArray);
   
   for(int l = 0; l < REF_CHANNELS_NUMBER; l++) {
     refTimeEpoch[l] = -222222;
     refTimeCoarse[l] = -222222;
     refTimeFine[l] = -222222;			
   }
   
   // fetch the reference times
   while( pHit = (TDCHit*) iter->Next()) {
     if (pHit->GetChannel() % refChannelOffset == 0){
       
       refTimeEpoch[pHit->GetChannel() / refChannelOffset] = pHit->GetLeadEpoch(0);
       refTimeCoarse[pHit->GetChannel() / refChannelOffset] = pHit->GetLeadCoarse(0);
       refTimeFine[pHit->GetChannel() / refChannelOffset] = pHit->GetLeadFine(0);
       
       double leadTime = (double) (
				   (						
				    ( (((unsigned)pHit->GetLeadEpoch(0)) << 11) * 5.0)
										)
				   );
       leadTime += ( ( (pHit->GetLeadCoarse(0) * 5000.) - (pHit->GetLeadFine(0)) ) / 1000.);
       
       TDCHitExtended* new_hit = new_event->AddTDCHitExtended(pHit->GetChannel());
       new_hit->SetAbsoluteTimeLine(leadTime, 0);
       new_hit->SetRisingEdge(true, 0);
       new_hit->SetAbsoluteTimeLine(leadTime + 10, 1);
       new_hit->SetRisingEdge(false, 1);
       new_hit->SetTimeLineSize(2);
     }
   }
   // create time lines for normal channels
   iter->Begin();
   while( pHit = (TDCHit*) iter->Next() ){
     if ( (pHit->GetLeadsNum() > 0 && pHit->GetTrailsNum() > 0) && ((pHit->GetChannel() % refChannelOffset) != 0) ){
       TDCHitExtended* new_hit = new_event->AddTDCHitExtended(pHit->GetChannel());
       //localTrailIndex = 0;
       lastTime = -1;
       localIndex = 0;
       
       int tdc_number = pHit->GetChannel() / refChannelOffset;
       
       for (int j = 0; j < pHit->GetLeadsNum(); j++) {

	 double leadTime = (double) (
				     (						
				      ( (((unsigned)pHit->GetLeadEpoch(j)) << 11) * 5.0) -
				      ( (((unsigned)refTimeEpoch[tdc_number]) << 11) * 5.0 )
										)
				     );
	 leadTime += ((((pHit->GetLeadCoarse(j) - refTimeCoarse[tdc_number]) * 5000.) - (pHit->GetLeadFine(j) - refTimeFine[tdc_number])) / 1000.);
	 if (localIndex > 0) {
	   for(int l = 0; l <= localIndex; l++)
	     {
	       if (leadTime < new_hit->GetAbsoluteTimeLine(l) || l == localIndex) {
		 new_hit->ShiftEverythingUpByOne(l - 1);
		 new_hit->SetAbsoluteTimeLine(leadTime, l);
		 new_hit->SetRisingEdge(true, l);
		 localIndex++;
		 new_hit->SetTimeLineSize(localIndex);
		 break;
	       }
	     }
	 }
	 else {
	   new_hit->SetAbsoluteTimeLine(leadTime, 0);
	   new_hit->SetRisingEdge(true, 0);
	   localIndex++;
	   new_hit->SetTimeLineSize(localIndex);
	 }
       }
       for (int k = 0; k < pHit->GetTrailsNum(); k++){

	 double trailTime = (double) (
				      (						
				       ( (((unsigned)pHit->GetTrailEpoch(k)) << 11) * 5.0) -
				       ( (((unsigned)refTimeEpoch[tdc_number]) << 11) * 5.0 )
										)
				      );
	 
	 trailTime -= calibHist->GetBinContent(pHit->GetChannel() + 1);
	 //cerr<<calibHist->GetBinContent(pHit->GetChannel() + 1)<<endl;
	 
	 trailTime += ( (((pHit->GetTrailCoarse(k) - refTimeCoarse[tdc_number]) * 5000.) - (pHit->GetTrailFine(k) - refTimeFine[tdc_number])) / 1000.);
	 
	 if (localIndex > 0) {
	   for(int l = 0; l <= localIndex; l++){
	     if (trailTime < new_hit->GetAbsoluteTimeLine(l) || l == localIndex ) {
	       new_hit->ShiftEverythingUpByOne(l - 1);
	       new_hit->SetAbsoluteTimeLine(trailTime, l);
	       new_hit->SetRisingEdge(false, l);
	       localIndex++;
	       new_hit->SetTimeLineSize(localIndex);
	       break;
	     }
	   }
	 }
	 else {
	   new_hit->SetAbsoluteTimeLine(trailTime, 0);
	   new_hit->SetRisingEdge(false, 0);
	   localIndex++;
	   new_hit->SetTimeLineSize(localIndex);
	 }
       }
       new_hit->SetTimeLineSize(localIndex);
     }
   }
   new_tree->Fill();
   new_event->Clear();
   delete iter;
 }
 
 new_tree->Write();
 
 new_file->Close();
 
 return 0;
}
