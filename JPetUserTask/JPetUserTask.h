/**
 *  @copyright Copyright 2017 The J-PET Framework Authors. All rights reserved.
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
#include "../JPetTask/JPetTask.h"
#include "../JPetParamsInterface/JPetParamsInterface.h"
#include "../JPetParams/JPetParams.h"
#include "../JPetStatistics/JPetStatistics.h"
#include "../JPetParamBank/JPetParamBank.h"
#include "../JPetTimeWindow/JPetTimeWindow.h"

/**
 * @brief abstract class that should be used as a main parent class for user tasks
 * The class realizes the  method template pattern:
 * The bool init(const JPetParamsInterface& inOptions),  bool terminate(JPetParamsInterface& outOptions)
 * and bool run()
 * are implemented as non-virtual and inside its body the virtual bool init(), bool terminate() methods
 * and bool exec methods(respectively) are being called.
 * bool init() and bool terminate() methods are ment to be implemented by user in the inherited class.
 *
 * The fParams field is set to inOptions by calling bool init(const JPetParamsInterface& inOptions) method  and its is
 * passed as outOptions while calling bool terminate(JPetParamsInterface& outOptions)
 *
 * The user should implement bool init(), bool exec() and bool terminate() methods in the inherited class.
 */
class JPetUserTask: public JPetTask
{
public:
  explicit JPetUserTask(const char* name = "");
  virtual ~JPetUserTask() {};

  bool init(const JPetParamsInterface& inOptions) override;
  bool run(const JPetDataInterface& inData) override;
  bool terminate(JPetParamsInterface& outOptions) override;

  virtual void setStatistics(std::unique_ptr<JPetStatistics> statistics);
  JPetStatistics& getStatistics();

  virtual void setEvent(TObject* ev);
  const JPetParamBank& getParamBank();

  virtual JPetTimeWindow * getOutputEvents(){return fOutputEvents; }
  
protected:
  virtual bool init() = 0; /// should be implemented in descendent class
  virtual bool exec() = 0; /// should be implemented in descendent class
  virtual bool terminate() = 0; /// should be implemented in descendent class

  TObject* fEvent = 0;
  std::unique_ptr<JPetStatistics> fStatistics = 0;
  JPetParams fParams;
  JPetTimeWindow * fOutputEvents;
};
#endif /*  !JPETUSERTASK_H */
