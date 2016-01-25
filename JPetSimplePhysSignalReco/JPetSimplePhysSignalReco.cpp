
#include <math.h>
#include <cassert>
#include <libconfig.h++>  // For reading configuration files
#include "HelperMathFunctions.h"
#include "JPetSimplePhysSignalReco.h"
#include "../JPetWriter/JPetWriter.h"

JPetSimplePhysSignalReco::JPetSimplePhysSignalReco():
  fAlpha(1),
  fThresholdSel(-1)
{
  readConfigFileAndSetAlphaAndThreshParams("configParams.cfg");
}

JPetSimplePhysSignalReco::~JPetSimplePhysSignalReco()
{
  /**/
}

void JPetSimplePhysSignalReco::exec()
{
  // Get a Reco Signal
  auto currSignal = (JPetRecoSignal&) (*getEvent());
  savePhysSignal(createPhysSignal(currSignal));
}

void JPetSimplePhysSignalReco::savePhysSignal(JPetPhysSignal sig)
{
  assert(fWriter);
  fWriter->write(sig);
}

JPetPhysSignal JPetSimplePhysSignalReco::createPhysSignal(JPetRecoSignal& recoSignal)
{
  // create a Phys Signal
  JPetPhysSignal physSignal;

  // use the values from Reco Signal to set the physical properties of signal
  // here, a dummy example - much more sophisticated procedures should go here
  physSignal.setPhe( recoSignal.getCharge() * 1.0 + 0.0 );
  physSignal.setQualityOfPhe(1.0);

  // in the previous module (C2) we have reconstructed one time at arbitrary
  // threshold - now we retrieve it by getting a map of times vs. thresholds,
  // and taking its first (and only) element by the begin() iterator. We get
  // an std::pair, where first is the threshold value, and second is time.
  double time = recoSignal.getRecoTimesAtThreshold().begin()->second;

  // -----------------------------------------------------------
  //
  // Estimate the time of the signal based on raw signal samples
  JPetRawSignal rawSignal = recoSignal.getRawSignal();

  if (rawSignal.getNumberOfPoints(JPetSigCh::Leading) >= 2
      && rawSignal.getNumberOfPoints(JPetSigCh::Trailing) >= 2) {
    // get number of points on leading edge
    int iNumPoints = rawSignal.getNumberOfPoints(JPetSigCh::Leading);

    std::vector<JPetSigCh> leadingPoints = rawSignal.getPoints(
        JPetSigCh::Leading, JPetRawSignal::ByThrValue);

    // create vectors
    vector<float> vecTime(iNumPoints);
    vector<float> vecVolt(iNumPoints);

    for (int j = 0; j < iNumPoints; j++) {
      vecTime(j) = leadingPoints.at(j).getValue();
      vecVolt(j) = leadingPoints.at(j).getThreshold();
    }

    // To evaluate time below parameters should be specified:

    // the parameter alfa of the below expression need to be specified:
    // vecVolt = a(t - vecTime)^(alfa);
    // Here alfa is fixed for the linear case.
    // Caution! alfa has to be an integer and positive value, negative values are ignored.
    int alfa = getAlpha();

    // thr_sel specifies the threshold level to read the time value,
    // and with thr_sel the below equation may be solved:
    // thr_sel = a(t - time)^(alfa);
    // Caution! thr_sel has to negative, and for positive values the program will set thr_sel equal to 0.
    float thr_sel = getThresholdSel();

    // The evaluation of time based on alfa and thr_sel
    assert(thr_sel < 0);
    assert(alfa > 0);
    time = static_cast<double>(polynomialFit(vecTime, vecVolt, alfa, thr_sel));
  }
  // ------------------------------------------------------------

  physSignal.setTime(time);
  physSignal.setQualityOfTime(1.0);

  // store the original JPetRecoSignal in the PhysSignal as a processing history
  physSignal.setRecoSignal(recoSignal);
  return physSignal;
}

void JPetSimplePhysSignalReco::terminate()
{
  /**/
}

void JPetSimplePhysSignalReco::readConfigFileAndSetAlphaAndThreshParams(const char* filename)
{
  libconfig::Config cfg;

  try {
    cfg.readFile(filename);
  } catch (const libconfig::FileIOException& fioex) {
    std::cerr << "I/O error while reading file." << std::endl;
  } catch (const libconfig::ParseException& pex) {
    std::cerr << "Parse error" << std::endl;
  }

  try {
    libconfig::Setting& l_settings = cfg.lookup("Configuration");
    int alpha = l_settings[0]["alpha"];
    float thresholdSel = l_settings[0]["thresholdSel"];
    setAlpha(alpha);
    setThresholdSel(thresholdSel);
  } catch (const libconfig::SettingNotFoundException& nfex) {
    std::cerr << "No 'name' setting in configuration file." << std::endl;
  }
}
