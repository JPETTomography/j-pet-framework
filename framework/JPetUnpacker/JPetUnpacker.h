/**
 * @file JPetUnpacker.h
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2014, Damian Trybek
 */

#ifndef _JPETUNPACKER_H_
#define _JPETUNPACKER_H_

#include <cstddef>

#include "../JPetAnalysisModule/JPetAnalysisModule.h"

class JPetUnpacker: public JPetAnalysisModule {
  
  public:

  JPetUnpacker();
  JPetUnpacker(const char* name, const char* title);
  virtual ~JPetUnpacker();
  virtual void CreateInputObjects(const char* inputFilename=0);
  virtual void CreateOutputObjects(const char* outputFilename=0);
  virtual void SetParams(const char* hldFile, const char* cfgFile, int numOfEvents);
  virtual void Exec();
  virtual long long GetEventNb() {return fEventNb;}
  virtual void Terminate();

  ClassDef(JPetUnpacker,1);

  private:
  
  int fEvent;
  int fEventNb;
  int fEventsToProcess;
  const char* fHldFile;	//!
  const char* fCfgFile;	//!
};

#endif
