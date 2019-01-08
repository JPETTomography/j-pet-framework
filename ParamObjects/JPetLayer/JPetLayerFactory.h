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
 *  @file JPetLayerFactory.h
 */

#ifndef JPET_LAYER_FACTORY_H
#define JPET_LAYER_FACTORY_H

#include "./JPetParamGetter/JPetParamGetter.h"
#include "./JPetFrame/JPetFrameFactory.h"
#include "JPetLayer.h"
#include <map>

/**
 * @brief A factory of JPetLayer objects.
 *
 * This class is able to create those objects using data from the database.
 */
class JPetLayerFactory
{
public:
  JPetLayerFactory(JPetParamGetter & paramGetter, int runId, JPetFrameFactory & frameFactory):
    paramGetter(paramGetter), runId(runId), frameFactory(frameFactory), fInitialized(false) {}
  std::map<int, JPetLayer*>& getLayers();

private:
  JPetParamGetter &paramGetter;
  const int runId;
  JPetFrameFactory &frameFactory;
  bool fInitialized;
  std::map<int, JPetLayer*> fLayers;
  void initialize();
  JPetLayer* build(ParamObjectDescription data);
};

#endif /* !JPET_LAYER_FACTORY_H */
