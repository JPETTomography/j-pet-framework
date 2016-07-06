/**
 * @file SDARecoChargeCalc.h
 * @author Szymon Niedźwiecki, szymon.niedzwiecki@googlemail.com
 * @copyright Copyright (c) 2015, Szymon Niedźwiecki
 * @brief Producer of charge for JPetRecoSignals
 * Reads a TTree of Reco Signals and calculates charges for each of them.
 * For more details look into README
 */

#ifndef _JPETANALYSISMODULE_SDACHARGE_H_
#define _JPETANALYSISMODULE_SDACHARGE_H_

#include "../../JPetTask/JPetTask.h"
#include "../../JPetWriter/JPetWriter.h"
#include "TCanvas.h"


class SDARecoChargeCalc: public JPetTask
{

 public:

  SDARecoChargeCalc(const char* name, const char* description);

  virtual ~SDARecoChargeCalc();
  virtual void exec();
  virtual void init(const JPetTaskInterface::Options& /* opts */);
  virtual void terminate();
  virtual void setWriter(JPetWriter* writer) {
    fWriter = writer;
  }

  
private:
	int fBadSignals;
	int fCurrentEventNumber;
	JPetWriter* fWriter;
};

#endif

