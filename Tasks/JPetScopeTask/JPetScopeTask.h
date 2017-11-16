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

#include <string>
#include <map>

#include "../JPetUserTask/JPetUserTask.h"
#include "../JPetRawSignal/JPetRawSignal.h"
#include "../JPetTimeWindow/JPetTimeWindow.h"
#include "../JPetParamBank/JPetParamBank.h"
#include "../JPetParamManager/JPetParamManager.h"

class JPetWriter;
struct cmpByTimeWindowIndex;

class JPetScopeTask: public JPetTask
{
public:
  JPetScopeTask(const char* name);
  virtual ~JPetScopeTask() {};

  bool init(const JPetParamsInterface& inOptions) override;
  bool run(const JPetDataInterface& inData) override;
  bool terminate(JPetParamsInterface& outOptions) override;

  static int getTimeWindowIndex(const std::string&  pathAndFileName);
  /// getting oscilloscope data full file names to process
  inline std::map<std::string, int> getInputFiles() const
  {
    return fInputFiles;
  }
  inline void setInputFiles(const std::map<std::string, int>& inputFiles)
  {
    fInputFiles = inputFiles;
  }

  virtual void setWriter(JPetWriter* writer)
  {
    fWriter = writer;
  }

  const JPetParamBank& getParamBank();
  virtual void setStatistics(JPetStatistics* statistics);
  JPetStatistics& getStatistics();

  std::multimap<std::string, int, cmpByTimeWindowIndex> getFilesInTimeWindowOrder(const std::map<std::string, int>& inputFiles) const;

protected:
  bool init();
  bool exec();
  bool terminate();

  std::map<std::string, int> fInputFiles;
  JPetWriter* fWriter = 0;
  JPetStatistics* fStatistics = 0;
  JPetParams fParams;
};

struct cmpByTimeWindowIndex {
  bool operator()(const std::string& a, const std::string& b) const
  {
    return JPetScopeTask::getTimeWindowIndex(a) < JPetScopeTask::getTimeWindowIndex(b);
  }
};

#endif /*  !JPETSCOPETASK_H */
