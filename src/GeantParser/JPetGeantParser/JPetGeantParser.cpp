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
 *  @file JPetGeantParser.cpp
 */

#include <JPetAnalysisTools/JPetAnalysisTools.h>
#include <JPetGeantParser/JPetGeantParser.h>
#include <JPetGeantParser/JPetGeantParserTools.h>
#include <JPetOptionsTools/JPetOptionsTools.h>
#include <JPetWriter/JPetWriter.h>
#include <iostream>

#include <JPetScin/JPetScin.h>
#include <TMath.h>
#include <array>
#include <cmath>
#include <string>

using namespace jpet_options_tools;

JPetGeantParser::JPetGeantParser(const char* name) : JPetUserTask(name) {}

JPetGeantParser::~JPetGeantParser() {}

bool JPetGeantParser::init()
{
  fOutputEvents = new JPetTimeWindowMC("JPetHit", "JPetMCHit", "JPetMCDecayTree");
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
  if (isOptionSet(fParams.getOptions(), kMakeHistogramsParamKey))
  {
    fMakeHisto = getOptionAsBool(fParams.getOptions(), kMakeHistogramsParamKey);
  }
  if (isOptionSet(fParams.getOptions(), kMakeEfficienciesParamKey))
  {
    fMakeEffiHisto = getOptionAsBool(fParams.getOptions(), kMakeEfficienciesParamKey);
  }
  if (isOptionSet(fParams.getOptions(), kEnergyThresholdParamKey))
  {
    fExperimentalThreshold = getOptionAsDouble(fParams.getOptions(), kEnergyThresholdParamKey);
  }
  if (isOptionSet(fParams.getOptions(), kProcessSingleEventinWindowParamKey))
  {
    fProcessSingleEventinWindow = getOptionAsBool(fParams.getOptions(), kProcessSingleEventinWindowParamKey);
  }

  if (isOptionSet(fParams.getOptions(), kSeedParamKey))
  {
    fSeed = getOptionAsInt(fParams.getOptions(), kSeedParamKey);
  }

  JPetGeantParserTools::setSeedTogRandom(getOriginalSeed());
  INFO("Seed value used for resolution smearing of MC simulation data: " << boost::lexical_cast<std::string>(getOriginalSeed()));

  loadSmearingOptionsAndSetupExperimentalParametrizer();

  if (fMakeHisto)
    bookBasicHistograms();
  if (fMakeEffiHisto)
    bookEfficiencyHistograms();

  // make distribution of decays in time window
  // needed to adjust simulation times into time window scheme
  std::tie(fTimeDistroOfDecays, fTimeDiffDistro) = JPetGeantParserTools::getTimeDistoOfDecays(fSimulatedActivity, fMinTime, fMaxTime);

  INFO("MC Hit wrapper started.");

  return true;
}

void JPetGeantParser::loadSmearingOptionsAndSetupExperimentalParametrizer()
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
}

bool JPetGeantParser::exec()
{

  if (auto& mcEventPack = dynamic_cast<JPetGeantEventPack* const>(fEvent))
  {

    processMCEvent(mcEventPack);

    if (fProcessSingleEventinWindow)
    {
      saveHits();
    }
    else
    {
      if (isTimeWindowFull())
      {
        saveHits();
        clearTimeDistoOfDecays();
        std::tie(fTimeDistroOfDecays, fTimeDiffDistro) = JPetGeantParserTools::getTimeDistoOfDecays(fSimulatedActivity, fMinTime, fMaxTime);
      }
    }
  }
  else
  {
    return false;
  }

  return true;
}

bool JPetGeantParser::terminate()
{
  INFO("MC events processing ended");
  float effi;
  float err_effi;
  std::tie(effi, err_effi) = JPetGeantParserTools::calculateEfficiency(nPromptGen, nPromptRec);
  INFO(" Efficiency for prompt gamma registration: " << boost::lexical_cast<std::string>(effi) << " pm "
                                                     << boost::lexical_cast<std::string>(err_effi));

  std::tie(effi, err_effi) = JPetGeantParserTools::calculateEfficiency(n2gGen, n2gRec);
  INFO(" Efficiency for prompt 2gamma registration: " << boost::lexical_cast<std::string>(effi) << " pm "
                                                      << boost::lexical_cast<std::string>(err_effi));

  std::tie(effi, err_effi) = JPetGeantParserTools::calculateEfficiency(n3gGen, n3gRec);
  INFO(" Efficiency for prompt 3gamma registration: " << boost::lexical_cast<std::string>(effi) << " pm "
                                                      << boost::lexical_cast<std::string>(err_effi));

  return true;
}

