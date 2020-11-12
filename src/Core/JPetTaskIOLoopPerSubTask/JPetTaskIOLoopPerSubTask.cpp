/**
 *  @copyright Copyright 2020 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetTaskIOLoopPerSubTask.cpp
 */

#include "./JPetTaskIOLoopPerSubTask/JPetTaskIOLoopPerSubTask.h"

#include "./JPetData/JPetData.h"
#include "./JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "./JPetUserTask/JPetUserTask.h"

JPetTaskIOLoopPerSubTask::JPetTaskIOLoopPerSubTask(const char* name, const char* in_file_type, const char* out_file_type)
    : JPetTaskIO(name, in_file_type, out_file_type)
{
}

JPetTaskIOLoopPerSubTask::~JPetTaskIOLoopPerSubTask(){};

bool JPetTaskIO::run(const JPetDataInterface&)
{
  using namespace jpet_options_tools;
  if (fSubTasks.empty())
  {
    ERROR("No subTask set");
    return false;
  }
  if (isInput())
  {
    if (!fInputHandler)
    {
      ERROR("No inputHandler set");
      return false;
    }
  }
  for (const auto& pTask : fSubTasks)
  {
    auto subTaskName = pTask->getName();
    bool isOK = pTask->init(fParams);

    if (!isOK)
    {
      WARNING("In init() of:" + subTaskName + ". run()  and terminate() of this task will be skipped.");
      continue;
    }

    if (isInput())
    {
      assert(fInputHandler);
      bool isProgressBarOn = isProgressBar(fParams.getOptions());
      isOK = fInputHandler->setEntryRange(fParams.getOptions());
      if (!isOK)
      {
        ERROR("Some error occured in setEntryRange");
        return false;
      }
      auto lastEvent = fInputHandler->getLastEntryNumber();
      assert(lastEvent >= 0);
      do
      {
        if (isProgressBarOn)
        {
          displayProgressBar(subTaskName, fInputHandler->getCurrentEntryNumber(), lastEvent);
        }
        JPetData event(fInputHandler->getEntry());
        isOK = pTask->run(event);
        if (!isOK)
        {
          ERROR("In run() of:" + subTaskName + ". ");
          return false;
        }
        if (isOutput())
        {
          if (!fOutputHandler->writeEventToFile(pTask.get()))
          {
            ERROR("Some problems occured, while writing the event to file.");
            return false;
          }
        }
      } while (fInputHandler->nextEntry());
    }
    else
    {
      JPetDataInterface dummyEvent;
      pTask->run(dummyEvent);
    }

    JPetParams subTaskParams;
    isOK = pTask->terminate(subTaskParams);
    if (!isOK)
    {
      ERROR("In terminate() of:" + subTaskName + ". ");
      return false;
    }
    fParams = mergeWithExtraParams(fParams, subTaskParams);
  }
  return true;
}
