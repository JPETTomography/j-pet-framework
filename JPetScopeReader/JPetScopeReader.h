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
 *  @file JPetScopeReader.h
 *  @brief Module for oscilloscope data
 *  Reads oscilloscope ASCII data and procudes JPetRecoSignal structures.
 */

#ifndef _SCOPE_READER_MODULE_H_
#define _SCOPE_READER_MODULE_H_

#include "../JPetTaskLoader/JPetTaskLoader.h"

#include <cstddef>
#include <fstream>
#include <string>
#include <set>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include "../JPetScopeTask/JPetScopeTask.h"
#include "../JPetScopeConfigParser/JPetScopeConfigPOD.h"

class JPetParamBank;
class JPetPM;
class JPetRecoSignal;
class JPetScin;
class JPetTreeHeader;
class JPetWriter;

/** @brief Analysis Module for oscilloscope ASCII files.
 *
 * This module reads oscilloscope ACSII data based on config file passed through command line.
 * Example of usign this module is located in workdir/ScopeReaderExample/ .
 */
class JPetScopeReader: public JPetTaskLoader {
  
 public:

  JPetScopeReader(JPetScopeTask * task);
  virtual ~JPetScopeReader();

  bool isCorrectScopeFileName(const std::string& filename) const;
  /** @brief Prepare list of input files.
   *
   * Parse config file and prepares parameters bank.
   *
   * @param inputFilename Config file name.
   */
  virtual void createInputObjects(const char* inputFilename);

  /** @brief Required by JPetManager.
   *
   */
  virtual void createOutputObjects(const char* outputFilename);

  /** @brief Perform any preparations for the analysis done by exec().
   *
   * Function containing per event analysis.
   */

  virtual void exec();
  
  /** @brief Return number of events to be processed.
   *
   * @return fEventNb
   */
  virtual long long getEventNb() {return fEventNb;}
  
  /** @brief End analysis.
   */
  virtual void terminate();

  /** @biref Set input file name.
   *
   * @param name input file name.
   */
  void setFileName(const char* name);
  
  /** @brief Create outfile name.
   */
  std::string createOutputFilename();
  
  /** @brief Create writer for new configuration.
   *
   * When processing events for new configuration new output file is created.
   */
  void createNewWriter();

  virtual void init(const JPetOptions::Options& opts);
  std::vector<std::string> createInputScopeFileNames(const std::string& inputPathToScopeFiles) const;
  
 private:

  long long fEventNb; /**< @brief Number of events to process. */ 
  
  JPetTreeHeader* fHeader; /**< @ref JPetTreeHeader. */ 
  JPetWriter* fWriter; /**< @ref JPetWriter. */

  TString fInFilename; /**< @brief Location of config file. */
  TString fOutFilename; /**< @brief Location of output root file. */

  std::vector <ScopeConfig> fConfigs; /**< @brief Vector of all configurations.
                                       * 
				       * @ref ScopeConfig
				       */

  std::vector <ScopeConfig> :: iterator fIter; /**< @ref fConfigs */

};

#endif