void JPetGeantParser::processMCEvent(JPetGeantEventPack* evPack)
{

  bool isRecPrompt = false;
  std::array<bool, 2> isSaved2g{false, false};
  std::array<bool, 3> isSaved3g{false, false, false};

  bool isRec2g = false;
  bool isRec3g = false;

  float enePrompt = 0;
  std::array<float, 2> ene2g{0., 0.};
  std::array<float, 3> ene3g{0., 0., 0.};

  bool isGenPrompt = evPack->GetEventInformation()->GetPromptGammaGen();
  bool isGen2g = evPack->GetEventInformation()->GetTwoGammaGen();
  bool isGen3g = evPack->GetEventInformation()->GetThreeGammaGen();

  float timeShift = getNextTimeShift();
  for (unsigned int i = 0; i < evPack->GetNumberOfHits(); i++)
  {

    // translate geantHit -> JPetMCHit
    JPetMCHit mcHit = JPetGeantParserTools::createJPetMCHit(evPack->GetHit(i), getParamBank());

    if (fMakeHisto)
      fillHistoMCGen(mcHit);
    // create reconstructed hit and add all smearings
    JPetHit recHit = JPetGeantParserTools::reconstructHit(mcHit, getParamBank(), timeShift, fExperimentalParametrizer);

    // add criteria for possible rejection of reconstructed events (e.g. E>50 keV)
    if (JPetGeantParserTools::isHitReconstructed(recHit, fExperimentalThreshold))
    {
      saveReconstructedHit(recHit);
      JPetGeantParserTools::identifyRecoHits(evPack->GetHit(i), recHit, isRecPrompt, isSaved2g, isSaved3g, enePrompt, ene2g, ene3g);

      if (fMakeHisto)
        fillHistoMCRec(recHit);
    }
    fStoredMCHits.push_back(mcHit);
  }

  isRec2g = isSaved2g[0] && isSaved2g[1];
  isRec3g = isSaved3g[0] && isSaved3g[1] && isSaved3g[2];

  if (fMakeHisto)
    fillHistoGenInfo(evPack->GetEventInformation());

  // fill efficiency histograms

  if (isGenPrompt && fMakeEffiHisto)
  {
    double x = evPack->GetEventInformation()->GetVtxPromptPositionX();
    double y = evPack->GetEventInformation()->GetVtxPromptPositionY();
    double z = evPack->GetEventInformation()->GetVtxPromptPositionZ();
    getStatistics().getEffiHisto("effi_prompt_in_rho_z")->Fill(isRecPrompt, sqrt(pow(x, 2) + pow(y, 2)), z);
  }

  if (isGen2g && fMakeEffiHisto)
  {
    double x = evPack->GetEventInformation()->GetVtxPositionX();
    double y = evPack->GetEventInformation()->GetVtxPositionY();
    double z = evPack->GetEventInformation()->GetVtxPositionZ();
    getStatistics().getEffiHisto("effi_2g_in_rho_z")->Fill(isRec2g, sqrt(pow(x, 2) + pow(y, 2)), z);
  }

  if (isGen3g && fMakeEffiHisto)
  {
    double x = evPack->GetEventInformation()->GetVtxPositionX();
    double y = evPack->GetEventInformation()->GetVtxPositionY();
    double z = evPack->GetEventInformation()->GetVtxPositionZ();
    getStatistics().getEffiHisto("effi_3g_in_rho_z")->Fill(isRec3g, sqrt(pow(x, 2) + pow(y, 2)), z);
  }

  if (isGenPrompt)
  {
    nPromptGen++;
    if (isRecPrompt)
      nPromptRec++;
  }

  if (isGen2g)
  {
    n2gGen++;
    if (isRec2g)
      n2gRec++;
  }

  if (isGen3g)
  {
    n3gGen++;
    if (isRec3g)
      n3gRec++;
  }

  //    // add loop processing DecayTree
}

