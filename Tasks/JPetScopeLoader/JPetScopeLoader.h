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
 *  @file JPetScopeLoader.h
 *  @brief Module for oscilloscope data
 *  Reads oscilloscope ASCII data and produces JPetRecoSignal structures.
 */

#ifndef _SCOPE_LOADER_MODULE_H_
#define _SCOPE_LOADER_MODULE_H_

#include "../JPetTask/JPetTask.h"

#include <cstddef>
#include <fstream>
#include <string>
#include <set>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include "../JPetTaskIO/JPetTaskIO.h"
#include "../JPetScopeTask/JPetScopeTask.h"
#include "../JPetScopeConfigParser/JPetScopeConfigPOD.h"

class JPetParamBank;
class JPetPM;
class JPetScin;
class JPetTreeHeader;
class JPetWriter;

/** @brief Analysis Module for oscilloscope ASCII files.
 *
 * This module reads oscilloscope ACSII data based on config file passed through command line.
 * Example of using this module is located in workdir/ScopeLoaderExample/ .
 *
 * Please, note that this class overrides the createInputObjects, createOutputObjects
 * and setInputAndOutputFile methods from JPetTaskIO class.
 * The overriden method setInputAndOutputFile is called in the original
 * init from JPetTaskIO.
 */
class JPetScopeLoader: public JPetTaskIO
{
public:
  JPetScopeLoader(std::unique_ptr<JPetScopeTask> task);
  virtual ~JPetScopeLoader();

  virtual bool init(const JPetParamsInterface& opts) override;
  virtual bool run(const JPetDataInterface& inData) override;
  virtual bool terminate(JPetParamsInterface& opts) override;


  virtual void addSubTask(std::unique_ptr<JPetTaskInterface> subTask) override;

  std::map<std::string, int> createInputScopeFileNames(
    const std::string& inputPathToScopeFiles,
    std::map<std::string, int> pmPref2Id
  ) const;
  std::map<std::string, int> getPMPrefixToPMIdMap();
  bool isCorrectScopeFileName(const std::string& filename) const;
  std::string getFilePrefix(const std::string& filename) const;

protected:
  bool createInputObjects(const char*) override;
  bool createOutputObjects(const char*) override;
  /// Method returns (isOK, inputFile, outputFileFullPath, isResetOutputPath) based on the provided options.
  /// if isOK is set to false, that means that an error has occured.
  /// inputFile argument has no meaning, because input files are set based on json file in the createOutputObjects
  /// which ignores this argument
  std::tuple<bool, std::string, std::string, bool> setInputAndOutputFile(const jpet_options_tools::OptsStrAny options) const override;
};

#endif
