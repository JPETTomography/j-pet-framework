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
 *  @file JPetTOMBChannelFactory.h
 */

#ifndef JPET_TOMB_CHANNEL_FACTORY_H
#define JPET_TOMB_CHANNEL_FACTORY_H

#include "./JPetParamGetter/JPetParamGetter.h"
#include "./JPetFEB/JPetFEBFactory.h"
#include "./JPetTRB/JPetTRBFactory.h"
#include "./JPetPM/JPetPMFactory.h"
#include "JPetTOMBChannel.h"
#include <map>

/**
 * @brief A factory of JPetTOMBChannel objects.
 *
 * This class is able to create those objects using data from the database.
 */
class JPetTOMBChannelFactory
{
public:
  JPetTOMBChannelFactory(JPetParamGetter &paramGetter, int runId,
    JPetFEBFactory &febFactory, JPetTRBFactory &TRBFactory, JPetPMFactory &PMFactory):
    paramGetter(paramGetter), runId(runId), febFactory(febFactory),
    TRBFactory(TRBFactory), PMFactory(PMFactory), fInitialized(false) {}
  std::map<int, JPetTOMBChannel*> & getTOMBChannels();

private:
  JPetParamGetter &paramGetter;
  const int runId;
  JPetFEBFactory &febFactory;
  JPetTRBFactory &TRBFactory;
  JPetPMFactory &PMFactory;
  bool fInitialized;
  std::map<int, JPetTOMBChannel*> fTOMBChannels;
  void initialize();
  JPetTOMBChannel* build(ParamObjectDescription data);
};

#endif /* JPET_TOMB_CHANNEL_FACTORY_H */
