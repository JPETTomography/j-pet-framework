/**
 * @file ModuleE.h
 * @author Aleksander Gajos, aleksander.gajos@uj.edu.pl
 * @copyright Copyright (c) 2014, Aleksander Gajos
 * @brief TSlot Cal structure producer
 * Reads a TTree of Raw Tslot objects (produced by Module A)
 * and produces a tree with calibrated time signals, still in TSlots
 */

#ifndef _JPETANALYSISMODULE_E_H_
#define _JPETANALYSISMODULE_E_H_

#include "JPetCommonAnalysisModule/JPetCommonAnalysisModule.h"

#ifdef MODULE_VERSION
#undef MODULE_VERSION
#endif

#define MODULE_VERSION 1

class ModuleE: public JPetCommonAnalysisModule
{
public:

  ModuleE(const char* name, const char* title,
	  const char *in_file_suffix, const char * out_file_suffix);
  
  virtual ~ModuleE();
  virtual void exec();
  virtual void begin();
  virtual void end();

  ClassDef(ModuleE, MODULE_VERSION );

private:

  // for statistics of the processing:
  int fInitialHits;
  int fPairsFound;
};

#endif
