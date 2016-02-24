#ifndef _J_PET_PARAM_MANAGER_
#define _J_PET_PARAM_MANAGER_

#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include "../JPetLoggerInclude.h"
#include "../JPetParamBank/JPetParamBank.h"
#include "../JPetDBParamGetter/JPetDBParamGetter.h"
#include "../JPetReader/JPetReader.h"
#include "../JPetWriter/JPetWriter.h"

class JPetParamManager
{
 public:
  JPetParamManager() : fParamGetter(new JPetDBParamGetter()), fBank(0) {}
  JPetParamManager(JPetParamGetter* paramGetter) : fParamGetter(paramGetter), fBank(0) {}
  ~JPetParamManager();

  void fillParameterBank(const int run);
  
  bool readParametersFromFile(JPetReader * reader);
  bool saveParametersToFile(JPetWriter * writer);

  bool readParametersFromFile(std::string filename);
  bool saveParametersToFile(std::string filename);
  
  void clearParameters();
  const JPetParamBank& getParamBank() const { assert(fBank); return *fBank;}

 private:
  JPetParamManager(const JPetParamManager&);
  JPetParamManager& operator=(const JPetParamManager&);

  JPetParamGetter* fParamGetter;
  JPetParamBank* fBank;

 protected:
  void createXMLFile(const std::string &channelDataFileName, int channelOffset, int numberOfChannels);
  void getTOMBDataAndCreateXMLFile(const int p_run_id);
};

#endif
