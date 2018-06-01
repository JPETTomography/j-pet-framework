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
 *  @file JPetUserTask.h
 */

#ifndef JPETUSERTASK_H
#define JPETUSERTASK_H
#include "JPetParamsInterface/JPetParamsInterface.h"
#include "JPetStatistics/JPetStatistics.h"
#include "JPetTimeWindow/JPetTimeWindow.h"
#include "JPetParamBank/JPetParamBank.h"
#include "JPetParams/JPetParams.h"
#include "JPetTask/JPetTask.h"

/**
 * @brief Abstract class that should be used as a main parent class for user tasks
 *
 * The class realizes the  method template pattern:
 * - bool init(const JPetParamsInterface& inOptions)
 * - bool terminate(JPetParamsInterface& outOptions)
 * - bool run()
 * are implemented as non-virtual and inside its body the virtual
 * - bool init()
 * - bool terminate()
 * - bool exec
 * methods (respectively) are being called.
 * bool init() and bool terminate() methods are ment to be implemented
 * by user in the inherited class. The fParams field is set to inOptions
 * by calling bool init(const JPetParamsInterface& inOptions) method and its is
 * passed as outOptions while calling bool terminate(JPetParamsInterface& outOptions)
 */
class JPetUserTask: public JPetTask
{
public:
  explicit JPetUserTask(const char* name = "");
  virtual ~JPetUserTask() {};

  bool init(const JPetParamsInterface& inOptions) override;
  bool run(const JPetDataInterface& inData) override;
  bool terminate(JPetParamsInterface& outOptions) override;
  JPetStatistics& getStatistics();
  virtual void setStatistics(JPetStatistics* statistics);
  virtual void setEvent(TObject* ev);
  const JPetParamBank& getParamBank();
  jpet_options_tools::OptsStrAny getOptions() const;
  virtual JPetTimeWindow* getOutputEvents();

protected:
  virtual bool init() = 0;
  virtual bool exec() = 0;
  virtual bool terminate() = 0;

  JPetTimeWindow* fOutputEvents = 0;
  JPetStatistics* fStatistics = 0;
  TObject* fEvent = 0;
  JPetParams fParams;
};
#endif /* !JPETUSERTASK_H */
