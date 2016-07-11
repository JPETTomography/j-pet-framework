/**
 * @file SDAMakePhysSignals.h
 * @author Szymon Niedzwiecki, szymon.niedzwiecki@googlemail.com
 * @copyright Copyright (c) 2015, Szymon Niedzwiecki
 * @brief Dummy producer of JPetPhysSignal objects
 * Reads a TTree of RecoSignals and transforms them into JPetPhysSignal objects
 * PhysSignals have charge value of their RecoSignals set as fPhe
 */

#ifndef _JPETANALYSISMODULE_SDAMAKEPHYSSIGNALS_H_
#define _JPETANALYSISMODULE_SDAMAKEPHYSSIGNALS_H_

#include "TCanvas.h"
#include "../../JPetTask/JPetTask.h"
#include "../../JPetWriter/JPetWriter.h"

class SDAMakePhysSignals: public JPetTask
{
public:

  SDAMakePhysSignals(const char* name, const char* description);
  virtual ~SDAMakePhysSignals();
  virtual void exec();
  virtual void init(const JPetTaskInterface::Options& /* opts */);
  virtual void terminate();
  virtual void setWriter(JPetWriter* writer) {
    fWriter = writer;
  }

  
private:

    JPetWriter* fWriter;
};

#endif
