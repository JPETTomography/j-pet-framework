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
 *  @file JPetChannelFactory.h
 */

#ifndef JPETCHANNELFACTORY_H
#define JPETCHANNELFACTORY_H

#include "JPetParamGetter/JPetParamGetter.h"
#include "JPetChannel/JPetChannel.h"
#include "JPetPM/JPetPMFactory.h"
#include <map>

/**
 * @brief A factory of JPetChannel objects.
 *
 * This class is able to create those objects using data from the database.
 */
class JPetChannelFactory
{
public:
  JPetChannelFactory();
  JPetChannelFactory(
    JPetParamGetter& paramGetter, const int runID, JPetPMFactory& pmFactory) :
    fParamGetter(paramGetter), fRunID(runID), fPMFactory(pmFactory),
    fInitialized(false) {}
  std::map<int, JPetChannel*>& getChannels();

private:
  JPetChannel* build(ParamObjectDescription data);
  std::map<int, JPetChannel*> fChannels;
  JPetParamGetter& fParamGetter;
  const int fRunID;
  JPetPMFactory& fPMFactory;
  bool fInitialized;
  void initialize();
};

#endif /* JPETCHANNELFACTORY_H */
