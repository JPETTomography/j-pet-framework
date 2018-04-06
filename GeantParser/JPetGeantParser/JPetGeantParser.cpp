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

using namespace jpet_options_tools;

JPetGeantParser::JPetGeantParser(const char* name) : JPetUserTask(name) { }

JPetGeantParser::~JPetGeantParser() { }

bool JPetGeantParser::init()
{

  // create detector map
  std::unique_ptr<JPetGeomMapping> fDetectorMap(new JPetGeomMapping(getParamBank()));

  fOutputEvents = new JPetTimeWindow("JPetHit","JPetMCHit","JPetMCDecayTree");
  auto opts = getOptions();

  getStatistics().createHistogram(   
          new TH1F("hits_per_time_window", 
              "Number of Hits in Time Window", 
              101, -0.5, 100.5 
              ));


  INFO("MC Hit wrapper started.");

  return true;
}

bool JPetGeantParser::exec()
{

    if(auto& mcEventPack = dynamic_cast<JPetGeantEventPack* const>(fEvent)){
        addEvent(mcEventPack);
        // put here also part of code responsible for activity
        // now 1 generated event for single window
        saveHits();
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
    for ( uint i=1; i <evPack->GetNumberOfHits(); i++){
        JPetGeantScinHits* geantHit = evPack->GetHit(i);
        JPetMCHit mcHit = JPetMCHit(
                0,//UInt_t MCDecayTreeIndex,
                0,//UInt_t MCVtxIndex,
                geantHit->GetEneDepos()*1000, // from MeV to  keV 
                geantHit->GetTime()*1000,   // from ns to ps   
                geantHit->GetHitPosition(),
                geantHit->GetPolarizationIn(),
                geantHit->GetMomentumIn()
                );

        JPetScin scin =  getParamBank().getScintillator(geantHit->GetScinID()); 
        mcHit.setScintillator(scin);
        //JPetScin::ScinDimensions size = scin.getScinSize();
        //printf("scin size %f \n",size.fHeight);


        fStoredMCHits.push_back(mcHit);
        // add criteria for possible rejection of reconstructed events (e.g. E>50 keV)
        fStoredHits.push_back(reconstructHit(mcHit));
    }

    // add loop processing DecayTree
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


    fStoredMCHits.clear();
    fStoredHits.clear();
}

JPetHit JPetGeantParser::reconstructHit(JPetMCHit mcHit)
{
    JPetHit hit = dynamic_cast<JPetHit&>(mcHit);
    hit.setEnergy( addEnergySmearing(mcHit.getEnergy()) );
    hit.setTime( addTimeSmearing(mcHit.getTime(),mcHit.getEnergy()) );
    //JPetScin scin = mcHit.getScintillator() ; 
    //hit.setScintillator(scin);
    // can scin returns the center of its position in LAB frame? 
    //hit.setPosX(); // in LargeBarrelAnalysis example this is treated as coordinate in LAB system; while the comment in JPetHit suggest scintillator reference frame - check this

    return hit;
}


float JPetGeantParser::addEnergySmearing(float eneIn)
{
    // eneIn in keV
    float alpha = 0.044/sqrt(eneIn/1000.);
    std::unique_ptr<TRandom3> random(new TRandom3);

    return eneIn + alpha*eneIn*random->Gaus(0,1);
}

float JPetGeantParser::addTimeSmearing(float timeIn, float eneIn)
{
    // eneIn in keV, timeIn in ps
    float time;
    std::unique_ptr<TRandom3> random(new TRandom3);

    if ( eneIn > 200 ) {
        time = timeIn + 80*random->Gaus(0,1);
    } else {
        time = timeIn+  80*random->Gaus(0,1)/sqrt(eneIn/270);
    }

    return time;
}
