/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file JPetDBParamGetter.h
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

class JPetParamManager;

class JPetDBParamGetter
{
public:
  enum ParamObjectType {kScintillator, kPM, kPMCalib, kFEB, kTRB, kTOMBChannel, kBarrelSlot, SIZE};
  JPetDBParamGetter();
  JPetParamBank* generateParamBank(const int p_run_id);
  ~JPetDBParamGetter();
  
private:
  JPetDBParamGetter(const JPetDBParamGetter &DBParamGetter);
  JPetDBParamGetter& operator=(const JPetDBParamGetter &DBParamGetter);
  
private:
  pqxx::result getDataFromDB(const std::string& sqlFunction, const std::string& args);
  std::string generateSelectQuery(const std::string& sqlFunction, const std::string& args);
  void printErrorMessageDB(std::string sqlFunction, int p_run_id);
  JPetScin generateScintillator(pqxx::result::const_iterator row);
  JPetPM generatePM(pqxx::result::const_iterator row);
  JPetPMCalib generatePMCalib(pqxx::result::const_iterator row);
  JPetBarrelSlot generateBarrelSlot(pqxx::result::const_iterator row);
  JPetLayer generateLayer(pqxx::result::const_iterator row);
  JPetFrame generateFrame(pqxx::result::const_iterator row);
  JPetFEB generateFEB(pqxx::result::const_iterator row);
  JPetTRB generateTRB(pqxx::result::const_iterator row);
  JPetTOMBChannel generateTOMBChannel(pqxx::result::const_iterator row);

  void fillScintillators(const int p_run_id, JPetParamBank& paramBank);
  void fillParamContainer(ParamObjectType type, const int p_run_id, JPetParamBank& paramBank);

  void fillPMs(const int p_run_id, JPetParamBank& paramBank);
  void fillPMCalibs(const int p_run_id, JPetParamBank& paramBank);
  void fillBarrelSlot(const int p_run_id, JPetParamBank& paramBank);
  void fillLayer(const int p_run_id, JPetParamBank& paramBank);
  void fillFrame(const int p_run_id, JPetParamBank& paramBank);
  void fillFEBs(const int p_run_id, JPetParamBank& paramBank);
  void fillTOMBChannels(const int p_run_id, JPetParamBank& paramBank);
  void fillTRBs(const int p_run_id, JPetParamBank& paramBank);
  void fillPMsTRefs(const int p_run_id, JPetParamBank& paramBank);
  void fillFEBsTRefs(const int p_run_id, JPetParamBank& paramBank);
  void fillTOMBChannelsTRefs(const int p_run_id, JPetParamBank& paramBank);
  void fillBarrelSlotTRefs(const int p_run_id, JPetParamBank& paramBank);
  void fillLayerTRefs(const int p_run_id, JPetParamBank& paramBank);
  void fillScinTRef(const int p_run_id, JPetParamBank& paramBank);
  void fillAllTRefs(const int p_run_id, JPetParamBank& paramBank);

  int getTOMBChannelFromDescription(std::string p_desc) const;
  
  friend class JPetParamManager;

  static std::map<int, JPetParamBank*> fParamCache;
};
#endif /*  !JPETDBPARAMGETTER_H */
