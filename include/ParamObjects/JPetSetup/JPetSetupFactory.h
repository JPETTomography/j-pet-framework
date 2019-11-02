/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetSetupFactory.h
 */

#ifndef JPET_SETUP_FACTORY_H
#define JPET_SETUP_FACTORY_H

#include "JPetParamGetter/JPetParamGetter.h"
#include "JPetSetup/JPetSetup.h"
#include <map>

/**
 * @brief A factory of JPetSetup objects.
 *
 * This class is able to create those objects using data from the database.
 */
class JPetSetupFactory
{
public:
  JPetSetupFactory(JPetParamGetter & paramGetter, int runID):
    fParamGetter(paramGetter), fRunID(runID), fInitialized(false) {}
  std::map<int, JPetSetup*> & getSetups();

private:
  JPetParamGetter& fParamGetter;
  const int fRunID;
  bool fInitialized;
  std::map<int, JPetSetup*> fSetups;
  void initialize();
  JPetSetup* build(ParamObjectDescription data);
};

#endif /* JPET_SETUP_FACTORY_H */
