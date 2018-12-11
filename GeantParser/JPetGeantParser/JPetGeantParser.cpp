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

#include <iostream>
#include <JPetWriter/JPetWriter.h>
#include <JPetAnalysisTools/JPetAnalysisTools.h>
#include <JPetOptionsTools/JPetOptionsTools.h>
#include <JPetGeantParser/JPetGeantParser.h>
#include <JPetGeantParser/JPetGeantParserTools.h>
#include <JPetRandom/JPetRandom.h>


#include <JPetScin/JPetScin.h>
#include <string>
#include <TMath.h>
#include <cmath>
#include <array>

using namespace jpet_options_tools;

JPetGeantParser::JPetGeantParser(const char* name) : JPetUserTask(name) { }

JPetGeantParser::~JPetGeantParser() { }


bool JPetGeantParser::init()
{

  // create detector map
  std::unique_ptr<JPetGeomMapping> fDetectorMap(new JPetGeomMapping(getParamBank()));

  fOutputEvents = new JPetTimeWindowMC("JPetHit", "JPetMCHit", "JPetMCDecayTree");
  auto opts = getOptions();

  if (isOptionSet(fParams.getOptions(), kMaxTimeWindowParamKey)) {
    fMaxTime = getOptionAsDouble(fParams.getOptions(), kMaxTimeWindowParamKey);
  }
  if (isOptionSet(fParams.getOptions(), kMinTimeWindowParamKey)) {
    fMinTime = getOptionAsDouble(fParams.getOptions(), kMinTimeWindowParamKey);
  }
  if (isOptionSet(fParams.getOptions(), kSourceActivityParamKey)) {
    fSimulatedActivity = getOptionAsDouble(fParams.getOptions(), kSourceActivityParamKey);
  }
  if (isOptionSet(fParams.getOptions(), kMakeHistogramsParamKey)) {
    fMakeHisto = getOptionAsBool(fParams.getOptions(), kMakeHistogramsParamKey);
  }
  if (isOptionSet(fParams.getOptions(), kMakeEfficienciesParamKey)) {
    fMakeEffiHisto = getOptionAsBool(fParams.getOptions(), kMakeEfficienciesParamKey);
  }
  if (isOptionSet(fParams.getOptions(), kZresolutionParamKey)) {
    fZresolution = getOptionAsDouble(fParams.getOptions(), kZresolutionParamKey);
  }
  if (isOptionSet(fParams.getOptions(), kEnergyThresholdParamKey)) {
    fExperimentalThreshold = getOptionAsDouble(fParams.getOptions(), kEnergyThresholdParamKey);
  }
  if (isOptionSet(fParams.getOptions(), kProcessSingleEventinWindowParamKey)) {
    fProcessSingleEventinWindow = getOptionAsBool(fParams.getOptions(), kProcessSingleEventinWindowParamKey);
  }
  if (fMakeHisto) bookBasicHistograms();
  if (fMakeEffiHisto) bookEfficiencyHistograms();

  INFO("MC Hit wrapper started.");

  return true;
}


bool JPetGeantParser::exec()
{

  if (auto& mcEventPack = dynamic_cast<JPetGeantEventPack* const>(fEvent)) {

    processMCEvent(mcEventPack);

      if (fProcessSingleEventinWindow){
              saveHits();
      } else {
            if (fActivityIndex > abs(fMinTime * fSimulatedActivity * pow(10, -6))) {
              saveHits();
              fActivityIndex = 0;
            } else {
              fActivityIndex++;
            }
      }
      

  } else {
    return false;
  }

  return true;
}


