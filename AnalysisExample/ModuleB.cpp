#include "./ModuleB.h"

#include <map>

ClassImp(ModuleB);

ModuleB::ModuleB(const char* name, const char* title,
                 const char * in_file_suffix, const char * out_file_suffix) :
    JPetCommonAnalysisModule(name, title, in_file_suffix, out_file_suffix) {
  setVersion(MODULE_VERSION);
}

ModuleB::~ModuleB() {
}

void ModuleB::begin() {
  // store any histograms which should be accessible throughout the processing
  // in order to control the statistics
  // you can use 'addStatsObject' to quickly register any TObject, e.g. a histogram
  // which will be accessible in the exec() function and will be automatically
  // written to the output file
  addStatsObject(
      new TH1F("single thr multiplicity",
               "Single threshold multiplicity in TSlot", 10, -0.5, 9.5));

}

void ModuleB::exec() {
  std::cout <<"executing module B" <<std::endl;
  // Get the TSlot with RAW times

  fReader->nthEvent(fEvent);
  JPetTimeWindow & tslotRaw = (JPetTimeWindow&) fReader->getData();

  // get number of SigCh-s in a tslot
  int nSigChs = tslotRaw.getNumberOfSigCh();
  // create an object for the CALIBRATED tslot
  JPetTimeWindow tslotCal;
  tslotCal.setIndex(tslotRaw.getIndex());

  // we would like to check if a signal from one DAQ channel can occur more than once
  // during one Time Slot, so we will create a map(channel, No. of occurences) to count multiplicities
  std::map<int,int> channelMultiplicities;

  // iterate over SigCh's in the tslot and calibrate their times
  for (int i = 0; i < nSigChs; i++) {
    JPetSigCh sigchRaw = tslotRaw[i];
    JPetSigCh sigchCal = sigchRaw; // start the calibrated SigCh as a copy of the raw one

    // do our multiplicity counting
    channelMultiplicities[sigchRaw.getDAQch()]++;

    // a dummy "calibration" example; real calibration should go here
    float time = sigchRaw.getValue();
    time = time * 1.0 + 0.0;
    // set time after calibration in the new SigCh object
    sigchCal.setValue(time);

    // insert the calibrated SigCh into calibrated TSlot
    tslotCal.addCh(sigchCal);
  }

  fWriter->write(tslotCal);

  // write all non-zero multiplicities to a histogram
  for (std::map<int,int>::iterator it=channelMultiplicities.begin(); it!=channelMultiplicities.end(); ++it){
    if( it->second > 0 ){
      // note the way to access the histogram registered by 'addStatsObject' in the begin() function
      // you can access it by name
      getHisto1D("single thr multiplicity")->Fill(it->second);
    }
  }

  fReader->nextEvent();
  fEvent = fReader->getCurrentEventNumber();
}

void ModuleB::end() {
}
