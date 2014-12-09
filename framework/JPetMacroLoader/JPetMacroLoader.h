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
  
private:
  JPetMacroLoader(const JPetMacroLoader &macroLoader);
  JPetMacroLoader& operator=(const JPetMacroLoader &macroLoader);
  
public:
  virtual void createInputObjects(const char* inputFilename=0);
  virtual void createOutputObjects(const char* outputFilename=0);
  virtual void exec();
  virtual long long getEventNb() {return fEventNb;}
  virtual void terminate();

  ClassDef(JPetMacroLoader,1);

  private:
  
  long long fEvent;
  long long fEventNb;
};

#endif
