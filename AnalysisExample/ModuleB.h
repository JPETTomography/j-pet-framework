/**
 * @file ModuleB.h
 * @author Aleksander Gajos, aleksander.gajos@uj.edu.pl
 * @copyright Copyright (c) 2014, Aleksander Gajos
 * @brief TSlot Cal structure producer
 * Reads a TTree of Raw TSlot objects (produced by Module A)
 * and produces a tree with calibrated time signals, still in TSlots
 */

#ifndef _MODULE_B_H_
#define _MODULE_B_H_

#include "JPetCommonAnalysisModule/JPetCommonAnalysisModule.h"

#ifdef MODULE_VERSION
#undef MODULE_VERSION
#endif

#define MODULE_VERSION 1

class ModuleB: public JPetCommonAnalysisModule
{

public:

  ModuleB(const char* name, const char* title, 
	  const char *in_file_suffix, const char * out_file_suffix);
  virtual ~ModuleB();
  virtual void exec();
  virtual void begin();
  virtual void end();

  ClassDef(ModuleB, MODULE_VERSION );

private:

};

#endif
