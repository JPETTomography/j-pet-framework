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

using namespace jpet_options_tools;

JPetGeantParser::JPetGeantParser(const char* name) : JPetUserTask(name) { }

JPetGeantParser::~JPetGeantParser() { }

bool JPetGeantParser::init()
{
  fOutputEvents = new JPetTimeWindow("JPetMCHit");
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
    // first try fill every time window with single generated event
    //  we will deal with many event in time window later


    // getting data loaded by JPetTaskIO::createInputObjectsFromMCGeant 
    if(auto& hitGeantRaw = dynamic_cast<JPetGeantScinHits* const >(fEvent)){
        JPetMCHit hit = JPetMCHit(
                1, // MCDecayTreeIndex,
                1, // MCVtxIndex,
                hitGeantRaw->GetEneDepos(), // Energy,
                hitGeantRaw->GetTime() , // Time,
                hitGeantRaw->GetHitPosition() , // Position
                hitGeantRaw->GetPolarizationIn(),//Polarization,
                hitGeantRaw->GetMomentumIn()  // Momentum
                );
        addHit(hit);

        if(kTmp == 5 ){
            kTmp =0; 
            saveHits();
        } else {
            kTmp++;
        }

  } else {
    return false;
  }

  return true;
}

 


bool JPetGeantParser::terminate()
{
  INFO("Hit parsing ended.");
  return true;
}


void JPetGeantParser::addHit(const JPetMCHit& hit)
{
    fStoredMCHits.push_back(hit);
}

void JPetGeantParser::saveHits()
{
  
  getStatistics().getHisto1D("hits_per_time_window")->Fill(fStoredMCHits.size());  
  for (const auto& hit : fStoredMCHits) {
        fOutputEvents->add<JPetMCHit>(hit);
  }

  fStoredMCHits.clear();
}

