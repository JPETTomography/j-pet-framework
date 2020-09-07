/**
 *  @copyright Copyright 2020 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetDataModuleFactory.h
 */

#ifndef JPET_DATA_MODULE_FACTORY_H
#define JPET_DATA_MODULE_FACTORY_H

#include "JPetDataSource/JPetDataSourceFactory.h"
#include "JPetDataModule.h"
#include <map>

/**
 * @brief A factory of JPetDataModule objects.
 *
 * This class is able to create those objects using data from the database.
 */
class JPetDataModuleFactory
{
public:
  JPetDataModuleFactory(
    JPetParamGetter& paramGetter, int runID, JPetDataSourceFactory& dataSourceFactory
  ): fParamGetter(paramGetter), fRunID(runID),
  fDataSourceFactory(dataSourceFactory), fInitialized(false) {}
  std::map<int, JPetDataModule *> & getDataModules();

private:
  JPetParamGetter &fParamGetter;
  int fRunID;
  JPetDataSourceFactory &fDataSourceFactory;
  bool fInitialized;
  std::map<int, JPetDataModule*> fDataModules;
  void initialize();
  JPetDataModule* build(ParamObjectDescription data);
};

#endif /* !JPET_DATA_MODULE_FACTORY_H */
