/**
 * @file JPetAnalysisModuleB.h
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2013, Damian Trybek
 * @brief Analysis Module A
 * Reads Signals form root tree and merge them into Events.
 */

#ifndef _JPETANALYSISMODULE_B_H_
#define _JPETANALYSISMODULE_B_H_

#include <cstddef>

#include <JPetAnalysisModule/JPetAnalysisModule.h>
#include <JPetReader/JPetReader.h>
#include <JPetWriter/JPetWriter.h>

class JPetAnalysisModuleB: public JPetAnalysisModule {
  
  public:

  JPetAnalysisModuleB();
  JPetAnalysisModuleB(const char* name, const char* title);
  virtual ~JPetAnalysisModuleB();
  virtual void createInputObjects(const char* inputFilename=0);
  virtual void createOutputObjects(const char* outputFilename=0);
  virtual void exec();
  virtual long long getEventNb() {return fEventNb/4;}
  virtual void terminate();

  ClassDef(JPetAnalysisModuleB,1);

  private:
  
  int fEvent;
  int fEventNb;
  JPetReader* fReader;
  JPetWriter* fWriter;
};

#endif
