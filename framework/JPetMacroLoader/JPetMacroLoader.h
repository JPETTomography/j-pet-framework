/**
 * @file JPetMacroLoader.h
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2013, Damian Trybek
 * @brief Allows to process root macro as an Analysis Module
 */

#ifndef _JPETMACROLOADER_H_
#define _JPETMACROLOADER_H_

#include <cstddef>

#include "../../framework/JPetAnalysisModule/JPetAnalysisModule.h"

class JPetMacroLoader: public JPetAnalysisModule {
  
  public:

  JPetMacroLoader(const char* name, const char* filename);
  virtual ~JPetMacroLoader();
  virtual void CreateInputObjects(const char* inputFilename=0);
  virtual void CreateOutputObjects(const char* outputFilename=0);
  virtual void Exec();
  virtual long long GetEventNb() {return fEventNb;}
  virtual void Terminate();

  ClassDef(JPetMacroLoader,1);

  private:
  
  long long fEvent;
  long long fEventNb;
};

#endif
