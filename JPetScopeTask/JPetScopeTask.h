/**
 * @file JPetScopeReader.h
 * @author Damian Trybek, damian.trybek@uj.edu.pl
 * @copyright Copyright (c) 2015, The J-PET Framework Authors
 * @brief Module for oscilloscope data
 * Produces JPetRecoSignal structures based on ASCII data.
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
  virtual void init(const JPetTaskInterface::Options& opts);
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
  
protected:

  /** @brief Produce JPetRecoSignal from single oscilloscope ASCII file.
   *
   * Functionality of old JPetScopeReader.
   *
   * @param filename oscilloscpe ASCII filename.
   * @return generated JPetRecoSignal
   */
  static JPetRecoSignal generateSignal (const char* filename);
  
  
  JPetWriter* fWriter;
  JPetParamManager* fParamManager;

  const ScopeConfig * fConfig;

};
#endif /*  !JPETSCOPETASK_H */

