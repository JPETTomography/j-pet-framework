#include "./ModuleC1.h"

ClassImp(ModuleC1);

ModuleC1::ModuleC1(const char* name, const char* title,
                   const char * in_file_suffix, const char * out_file_suffix) :
    JPetCommonAnalysisModule(name, title, in_file_suffix, out_file_suffix) {
  setVersion(MODULE_VERSION);
}

ModuleC1::~ModuleC1() {
}

void ModuleC1::begin() {
  // store any histograms which should be accessible throughout the processing
  // in order to control the statistics
  // you can use 'addStatsObject' to quickly register any TObject, e.g. a histogram
  // which will be accessible in the exec() function and will be automatically
  // written to the output file
  addStatsObject(
      new TH1F("No. leading points", "Leading edge points per signal", 5, -0.5,
               4.5));
  addStatsObject(
      new TH1F("No. trailing points", "Trailing edge points per signal", 5,
               -0.5, 4.5));
  addStatsObject(
      new TH2F("leading vs trailing", "Leading vs trailing points per signal",
               5, -0.5, 4.5, 5, -0.5, 4.5));
  addStatsObject(
      new TH1F("No. of fired PM-s", "Fired PMs per event", 9, -0.5, 8.5));
  addStatsObject(
      new TH1F("PM multiplicity", "PM signal multiplicity", 60, 0.5, 60.5));
}

void ModuleC1::exec() {

  // Get the TSlot with calibrated times
  fReader->nthEvent(fEvent);
  JPetTimeWindow & tslot = (JPetTimeWindow&) fReader->getData();

  // get number of SigCh's in a tslot
  int nSigChs = tslot.getNumberOfSigCh();

  JPetRawSignal * signalsArray = new JPetRawSignal[getParamBank().getPMsSize()];

  // iterate over SigCh's in the Tslot and join them in signals
  for (int i = 0; i < nSigChs; i++) {
    JPetSigCh sigch = tslot[i];

    int index = 0;
    while (index < getParamBank().getPMsSize()
        && getParamBank().getPM(index) != sigch.getPM())
    {
        index++;
    }
    signalsArray[index].addPoint(sigch);

  }

  int nPMs = 0;

  for (int i = 0; i < getParamBank().getPMsSize(); i++) {
    JPetRawSignal sig = signalsArray[i];

    if (sig.getNumberOfPoints(JPetSigCh::Leading) == 0
        && sig.getNumberOfPoints(JPetSigCh::Trailing) == 0) { //skip empty signals
      continue;
    }
    nPMs++; // count how many PM-s fired in one TSlot

    sig.setTSlotIndex(tslot.getIndex());
    sig.setPM(getParamBank().getPM(i));

    // keep some statistics
    getHisto1D("No. leading points")->Fill(sig.getNumberOfPoints(JPetSigCh::Leading));
    getHisto1D("No. trailing points")->Fill(
        sig.getNumberOfPoints(JPetSigCh::Trailing));
    getHisto2D("leading vs trailing")->Fill(
        sig.getNumberOfPoints(JPetSigCh::Leading),
        sig.getNumberOfPoints(JPetSigCh::Trailing));

    getHisto1D("PM multiplicity")->Fill(sig.getPM().getID());

    // consider events with at least 3 fired thresholds
    if (sig.getNumberOfPoints(JPetSigCh::Leading) >= 2
        && sig.getNumberOfPoints(JPetSigCh::Trailing) >= 2) {

      // if the signal is worth keeping, write the signal to output tree
      fWriter->write(sig);
    }

  }

  getHisto1D("No. of fired PM-s")->Fill(nPMs);
  fReader->nextEvent();
  fEvent=fReader->getCurrentEventNumber();

  delete[] signalsArray;
}

void ModuleC1::end() {
}
