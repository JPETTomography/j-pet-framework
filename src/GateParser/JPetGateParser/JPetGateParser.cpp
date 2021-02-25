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
 *  @file JPetGateParser.cpp
 */

#include <JPetAnalysisTools/JPetAnalysisTools.h>
#include <JPetGateParser/JPetGateParser.h>
#include <JPetGeantParser/JPetGeantParserTools.h>
#include <JPetOptionsTools/JPetOptionsTools.h>
#include <JPetTimeWindow/JPetTimeWindow.h>
#include <JPetWriter/JPetWriter.h>
#include <iostream>

#include <GateHit/GateHit.h>
#include <JPetScin/JPetScin.h>
#include <JPetScin/JPetScin.h>
#include <TMath.h>
#include <array>
#include <cmath>
#include <string>

using namespace jpet_options_tools;

JPetGateParser::JPetGateParser(const char* name) : JPetUserTask(name) {}

JPetGateParser::~JPetGateParser() {}

bool JPetGateParser::init()
{
  std::unique_ptr<JPetGeomMapping> fDetectorMap(new JPetGeomMapping(getParamBank()));
  fOutputEvents = new JPetTimeWindow("JPetHit");

  // Cmds handling
  auto opts = getOptions();

  if (isOptionSet(fParams.getOptions(), kMaxTimeWindowParamKey))
  {
    fMaxTime = getOptionAsDouble(fParams.getOptions(), kMaxTimeWindowParamKey);
  }
  if (isOptionSet(fParams.getOptions(), kMinTimeWindowParamKey))
  {
    fMinTime = getOptionAsDouble(fParams.getOptions(), kMinTimeWindowParamKey);
  }
  if (isOptionSet(fParams.getOptions(), kSourceActivityParamKey))
  {
    fSimulatedActivity = getOptionAsDouble(fParams.getOptions(), kSourceActivityParamKey);
  }
  if (isOptionSet(fParams.getOptions(), kEnergyThresholdParamKey))
  {
    fExperimentalThreshold = getOptionAsDouble(fParams.getOptions(), kEnergyThresholdParamKey);
  }
  if (isOptionSet(fParams.getOptions(), kSeedParamKey))
  {
    fSeed = getOptionAsInt(fParams.getOptions(), kSeedParamKey);
  }

  JPetGeantParserTools::setSeedTogRandom(getOriginalSeed());

  loadSmearingOptionsAndSetupExperimentalParametrizer();
  // make distribution of decays in time window
  // needed to adjust simulation times into time window scheme
  std::tie(fTimeDistroOfDecays, fTimeDiffDistro) = JPetGeantParserTools::getTimeDistoOfDecays(fSimulatedActivity, fMinTime, fMaxTime);

  INFO("[#] JPetGateParser::init()");
  return true;
}

void JPetGateParser::loadSmearingOptionsAndSetupExperimentalParametrizer()
{
  std::vector<double> timeSmearingParameters;
  if (isOptionSet(fParams.getOptions(), kTimeSmearingParametersParamKey))
  {
    timeSmearingParameters = getOptionAsVectorOfDoubles(fParams.getOptions(), kTimeSmearingParametersParamKey);
  }

  std::string timeSmearingFormula;
  if (isOptionSet(fParams.getOptions(), kTimeSmearingFunctionParamKey))
  {
    timeSmearingFormula = getOptionAsString(fParams.getOptions(), kTimeSmearingFunctionParamKey);
  }

  std::vector<double> timeSmearingLimits;
  if (isOptionSet(fParams.getOptions(), kTimeSmearingFunctionLimitsParamKey))
  {
    timeSmearingLimits = getOptionAsVectorOfDoubles(fParams.getOptions(), kTimeSmearingFunctionLimitsParamKey);
  }

  std::vector<double> energySmearingParameters;
  if (isOptionSet(fParams.getOptions(), kEnergySmearingParametersParamKey))
  {
    energySmearingParameters = getOptionAsVectorOfDoubles(fParams.getOptions(), kEnergySmearingParametersParamKey);
  }

  std::string energySmearingFormula;
  if (isOptionSet(fParams.getOptions(), kEnergySmearingFunctionParamKey))
  {
    energySmearingFormula = getOptionAsString(fParams.getOptions(), kEnergySmearingFunctionParamKey);
  }

  std::vector<double> energySmearingLimits;
  if (isOptionSet(fParams.getOptions(), kEnergySmearingFunctionLimitsParamKey))
  {
    energySmearingLimits = getOptionAsVectorOfDoubles(fParams.getOptions(), kEnergySmearingFunctionLimitsParamKey);
  }

  std::vector<double> zPositionSmearingParameters;
  if (isOptionSet(fParams.getOptions(), kZPositionSmearingParametersParamKey))
  {
    zPositionSmearingParameters = getOptionAsVectorOfDoubles(fParams.getOptions(), kZPositionSmearingParametersParamKey);
  }

  std::string zPositionSmearingFormula;
  if (isOptionSet(fParams.getOptions(), kZPositionSmearingFunctionParamKey))
  {
    zPositionSmearingFormula = getOptionAsString(fParams.getOptions(), kZPositionSmearingFunctionParamKey);
  }

  std::vector<double> zPositionSmearingLimits;
  if (isOptionSet(fParams.getOptions(), kZPositionSmearingFunctionLimitsParamKey))
  {
    zPositionSmearingLimits = getOptionAsVectorOfDoubles(fParams.getOptions(), kZPositionSmearingFunctionLimitsParamKey);
  }

  fExperimentalParametrizer.setSmearingFunctions({{timeSmearingFormula, timeSmearingParameters},
                                                  {energySmearingFormula, energySmearingParameters},
                                                  {zPositionSmearingFormula, zPositionSmearingParameters}});

  std::vector<std::pair<double, double>> limits;

  if (timeSmearingLimits.size() == 2)
  {
    limits.push_back({timeSmearingLimits[0], timeSmearingLimits[1]});
  }
  else
  {
    limits.push_back({-1, -1});
  }

  if (energySmearingLimits.size() == 2)
  {
    limits.push_back({energySmearingLimits[0], energySmearingLimits[1]});
  }
  else
  {
    limits.push_back({-1, -1});
  }

  if (zPositionSmearingLimits.size() == 2)
  {
    limits.push_back({zPositionSmearingLimits[0], zPositionSmearingLimits[1]});
  }
  else
  {
    limits.push_back({-1, -1});
  }

  fExperimentalParametrizer.setSmearingFunctionLimits(limits);

  fExperimentalParametrizer.printAllParameters();
}

