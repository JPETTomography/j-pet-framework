#include "./ModuleD.h"

ClassImp(ModuleD);

ModuleD::ModuleD(const char* name, const char* title,
                 const char * in_file_suffix, const char * out_file_suffix) :
    JPetCommonAnalysisModule(name, title, in_file_suffix, out_file_suffix) {
  setVersion(MODULE_VERSION);
}

ModuleD::~ModuleD() {
}

void ModuleD::begin() {
  fInitialSignals = 0;
  fPairsFound = 0;

  addStatsObject(
      new TH1F("No. signals in TSlot", "Signals multiplicity per TSlot", 10,
               -0.5, 9.5));

  addStatsObject(
      new TH1F("Scins multiplicity", "scintillators multiplicity", 65, 5.5,
               70.5));

  // create a histogram of time difference for every scintillator in the setup
  // we loop over all scintillator objects in the parameters bank downloaded
  // from database for the run number given by user
  for(int i=0; i< getParamBank().getScintillatorsSize(); i++){
    JPetScin & scin = getParamBank().getScintillator(i);
    TString name = Form("dt for scin %d", scin.getID());
    addStatsObject(new TH1F(name, name, 100, -10000., 10000.));
  }

}

void ModuleD::exec() {
  if (fEvent > fEventNb - 2) return;
  
  // A dummy analysis example:
  JPetPhysSignal signals[20];
  int count = 0;
  // read subsequent signals
  while (true) {
    if (fEvent == fEventNb) break;
    fReader->nthEvent(fEvent);
    signals[count] = (JPetPhysSignal&) fReader->getCurrentEvent();
    if (signals[count].getTSlotIndex() == signals[0].getTSlotIndex()) {
      count++;
      fReader->nextEvent();
    } else {
      break;
    }
  }

  fInitialSignals += count;

  getHisto1D("No. signals in TSlot")->Fill(count);

  // only if there were at least 2 signals in one TSlot
  // there is a chance to find a Hit
  if (count >= 2) {

    for (int i = 0; i < count; i++) { // iterate over signals
      for (int j = i + 1; j < count; j++) {

        if (signals[i].getPM().getScin() == signals[j].getPM().getScin()) {
          // found 2 signals from the same scintillator
          JPetHit hit;
          if (signals[i].getPM().getSide() == JPetPM::SideA
              && signals[j].getPM().getSide() == JPetPM::SideB) {
            hit.setSignalA(signals[i]);
            hit.setSignalB(signals[j]);
          } else if (signals[j].getPM().getSide() == JPetPM::SideA
              && signals[i].getPM().getSide() == JPetPM::SideB) {
            hit.setSignalA(signals[j]);
            hit.setSignalB(signals[i]);
          } else {
            // if two hits on the same side, ignore
            continue;
          }

          hit.setScintillator(signals[i].getPM().getScin());

          getHisto1D("Scins multiplicity")->Fill(signals[i].getPM().getScin().getID());

          double dt = hit.getSignalA().getTime() - hit.getSignalB().getTime();
          hit.setTimeDiff(dt);

          double t = 0.5
              * (hit.getSignalA().getTime() + hit.getSignalB().getTime());
          hit.setTime(t);

          // fill the appropriate dt histogram for this scintillator
          getHisto1D( Form("dt for scin %d", hit.getScintillator().getID()))->Fill(hit.getTimeDiff());

          fPairsFound++;
          fWriter->write(hit);

        }

      }
    }

  }

  //  fReader->nextEvent();
}

void ModuleD::end() {
  // at any time of the analysis, you can write any information to the log (JPet.log) file
  // using three possible macros: INFO(const char*), WARNING(const char*) or ERROR(const char*)
  INFO(
      Form("From %d initial signals %d hits were paired.", fInitialSignals,
           fPairsFound));
}

