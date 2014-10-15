/**
 *  @copyright Copyright (c) 2014, Wojciech Krzemien
 *  @file JPetDBParamGetter.h
 *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
 *  @brief
 */

#ifndef JPETDBPARAMGETTER_H
#define JPETDBPARAMGETTER_H

#include "../JPetParamBank/JPetParamBank.h"
#ifndef __CINT__
#include <pqxx/pqxx>
#else
class pqxx;
class pqxx::result;
class pqxx::result::const_iterator;
#endif /* __CINT __ */

class JPetDBParamGetter
{
public:
  enum ParamObjectType {kScintillator, kPM, kFEB, kTRB, kTOMB, SIZE};
  JPetDBParamGetter();
  JPetDBParamGetter(const char* dBConfigFile);
  void fillAllContainers     (const int p_run_id);
  const JPetParamBank& getParamBank() const { return fBank; }

private:
  pqxx::result getDataFromDB(std::string sqlFunction, int p_id);
  std::string generateSelectQuery(std::string sqlFunction, std::string arg);
  void printErrorMessageDB(std::string sqlFunction, int p_run_id);
  JPetScin generateScintillator(pqxx::result::const_iterator row);
  JPetPM generatePM(pqxx::result::const_iterator row);
  JPetFEB generateFEB(pqxx::result::const_iterator row);
  JPetTRB generateTRB(pqxx::result::const_iterator row);
  JPetTOMB generateTOMB(pqxx::result::const_iterator row);

  void fillTRefs(ParamObjectType type);

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
#endif /*  !JPETDBPARAMGETTER_H */
