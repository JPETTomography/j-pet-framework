//
// Created by karol on 12.05.15.
//

#include "JPetAnalysisRunner.h"

#include <TH1F.h>
#include <TRandom3.h>
#include <TCanvas.h>

//_____________________________________________________________________________
JPetAnalysisRunner::JPetAnalysisRunner()
{
    // Constructor
    fH1F = 0;
    fRandom = 0;
}

//_____________________________________________________________________________
JPetAnalysisRunner::~JPetAnalysisRunner()
{
    // Destructor
    if (fRandom) delete fRandom;
}
void JPetAnalysisRunner::SlaveBegin(TTree * /*tree*/)
{
    // The SlaveBegin() function is called after the Begin() function.
    // When running with PROOF SlaveBegin() is called on each slave server.
    // The tree argument is deprecated (on PROOF 0 is passed).

    // TString option = GetOption();

    // Histogram
    fH1F = new TH1F("FirstH1F", "First TH1F in PROOF", 100, -10., 10.);
    fOutput->Add(fH1F);

    // Random number generator
    fRandom = new TRandom3(0);
}

Bool_t JPetAnalysisRunner::Process(Long64_t)
{
    // The Process() function is called for each entry in the tree (or possibly
    // keyed object in the case of PROOF) to be processed. The entry argument
    // specifies which entry in the currently loaded tree is to be processed.
    // It can be passed to either ProofFirst::GetEntry() or TBranch::GetEntry()
    // to read either all or the required parts of the data. When processing
    // keyed objects with PROOF, the object is already loaded and is available
    // via the fObject pointer.
    //
    // This function should contain the "body" of the analysis. It can contain
    // simple or elaborate selection criteria, run algorithms on the data
    // of the event and typically fill histograms.
    //
    // The processing can be stopped by calling Abort().
    //
    // Use fStatus to set the return value of TTree::Process().
    //
    // The return value is currently not used.

    if (fRandom && fH1F) {
        Double_t x = fRandom->Gaus(0.,1.);
        fH1F->Fill(x);
    }

    return kTRUE;
}

void JPetAnalysisRunner::Terminate()
{
    // The Terminate() function is the last function to be called during
    // a query. It always runs on the client, it can be used to present
    // the results graphically or save the results to file.

    // Create a canvas, with 100 pads
    TCanvas *c1 = new TCanvas("c1", "Proof ProofFirst canvas",200,10,400,400);
    fH1F = dynamic_cast<TH1F *>(fOutput->FindObject("FirstH1F"));
    if (fH1F) fH1F->Draw();
    c1->Update();
    c1->SaveAs("histo.jpg");
}