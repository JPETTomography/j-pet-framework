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
 *  @file JPetParamManager.h
 */

#ifndef J_PET_PARAM_MANAGER
#define J_PET_PARAM_MANAGER

#include "JPetScopeConfigParser/JPetScopeConfigPOD.h"
#include "JPetChannel/JPetChannelFactory.h"
#include "JPetParamBank/JPetParamBank.h"
#include "JPetSetup/JPetSetupFactory.h"
#include "JPetLayer/JPetLayerFactory.h"
#include "JPetScin/JPetScinFactory.h"
#include "JPetSlot/JPetSlotFactory.h"
#include "JPetReader/JPetReader.h"
#include "JPetWriter/JPetWriter.h"
#include "JPetPM/JPetPMFactory.h"
#include "JPetLoggerInclude.h"
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
  std::map<int, JPetSetup*>& getSetups(const int runID);
  std::map<int, JPetLayer*>& getLayers(const int runID);
  std::map<int, JPetSlot*>& getSlots(const int runID);
  std::map<int, JPetScin*>& getScins(const int runID);
  std::map<int, JPetPM*>& getPMs(const int runID);
  std::map<int, JPetChannel*>& getChannels(const int runID);
  void fillParameterBank(const int runID);
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
  std::map<int, JPetSetupFactory> fSetupFactories;
  std::map<int, JPetLayerFactory> fLayerFactories;
  std::map<int, JPetSlotFactory> fSlotFactories;
  std::map<int, JPetScinFactory> fScinFactories;
  std::map<int, JPetPMFactory> fPMFactories;
  std::map<int, JPetChannelFactory> fChannelFactories;
  JPetSetupFactory& getSetupFactory(const int runID);
  JPetLayerFactory& getLayerFactory(const int runID);
  JPetSlotFactory& getSlotFactory(const int runID);
  JPetScinFactory& getScinFactory(const int runID);
  JPetPMFactory& getPMFactory(const int runID);
  JPetChannelFactory& getChannelFactory(const int runID);
};

#endif /* !J_PET_PARAM_MANAGER */
