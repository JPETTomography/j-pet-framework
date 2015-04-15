#ifndef _SCOPE_READER_MODULE_H_
#define _SCOPE_READER_MODULE_H_

#include <cstddef>
#include <fstream>
#include <string>
#include <set>
#include <vector>

#include "../JPetAnalysisModule/JPetAnalysisModule.h"

#define MODULE_VERSION 0.1

class JPetParamBank;
class JPetPM;
class JPetRecoSignal;
class JPetScin;
class JPetTreeHeader;
class JPetWriter;

class JPetScopeReader: public JPetAnalysisModule {
  
  private:

  typedef struct ScopeConfig {
    
    std::string pName;
    int pCollPosition;

    JPetParamBank* pParamBank;

    JPetPM *pPM1, *pPM2, *pPM3, *pPM4;
    JPetScin *pScin1, *pScin2;

    std::string pPrefix1, pPrefix2, pPrefix3, pPrefix4;
    std::set <std::string> pFiles;

    #ifndef __CINT__
    std::set <std::string> :: iterator pIter;
    #endif /* __CINT__ */

  } ScopeConfig;

  public:
  
  JPetScopeReader();
  JPetScopeReader(const char* name, const char* title);

  virtual ~JPetScopeReader();

  virtual void createInputObjects(const char* inputFilename = 0);
  virtual void createOutputObjects(const char* outputFilename = 0);

  virtual void exec();

  virtual long long getEventNb() {return fEventNb;}

  virtual void terminate();

  void setFileName(const char* name);

  ClassDef(JPetScopeReader, MODULE_VERSION);

  static JPetRecoSignal generateSignal (const char* filename);

  private:

  long long fEventNb;

  std::ifstream fConfigFile;
  
  JPetScopeReader* fReader; /**< @ref JPetScopeReader. */
  JPetTreeHeader* fHeader; /**< @ref JPetTreeHeader. */ 
  JPetWriter* fWriter; /**< @ref JPetWriter. */

  TString fInFilename; /**< @brief Location of config file. */
  TString fOutFilename; /**< @brief Location of output root file. */

  std::vector <ScopeConfig> fConfigs;

  #ifndef __CINT__
  std::vector <ScopeConfig> :: iterator fIter;
  #endif /* __CINT__ */

};

#endif
