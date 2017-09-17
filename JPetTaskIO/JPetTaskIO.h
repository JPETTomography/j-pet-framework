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
#include "../JPetTask/JPetTask.h"
#include "../JPetProgressBarManager/JPetProgressBarManager.h"

#include "../JPetParams/JPetParams.h"

#include <memory>

class JPetWriter;
class JPetReader;
class JPetTreeHeader;
class JPetStatistics;


/**
 * @brief Class representing computing task with input/output operations.
 *
 */
class JPetTaskIO: public JPetTask
{
public:
  JPetTaskIO(const char* name = "");
  virtual bool init(const JPetParamsInterface& inOptions) override;
  virtual bool run(const JPetDataInterface& inData) override;
  virtual bool terminate(JPetParamsInterface& outOptions) override;
  virtual ~JPetTaskIO();
  void setOptions(const JPetParams& opts);

  inline JPetParams getOptions() const
  {
    return fParams;
  }

  void displayProgressBar(int currentEventNumber, int numberOfEvents) const;

protected:
  virtual bool createInputObjects(const char* inputFilename);
  virtual bool createOutputObjects(const char* outputFilename);
  bool setUserLimits(const jpet_options_tools::OptsStrAny& opts, const long long kTotEventsFromReader, long long& first, long long& last) const;

  const JPetParamBank& getParamBank();
  JPetParamManager& getParamManager();

  int fEventNb = -1;
  JPetParams fParams;
  JPetWriter* fWriter = 0;
  JPetReaderInterface* fReader = 0;
  JPetTreeHeader* fHeader = 0;
  std::unique_ptr<JPetStatistics> fStatistics = 0;
  JPetProgressBarManager fProgressBar;
};
#endif /*  !JPETTASKIO_H */
