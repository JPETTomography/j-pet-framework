/**
 * @file JPetScopeModule.h
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2014, Damian Trybek
 * @brief Module for oscilloscope data
 * Reads oscilloscope ASCII data and procudes JPetEvent structures
 */

#ifndef _SCOPE_READER_MODULE_H_
#define _SCOPE_READER_MODULE_H_

#include <cstddef>
#include <fstream>
#include <map>
#include <string>
#include <set>

#include "../JPetAnalysisModule/JPetAnalysisModule.h"
#include "../JPetScopeReader/JPetScopeReader.h"
#include "../JPetWriter/JPetWriter.h"

#define MODULE_VERSION 0.1

class JPetTreeHeader;

class JPetScopeModule: public JPetAnalysisModule {

  public:

  JPetScopeModule();
  JPetScopeModule(const char* name, const char* title);
  virtual ~JPetScopeModule();
  virtual void createInputObjects(const char* inputFilename = 0);
  virtual void createOutputObjects(const char* outputFilename = 0);
  virtual void exec();
  virtual long long getEventNb() {return fFiles.size();}
  virtual void terminate();
  void setFileName(const char* name);

  // functions for debugging:
  virtual void printCollPositions ();
  virtual void printFiles();

  ClassDef(JPetScopeModule, MODULE_VERSION );

  private:

  int readFromConfig (int to_erase, const char* fmt, ...);

  int fCurrentPosition;

  typedef struct configStruct {
    int pm1, pm2, pm3, pm4;
    std::string file1, file2, file3, file4;
    int scin1, scin2;
    int collimator;
  } configStruct;
  configStruct fConfig;

  std::ifstream fConfigFile;
  
  std::multimap <int, std::string> fFiles;
  std::set <int> fCollPositions;

  JPetWriter* fWriter;
  JPetScopeReader fReader;
  JPetTreeHeader* fHeader;
  
  TString fInFilename;
  TString fOutFilename;

};

#endif