void JPetGeantParser::saveReconstructedHit(JPetHit recHit)
{
  recHit.setMCindex(fStoredMCHits.size());
  fStoredHits.push_back(recHit);
}

void JPetGeantParser::fillHistoGenInfo(JPetGeantEventInformation* evInfo)
{
  bool isGenPrompt = evInfo->GetPromptGammaGen();
  bool isGen2g = evInfo->GetTwoGammaGen();
  bool isGen3g = evInfo->GetThreeGammaGen();

  // general histograms
  getStatistics().getHisto1D("gen_lifetime")->Fill(evInfo->GetLifetime());

  // histograms for prompt gamma
  if (isGenPrompt)
  {
    getStatistics().getHisto1D("gen_hit_multiplicity")->Fill(1);
    getStatistics().getHisto2D("gen_prompt_XY")->Fill(evInfo->GetVtxPromptPositionX(), evInfo->GetVtxPromptPositionY());
    getStatistics().getHisto2D("gen_prompt_XZ")->Fill(evInfo->GetVtxPromptPositionX(), evInfo->GetVtxPromptPositionZ());
    getStatistics().getHisto2D("gen_prompt_YZ")->Fill(evInfo->GetVtxPromptPositionY(), evInfo->GetVtxPromptPositionZ());
  }

  // histograms for annihilation 2g 3g
  if (isGen2g)
  {
    getStatistics().getHisto1D("gen_hit_multiplicity")->Fill(2);
  }

  if (isGen3g)
  {
    getStatistics().getHisto1D("gen_hit_multiplicity")->Fill(3);
  }

  if (isGen2g || isGen3g)
  {
    getStatistics().getHisto2D("gen_XY")->Fill(evInfo->GetVtxPositionX(), evInfo->GetVtxPositionY());
    getStatistics().getHisto2D("gen_XZ")->Fill(evInfo->GetVtxPositionX(), evInfo->GetVtxPositionZ());
    getStatistics().getHisto2D("gen_YZ")->Fill(evInfo->GetVtxPositionY(), evInfo->GetVtxPositionZ());
  }
}

void JPetGeantParser::saveHits()
{

  for (const auto& hit : fStoredHits)
  {
    fOutputEvents->add<JPetHit>(hit);
  }

  for (const auto& mcHit : fStoredMCHits)
  {
    dynamic_cast<JPetTimeWindowMC*>(fOutputEvents)->addMCHit<JPetMCHit>(mcHit);
  }

  if (fMakeHisto)
  {
    getStatistics().getHisto1D("hits_per_time_window")->Fill(fStoredHits.size());
    for (const auto i : fTimeDiffDistro)
    {
      getStatistics().getHisto1D("time_diff_bw_decays")->Fill(i);
    }
  }

  fStoredMCHits.clear();
  fStoredHits.clear();
}

void JPetGeantParser::fillHistoMCGen(JPetMCHit& mcHit)
{
  getStatistics().getHisto1D("gen_hits_z_pos")->Fill(mcHit.getPosZ());
  getStatistics().getHisto2D("gen_hits_xy_pos")->Fill(mcHit.getPosX(), mcHit.getPosY());
  getStatistics().getHisto1D("gen_hit_time")->Fill(mcHit.getTime());
  getStatistics().getHisto1D("gen_hit_eneDepos")->Fill(mcHit.getEnergy());
}

void JPetGeantParser::fillHistoMCRec(JPetHit& recHit)
{
  getStatistics().getHisto1D("hits_z_pos")->Fill(recHit.getPosZ());
  getStatistics().getHisto2D("hits_xy_pos")->Fill(recHit.getPosX(), recHit.getPosY());
  getStatistics().getHisto1D("rec_hit_time")->Fill(recHit.getTime());
  getStatistics().getHisto1D("rec_hit_eneDepos")->Fill(recHit.getEnergy());
}

