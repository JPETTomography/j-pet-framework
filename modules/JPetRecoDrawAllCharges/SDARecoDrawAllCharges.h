/**
 * @file drawAllCharges.h
 * @author Szymon Niedzwiecki, szymon.niedzwiecki@googlemail.com
 * @copyright Copyright (c) 2015, Szymon Niedzwiecki
 * @brief Draws charges spectra for PMT
 * Reads a TTree of JPetRecoSignals and fills charge values from PMTs to the histo. 
 */

#ifndef _JPETANALYSISMODULE_DRAWALLCHARGES_H_
#define _JPETANALYSISMODULE_DRAWALLCHARGES_H_

#include "../../JPetTask/JPetTask.h"
#include "TCanvas.h"
#include <map>

class SDARecoDrawAllCharges: public JPetTask
{

public:

  SDARecoDrawAllCharges(const char* name, const char* description);
  virtual ~SDARecoDrawAllCharges();
  virtual void exec();
  virtual void init();
  virtual void terminate();

private:
  // put any custom variables (e.g. histograms) here:
  std::map<int,TH1F*> fChargeHistos;
  std::map<int,std::vector<double> > fCharges;
  double fCharge;
  std::vector<int> fIDs;
  unsigned int fNumberOfPMTs;
  std::string fFileName;
};

#endif

