/**
 * @file ModuleC3.h
 * @author Aleksander Gajos, aleksander.gajos@uj.edu.pl
 * @copyright Copyright (c) 2014, Aleksander Gajos
 * @brief Producer of JPetPhysSignal objects
 * Reads a TTree of JPetRecoSignal objects and transforms them into JPetPhysSignal objects
 * The signal properties reconstructed in the previous module can be used here
 * to reconstruct the physical values: signal arrival time and number of photoelectrons.
 */

#ifndef _JPETANALYSISMODULE_C3_H_
#define _JPETANALYSISMODULE_C3_H_

#include "JPetCommonAnalysisModule/JPetCommonAnalysisModule.h"

#ifdef MODULE_VERSION
#undef MODULE_VERSION
#endif

#define MODULE_VERSION 1

class ModuleC3: public JPetCommonAnalysisModule
{

public:

  ModuleC3(const char* name, const char* title,
	  const char *in_file_suffix, const char * out_file_suffix);
  virtual ~ModuleC3();
  virtual void exec();
  virtual void begin();
  virtual void end();
  //  virtual long long GetEventNb() const { return fEventNb; }
  
  ClassDef(ModuleC3, MODULE_VERSION );

private:
  // put any custom variables (e.g. histograms) here:

};

#endif
