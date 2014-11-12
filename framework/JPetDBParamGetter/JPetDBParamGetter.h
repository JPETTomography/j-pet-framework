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
class pqxx::result::const_iterator;r
#endif /* __CINT __ */

class JPetDBParamGetter
{
public:
  enum ParamObjectType {kScintillator, kPM, kPMCalib, kFEB, kTRB, kTOMBChannel, kBarrelSlot, SIZE};
  JPetDBParamGetter();
  JPetDBParamGetter(const char* dBConfigFile);
  JPetParamBank* generateParamBank(const int p_run_id);

private:
  pqxx::result getDataFromDB(const std::string& sqlFunction, const std::string& args);
  std::string generateSelectQuery(const std::string& sqlFunction, const std::string& args);
  void printErrorMessageDB(std::string sqlFunction, int p_run_id);
  JPetScin generateScintillator(pqxx::result::const_iterator row);
  JPetPM generatePM(pqxx::result::const_iterator row);
  JPetPMCalib generatePMCalib(pqxx::result::const_iterator row);
  JPetFEB generateFEB(pqxx::result::const_iterator row);
  JPetTRB generateTRB(pqxx::result::const_iterator row);
  JPetTOMBChannel generateTOMBChannel(pqxx::result::const_iterator row);

  void fillScintillators(const int p_run_id, JPetParamBank& paramBank);
  void fillParamContainer(ParamObjectType type, const int p_run_id, JPetParamBank& paramBank);

  void fillPMs(const int p_run_id, JPetParamBank& paramBank);
  void fillPMCalibs(const int p_run_id, JPetParamBank& paramBank);
  void fillFEBs(const int p_run_id, JPetParamBank& paramBank);
  void fillTOMBChannels(const int p_run_id, JPetParamBank& paramBank);
  void fillTRBs(const int p_run_id, JPetParamBank& paramBank);
  void fillPMsTRefs(const int p_run_id, JPetParamBank& paramBank);
  void fillFEBsTRefs(const int p_run_id, JPetParamBank& paramBank);
  void fillTOMBChannelsTRefs(const int p_run_id, JPetParamBank& paramBank);
  void fillAllTRefs(const int p_run_id, JPetParamBank& paramBank);

  int getTOMBChannelFromDescription(std::string p_desc) const;

};
#endif /*  !JPETDBPARAMGETTER_H */
