/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetDataSourceFactory.h
 */

#ifndef JPET_DATA_SOURCE_FACTORY_H
#define JPET_DATA_SOURCE_FACTORY_H

#include "JPetDataSource.h"
#include "JPetParamGetter/JPetParamGetter.h"
#include <map>

/**
 * @brief A factory of JPetDataSource objects.
 *
 * This class is able to create those objects using data from the database.
 */
class JPetDataSourceFactory
{
public:
  JPetDataSourceFactory(JPetParamGetter& paramGetter, int runID) : fParamGetter(paramGetter), fRunID(runID), fInitialized(false) {}
  std::map<int, JPetDataSource*>& getDataSources();

private:
  JPetParamGetter& fParamGetter;
  int fRunID;
  bool fInitialized;
  std::map<int, JPetDataSource*> fDataSources;
  void initialize();
  JPetDataSource* build(ParamObjectDescription data);
};

#endif /* !JPET_DATA_SOURCE_FACTORY_H */
