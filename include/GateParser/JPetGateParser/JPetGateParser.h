/**
 *  @copyright Copyright 2020 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetGateParser.h
 */

#ifndef JPETGATEPARSER_H
#define JPETGATEPARSER_H

#include <JPetGeomMapping/JPetGeomMapping.h>
#include <JPetHit/JPetHit.h>
#include <JPetMCHit/JPetMCHit.h>
#include <JPetUserTask/JPetUserTask.h>
#include <functional>
#include <map>
#include <tuple>
#include <vector>

#include <GateHit/GateHit.h>
#include <JPetSmearingFunctions/JPetSmearingFunctions.h>

class JPetWriter;

#ifdef __CINT__
// when cint is used instead of compiler, override word is not recognized
// nevertheless it's needed for checking if the structure of project is correct
#define override
#endif

/**
 * @brief      Module responsible for creating JPetMCHit from GATE MC simulations
 *
 */
class JPetGateParser : public JPetUserTask
{

public:
  JPetGateParser(const char* name);
  virtual ~JPetGateParser();
  virtual bool init() override;
  virtual bool exec() override;
  virtual bool terminate() override;

  void saveHits();
  void saveReconstructedHit(JPetHit recHit);
  void processGateHit(GateHit* gate_hit);
  unsigned int getScintilatorID(const JPetParamBank& paramBank, const TVector3& scintilator_position);
  void loadSmearingOptionsAndSetupExperimentalParametrizer();
  unsigned long getOriginalSeed() const;

protected:
  JPetGeomMapping* fDetectorMap = nullptr;
  double fMaxTime = 0.;
  double fMinTime = -50.e6;           // electronic time window 50 micro seconds - true for run 3
  double fSimulatedActivity = 4.7;    // 4.7; //< in MBq; value for run3
  double fExperimentalThreshold = 10; //< in keV
  JPetHitExperimentalParametrizer fExperimentalParametrizer;
  double fTimeShift = fMinTime;
  unsigned long fSeed = 0.;

  // Cmds
  const std::string kMaxTimeWindowParamKey = "GateParser_MaxTimeWindow_double";
  const std::string kMinTimeWindowParamKey = "GateParser_MinTimeWindow_double";
  const std::string kSourceActivityParamKey = "GateParser_SourceActivity_double";
  const std::string kEnergyThresholdParamKey = "GateParser_EnergyThreshold_double";

  const std::string kTimeSmearingParametersParamKey = "GateParser_TimeSmearingParameters_std::vector<double>";
  const std::string kTimeSmearingFunctionParamKey = "GateParser_TimeSmearingFunction_std::string";
  const std::string kTimeSmearingFunctionLimitsParamKey = "GateParser_TimeSmearingFunctionLimits_std::vector<double>";

  const std::string kEnergySmearingParametersParamKey = "GateParser_EnergySmearingParameters_std::vector<double>";
  const std::string kEnergySmearingFunctionParamKey = "GateParser_EnergySmearingFunction_std::string";
  const std::string kEnergySmearingFunctionLimitsParamKey = "GateParser_EnergySmearingFunctionLimits_std::vector<double>";

  const std::string kZPositionSmearingParametersParamKey = "GateParser_ZPositionSmearingParameters_std::vector<double>";
  const std::string kZPositionSmearingFunctionParamKey = "GateParser_ZPositionSmearingFunction_std::string";
  const std::string kZPositionSmearingFunctionLimitsParamKey = "GateParser_ZPositionSmearingFunctionLimits_std::vector<double>";

  const std::string kSeedParamKey = "GateParser_Seed_int";

  std::vector<JPetHit> fStoredHits; ///< save RECONSTRUCTED MC hits into single time window when it contains enough hits

  int fLastEventID = -1;

  std::vector<float> fTimeDistroOfDecays = {};
  std::vector<float> fTimeDiffDistro = {};
  unsigned int fCurrentIndexTimeShift = 0;

  unsigned int getNumberOfDecaysInWindow() const;
  float getNextTimeShift();
  void clearTimeDistoOfDecays();
  bool isTimeWindowFull() const;
};

#endif