bool JPetGateParser::exec()
{
  if (auto& gate_hit = dynamic_cast<GateHit* const>(fEvent))
  {
    processGateHit(gate_hit);
    if (isTimeWindowFull())
    {
      saveHits();
      clearTimeDistoOfDecays();
      std::tie(fTimeDistroOfDecays, fTimeDiffDistro) = JPetGeantParserTools::getTimeDistoOfDecays(fSimulatedActivity, fMinTime, fMaxTime);
    }
  }
  else
    return false;
  return true;
}

bool JPetGateParser::terminate()
{
  INFO("[#]  JPetGateParser::terminate()");

  return true;
}

void JPetGateParser::saveHits()
{
  // INFO("[#]  JPetGateParser::saveHits");
  for (const auto& hit : fStoredHits)
  {
    fOutputEvents->add<JPetHit>(hit);
  }

  fStoredHits.clear();
}

void JPetGateParser::saveReconstructedHit(JPetHit recHit) { fStoredHits.push_back(recHit); }

void JPetGateParser::processGateHit(GateHit* gate_hit)
{
  if (fLastEventID != gate_hit->event_id)
  {
    fTimeShift = getNextTimeShift();
    fLastEventID = gate_hit->event_id;
  }

  JPetHit hit;

  JPetScin& scin = getParamBank().getScintillator(gate_hit->sci_id);
  hit.setScintillator(scin);
  hit.setBarrelSlot(scin.getBarrelSlot());

  /// Nonsmeared values
  auto scinID = gate_hit->sci_id;
  auto posZ = gate_hit->posz;
  auto energy = gate_hit->edep * 1000.0;
  auto time = gate_hit->time * 1e6 + fTimeShift;

  /// Smeared values
  hit.setEnergy(fExperimentalParametrizer.addEnergySmearing(scinID, posZ, energy, time));
  // adjust to time window and smear
  hit.setTime(fExperimentalParametrizer.addTimeSmearing(scinID, posZ, energy, time));
  auto radius = getParamBank().getScintillator(scinID).getBarrelSlot().getLayer().getRadius();
  auto theta = TMath::DegToRad() * getParamBank().getScintillator(hit.getScintillator().getID()).getBarrelSlot().getTheta();
  hit.setPosX(radius * std::cos(theta));
  hit.setPosY(radius * std::sin(theta));
  hit.setPosZ(fExperimentalParametrizer.addZHitSmearing(scinID, posZ, energy, time));

  if (JPetGeantParserTools::isHitReconstructed(hit, fExperimentalThreshold))
  {
    saveReconstructedHit(hit);
  }
}

unsigned int JPetGateParser::getNumberOfDecaysInWindow() const { return fTimeDistroOfDecays.size(); }

float JPetGateParser::getNextTimeShift()
{
  float t = fTimeDistroOfDecays[fCurrentIndexTimeShift];
  fCurrentIndexTimeShift++;
  return t;
}

void JPetGateParser::clearTimeDistoOfDecays()
{
  fCurrentIndexTimeShift = 0;
  fTimeDiffDistro.clear();
  fTimeDistroOfDecays.clear();
}

bool JPetGateParser::isTimeWindowFull() const
{
  if (fCurrentIndexTimeShift >= getNumberOfDecaysInWindow())
  {
    return true;
  }
  else
  {
    return false;
  }
}

unsigned long JPetGateParser::getOriginalSeed() const { return fSeed; }
