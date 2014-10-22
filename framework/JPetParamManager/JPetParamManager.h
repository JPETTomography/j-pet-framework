#ifndef _J_PET_PARAM_MANAGER_
#define _J_PET_PARAM_MANAGER_

#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include "../../JPetLoggerInclude.h"
#include "../JPetParamBank/JPetParamBank.h"
#include "../JPetDBParamGetter/JPetDBParamGetter.h"

class JPetParamManager
{
 public:
  enum ParamObjectType {kScintillator, kPM, kFEB, kTRB, kTOMB, SIZE};

  JPetParamManager();
  JPetParamManager(const char* dBConfigFile);

  void getParametersFromDatabase(const int run);
  bool saveParametersToFile(const char* filename);
  bool readParametersFromFile(const char* filename);
  const JPetParamBank& getParamBank() const { return fBank;}
  void clearParameters();

 private:

  JPetDBParamGetter fDBParamGetter;
  JPetParamBank fBank;
};

#endif
