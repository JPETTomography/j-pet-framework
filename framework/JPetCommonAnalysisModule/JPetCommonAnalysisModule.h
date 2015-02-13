#ifndef _JPET_COMMON_ANALYSIS_MODULE_H_
#define _JPET_COMMON_ANALYSIS_MODULE_H_

#include "../JPetAnalysisModule/JPetAnalysisModule.h"
#include "../JPetWriter/JPetWriter.h"
#include "../JPetReader/JPetReader.h"
#include "../JPetTreeHeader/JPetTreeHeader.h"

#include "../JPetTSlot/JPetTSlot.h"
#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetPhysSignal/JPetPhysSignal.h"
#include "../JPetHit/JPetHit.h"
#include "../JPetLOR/JPetLOR.h"

#include "../JPetParamBank/JPetParamBank.h"

#include <cassert>
#include <cmath>
#include <string>

#include "TH1F.h"
#include "TH2F.h"

#define MODULE_VERSION 0.1

class JPetCommonAnalysisModule: public JPetAnalysisModule
{

public:

  JPetCommonAnalysisModule(const char* name, const char* title,
		     const char *in_file_suffix, const char * out_file_suffix);
  virtual ~JPetCommonAnalysisModule();
  virtual void createInputObjects(const char* inputFilename = 0);
  virtual void createOutputObjects(const char* outputFilename = 0);
  virtual void exec() = 0;
  virtual void begin() = 0;
  virtual void end() = 0;
  virtual long long getEventNb() { return fEventNb; }
  virtual void terminate();

  ClassDef(JPetCommonAnalysisModule, MODULE_VERSION );

protected:
  int fRunNb;
  int fEventNb;
  int fEvent;
  JPetWriter* fWriter;
  JPetReader* fReader;
  JPetTreeHeader* fHeader;
  //  JPetParamManager & fParamManager; 

  /* TString fInFileName; */
  /* TString fOutFileName; */
  /* TString fInFileSuffix; */
  /* TString fOutFileSuffix; */

  std::string fInFileName;
  std::string fOutFileName;
  std::string fInFileSuffix;
  std::string fOutFileSuffix;

  const JPetParamBank & getParamBank();

};

#endif

