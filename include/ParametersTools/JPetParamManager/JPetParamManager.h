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
 *  @file JPetParamManager.h
 */

#ifndef _J_PET_PARAM_MANAGER_
#define _J_PET_PARAM_MANAGER_

#include "./JPetScopeConfigParser/JPetScopeConfigPOD.h"
#include "./JPetTOMBChannel/JPetTOMBChannelFactory.h"
#include "./JPetBarrelSlot/JPetBarrelSlotFactory.h"
#include "./JPetDataSource/JPetDataSourceFactory.h"
#include "./JPetDataModule/JPetDataModuleFactory.h"
#include "./JPetParamBank/JPetParamBank.h"
#include "./JPetFrame/JPetFrameFactory.h"
#include "./JPetLayer/JPetLayerFactory.h"
#include "./JPetScin/JPetScinFactory.h"
#include "./JPetFEB/JPetFEBFactory.h"
#include "./JPetTRB/JPetTRBFactory.h"
#include "./JPetReader/JPetReader.h"
#include "./JPetWriter/JPetWriter.h"
#include "./JPetPM/JPetPMFactory.h"
#include "./JPetLoggerInclude.h"
#include <boost/any.hpp>
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <set>

class JPetParamManager
{
public:
  explicit JPetParamManager(): fParamGetter(), fBank(0), fIsNullObject(false) {}
  explicit JPetParamManager(JPetParamGetter* paramGetter):
    fParamGetter(paramGetter), fBank(0) , fIsNullObject(false) {}
  explicit JPetParamManager(JPetParamGetter* paramGetter, const std::set<ParamObjectType>& expectMissing):
    fParamGetter(paramGetter), fExpectMissing(expectMissing), fBank(0), fIsNullObject(false) {}

  /**
   * Special constructor to create NullObject. This object can be returned
   * if JPetParamManager is not created, and the const& is expected to be returned.
   */
  explicit JPetParamManager(bool isNull): fParamGetter(), fBank(0), fIsNullObject(isNull) {}
  ~JPetParamManager();

  /**
   * Factory method to produce JPetParamManager instance based on provided options
   */
  static std::shared_ptr<JPetParamManager> generateParamManager(
    const std::map<std::string, boost::any>& options
  );
  std::map<int, JPetTRB*>& getTRBs(const int runID);
  std::map<int, JPetFEB*>& getFEBs(const int runID);
  std::map<int, JPetFrame*>& getFrames(const int runID);
  std::map<int, JPetLayer*>& getLayers(const int runID);
  std::map<int, JPetBarrelSlot*>& getBarrelSlots(const int runID);
  std::map<int, JPetScin*>& getScins(const int runID);
  std::map<int, JPetPM*>& getPMs(const int runID);
  std::map<int, JPetTOMBChannel*>& getTOMBChannels(const int runID);
  std::map<int, JPetDataSource*>& getDataSources(const int runID);
  std::map<int, JPetDataModule*>& getDataModules(const int runID);

  void fillParameterBank(const int run);
  bool readParametersFromFile(JPetReader* reader);
  bool saveParametersToFile(JPetWriter* writer);
  bool readParametersFromFile(std::string filename);
  bool saveParametersToFile(std::string filename);
  void clearParameters();
  const JPetParamBank& getParamBank() const;
  inline bool isNullObject() const { return fIsNullObject; }
  inline std::set<ParamObjectType> getExpectMissing() const { return fExpectMissing; }

private:
  JPetParamManager(const JPetParamManager&);
  JPetParamManager& operator=(const JPetParamManager&);
  JPetParamGetter* fParamGetter = nullptr;
  std::set<ParamObjectType> fExpectMissing;
  JPetParamBank* fBank = nullptr;
  bool fIsNullObject;

  std::map<int, JPetTRBFactory> fTRBFactories;
  std::map<int, JPetFEBFactory> fFEBFactories;
  std::map<int, JPetFrameFactory> fFrameFactories;
  std::map<int, JPetLayerFactory> fLayerFactories;
  std::map<int, JPetBarrelSlotFactory> fBarrelSlotFactories;
  std::map<int, JPetScinFactory> fScinFactories;
  std::map<int, JPetPMFactory> fPMFactories;
  std::map<int, JPetTOMBChannelFactory> fTOMBChannelFactories;
  std::map<int, JPetDataSourceFactory> fDataSourceFactories;
  std::map<int, JPetDataModuleFactory> fDataModuleFactories;

  JPetTRBFactory& getTRBFactory(const int runID);
  JPetFEBFactory& getFEBFactory(const int runID);
  JPetFrameFactory& getFrameFactory(const int runID);
  JPetLayerFactory& getLayerFactory(const int runID);
  JPetBarrelSlotFactory& getBarrelSlotFactory(const int runID);
  JPetScinFactory& getScinFactory(const int runID);
  JPetPMFactory& getPMFactory(const int runID);
  JPetTOMBChannelFactory& getTOMBChannelFactory(const int runID);
  JPetDataSourceFactory& getDataSourceFactory(const int runID);
  JPetDataModuleFactory& getDataModuleFactory(const int runID);
};

#endif /* !_J_PET_PARAM_MANAGER_ */
