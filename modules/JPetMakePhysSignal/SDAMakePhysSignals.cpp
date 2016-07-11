#include "./SDAMakePhysSignals.h"
#include "../../tools/JPetRecoSignalTools/JPetRecoSignalTools.h"

SDAMakePhysSignals::SDAMakePhysSignals(const char* name, const char* description) 
  : JPetTask(name, description)
{
}

SDAMakePhysSignals::~SDAMakePhysSignals()
{
}

void SDAMakePhysSignals::init(const JPetTaskInterface::Options& /* opts */)
{
}

void SDAMakePhysSignals::exec()
{
  const JPetRecoSignal& signal = (JPetRecoSignal&)(*getEvent());

  JPetPhysSignal physSignal;
  physSignal.setRecoSignal(signal);

  // NOTE: This module currently sets number of photoelectrons
  // equal to charge of JPetRecoSignal
  physSignal.setPhe(physSignal.getRecoSignal().getCharge() );
  
  fWriter->write(physSignal);
}


void SDAMakePhysSignals::terminate()
{
}
