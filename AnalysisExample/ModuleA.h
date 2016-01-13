/**
 * @file ModuleA.h
 * @author Aleksander Gajos, aleksander.gajos@uj.edu.pl
 * @copyright Copyright (c) 2014, Aleksander Gajos
 * @brief TSlot Raw structure producer
 * Reads an unpacked HLD file and produces a TTree of tslot raw structures.
 */

#ifndef _MODULE_A_H_
#define _MODULE_A_H_

#include "JPetCommonAnalysisModule/JPetCommonAnalysisModule.h"

#include "JPetHLDReader/JPetHLDReader.h"

#ifdef MODULE_VERSION
#undef MODULE_VERSION
#endif

#define MODULE_VERSION 1

class ModuleA: public JPetCommonAnalysisModule
{

public:

  ModuleA(const char* name, const char* title, const char *in_file_suffix,
          const char * out_file_suffix);
  virtual ~ModuleA();
  virtual void createInputObjects(const char* inputFilename = 0);
  virtual void exec();
  virtual void begin();
  virtual void end();
  virtual void terminate();

ClassDef(ModuleA, MODULE_VERSION )
  ;

private:
  JPetHLDReader* fHLDReader;

};

#endif