void JPetGeantParser::bookBasicHistograms()
{
  // HISTOGRAMS FROM STANDARD HITFINDER

  getStatistics().createHistogram(new TH1F("hits_per_time_window", "Number of Hits in Time Window", 101, -0.5, 500.5));

  getStatistics().createHistogram(new TH1F("time_diff_bw_decays", "Time difference between decays", 101, -0.5, (fMaxTime - fMinTime) / 50.));

  // GENERATED HISTOGRAMS

  getStatistics().createHistogram(new TH1F("gen_hits_z_pos", "Gen hits Z position", 100, -60.0, 60.0));

  getStatistics().createHistogram(new TH2F("gen_hits_xy_pos", "GEN hits XY pos", 121, -60.5, 60.5, 121, -60.5, 60.5));

  getStatistics().createHistogram(new TH1F("gen_hit_time", "Gen hit time", 100, 0.0, 15000.0));

  getStatistics().createHistogram(new TH1F("gen_hit_eneDepos", "Gen hit ene deposition", 750, 0.0, 1500.0));

  getStatistics().createHistogram(new TH2F("gen_XY", "GEN XY coordinates of annihilation point", 121, -60.5, 60.5, 121, -60.5, 60.5));

  getStatistics().createHistogram(new TH2F("gen_XZ", "GEN XZ coordinates of annihilation point", 121, -60.5, 60.5, 121, -60.5, 60.5));

  getStatistics().createHistogram(new TH2F("gen_YZ", "GEN YZ coordinates of annihilation point", 121, -60.5, 60.5, 121, -60.5, 60.5));

  getStatistics().createHistogram(new TH2F("gen_prompt_XY", "GEN XY coordinates of prompt emission point", 121, -60.5, 60.5, 121, -60.5, 60.5));

  getStatistics().createHistogram(new TH2F("gen_prompt_XZ", "GEN XZ coordinates of prompt emission point", 121, -60.5, 60.5, 121, -60.5, 60.5));

  getStatistics().createHistogram(new TH2F("gen_prompt_YZ", "GEN YZ coordinates of prompt emission point", 121, -60.5, 60.5, 121, -60.5, 60.5));

  getStatistics().createHistogram(new TH1F("gen_hit_multiplicity", "Gen hit multiplicity", 6, 0.0, 5.0));

  getStatistics().createHistogram(new TH1F("gen_lifetime", "Gen lifetime", 100, 0.0, 1500.0));

  // RECONSTRUCTED HISTOGRAMS

  getStatistics().createHistogram(new TH1F("hits_z_pos", "hits Z position", 100, -60.0, 60.0));

  getStatistics().createHistogram(new TH2F("hits_xy_pos", "hits XY pos", 121, -60.5, 60.5, 121, -60.5, 60.5));

  getStatistics().createHistogram(new TH1F("rec_hit_time", "hit time", 100, 0.0, 15000.0));

  getStatistics().createHistogram(new TH1F("rec_hit_eneDepos", "hit ene deposition", 750, 0.0, 1500.0));
}

void JPetGeantParser::bookEfficiencyHistograms()
{

  getStatistics().createHistogram(new TEfficiency("effi_3g_in_rho_z", "effi for 1g as function of rho and z of vtx", 100, 0., 50., 100, -25., 25.));

  getStatistics().createHistogram(new TEfficiency("effi_2g_in_rho_z", "effi for 2g as function of rho and z of vtx", 100, 0., 50., 100, -25., 25.));

  getStatistics().createHistogram(
      new TEfficiency("effi_prompt_in_rho_z", "effi for 3g as function of rho and z of vtx", 100, 0., 50., 100, -25., 25.));
}

unsigned int JPetGeantParser::getNumberOfDecaysInWindow() const { return fTimeDistroOfDecays.size(); }

float JPetGeantParser::getNextTimeShift()
{
  float t = fTimeDistroOfDecays[fCurrentIndexTimeShift];
  fCurrentIndexTimeShift++;
  return t;
}

void JPetGeantParser::clearTimeDistoOfDecays()
{
  fCurrentIndexTimeShift = 0;
  fTimeDiffDistro.clear();
  fTimeDistroOfDecays.clear();
}

bool JPetGeantParser::isTimeWindowFull() const
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

unsigned long JPetGeantParser::getOriginalSeed() const { return fSeed; }
