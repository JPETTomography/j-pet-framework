#include "JPetHLDReader.h"
#include <iostream>
#include <cassert>

JPetHLDReader::JPetHLDReader () : fBranch(NULL), fFile(NULL), fObject(NULL), fTree(NULL) {
}

JPetHLDReader::JPetHLDReader (const char* filename) : fBranch(NULL), fFile(NULL), fObject(NULL), fTree(NULL) {
  if (OpenFile(filename) ) ReadData("");
}

JPetHLDReader::~JPetHLDReader () {
  CloseFile();
}

void JPetHLDReader::CloseFile () {
  if (fFile != NULL) {
    if (fFile->IsOpen()) fFile->Close();
    delete fFile;
  }
  fBranch = NULL;
  fFile = NULL;
  fObject = NULL;
  fTree = NULL;
}


bool JPetHLDReader::OpenFile (const char* filename) {
  CloseFile();
  fFile = new TFile(filename);

  if ((!fFile->IsOpen())||fFile->IsZombie()) {
    ERROR("Cannot open file.");
    delete fFile;
    fFile = NULL;
    return false;
  }
  return true;
}


void JPetHLDReader::ReadData () {

  fTree = static_cast<TTree*>(fFile->Get("T")); /// @todo add some comment
  assert(fTree);
  fBranch = fTree->GetBranch("event");
  assert(fBranch);
  fBranch->SetAddress(&fObject);
}
//
//
//       nbytes += Tn->GetEntry(i);
//       //cout <<"Event nr: " <<i <<endl; 
//       Tot_NADCHits = event->GetTotalNTDCHits();
//       //cout <<"Total number of ADC hits=" <<Tot_NADCHits<<endl;
//       Tot_NTDCHits = event->GetTotalNADCHits();
//       //cout <<"Total number of TDC hits="<<Tot_NTDCHits<<endl;
//       TDCReferenceTime = event->GetTDCReferenceTime();
//       //cout <<"TDC reference time"<<TDCReferenceTime<<endl;
//
//       tdc = event->GetTDCHitsArray();
//       adc = event->GetADCHitsArray();
//       signal->nChannel = tdc->GetEntriesFast();//Number of channels fired in event
//       signal->nSig = event->GetTotalNADCHits();
//     //loop over all channels
//       for(ii=0;ii<signal->nSig; ii++)
//      {
//        TDCHit* tshit = (TDCHit*) tdc->At(ii);
//
//          signal->channel[ii] = tshit->GetChannel();
//
//        for(j=0;j<maxChannelHits;j++)
//           {
//             signal->LTimes[ii][j] = tshit->GetLeadTime(j);
//             signal->TTimes[ii][j] = tshit->GetTrailTime(j);
//           }
//      }
//
//return 0;
//}
