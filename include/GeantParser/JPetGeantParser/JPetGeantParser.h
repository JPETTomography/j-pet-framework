/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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

#include <JPetGeantEventPack/JPetGeantEventPack.h>
#include <JPetGeantScinHits/JPetGeantScinHits.h>
#include <JPetGeomMapping/JPetGeomMapping.h>
#include <JPetHit/JPetHit.h>
#include <JPetMCDecayTree/JPetMCDecayTree.h>
#include <JPetMCHit/JPetMCHit.h>
#include <JPetSmearingFunctions/JPetSmearingFunctions.h>
#include <JPetUserTask/JPetUserTask.h>
#include <functional>
#include <map>
#include <tuple>
#include <vector>

class JPetWriter;

#ifdef __CINT__
// when cint is used instead of compiler, override word is not recognized
// nevertheless it's needed for checking if the structure of project is correct
#define override
#endif

/**
 * @brief      Module responsible for creating JPetMCHit from GEANT MC simulations
 *
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
  JPetGeomMapping* fDetectorMap = nullptr;

  bool fProcessSingleEventinWindow = false;
  bool fMakeEffiHisto = true;
  bool fMakeHisto = true;
  double fMaxTime = 0.;
  double fMinTime = -50.e6;           // electronic time window 50 micro seconds - true for run 3
  double fSimulatedActivity = 4.7;    //< in MBq; value for run3
  double fExperimentalThreshold = 10; //< in keV
  unsigned long fSeed = 0.;

  bool fUseDefaultZSmearing = false;
  bool fUseDefaultTimeSmearing = false;
  bool fUseDefaultEnergySmearing = false;

  float fDefaultZSmearingSigma = 3.0;
  float fDefaultTimeSmearingSigma = 220.0;
  float fDefaultTimeSmearingThresholdEnergy = 200.0;
  float fDefaultTimeSmearingReferenceEnergy = 270.0;
  float fDefaultEnergySmearingFraction = 0.044;

  JPetHitExperimentalParametrizer fExperimentalParametrizer;

  // internal variables
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

  const std::string kUseDefaultZSmearingKey = "GeantParser_UseDefaultZSmearing_bool";
  const std::string kDefaultZSmearingSigmaKey = "GeantParser_DefaultZSmearingSigma_double";

  const std::string kUseDefaultTimeSmearingKey = "GeantParser_UseDefaultTimeSmearing_bool";
  const std::string kDefaultTimeSmearingSigmaKey = "GeantParser_DefaultTimeSmearingSigma_double";
  const std::string kDefaultTimeSmearingThresholdEnergyKey = "GeantParser_DefaultTimeSmearingThresholdEnergy_double";
  const std::string kDefaultTimeSmearingReferenceEnergyKey = "GeantParser_DefaultTimeSmearingReferenceEnergy_double";
  
  const std::string kUseDefaultEnergySmearingKey = "GeantParser_UseDefaultEnergySmearing_bool";
  const std::string kDefaultEnergySmearingFractionKey = "GeantParser_DefaultEnergySmearingFraction_double";

  const std::string kSeedParamKey = "GeantParser_Seed_int";

  long fExpectedNumberOfEvents = 0;
  float fTimeShift = fMinTime;

  std::vector<JPetMCHit> fStoredMCHits; ///< save MC hits into single time window when it contains enough hits
  std::vector<JPetHit> fStoredHits;     ///< save RECONSTRUCTED MC hits into single time window when it contains enough hits

  void loadSmearingOptionsAndSetupExperimentalParametrizer();

  void processMCEvent(JPetGeantEventPack*);
  void saveHits();
  void saveReconstructedHit(JPetHit recHit);

  void bookEfficiencyHistograms();
  void bookBasicHistograms();

  void fillHistoGenInfo(JPetGeantEventInformation*);
  void fillHistoMCGen(JPetMCHit&);
  void fillHistoMCRec(JPetHit&);

  unsigned long nPromptGen = 0u;
  unsigned long nPromptRec = 0u;
  unsigned long n2gGen = 0u;
  unsigned long n2gRec = 0u;
  unsigned long n3gGen = 0u;
  unsigned long n3gRec = 0u;

  std::vector<float> fTimeDistroOfDecays = {};
  std::vector<float> fTimeDiffDistro = {};
  unsigned int fCurrentIndexTimeShift = 0;

  unsigned int getNumberOfDecaysInWindow() const;
  float getNextTimeShift();
  void clearTimeDistoOfDecays();
  bool isTimeWindowFull() const;
};

#endif
