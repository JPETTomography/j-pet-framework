/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetTRBFactory.h
 */

#ifndef JPET_TRB_FACTORY_H
#define JPET_TRB_FACTORY_H

#include "./JPetParamGetter/JPetParamGetter.h"
#include "JPetTRB.h"
#include <map>

/**
 * @brief A factory of JPetTRB objects.
 *
 * This class is able to create those objects using data from the database.
 */
class JPetTRBFactory
{
public:
  JPetTRBFactory(JPetParamGetter & paramGetter, int runId):
    paramGetter(paramGetter), runId(runId), fInitialized(false) {}
  std::map<int, JPetTRB*> &getTRBs();

private:
  JPetParamGetter &paramGetter;
  const int runId;
  bool fInitialized;
  std::map<int, JPetTRB*> fTRBs;
  void initialize();
  JPetTRB* build(ParamObjectDescription data);
};

#endif /* !JPET_TRB_FACTORY_H */
