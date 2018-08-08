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
#include "JPetTask/JPetTask.h"
#include "JPetParams/JPetParams.h"
#include "JPetStatistics/JPetStatistics.h"
#include "JPetTimeWindowMC/JPetTimeWindowMC.h"
#include "JPetParamBank/JPetParamBank.h"
#include "JPetTimeWindow/JPetTimeWindow.h"

/**
 * @brief abstract class that should be used as a main parent class for user tasks
 * The class realizes the  method template pattern:
 * The bool init(const JPetParams& inOptions),  bool terminate(JPetParams& outOptions)
 * and bool run()
 * are implemented as non-virtual and inside its body the virtual bool init(), bool terminate() methods
 * and bool exec methods(respectively) are being called.
 * bool init() and bool terminate() methods are ment to be implemented by user in the inherited class.
 *
 * The fParams field is set to inOptions by calling bool init(const JPetParams& inOptions) method  and its is
 * passed as outOptions while calling bool terminate(JPetParams& outOptions)
 *
 * The user should implement bool init(), bool exec() and bool terminate() methods in the inherited class.
 */
class JPetUserTask: public JPetTask
{
public:
  explicit JPetUserTask(const char* name = "");
  virtual ~JPetUserTask() {};

  bool init(const JPetParams& inOptions) override;
  bool run(const JPetDataInterface& inData) override; /// This function cleans the fOutputEvents array before starting the execution.
  bool terminate(JPetParams& outOptions) override;

  virtual void setStatistics(JPetStatistics* statistics);
  JPetStatistics& getStatistics();

  virtual void setEvent(TObject* ev);
  const JPetParamBank& getParamBank();
  jpet_options_tools::OptsStrAny getOptions() const;
  virtual JPetTimeWindow* getOutputEvents();

protected:
  virtual bool init() = 0; /// should be implemented in descendent class
  virtual bool exec() = 0; /// should be implemented in descendent class
  virtual bool terminate() = 0; /// should be implemented in descendent class

  void clearOutputEvents();  /// It clears the JPetTimeWindow array assigned  to fOutputEvents.

  TObject* fEvent = 0;
  JPetStatistics* fStatistics = 0;
  JPetParams fParams;
  JPetTimeWindow* fOutputEvents = 0;
};
#endif /* !JPETUSERTASK_H */