bool JPetGeantParser::terminate()
{
  INFO("MC events processing ended");
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


  // first adjust all hits in single event to time window scheme
  float timeShift = JPetRandom::GetRandomGenerator()->Uniform(fMinTime, fMaxTime);

  for ( unsigned int i = 0; i < evPack->GetNumberOfHits(); i++) {

    // translate geantHit -> JPetMCHit
    JPetMCHit mcHit = JPetGeantParserTools::createJPetMCHit(evPack->GetHit(i), getParamBank());


    fStoredMCHits.push_back(mcHit);
    if (fMakeHisto) fillHistoMCGen(mcHit);

    // create reconstructed hit and add all smearings
    JPetHit  recHit =  JPetGeantParserTools::reconstructHit(mcHit, getParamBank(), timeShift, fZresolution);
    // add criteria for possible rejection of reconstructed events (e.g. E>50 keV)

    if (JPetGeantParserTools::isHitReconstructed(recHit, fExperimentalThreshold)) {
      fStoredHits.push_back(recHit);
      JPetGeantParserTools::identifyRecoHits(evPack->GetHit(i), recHit,
                                             isRecPrompt, isSaved2g, isSaved3g,
                                             enePrompt, ene2g, ene3g);

      if (fMakeHisto) fillHistoMCRec(recHit);
    }

  }

  isRec2g = isSaved2g[0] && isSaved2g[1];
  isRec3g = isSaved3g[0] && isSaved3g[1] && isSaved3g[2];


  if (fMakeHisto) fillHistoGenInfo(evPack->GetEventInformation());



  // fill efficiency histograms

  if (isGenPrompt && fMakeEffiHisto) {
    for ( int i = 0; i < kEffiHisto_ene_nBin; i++) {
      getStatistics().getEffiHisto("effi_prompt_eneDepos")->Fill(isRecPrompt &&
          ( enePrompt > i * kEffiHisto_ene_width )
          , i * kEffiHisto_ene_width);
    }
  }

  if (isGen2g && fMakeEffiHisto) {
    for ( int i = 0; i < kEffiHisto_ene_nBin; i++) {
      getStatistics().getEffiHisto("effi_2g_hit_eneDepos")->Fill(isRec2g &&
          ( ene2g[0] > i * kEffiHisto_ene_width ) && ( ene2g[1] > i * kEffiHisto_ene_width)
          , i * kEffiHisto_ene_width);
    }

  }

  if (isGen3g && fMakeEffiHisto) {
    for ( int i = 0; i < kEffiHisto_ene_nBin; i++) {
      getStatistics().getEffiHisto("effi_3g_hit_eneDepos")->Fill(isRec3g &&
          ( ene3g[0] > i * kEffiHisto_ene_width ) && ( ene3g[1] > i * kEffiHisto_ene_width) && (ene3g[2] > i * kEffiHisto_ene_width)
          , i * kEffiHisto_ene_width);
    }

  }

//    // add loop processing DecayTree
}


void JPetGeantParser::fillHistoGenInfo(JPetGeantEventInformation* evInfo)
{
  bool isGenPrompt = evInfo->GetPromptGammaGen();
  bool isGen2g = evInfo->GetTwoGammaGen();
  bool isGen3g = evInfo->GetThreeGammaGen();


  // general histograms
  getStatistics().getHisto1D("gen_lifetime")->Fill(evInfo->GetLifetime());

  // histograms for prompt gamma
  if (isGenPrompt) {
    getStatistics().getHisto1D("gen_hit_multiplicity")->Fill(1);
    getStatistics().getHisto2D("gen_prompt_XY")->Fill(evInfo->GetVtxPromptPositionX(), evInfo->GetVtxPromptPositionY());
    getStatistics().getHisto2D("gen_prompt_XZ")->Fill(evInfo->GetVtxPromptPositionX(), evInfo->GetVtxPromptPositionZ());
    getStatistics().getHisto2D("gen_prompt_YZ")->Fill(evInfo->GetVtxPromptPositionY(), evInfo->GetVtxPromptPositionZ());

  }

  // histograms for annihilation 2g 3g
  if (isGen2g) {
    getStatistics().getHisto1D("gen_hit_multiplicity")->Fill(2);
  }

  if (isGen3g) {
    getStatistics().getHisto1D("gen_hit_multiplicity")->Fill(3);
  }

  if ( isGen2g || isGen3g ) {
    getStatistics().getHisto2D("gen_XY")->Fill(evInfo->GetVtxPositionX(), evInfo->GetVtxPositionY());
    getStatistics().getHisto2D("gen_XZ")->Fill(evInfo->GetVtxPositionX(), evInfo->GetVtxPositionZ());
    getStatistics().getHisto2D("gen_YZ")->Fill(evInfo->GetVtxPositionY(), evInfo->GetVtxPositionZ());
  }
}


