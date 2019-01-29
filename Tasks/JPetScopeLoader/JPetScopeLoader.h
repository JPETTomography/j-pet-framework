/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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
 */

#ifndef _SCOPE_LOADER_MODULE_H_
#define _SCOPE_LOADER_MODULE_H_

#include "./JPetScopeConfigParser/JPetScopeConfigPOD.h"
#include "./JPetScopeTask/JPetScopeTask.h"
#include <boost/property_tree/ptree.hpp>
#include "./JPetTaskIO/JPetTaskIO.h"
#include "./JPetTask/JPetTask.h"
#include <cstddef>
#include <fstream>
#include <vector>
#include <string>
#include <set>

class JPetParamBank;
class JPetPM;
class JPetScin;
class JPetTreeHeader;
class JPetWriter;

/**
 * @brief Analysis Module for oscilloscope ASCII files.
 *
 * This module reads oscilloscope ACSII data based on config file passed through
 * the command line. Example of using this module is located in
 * workdir/ScopeLoaderExample/
 * Reads oscilloscope ASCII data and produces JPetRecoSignal structures.
 * It plays a role of JPetTaskIO specialized for oscilloscope data.
 * JPetScopeLoader provides to the JPetScopeTask the data wrapped in JPetScopeData,
 * where one 'event' is in form of std::pair<int , std::map<std::string, int>>
 * The first int corresponds to the current TimeWindow index, and the
 * map contains a set of file names corresponding to the signals and (second int)
 * photomultiplier ids bound to given signal.
 *
 * Please, note that this class overrides the createInputObjects, createOutputObjects
 * and setInputAndOutputFile methods from JPetTaskIO class. The overriden method
 * setInputAndOutputFile is called init() in the original JPetTaskIO.
 * Also, init(), run() and terminate() methods are overriden.
 */
class JPetScopeLoader: public JPetTaskIO
{
public:
  JPetScopeLoader(std::unique_ptr<JPetScopeTask> task);
  virtual ~JPetScopeLoader();
  virtual bool init(const JPetParams& opts) override;
  virtual bool run(const JPetDataInterface& inData) override;
  virtual bool terminate(JPetParams& opts) override;
  virtual void addSubTask(std::unique_ptr<JPetTaskInterface> subTask) override;
  static std::map<int, std::map<std::string, int>> groupScopeFileNamesByTimeWindowIndex(
    const std::map<std::string, int>& scopeFileNames);
  static int getTimeWindowIndex(const std::string&  pathAndFileName);
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
  std::tuple<bool, std::string, std::string, bool> setInputAndOutputFile(
    const jpet_options_tools::OptsStrAny options) const override;
};

#endif /* !_SCOPE_LOADER_MODULE_H_ */
