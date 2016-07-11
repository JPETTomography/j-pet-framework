/**
 * @file drawAllOffsets.h
 * @author Szymon Niedzwiecki, szymon.niedzwiecki@googlemail.com
 * @copyright Copyright (c) 2015, Szymon Niedzwiecki
 * @brief Draws charges spectra for PMT
 * Reads a TTree of JPetRecoSignals and fills offset values from PMTs to the histo. 
 */

#ifndef _JPETANALYSISMODULE_DRAWALLOFFSETS_H_
#define _JPETANALYSISMODULE_DRAWALLOFFSETS_H_

#include "../../JPetTask/JPetTask.h"
#include "TCanvas.h"

class SDARecoDrawAllOffsets: public JPetTask
{

public:

  SDARecoDrawAllOffsets(const char* name, const char* description);
  virtual ~SDARecoDrawAllOffsets();
  virtual void exec();
  virtual void init();
  virtual void terminate();

private:
  // put any custom variables (e.g. histograms) here:
    std::vector<TH1F*> fOffsetHistos;
    std::vector<std::vector<double> > fOffsets;
    double fOffset;
    std::vector<int> fIDs;
    unsigned int fNumberOfPMTs;
    std::string fFileName;
};

#endif

