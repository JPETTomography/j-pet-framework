/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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

#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <boost/any.hpp>

#include "./JPetLoggerInclude.h"
#include "./JPetParamBank/JPetParamBank.h"
#include "./JPetReader/JPetReader.h"
#include "./JPetWriter/JPetWriter.h"
#include "./JPetScopeConfigParser/JPetScopeConfigPOD.h" /// for generateParametersFromScopeConfig
#include "./JPetTRB/JPetTRBFactory.h"
#include "./JPetFEB/JPetFEBFactory.h"
#include "./JPetFrame/JPetFrameFactory.h"
#include "./JPetLayer/JPetLayerFactory.h"
#include "./JPetBarrelSlot/JPetBarrelSlotFactory.h"
#include "./JPetScin/JPetScinFactory.h"
#include "./JPetPM/JPetPMFactory.h"
#include "./JPetTOMBChannel/JPetTOMBChannelFactory.h"

class JPetParamManager
{
public:
  /// factory method to produce JPetParamManager instance based on provided options
  static std::shared_ptr<JPetParamManager> generateParamManager(const std::map<std::string, boost::any>& options);

  JPetParamManager() : fBank(0), fIsNullObject(false) {}
  JPetParamManager(bool isNull) : fBank(0), fIsNullObject(isNull) {}
  JPetParamManager(JPetParamGetter* paramGetter) : fParamGetter(paramGetter), fBank(0) , fIsNullObject(false) {}
  JPetParamManager(JPetParamGetter* paramGetter, std::set<ParamObjectType> expectMissing) : fParamGetter(paramGetter), fExpectMissing(expectMissing), fBank(0) , fIsNullObject(false) {}
  ~JPetParamManager();

  std::map<int, JPetTRB*>& getTRBs(const int runId);
  std::map<int, JPetFEB*>& getFEBs(const int runId);
  std::map<int, JPetFrame*>& getFrames(const int runId);
  std::map<int, JPetLayer*>& getLayers(const int runId);
  std::map<int, JPetBarrelSlot*>& getBarrelSlots(const int runId);
  std::map<int, JPetScin*>& getScins(const int runId);
  std::map<int, JPetPM*>& getPMs(const int runId);
  std::map<int, JPetTOMBChannel*>& getTOMBChannels(const int runId);

  void fillParameterBank(const int run);

  bool readParametersFromFile(JPetReader* reader);
  bool saveParametersToFile(JPetWriter* writer);

  bool readParametersFromFile(std::string filename);
  bool saveParametersToFile(std::string filename);

  void clearParameters();
  const JPetParamBank& getParamBank() const;

  inline bool isNullObject() const
  {
    return fIsNullObject;
  }

  inline std::set<ParamObjectType> getExpectMissing() const
  {
    return fExpectMissing;
  }

private:
  JPetParamManager(const JPetParamManager&);
  JPetParamManager& operator=(const JPetParamManager&);

  JPetParamGetter* fParamGetter;
  std::set<ParamObjectType> fExpectMissing;
  JPetParamBank* fBank;
  bool fIsNullObject;

  std::map<int, JPetTRBFactory> fTRBFactories;
  std::map<int, JPetFEBFactory> fFEBFactories;
  std::map<int, JPetFrameFactory> fFrameFactories;
  std::map<int, JPetLayerFactory> fLayerFactories;
  std::map<int, JPetBarrelSlotFactory> fBarrelSlotFactories;
  std::map<int, JPetScinFactory> fScinFactories;
  std::map<int, JPetPMFactory> fPMFactories;
  std::map<int, JPetTOMBChannelFactory> fTOMBChannelFactories;

  JPetTRBFactory& getTRBFactory(const int runId);
  JPetFEBFactory& getFEBFactory(const int runId);
  JPetFrameFactory& getFrameFactory(const int runId);
  JPetLayerFactory& getLayerFactory(const int runId);
  JPetBarrelSlotFactory& getBarrelSlotFactory(const int runId);
  JPetScinFactory& getScinFactory(const int runId);
  JPetPMFactory& getPMFactory(const int runId);
  JPetTOMBChannelFactory& getTOMBChannelFactory(const int runId);

protected:
  void createXMLFile(const std::string& channelDataFileName, int channelOffset, int numberOfChannels);
  void getTOMBDataAndCreateXMLFile(const int p_run_id);
};

#endif
