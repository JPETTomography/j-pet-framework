/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file JPetScopeTask.h
 *  @brief Module for oscilloscope data
 */

#ifndef JPETSCOPETASK_H
#define JPETSCOPETASK_H

#include <vector>
#include <string>
#include <set>

#include "../JPetTask/JPetTask.h"
#include "../JPetRawSignal/JPetRawSignal.h"
#include "../JPetTimeWindow/JPetTimeWindow.h"
#include "../JPetParamBank/JPetParamBank.h"
#include "../JPetParamManager/JPetParamManager.h"

/** @brief Collection of system parameters read from config file.
 *
 * One object per signle configuration + collimator position is created.
 */
typedef struct ScopeConfig {
  
  std::string pName; /**< @brief Config name. */
  int pCollPosition; /**< @brief Collimator position. */
  
  JPetParamBank const* pParamBank; /**< @brief Pointer to JPetParamBank for current configuration.
				    *
				    * @ref JPetParamBank
				    */
  
  JPetPM *pPM1, *pPM2, *pPM3, *pPM4; /**< @ref JPetPM */
  JPetScin *pScin1, *pScin2; /**< @ref JPeScin */
  
  std::string pPrefix1, pPrefix2, pPrefix3, pPrefix4; /**< @brief Oscilloscope ACII files prefixes. */
  
  std::set <std::string> pFiles; /**< @brief Set of files to process. */
  std::set <std::string> :: iterator pIter; /**< @ref pIter */
  
} ScopeConfig;


class JPetWriter;

class JPetScopeTask: public JPetTask
{
public:
  JPetScopeTask(const char * name, const char * description);
  virtual void init(const JPetTaskInterface::Options&);
  virtual void exec();
  virtual void terminate();
  virtual void setWriter(JPetWriter* writer) {
    fWriter = writer;
  }
  void setParamManager(JPetParamManager* paramManager) {
    fParamManager = paramManager;
  }
  const JPetParamBank& getParamBank() {
    return fParamManager->getParamBank();
  }

  void setScopeConfig(const ScopeConfig * config){
    fConfig = config;
  }

  int getTimeWindowIndex(const std::string&  pathAndFileName) const;
  
protected:

  /** @brief Produce JPetRecoSignal from single oscilloscope ASCII file.
   *
   * Functionality of old JPetScopeReader.
   *
   * @param filename oscilloscpe ASCII filename.
   * @return generated JPetRecoSignal
   */
  
  
  JPetWriter* fWriter;
  JPetParamManager* fParamManager;

  const ScopeConfig * fConfig;

};
#endif /*  !JPETSCOPETASK_H */

