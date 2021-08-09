/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file JPetGeantParser.h
 */

#ifndef JPETGEANTPARSER_H
#define JPETGEANTPARSER_H

#include "Hits/JPetMCRecoHit/JPetMCRecoHit.h"
#include "JPetGeantEventPack/JPetGeantEventPack.h"
#include "JPetGeantScinHits/JPetGeantScinHits.h"
#include "JPetMCDecayTree/JPetMCDecayTree.h"
#include "JPetRawMCHit/JPetRawMCHit.h"
#include "JPetSmearingFunctions/JPetSmearingFunctions.h"
#include "JPetUserTask/JPetUserTask.h"
#include <functional>
#include <vector>

class JPetWriter;

/**
 * @brief Module responsible for creating JPetMCHit from GEANT MC simulations
 */
class JPetGeantParser : public JPetUserTask
{

public:
  JPetGeantParser(const char* name);
  virtual ~JPetGeantParser();
  virtual bool init() override;
  virtual bool exec() override;
  virtual bool terminate() override;

  unsigned long getOriginalSeed() const;

protected:
  bool fProcessSingleEventinWindow = false;
  bool fMakeEffiHisto = true;
  bool fMakeHisto = true;
  double fMaxTime = 0.;
  double fMinTime = -50.e6;
  ///< Source activity in MBq
  double fSimulatedActivity = 4.7;
  ///< Lowest deposited energy value in keV, that can be reconstructed
  double fExperimentalThreshold = 10.0;
  unsigned long fSeed = 0.0;

  JPetHitExperimentalParametrizer fExperimentalParametrizer;

  ///< internal variables
  const std::string kMaxTimeWindowParamKey = "GeantParser_MaxTimeWindow_double";
  const std::string kMinTimeWindowParamKey = "GeantParser_MinTimeWindow_double";
  const std::string kSourceActivityParamKey = "GeantParser_SourceActivity_double";
  const std::string kMakeHistogramsParamKey = "GeantParser_MakeHistograms_bool";
  const std::string kMakeEfficienciesParamKey = "GeantParser_MakeEfficiencies_bool";
  const std::string kEnergyThresholdParamKey = "GeantParser_EnergyThreshold_double";
  const std::string kProcessSingleEventinWindowParamKey = "GeantParser_ProcessSingleEventInWindow_bool";

  const std::string kTimeSmearingParametersParamKey = "GeantParser_TimeSmearingParameters_std::vector<double>";
  const std::string kTimeSmearingFunctionParamKey = "GeantParser_TimeSmearingFunction_std::string";
  const std::string kTimeSmearingFunctionLimitsParamKey = "GeantParser_TimeSmearingFunctionLimits_std::vector<double>";

  const std::string kEnergySmearingParametersParamKey = "GeantParser_EnergySmearingParameters_std::vector<double>";
  const std::string kEnergySmearingFunctionParamKey = "GeantParser_EnergySmearingFunction_std::string";
  const std::string kEnergySmearingFunctionLimitsParamKey = "GeantParser_EnergySmearingFunctionLimits_std::vector<double>";

  const std::string kZPositionSmearingParametersParamKey = "GeantParser_ZPositionSmearingParameters_std::vector<double>";
  const std::string kZPositionSmearingFunctionParamKey = "GeantParser_ZPositionSmearingFunction_std::string";
  const std::string kZPositionSmearingFunctionLimitsParamKey = "GeantParser_ZPositionSmearingFunctionLimits_std::vector<double>";

  const std::string kSeedParamKey = "GeantParser_Seed_int";

  long fExpectedNumberOfEvents = 0;
  double fTimeShift = fMinTime;

  ///< save MC hits into single time window when it contains enough hits
  std::vector<JPetRawMCHit> fStoredMCHits;
  ///< save RECONSTRUCTED MC hits into single time window when it contains enough hits
  std::vector<JPetMCRecoHit> fStoredRecoHits;

  void loadSmearingOptionsAndSetupExperimentalParametrizer();

  void processMCEvent(JPetGeantEventPack*);
  void saveHits();
  void saveReconstructedHit(JPetMCRecoHit recHit);

  void bookEfficiencyHistograms();
  void bookBasicHistograms();

  void fillHistoGenInfo(JPetGeantEventInformation*);
  void fillHistoMCGen(JPetRawMCHit&);
  void fillHistoMCRec(JPetMCRecoHit&);

  unsigned long nPromptGen = 0u;
  unsigned long nPromptRec = 0u;
  unsigned long n2gGen = 0u;
  unsigned long n2gRec = 0u;
  unsigned long n3gGen = 0u;
  unsigned long n3gRec = 0u;

  std::vector<double> fTimeDistroOfDecays = {};
  std::vector<double> fTimeDiffDistro = {};
  unsigned int fCurrentIndexTimeShift = 0;

  unsigned int getNumberOfDecaysInWindow() const;
  double getNextTimeShift();
  void clearTimeDistoOfDecays();
  bool isTimeWindowFull() const;
};

#endif /* !JPETGEANTPARSER_H */
