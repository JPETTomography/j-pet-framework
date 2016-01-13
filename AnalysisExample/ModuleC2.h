/**
 * @file ModuleC1.h
 * @author Aleksander Gajos, aleksander.gajos@uj.edu.pl
 * @copyright Copyright (c) 2014, Aleksander Gajos
 * @brief Producer of JPetRecoSignal objects
 * Reads a TTree of Raw Signals and transforms them into JPetRecoSignal objects
 * Reconstruction of signal shape, amplitude, offset, delay and charge can take place here.
 */

#ifndef _JPETANALYSISMODULE_C2_H_
#define _JPETANALYSISMODULE_C2_H_

#include "JPetCommonAnalysisModule/JPetCommonAnalysisModule.h"

#ifdef MODULE_VERSION
#undef MODULE_VERSION
#endif

#define MODULE_VERSION 1

class ModuleC2: public JPetCommonAnalysisModule
{

public:

  ModuleC2(const char* name, const char* title,
	  const char *in_file_suffix, const char * out_file_suffix);
  virtual ~ModuleC2();
  virtual void exec();
  virtual void begin();
  virtual void end();
  
  ClassDef(ModuleC2, MODULE_VERSION );

private:
  // put any custom variables (e.g. histograms) here:

};

#endif
