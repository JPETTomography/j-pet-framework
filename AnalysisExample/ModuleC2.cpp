#include "./ModuleC2.h"

ClassImp(ModuleC2);

ModuleC2::ModuleC2(const char* name, const char* title,
                   const char * in_file_suffix, const char * out_file_suffix) :
    JPetCommonAnalysisModule(name, title, in_file_suffix, out_file_suffix) {
  setVersion(MODULE_VERSION);
}

ModuleC2::~ModuleC2() {
}

void ModuleC2::begin() {
  addStatsObject(new TH1F("tot", "Time over Threshold", 100, 0., 5000));
}

void ModuleC2::exec() {

  // Get a Raw Signal
  fReader->nthEvent(fEvent);
  JPetRawSignal & rawSignal = (JPetRawSignal&) fReader->getCurrentEvent();

  // create a Reco Signal
  JPetRecoSignal recoSignal;

  // example dummy analysis - calculate Time Over Threshold:
  double ToT = rawSignal.getTOT(); // will return a reasonable value only if
  // the raw signal contains a ToT measurement from the electronics

  if (ToT == JPetSigCh::kUnset) { // we got JPetSigCh::kUnset value,
    // perhaps boards without ToT capability were used?
    // we calculate ToT by hand, then

    // first, get vectors of SigCh-s from both edges, sorted by their threshold values
    std::vector<JPetSigCh> leadingPoints = rawSignal.getPoints(
        JPetSigCh::Leading, JPetRawSignal::ByThrValue);
    std::vector<JPetSigCh> trailingPoints = rawSignal.getPoints(
        JPetSigCh::Trailing, JPetRawSignal::ByThrValue);
    // if the values of thresholds were not set i the database, you may want to use
    // JPetRawSignal::ByThrNum option instead which will sort the SigCh-s by the number
    // of threshold on its edge (1,..,4 in this case) rather by threshold value

    // on each edge, take the first (smallest) threshold and its corresponding time
    double t1 = leadingPoints.front().getValue();
    double t2 = trailingPoints.front().getValue();
    // note that there is no guarantee that these two smallest thresholds will actually
    // have the same threshold value: for some reason, time on the smallest threshold
    // might not have been recorded on one of the edges
    // this should be checked, but it is beyond the scope of this simple example

    // finally, calculate the ToT
    ToT = t2 - t1;
  }

  // now, that we have the ToT, we can calculate charge from it
  // here, a dummy calculation
  double charge = ToT * 1.0 + 0.0;

  // and write the tot value to a histogram
  getHisto1D("tot")->Fill(ToT);

  // store the newly calculated charge value in the RecoSignal
  recoSignal.setCharge( charge );

  // similarly to the above example, we can calculate other properties
  // and store them
  recoSignal.setDelay( 0.0 );
  recoSignal.setOffset( 0.0 );
  recoSignal.setAmplitude( 0.0 );

  // one more silly example - calculate time at arbitrary threshold by "interpolation"
  // between lowest and second-lowest threshold measured by DAQ on leading edge
  double t1,t2, thr1, thr2;
  t1 = rawSignal.getPoints(JPetSigCh::Leading, JPetRawSignal::ByThrValue).at(0).getValue();
  thr1 = rawSignal.getPoints(JPetSigCh::Leading, JPetRawSignal::ByThrValue).at(0).getThreshold();
  t2 = rawSignal.getPoints(JPetSigCh::Leading, JPetRawSignal::ByThrValue).at(1).getValue();
  thr2 = rawSignal.getPoints(JPetSigCh::Leading, JPetRawSignal::ByThrValue).at(1).getThreshold();

  recoSignal.setRecoTimeAtThreshold((thr1+thr2)/2., (t1+t2)/2. );
  //recoSignal.setRecoTimeAtThreshold(10., 20. );

  // store the original JPetRawSignal in the RecoSignal as a processing history
  recoSignal.setRawSignal(rawSignal);

  // finally, write the RecoSignal to the output tree
  fWriter->write(recoSignal);

  // increase event counter - otherwise the same raw signal would be read in the next iteration
  fReader->nextEvent();
}

void ModuleC2::end() {
}
