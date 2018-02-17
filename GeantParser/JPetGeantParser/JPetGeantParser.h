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

#ifndef JPetGeantParser_H
#define JPetGeantParser_H

#include <map>
#include <vector>
#include <JPetUserTask/JPetUserTask.h>
#include <JPetMCHit/JPetMCHit.h>
#include <JPetGeantScinHits/JPetGeantScinHits.h>

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
  bool kFirstTime = true;
  uint kTmp = 0;
//  JPetGeantParserTools::SignalsContainer fAllSignalsInTimeWindow;
//  JPetGeantParserTools fHitTools;
//
//  void fillSignalsMap(const JPetPhysSignal& signal);
  std::vector<JPetMCHit> fStoredMCHits; ///< save MC hits into single time window when it contains enought hits
  void addHit(const JPetMCHit& hit);
  void saveHits();
//  const std::string fTimeWindowWidthParamKey = "JPetGeantParser_TimeWindowWidth_float";


};

#endif 
