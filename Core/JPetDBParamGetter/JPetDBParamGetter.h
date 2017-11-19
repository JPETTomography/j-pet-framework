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

#include "./JPetParamGetter/JPetParamGetter.h"
#ifndef __CINT__
#include <pqxx/pqxx>
#else
class pqxx;
class pqxx::result;
class pqxx::result::const_iterator;
#endif /* __CINT __ */

class JPetDBParamGetter : public JPetParamGetter
{
public:
  JPetDBParamGetter() {}
  ~JPetDBParamGetter() {}
  ParamObjectsDescriptions getAllBasicData(ParamObjectType type, const int runId);
  ParamRelationalData getAllRelationalData(ParamObjectType type1, ParamObjectType type2, const int runId);
  static void clearParamCache();
  
private:
  JPetDBParamGetter(const JPetDBParamGetter &DBParamGetter);
  JPetDBParamGetter& operator=(const JPetDBParamGetter &DBParamGetter);
  
  pqxx::result getDataFromDB(const std::string& sqlFunction, const std::string& args);
  std::string generateSelectQuery(const std::string& sqlFunction, const std::string& args);
  void printErrorMessageDB(std::string sqlFunction, int p_run_id);

  static std::map<int, std::map<ParamObjectType, ParamObjectsDescriptions>> gBasicDataCache;
  static std::map<int, std::map<ParamObjectType, std::map<ParamObjectType, ParamRelationalData>>> gRelationalDataCache;
};
#endif /*  !JPETDBPARAMGETTER_H */
