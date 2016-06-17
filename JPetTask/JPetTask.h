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
 *  @file JPetTask.h 
 */

#ifndef JPETTASK_H 
#define JPETTASK_H 
#include "../JPetTaskInterface/JPetTaskInterface.h"
#include "../JPetParamBank/JPetParamBank.h"
#include "../JPetStatistics/JPetStatistics.h"
#include <TNamed.h>

class JPetWriter;

class JPetTask: public JPetTaskInterface, public TNamed
{
 public:
  JPetTask(const char * name="", const char * description="");
  virtual void init(const JPetTaskInterface::Options&);
  virtual void exec();
  virtual void terminate();
  virtual void addSubTask(JPetTaskInterface*) {};
  virtual void setParamManager(JPetParamManager*paramManager);
  virtual void setStatistics(JPetStatistics* statistics);
  virtual void setWriter(JPetWriter*) {};
  virtual void setEvent(TNamed* ev);
  const JPetParamBank& getParamBank();
  JPetStatistics & getStatistics();
  virtual TNamed* getEvent() {return fEvent;}

 protected:
  TNamed* fEvent;
  JPetParamManager* fParamManager;
  JPetStatistics * fStatistics;
  
};
#endif /*  !JPETTASK_H */
