/**
 * @file SDARecoOffsetsCalc.h
 * @author Szymon Niedzwiecki, szymon.niedzwiecki@googlemail.com
 * @copyright Copyright (c) 2015, Szymon Niedzwiecki
 * @brief Calculates offsets for each JPetRecoSignal from SDA
 * Reads a TTree of JPetRecoSignals and calculates is offset value. For more info
 * look into Monika Pawlik-Niedzwiecka master thesis. 
 */

#ifndef _JPETANALYSISMODULE_SDARECOOFFSETCALC_H_
#define _JPETANALYSISMODULE_SDARECOOFFSETCALC_H_

#include "../../JPetTask/JPetTask.h"
#include "TCanvas.h"

class SDARecoOffsetsCalc: public JPetTask
{

public:

  SDARecoOffsetsCalc(const char* name, const char* title);
  virtual ~SDARecoOffsetsCalc();
  virtual void init(const JPetTaskInterface::Options& /* opts */);
  virtual void exec();
  virtual void terminate();

private:
  // put any custom variables (e.g. histograms) here:
  int fCurrentEventNumber;
  double fOffset;
  int fBadSignals;
};

#endif
