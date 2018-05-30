/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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

#include <JPetScin/JPetScin.h>
#include<TRandom3.h>
#include <string>
#include <TMath.h> 
#include <cmath> 

using namespace jpet_options_tools;

JPetGeantParser::JPetGeantParser(const char* name) : JPetUserTask(name) { }

JPetGeantParser::~JPetGeantParser() { }

bool JPetGeantParser::init()
{

    // create detector map
    std::unique_ptr<JPetGeomMapping> fDetectorMap(new JPetGeomMapping(getParamBank()));

    fOutputEvents = new JPetTimeWindow("JPetHit","JPetMCHit","JPetMCDecayTree");
    auto opts = getOptions();

    if (isOptionSet(fParams.getOptions(), kMaxTimeWindowParamKey)) { 
        fMaxTime = getOptionAsDouble(fParams.getOptions(), kMaxTimeWindowParamKey);
    }
    if (isOptionSet(fParams.getOptions(), kMinTimeWindowParamKey)) { 
        fMinTime = getOptionAsDouble(fParams.getOptions(), kMinTimeWindowParamKey);
    }
    if (isOptionSet(fParams.getOptions(), kSourceActivityParamKey)) { 
        kSimulatedActivity = getOptionAsDouble(fParams.getOptions(), kSourceActivityParamKey);
    }


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

    // EFFICIENCY HISTOGRAMS

    getStatistics().createHistogram(
            new TEfficiency("effi_3g_hit_eneDepos",
                "effi 3g ene deposition",
                effiHisto_ene_nBin, 0.0, effiHisto_ene_nBin*effiHisto_ene_width )
            );

    getStatistics().createHistogram(
            new TEfficiency("effi_2g_hit_eneDepos",
                "effi 2g ene deposition",
                effiHisto_ene_nBin, 0.0, effiHisto_ene_nBin*effiHisto_ene_width )
            );


    getStatistics().createHistogram(
            new TEfficiency("effi_prompt_eneDepos",
                "effi prompt ene deposition",
                effiHisto_ene_nBin, 0.0, effiHisto_ene_nBin*effiHisto_ene_width )
            );




    for (Int_t i=0; i<effiMap_nSlice; i++){
        getStatistics().createHistogram(   
                new TEfficiency(TString("effi_prompt_vtx_")+TString::Itoa(i,10), 
                    "effi prompt registration as vtx ", 
                    121, -60., 60.,
                    121, -60., 60.
                    ));

        getStatistics().createHistogram(   
                new TEfficiency(TString("effi_2g_vtx_")+TString::Itoa(i,10), 
                    "effi 2g annihilation registration as vtx ", 
                    121, -60., 60.,
                    121, -60., 60.
                    ));

        getStatistics().createHistogram(   
                new TEfficiency(TString("effi_3g_vtx_")+TString::Itoa(i,10), 
                    "effi 3g annihilation registration as vtx ", 
                    121, -60., 60.,
                    121, -60., 60.
                    ));


    };


    INFO("MC Hit wrapper started.");

    return true;
}

