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
 *  @file JPetTaskIO.h
 */

#ifndef JPETTASKIO_H
#define JPETTASKIO_H
#include "../JPetTaskInterface/JPetTaskInterface.h"
#include "../JPetParamManager/JPetParamManager.h"
#include "../JPetStatistics/JPetStatistics.h"
#include "../JPetAuxilliaryData/JPetAuxilliaryData.h"
#include "../JPetOptions/JPetOptions.h"
#include "../JPetTask/JPetTask.h"
#include "../JPetProgressBarManager/JPetProgressBarManager.h"


class JPetWriter;
class JPetReader;
class JPetTreeHeader;
class JPetStatistics;
class JPetAuxilliaryData;
//class JPetTask;


/**
 * @brief Class representing computing task with input/output operations.
 *
 */
class JPetTaskIO: public JPetTaskInterface
{
public:
  JPetTaskIO();
  virtual void init(const JPetOptions::Options& opts);
  virtual void exec();
  virtual void terminate();
  virtual ~JPetTaskIO();
  virtual void addSubTask(JPetTaskInterface* subtask);
  virtual JPetTask* getSubTask() const;

  void setOptions(const JPetOptions& opts);
  inline JPetOptions getOptions() const {
    return fOptions;
  }

  void displayProgressBar(int currentEventNumber, int numberOfEvents) const;

  void setParamManager(JPetParamManager* paramManager);

protected:
  virtual void createInputObjects(const char* inputFilename);
  virtual void createOutputObjects(const char* outputFilename);
  void setUserLimits(const JPetOptions& opts, const long long totEventsFromReader, long long& firstEvent, long long& lastEvent) const;

  const JPetParamBank& getParamBank();
  JPetParamManager& getParamManager();

  JPetTask* fTask;
  int fEventNb;
  JPetOptions fOptions; //options like max num of events, first event, last event, inputFileType, outputFileType
  JPetWriter* fWriter;
  JPetReaderInterface* fReader;
  JPetTreeHeader* fHeader;
  JPetStatistics* fStatistics;
  JPetAuxilliaryData* fAuxilliaryData;
  JPetParamManager* fParamManager;
  JPetProgressBarManager fProgressBar;
};
#endif /*  !JPETTASKIO_H */
