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
 *  @file JPetGeantParser.h
 */

#ifndef JPETGEANTPARSER_H
#define JPETGEANTPARSER_H

#include <map>
#include <vector>
#include <JPetUserTask/JPetUserTask.h>
#include <JPetMCHit/JPetMCHit.h>
#include <JPetHit/JPetHit.h>
#include <JPetMCDecayTree/JPetMCDecayTree.h>
#include <JPetGeantScinHits/JPetGeantScinHits.h>
#include <JPetGeantEventPack/JPetGeantEventPack.h>
#include <JPetGeomMapping/JPetGeomMapping.h>

class JPetWriter;

#ifdef __CINT__
//when cint is used instead of compiler, override word is not recognized
//nevertheless it's needed for checking if the structure of project is correct
#   define override
#endif

/**
 * @brief      Module responsible for creating JPetMCHit from GEANT MC simulations
 *
 */
class JPetGeantParser: public JPetUserTask
{

public:
  JPetGeantParser(const char* name);
  virtual ~JPetGeantParser();
  virtual bool init() override;
  virtual bool exec() override;
  virtual bool terminate() override;


protected :
  JPetGeomMapping* fDetectorMap; 

  // variables to modify by user
  bool fMakeEffiHisto = false;
  bool fMakeHisto = true;
  double fMaxTime = 0.;
  double fMinTime = -50.e6; // electronic time window 50 micro seconds - true for run 3 
  double kSimulatedActivity = 4.7; //< in MBq; value for run3  
  //double kSimulatedActivity = 9.38; //< in MBq; value for run3  

  float z_resolution = 0.976; // 80ps   12.2  velocity
  double experimentalThreshold = 10; //< in keV

  // constant for histograms
  int effiHisto_ene_nBin = 200;
  double effiHisto_ene_width = 8;

  int effiMap_nSlice = 81;
  float effiMap_width = 0.5; // cm  -20:20 


  // internal variables 
  const std::string kMaxTimeWindowParamKey = "GeantParser_MaxTimeWindow_double";
  const std::string kMinTimeWindowParamKey = "GeantParser_MinTimeWindow_double";
  const std::string kSourceActivityParamKey = "GeantParser_SourceActivity_double";

  bool kFirstTime = true;
  long activityIndex = 0;

  std::vector<JPetMCHit> fStoredMCHits; ///< save MC hits into single time window when it contains enought hits
  std::vector<JPetHit> fStoredHits; ///< save RECONSTRUCTED MC hits into single time window when it contains enought hits

  void processMCEvent(JPetGeantEventPack*);
  void saveHits();


  void bookEfficiencyHistograms();
  void bookBasicHistograms();

  void fillHistoGenInfo(JPetGeantEventInformation*, bool, bool, bool);
  void fillHistoMCGen(JPetMCHit&);
  void fillHistoMCRec(JPetHit&);

};

#endif 
