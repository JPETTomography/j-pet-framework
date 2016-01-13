/**
 * @file JPetAnalysisModuleA.h
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2013, Damian Trybek
 * @brief Analysis Module A
 * Reads raw data and produce ROOT tree, then saves it into binary file.
 */

#ifndef _JPETANALYSISMODULE_A_H_
#define _JPETANALYSISMODULE_A_H_

#include <cstddef>

#include <JPetAnalysisModule/JPetAnalysisModule.h>
#include <JPetWriter/JPetWriter.h>

class JPetAnalysisModuleA: public JPetAnalysisModule {
  
  public:

  JPetAnalysisModuleA();
  JPetAnalysisModuleA(const char* name, const char* title);
  virtual ~JPetAnalysisModuleA();
  virtual void createInputObjects(const char* inputFilename=0);
  virtual void createOutputObjects(const char* outputFilename=0);
  virtual void exec();
  virtual long long getEventNb() {return fEventNb;}
  virtual void terminate();

  ClassDef(JPetAnalysisModuleA,1);

  private:
  int fEventNb;
};

#endif
