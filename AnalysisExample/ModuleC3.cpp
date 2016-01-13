#include "./ModuleC3.h"

ClassImp(ModuleC3);

ModuleC3::ModuleC3(const char* name, const char* title,
                   const char * in_file_suffix, const char * out_file_suffix) :
    JPetCommonAnalysisModule(name, title, in_file_suffix, out_file_suffix) {
  setVersion(MODULE_VERSION);
}

ModuleC3::~ModuleC3() {
}

void ModuleC3::begin() {
}

void ModuleC3::exec() {
  // Get a Reco Signal
  fReader->nthEvent(fEvent);
  JPetRecoSignal & recoSignal = (JPetRecoSignal&) fReader->getCurrentEvent();

  // create a Phys Signal
  JPetPhysSignal physSignal;

  // use the values from Reco Signal to set the physical properties of signal
  // here, a dummy example - much more sophisticated procedures should go here
  physSignal.setPhe( recoSignal.getCharge()*1.0 + 0.0 );
  physSignal.setQualityOfPhe(1.0);

  // in the previous module (C2) we have reconstructed one time at arbitrary
  // threshold - now we retrieve it by getting a map of times vs. thresholds,
  // and taking its first (and only) element by the begin() iterator. We get
  // an std::pair, where first is the threshold value, and second is time.
  double time =recoSignal.getRecoTimesAtThreshold().begin()->second;
  physSignal.setTime(time);
  physSignal.setQualityOfTime(1.0);

  // store the original JPetRecoSignal in the PhysSignal as a processing history
  physSignal.setRecoSignal(recoSignal);

  // finally, write the RecoSignal to the output tree
  fWriter->write(physSignal);

  // increase event counter - otherwise the same raw signal would be read in the next iteration
  fReader->nextEvent();

}

void ModuleC3::end() {
}
