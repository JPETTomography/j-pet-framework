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
 *  @file JPetTaskStreamIO.cpp
 */

#include "JPetTaskStreamIO/JPetTaskStreamIO.h"

#include "./JPetUserTask/JPetUserTask.h"
#include "./JPetData/JPetData.h"
#include "./JPetOptionsGenerator/JPetOptionsGeneratorTools.h"

JPetTaskStreamIO::JPetTaskStreamIO(const char* name,
                                   const char* in_file_type,
                                   const char* out_file_type):
  JPetTaskIO(name, in_file_type, out_file_type)
{
  if (std::string(out_file_type).empty()) {
    WARNING("JPetTaskStreamIO is not intended to be executed without an output file.");
    fIsOutput = false;
  }
  if (std::string(in_file_type).empty()) {
    WARNING("JPetTaskStreamIO is not intended to be executed without an input file.");
    fIsInput = false;
  }
}

bool JPetTaskStreamIO::run(const JPetDataInterface&)
{
  using namespace jpet_options_tools;
  if (fSubTasks.empty()) {
    ERROR("No subTask set");
    return false;
  }
  if (isInput()) {
    if (!fInputHandler) {
      ERROR("No inputHandler set");
      return false;
    }
  }

  // init all subtasks before any processing
  for (const auto& pTask : fSubTasks) {
    auto subTaskName = pTask->getName();
    if (!pTask->init(fParams)) {
      // if init of any task fails, execution of the task stream makes no sense
      ERROR("Init() of: " + subTaskName + " failed. Aborting execution of the whole task stream. ");
      return false;
    }
  }

  assert(fInputHandler);
  if (!fInputHandler->setEntryRange(fParams.getOptions())) {
    ERROR("An error occured in setEntryRange");
    return false;
  }

  auto lastEvent =  fInputHandler->getLastEntryNumber();
  assert(lastEvent >= 0);

  do{

    if (isProgressBar(fParams.getOptions())) {
      displayProgressBar(getName(), fInputHandler->getCurrentEntryNumber(), lastEvent);
    }

    // subsequently run all subtasks on the same event
    TObject* output_event = &(fInputHandler->getEntry());

    // iterator
    auto subtask_it = fSubTasks.begin();

    while (subtask_it != fSubTasks.end()) {

      auto& current_task = *subtask_it;

      if (!current_task->run(JPetData(*output_event))) {
        ERROR("In run() of: " + current_task->getName() + ". ");
      }

      output_event = dynamic_cast<JPetUserTask*>(current_task.get())->getOutputEvents();

      subtask_it++;
    }

    auto& lastTask = fSubTasks.back();

    if (isOutput()) {
      if (!fOutputHandler->writeEventToFile(lastTask.get())) {
        WARNING("Some problems occured while writing the event to file.");
        return false;
      }
    }

  }while(fInputHandler->nextEntry());

  // terminate all subtasks after all processing
  for (const auto& pTask : fSubTasks) {
    JPetParams subTaskParams;

    bool ok = pTask->terminate(subTaskParams);
    if (!ok) {
      ERROR("In terminate() of:" + pTask->getName() + ". ");
    }
    fParams = mergeWithExtraParams(fParams, subTaskParams);
  }

  return true;
}

JPetTaskStreamIO::~JPetTaskStreamIO()
{
}
