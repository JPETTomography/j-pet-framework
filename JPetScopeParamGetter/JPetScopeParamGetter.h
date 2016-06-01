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
 *  @file JPetScopeParamGetter.h
 */

#ifndef JPETSCOPEPARAMGETTER_H
#define JPETSCOPEPARAMGETTER_H

#include "../JPetParamBank/JPetParamBank.h"
#include "../JPetScopeConfigParser/JPetScopeConfigPOD.h" /// for generateParametersFromScopeConfig
#include <map>

class JPetParamManager;

class JPetScopeParamGetter
{
public:
  enum ParamObjectType {kScintillator, kPM, kPMCalib, kFEB, kTRB, kTOMBChannel, kBarrelSlot, SIZE};
  JPetScopeParamGetter();
  JPetParamBank* generateParamBank(const scope_config::Config& config);
  ~JPetScopeParamGetter();
  
private:
  JPetScopeParamGetter(const JPetScopeParamGetter&);
  JPetScopeParamGetter& operator=(const JPetScopeParamGetter&);
  
  friend class JPetParamManager;
  static std::map<std::string, JPetParamBank*> fParamCache;
};
#endif /*  !JPETSCOPEPARAMGETTER_H */
