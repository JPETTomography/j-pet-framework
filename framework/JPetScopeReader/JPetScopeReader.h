#ifndef _SCOPE_READER_MODULE_H_
#define _SCOPE_READER_MODULE_H_

#define MODULE_VERSION 0.4

#include "../JPetAnalysisModule/JPetAnalysisModule.h"

#include <cstddef>
#include <fstream>
#include <string>
#include <set>
#include <vector>

#include <boost/property_tree/ptree.hpp>

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

    JPetParamBank const* pParamBank;
    
    JPetPM *pPM1, *pPM2, *pPM3, *pPM4;
    JPetScin *pScin1, *pScin2;

    std::string pPrefix1, pPrefix2, pPrefix3, pPrefix4;

    std::set <std::string> pFiles;
    std::set <std::string> :: iterator pIter;

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

  void createNewWriter(const char* outputFilename = 0);
  JPetParamBank const& createParamBank (boost::property_tree::ptree const& conf_data);

  static JPetRecoSignal generateSignal (const char* filename);

  private:

  long long fEventNb;

  std::ifstream fConfigFile;
  
  JPetTreeHeader* fHeader; /**< @ref JPetTreeHeader. */ 
  JPetWriter* fWriter; /**< @ref JPetWriter. */

  TString fInFilename; /**< @brief Location of config file. */
  TString fOutFilename; /**< @brief Location of output root file. */

  std::vector <ScopeConfig> fConfigs;
  std::vector <ScopeConfig> :: iterator fIter;

};

#endif