bool JPetGeantParser::exec()
{

    if(auto& mcEventPack = dynamic_cast<JPetGeantEventPack* const>(fEvent)){

        addEvent(mcEventPack);

        if (activityIndex > abs(fMinTime*kSimulatedActivity*pow(10,-6))){
            saveHits();
            activityIndex = 0;
        } else {
            activityIndex++;
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


void JPetGeantParser::addEvent(JPetGeantEventPack* evPack) 
{



    bool isRecPrompt = false;
    bool isSaved2g[2] = {false, false};
    bool isSaved3g[3] =  {false, false, false};

    float enePrompt = 0;
    float ene2g[2] = {0., 0.};
    float ene3g[3] =  {0., 0., 0.};



    bool isGenPrompt = evPack->GetEventInformation()->GetPromptGammaGen();
    bool isGen2g = evPack->GetEventInformation()->GetTwoGammaGen();
    bool isGen3g = evPack->GetEventInformation()->GetThreeGammaGen();


    // first adjust all hits in single event to time window scheme
    std::unique_ptr<TRandom3> random(new TRandom3(0));
    timeShift = random->Uniform(fMinTime,fMaxTime);

     //std::cout << timeShift << std::endl;

    for ( uint i=0; i <evPack->GetNumberOfHits(); i++){

        // translate geantHit -> JPetMCHit
        JPetGeantScinHits* geantHit = evPack->GetHit(i);
        JPetMCHit mcHit = JPetMCHit(
                0,//UInt_t MCDecayTreeIndex,
                0,//UInt_t MCVtxIndex,
                geantHit->GetEneDepos(), //  keV 
                geantHit->GetTime(),   //  ps   
                geantHit->GetHitPosition(),
                geantHit->GetPolarizationIn(),
                geantHit->GetMomentumIn()
                );

        JPetScin scin =  getParamBank().getScintillator(geantHit->GetScinID()); 
        mcHit.setScintillator(scin);
        //JPetScin::ScinDimensions size = scin.getScinSize();
        //printf("scin size %f \n",size.fHeight);

        fStoredMCHits.push_back(mcHit);
        fillHistoMCGen(mcHit);


        // create reconstructed hit and add all smearings        
        JPetHit  recHit =  reconstructHit(mcHit);
        // add criteria for possible rejection of reconstructed events (e.g. E>50 keV)

        if (isHitReconstructed(recHit)) 
        {
            fStoredHits.push_back(recHit);

            // identify generated hits        
            if( geantHit->GetGenGammaMultiplicity() == 1)  
            {
                isRecPrompt = true;
                enePrompt = recHit.getEnergy();
            }

            if( geantHit->GetGenGammaMultiplicity() == 2)
            {
                isSaved2g[ geantHit->GetGenGammaIndex()-1] = true;
                ene2g[ geantHit->GetGenGammaIndex()-1] = recHit.getEnergy();
            }

            if( geantHit->GetGenGammaMultiplicity() == 3)
            {
                isSaved3g[ geantHit->GetGenGammaIndex()-1] = true;
                ene3g[ geantHit->GetGenGammaIndex()-1] = recHit.getEnergy();
            }

            fillHistoMCRec(recHit);
        }

    }

    bool isRec2g = isSaved2g[0] && isSaved2g[1];
    bool isRec3g = isSaved3g[0] && isSaved3g[1] && isSaved3g[2];

    // fill efficiency histograms        

    fillHistoGenInfo(evPack->GetEventInformation(),isRecPrompt,isRec2g,isRec3g);


     if( isGenPrompt )
     {
         for( int i=0; i<effiHisto_ene_nBin; i++){
          getStatistics().getEffiHisto("effi_prompt_eneDepos")->Fill(isRecPrompt&&
                  ( enePrompt > i*effiHisto_ene_width )
                  , i*effiHisto_ene_width);
         }
     }

     if (isGen2g)
     {
         for( int i=0; i<effiHisto_ene_nBin; i++){
          getStatistics().getEffiHisto("effi_2g_hit_eneDepos")->Fill(isRec2g&&
                  ( ene2g[0] > i*effiHisto_ene_width ) && ( ene2g[1] > i*effiHisto_ene_width)
                  , i*effiHisto_ene_width);
         }

     }

     if (isGen3g)
     {
         for( int i=0; i<effiHisto_ene_nBin; i++){
          getStatistics().getEffiHisto("effi_3g_hit_eneDepos")->Fill(isRec3g&&
                  ( ene3g[0] > i*effiHisto_ene_width ) && ( ene3g[1] > i*effiHisto_ene_width) && (ene3g[2] > i*effiHisto_ene_width)
                  , i*effiHisto_ene_width);
         }

     }

    // add loop processing DecayTree
}


void JPetGeantParser::fillHistoGenInfo(JPetGeantEventInformation* evInfo, bool isRecPrompt, bool isRec2g, bool isRec3g)
{
    bool isGenPrompt = evInfo->GetPromptGammaGen();
    bool isGen2g = evInfo->GetTwoGammaGen();
    bool isGen3g = evInfo->GetThreeGammaGen();


    // general histograms
    getStatistics().getHisto1D("gen_lifetime")->Fill(evInfo->GetLifetime());

    // histograms for prompt gamma
    if(isGenPrompt)
    {
        getStatistics().getHisto1D("gen_hit_multiplicity")->Fill(1);
        getStatistics().getHisto2D("gen_prompt_XY")->Fill(evInfo->GetVtxPromptPositionX(),evInfo->GetVtxPromptPositionY());
        getStatistics().getHisto2D("gen_prompt_XZ")->Fill(evInfo->GetVtxPromptPositionX(),evInfo->GetVtxPromptPositionZ());
        getStatistics().getHisto2D("gen_prompt_YZ")->Fill(evInfo->GetVtxPromptPositionY(),evInfo->GetVtxPromptPositionZ());


        for (Int_t i=0; i<effiMap_nSlice; i++){
            if((-20+effiMap_width*i<evInfo->GetVtxPromptPositionZ()) && (evInfo->GetVtxPromptPositionZ()<-20+effiMap_width*(i+1))) 
            {
                getStatistics().getEffiHisto("effi_prompt_vtx_"+TString::Itoa(i,10))->Fill(
                        isRecPrompt, 
                        evInfo->GetVtxPromptPositionX(),evInfo->GetVtxPromptPositionY());
            }
        }

    }

    // histograms for annihilation 2g 3g 
    if(isGen2g)
    {
        getStatistics().getHisto1D("gen_hit_multiplicity")->Fill(2);

        for (Int_t i=0; i<effiMap_nSlice; i++){
            if((-20+effiMap_width*i<evInfo->GetVtxPositionZ()) && (evInfo->GetVtxPositionZ()<-20+effiMap_width*(i+1))) 
            {
                getStatistics().getEffiHisto("effi_2g_vtx_"+TString::Itoa(i,10))->Fill(
                        isRec2g, 
                        evInfo->GetVtxPositionX(),evInfo->GetVtxPositionY());
            }
        }
    }

    if(isGen3g)
    {
        getStatistics().getHisto1D("gen_hit_multiplicity")->Fill(3);
        for (Int_t i=0; i<effiMap_nSlice; i++){
            if((-20.+effiMap_width*i<evInfo->GetVtxPositionZ()) && (evInfo->GetVtxPositionZ()<-20.+effiMap_width*(i+1))) 
            {
                getStatistics().getEffiHisto("effi_3g_vtx_"+TString::Itoa(i,10))->Fill(
                        isRec3g, 
                        evInfo->GetVtxPositionX(),evInfo->GetVtxPositionY());
            }
        }
    }

    if( isGen2g || isGen3g )
    {
        getStatistics().getHisto2D("gen_XY")->Fill(evInfo->GetVtxPositionX(),evInfo->GetVtxPositionY());
        getStatistics().getHisto2D("gen_XZ")->Fill(evInfo->GetVtxPositionX(),evInfo->GetVtxPositionZ());
        getStatistics().getHisto2D("gen_YZ")->Fill(evInfo->GetVtxPositionY(),evInfo->GetVtxPositionZ());
    }
}


void JPetGeantParser::fillHistoMCGen(JPetMCHit &mcHit)
{
    getStatistics().getHisto1D("gen_hits_z_pos")->Fill(mcHit.getPosZ());
    getStatistics().getHisto2D("gen_hits_xy_pos")->Fill(mcHit.getPosX(),mcHit.getPosY());

    getStatistics().getHisto1D("gen_hit_time")->Fill(mcHit.getTime());
    getStatistics().getHisto1D("gen_hit_eneDepos")->Fill(mcHit.getEnergy());
}

void JPetGeantParser::fillHistoMCRec(JPetHit &recHit)
{
    getStatistics().getHisto1D("hits_z_pos")->Fill(recHit.getPosZ());
    getStatistics().getHisto2D("hits_xy_pos")->Fill(recHit.getPosX(),recHit.getPosY());
    getStatistics().getHisto1D("rec_hit_time")->Fill(recHit.getTime());

    getStatistics().getHisto1D("rec_hit_eneDepos")->Fill(recHit.getEnergy());

}

void JPetGeantParser::saveHits()
{

    //  getStatistics().getHisto1D("hits_per_time_window")->Fill(fStoredMCHits.size());  


    for (const auto& hit : fStoredHits) {
        fOutputEvents->add<JPetHit>(hit);
    }

    for (const auto& mcHit : fStoredMCHits) {
        fOutputEvents->addMCHit<JPetMCHit>(mcHit);
    }

    getStatistics().getHisto1D("hits_per_time_window")->Fill(fStoredHits.size());

    fStoredMCHits.clear();
    fStoredHits.clear();
}

JPetHit JPetGeantParser::reconstructHit(JPetMCHit mcHit)
{
    JPetHit hit = dynamic_cast<JPetHit&>(mcHit);
    hit.setEnergy( addEnergySmearing(mcHit.getEnergy()) );
    // adjust to time window and smear
    hit.setTime( addTimeSmearing( -(mcHit.getTime()-timeShift)  ,mcHit.getEnergy()) );


    auto radius = getParamBank().getScintillator(mcHit.getScintillator().getID()).getBarrelSlot().getLayer().getRadius();
    auto theta = TMath::DegToRad() * getParamBank().getScintillator(mcHit.getScintillator().getID()).getBarrelSlot().getTheta();
    hit.setPosX(radius * std::cos(theta));
    hit.setPosY(radius * std::sin(theta));

    hit.setPosZ( addZHitSmearing(hit.getPosZ()));

    return hit;
}

float JPetGeantParser::addZHitSmearing(float zIn)
{
    std::unique_ptr<TRandom3> random(new TRandom3(0));

    return random->Gaus(zIn,z_resolution);
}

float JPetGeantParser::addEnergySmearing(float eneIn)
{
    // eneIn in keV
    float alpha = 0.044/sqrt(eneIn/1000.);
    std::unique_ptr<TRandom3> random(new TRandom3(0));

    return eneIn + alpha*eneIn*random->Gaus(0,1);
}

float JPetGeantParser::addTimeSmearing(float timeIn, float eneIn)
{
    // eneIn in keV, timeIn in ps
    float time;
    std::unique_ptr<TRandom3> random(new TRandom3(0));

    if ( eneIn > 200 ) {
        time = timeIn + 80*random->Gaus(0,1);
    } else {
        time = timeIn+  80*random->Gaus(0,1)/sqrt(eneIn/270);
    }

    return time;
}


bool JPetGeantParser::isHitReconstructed(JPetHit& hit)
{
    bool isOk = true;
    if( hit.getEnergy() < experimentalThreshold ) isOk = false;

    return isOk;
}
