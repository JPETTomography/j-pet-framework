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

JPetGateParser::JPetGateParser(const char* name) : JPetTask(name) {}

JPetGateParser::~JPetGateParser() {}

bool JPetGateParser::init(const JPetParams& inParams)
{
  INFO("GateTransformer started.");
  fParams = inParams;

  std::unique_ptr<JPetGeomMapping> fDetectorMap(new JPetGeomMapping(getParamBank()));
  fOutputEvents = new JPetTimeWindow("JPetHit");

  // Cmds handling
  auto opts = fParams.getOptions();

  if (isOptionSet(opts, kMaxTimeWindowParamKey))
  {
    fMaxTime = getOptionAsDouble(opts, kMaxTimeWindowParamKey);
  }
  if (isOptionSet(opts, kMinTimeWindowParamKey))
  {
    fMinTime = getOptionAsDouble(opts, kMinTimeWindowParamKey);
  }
  if (isOptionSet(opts, kSourceActivityParamKey))
  {
    fSimulatedActivity = getOptionAsDouble(opts, kSourceActivityParamKey);
  }
  if (isOptionSet(opts, kEnergyThresholdParamKey))
  {
    fExperimentalThreshold = getOptionAsDouble(opts, kEnergyThresholdParamKey);
  }
  if (isOptionSet(opts, kSeedParamKey))
  {
    fSeed = getOptionAsInt(opts, kSeedParamKey);
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
  auto opts = fParams.getOptions();
  std::vector<double> timeSmearingParameters;
  if (isOptionSet(opts, kTimeSmearingParametersParamKey))
  {
    timeSmearingParameters = getOptionAsVectorOfDoubles(opts, kTimeSmearingParametersParamKey);
  }

  std::string timeSmearingFormula;
  if (isOptionSet(opts, kTimeSmearingFunctionParamKey))
  {
    timeSmearingFormula = getOptionAsString(opts, kTimeSmearingFunctionParamKey);
  }

  std::vector<double> timeSmearingLimits;
  if (isOptionSet(opts, kTimeSmearingFunctionLimitsParamKey))
  {
    timeSmearingLimits = getOptionAsVectorOfDoubles(opts, kTimeSmearingFunctionLimitsParamKey);
  }

  std::vector<double> energySmearingParameters;
  if (isOptionSet(opts, kEnergySmearingParametersParamKey))
  {
    energySmearingParameters = getOptionAsVectorOfDoubles(opts, kEnergySmearingParametersParamKey);
  }

  std::string energySmearingFormula;
  if (isOptionSet(opts, kEnergySmearingFunctionParamKey))
  {
    energySmearingFormula = getOptionAsString(opts, kEnergySmearingFunctionParamKey);
  }

  std::vector<double> energySmearingLimits;
  if (isOptionSet(opts, kEnergySmearingFunctionLimitsParamKey))
  {
    energySmearingLimits = getOptionAsVectorOfDoubles(opts, kEnergySmearingFunctionLimitsParamKey);
  }

  std::vector<double> zPositionSmearingParameters;
  if (isOptionSet(opts, kZPositionSmearingParametersParamKey))
  {
    zPositionSmearingParameters = getOptionAsVectorOfDoubles(opts, kZPositionSmearingParametersParamKey);
  }

  std::string zPositionSmearingFormula;
  if (isOptionSet(opts, kZPositionSmearingFunctionParamKey))
  {
    zPositionSmearingFormula = getOptionAsString(opts, kZPositionSmearingFunctionParamKey);
  }

  std::vector<double> zPositionSmearingLimits;
  if (isOptionSet(opts, kZPositionSmearingFunctionLimitsParamKey))
  {
    zPositionSmearingLimits = getOptionAsVectorOfDoubles(opts, kZPositionSmearingFunctionLimitsParamKey);
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

bool JPetGateParser::run(const JPetDataInterface&)
{
  auto inFile = getInputFile(fParams.getOptions());
  JPetGateTreeReader::DetectorGeometry geom = JPetGateTreeReader::DetectorGeometry::ThreeLayers;
  auto outputPath = getOutputPath(fParams.getOptions());
  if (outputPath == "")
  {
    outputPath = "./";
  }

  return transformTree(inFile, outputPath, geom, fSimulatedActivity, fMinTime, fMaxTime);
}

bool JPetGateParser::transformTree(const std::string& inFile, const std::string& outFile, JPetGateTreeReader::DetectorGeometry geom,
                                   double simulatedActivity, double minTime, double maxTime)
{
  std::cout << "transformTree" << std::endl;
  std::tie(fTimeDistroOfDecays, fTimeDiffDistro) = JPetGeantParserTools::getTimeDistoOfDecays(simulatedActivity, minTime, maxTime);

  JPetGateTreeReader r(inFile, geom, -1);
  while (r.read())
  {
    GateHit* p_gh = r.get();
    if (!p_gh)
      continue;
    processGateHit(p_gh);
    if (isTimeWindowFull())
    {
      saveHits();
      clearTimeDistoOfDecays();
      std::tie(fTimeDistroOfDecays, fTimeDiffDistro) = JPetGeantParserTools::getTimeDistoOfDecays(simulatedActivity, minTime, maxTime);
    }
  }
  std::cout << "done transformTree" << std::endl;
  return true;
}

bool JPetGateParser::terminate(JPetParams& outParams)
{
  DEBUG("[#]  JPetGateParser::terminate()");
  OptsStrAny new_opts;
  // setOutputFileType(new_opts, "hld");
  // auto outputFile =
  // getOutputPath(fOptions)
  //+ JPetCommonTools::stripFileNameSuffix(getInputFile(fOptions));
  // setOutputFile(new_opts, outputFile);

  // if (isOptionSet(fOptions, "firstEvent_int") && isOptionSet(fOptions, "lastEvent_int")) {
  // if (getOptionAsInt(fOptions, "firstEvent_int") != -1 && getOptionAsInt(fOptions, "lastEvent_int") != -1) {
  // setResetEventRangeOption(new_opts, true);
  //}
  //}

  // outParams = JPetParams(new_opts, outParams.getParamManagerAsShared());
  // INFO(Form(
  //"GateTransformer finished, unzipped file name: %s", outputFile.c_str()
  //));
  return true;
}

void JPetGateParser::saveHits()
{
  DEBUG("[#]  JPetGateParser::saveHits");
  for (const auto& hit : fStoredHits)
  {
    fOutputEvents->add<JPetHit>(hit);
  }

  fStoredHits.clear();
}

void JPetGateParser::saveReconstructedHit(JPetHit recHit) { fStoredHits.push_back(recHit); }

void JPetGateParser::processGateHit(GateHit* gate_hit)
{
  assert(gate_hit);
  if (fLastEventID != gate_hit->event_id)
  {
    fTimeShift = getNextTimeShift();
    fLastEventID = gate_hit->event_id;
  }

  JPetHit hit;
  assert(!getParamBank().isDummy());
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
  assert(fTimeDistroOfDecays.size() > fCurrentIndexTimeShift);
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

const JPetParamBank& JPetGateParser::getParamBank()
{
  DEBUG("JPetGateParser");
  auto paramManager = fParams.getParamManager();
  assert(paramManager);
  return paramManager->getParamBank();
}
