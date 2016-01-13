/**
 * @file ModuleC1.h
 * @author Aleksander Gajos, aleksander.gajos@uj.edu.pl
 * @copyright Copyright (c) 2014, Aleksander Gajos
 * @brief Producer of JPetRawSignal objects
 * Reads a TTree of Calibrated TSlot objects (produced by Module B)
 * and produces a tree with Raw Signals
 */

#ifndef _JPETANALYSISMODULE_C1_H_
#define _JPETANALYSISMODULE_C1_H_

#include <JPetCommonAnalysisModule/JPetCommonAnalysisModule.h>

#ifdef MODULE_VERSION
#undef MODULE_VERSION
#endif

#define MODULE_VERSION 1

class ModuleC1: public JPetCommonAnalysisModule
{

public:

  ModuleC1(const char* name, const char* title,
	  const char *in_file_suffix, const char * out_file_suffix);
  virtual ~ModuleC1();
  virtual void exec();
  virtual void begin();
  virtual void end();
  
  ClassDef(ModuleC1, MODULE_VERSION );

private:
  // put any custom variables (e.g. histograms) here:

};

#endif
