#ifndef _J_PET_PARAM_MANAGER_
#define _J_PET_PARAM_MANAGER_

#include <vector>
#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include "../../JPetLoggerInclude.h"
#include "../JPetScin/JPetScin.h"
#include "../JPetParamBank/JPetParamBank.h"
#ifndef __CINT__
#include <pqxx/pqxx>
#else
class pqxx;
class pqxx::result;
class pqxx::result::const_iterator;
#endif /* __CINT __ */

class JPetParamManager
{
 public:
  JPetParamManager();
  JPetParamManager(const char* dBConfigFile);

  void getParametersFromDatabase(const int run);
  bool saveParametersToFile(const char* filename);
  bool readParametersFromFile(const char* filename);
  const JPetParamBank& getParamBank() const { return fBank;}
  void clearParameters();

 private:
  pqxx::result getDataFromDB(std::string sqlFunction, int p_run_id);
  std::string generateSelectQuery(std::string sqlFunction, std::string run_id);
  void printErrorMessageDB(std::string sqlFunction, int p_run_id);
  JPetScin generateScintillator(pqxx::result::const_iterator row);
  JPetPM generatePM(pqxx::result::const_iterator row);
  JPetFEB generateFEB(pqxx::result::const_iterator row);
  JPetTRB generateTRB(pqxx::result::const_iterator row);
  JPetTOMB generateTOMB(pqxx::result::const_iterator row);

  void fillAllContainers     (const int p_run_id);
  void fillScintillators     (const int p_run_id);
  void fillPMs               (const int p_run_id);
  void fillFEBs               (const int p_run_id);
  void fillTRBs              (const int p_run_id);
  void fillTOMB              (const int p_run_id);
  void fillScintillatorsTRefs(void);
  void fillPMsTRefs          (void);
  void fillFEBsTRefs          (void);
  void fillTRBsTRefs         (void);

  void fillAllTRefs          (void);


  JPetParamBank fBank;
};

#endif
