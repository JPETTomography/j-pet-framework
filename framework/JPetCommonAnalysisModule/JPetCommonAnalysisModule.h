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

  int getVersion() const {
    return fVersion;
  }

  void setVersion(int version) {
    fVersion = version;
  }

ClassDef(JPetCommonAnalysisModule, 0 )
  ;

protected:
  const int fRunNb;
  int fVersion;
  int fEventNb;
  int fEvent;
  JPetWriter* fWriter;
  JPetReader* fReader;
  JPetTreeHeader* fHeader;
  //  JPetParamManager & fParamManager; 

  std::string fInFileName;
  std::string fOutFileName;
  std::string fInFileSuffix;
  std::string fOutFileSuffix;

  const JPetParamBank & getParamBank();

};

#endif

