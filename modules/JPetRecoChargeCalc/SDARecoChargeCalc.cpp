#include "./SDARecoChargeCalc.h"
#include "../../tools/JPetRecoSignalTools/JPetRecoSignalTools.h"

SDARecoChargeCalc::SDARecoChargeCalc(const char* name, const char* description) 
  : JPetTask(name, description),
    fBadSignals(0),
    fCurrentEventNumber(0)
{}

SDARecoChargeCalc::~SDARecoChargeCalc()
{
}

void SDARecoChargeCalc::init(const JPetTaskInterface::Options& /* opts */)
{
  INFO(
       Form("Starting charge calculation")
       );
  fBadSignals =0;
}

void SDARecoChargeCalc::exec()
{
  // first take signal from fEvent
  const JPetRecoSignal& signal = (JPetRecoSignal&)(*getEvent());

  //calculate charge of the signal
  double charge = JPetRecoSignalTools::calculateAreaFromStartingIndex(signal);

  // if something went wrong with calculation charge value will be equal to 999999
  if (charge == JPetRecoSignalTools::ERRORS::badCharge) {
	  WARNING( Form("Something went wrong when calculating charge for event: %d", fCurrentEventNumber) );
	  JPetRecoSignalTools::saveBadSignalIntoRootFile(signal, fBadSignals, "badCharges.root");
	  fBadSignals++;
	  fCurrentEventNumber++; 
	  return;
  }



  //to save Reco signal one needs to copy it to non const variable
  JPetRecoSignal signalWithCharge = signal;

  //setting offset of signal
  signalWithCharge.setCharge(charge);
  
  //saving singal into output root file
  fWriter->write(signalWithCharge);

  // increase event counter
  fCurrentEventNumber++;
}

void SDARecoChargeCalc::terminate()
{
  int fEventNb = fCurrentEventNumber; 
  double goodPercent = (fEventNb-fBadSignals) * 100.0/fEventNb;
  INFO(
       Form("Charge` calculation complete \nAmount of bad signals: %d \n %f %% of data is good" , fBadSignals, goodPercent) );
}