void JPetGeantParser::saveHits()
{

  for (const auto& hit : fStoredHits) {
    fOutputEvents->add<JPetHit>(hit);
  }

  for (const auto& mcHit : fStoredMCHits) {
    dynamic_cast<JPetTimeWindowMC*>(fOutputEvents)->addMCHit<JPetMCHit>(mcHit);
  }

  if (fMakeHisto) getStatistics().getHisto1D("hits_per_time_window")->Fill(fStoredHits.size());

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

  getStatistics().createHistogram(
    new TH1F("hits_per_time_window",
             "Number of Hits in Time Window",
             101, -0.5, 100.5
            ));



  // GENERATED HISTOGRAMS

  getStatistics().createHistogram(
    new TH1F("gen_hits_z_pos",
             "Gen hits Z position",
             100, -60.0, 60.0)
  );

  getStatistics().createHistogram(
    new TH2F("gen_hits_xy_pos",
             "GEN hits XY pos",
             121, -60.5, 60.5,
             121, -60.5, 60.5
            ));


  getStatistics().createHistogram(
    new TH1F("gen_hit_time",
             "Gen hit time",
             100, 0.0, 15000.0)
  );

  getStatistics().createHistogram(
    new TH1F("gen_hit_eneDepos",
             "Gen hit ene deposition",
             750, 0.0, 1500.0)
  );


  getStatistics().createHistogram(
    new TH2F("gen_XY",
             "GEN XY coordinates of annihilation point",
             121, -60.5, 60.5,
             121, -60.5, 60.5
            ));

  getStatistics().createHistogram(
    new TH2F("gen_XZ",
             "GEN XZ coordinates of annihilation point",
             121, -60.5, 60.5,
             121, -60.5, 60.5
            ));

  getStatistics().createHistogram(
    new TH2F("gen_YZ",
             "GEN YZ coordinates of annihilation point",
             121, -60.5, 60.5,
             121, -60.5, 60.5
            ));

  getStatistics().createHistogram(
    new TH2F("gen_prompt_XY",
             "GEN XY coordinates of prompt emission point",
             121, -60.5, 60.5,
             121, -60.5, 60.5
            ));

  getStatistics().createHistogram(
    new TH2F("gen_prompt_XZ",
             "GEN XZ coordinates of prompt emission point",
             121, -60.5, 60.5,
             121, -60.5, 60.5
            ));

  getStatistics().createHistogram(
    new TH2F("gen_prompt_YZ",
             "GEN YZ coordinates of prompt emission point",
             121, -60.5, 60.5,
             121, -60.5, 60.5
            ));



  getStatistics().createHistogram(
    new TH1F("gen_hit_multiplicity",
             "Gen hit multiplicity",
             6, 0.0, 5.0)
  );

  getStatistics().createHistogram(
    new TH1F("gen_lifetime",
             "Gen lifetime",
             100, 0.0, 1500.0)
  );




  // RECONSTRUCTED HISTOGRAMS

  getStatistics().createHistogram(
    new TH1F("hits_z_pos",
             "hits Z position",
             100, -60.0, 60.0)
  );

  getStatistics().createHistogram(
    new TH2F("hits_xy_pos",
             "hits XY pos",
             121, -60.5, 60.5,
             121, -60.5, 60.5
            ));

  getStatistics().createHistogram(
    new TH1F("rec_hit_time",
             "hit time",
             100, 0.0, 15000.0)
  );

  getStatistics().createHistogram(
    new TH1F("rec_hit_eneDepos",
             "hit ene deposition",
             750, 0.0, 1500.0)
  );


}

void JPetGeantParser::bookEfficiencyHistograms()
{

  getStatistics().createHistogram(
    new TEfficiency("effi_3g_hit_eneDepos",
                    "effi 3g ene deposition",
                    kEffiHisto_ene_nBin, 0.0, kEffiHisto_ene_nBin * kEffiHisto_ene_width )
  );

  getStatistics().createHistogram(
    new TEfficiency("effi_2g_hit_eneDepos",
                    "effi 2g ene deposition",
                    kEffiHisto_ene_nBin, 0.0, kEffiHisto_ene_nBin * kEffiHisto_ene_width )
  );


  getStatistics().createHistogram(
    new TEfficiency("effi_prompt_eneDepos",
                    "effi prompt ene deposition",
                    kEffiHisto_ene_nBin, 0.0, kEffiHisto_ene_nBin * kEffiHisto_ene_width )
  );


}

