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
 *  @file JPetFEBFactory.h
 */

#ifndef JPET_FEB_FACTORY_H
#define JPET_FEB_FACTORY_H

#include "./JPetParamGetter/JPetParamGetter.h"
#include "./JPetTRB/JPetTRBFactory.h"
#include "JPetFEB.h"
#include <map>

/**
 * @brief A factory of JPetFEB objects.
 *
 * This class is able to create those objects using data from the database.
 */
class JPetFEBFactory
{
public:
  JPetFEBFactory(JPetParamGetter &paramGetter, int runId, JPetTRBFactory &trbFactory):
    paramGetter(paramGetter), runId(runId), trbFactory(trbFactory), fInitialized(false) {}
  std::map<int, JPetFEB*> &getFEBs();

private:
  JPetParamGetter &paramGetter;
  const int runId;
  JPetTRBFactory &trbFactory;
  bool fInitialized;
  std::map<int, JPetFEB*> fFEBs;
  void initialize();
  JPetFEB* build(ParamObjectDescription data);
};

#endif /* !JPET_FEB_FACTORY_H */
