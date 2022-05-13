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
 *  @file JPetTaskIOLoopPerSubTask.h
 */

#include "./JPetTaskIO/JPetTaskIO.h"

#ifndef JPETTASKIOLOOPPERSUBTASK_H
#define JPETTASKIOLOOPPERSUBTASK_H

/**
 * @brief Class representing a stream of computing tasks (subtasks),
 * executed by subsequently processing all events task by task.
 * E.g. all events are first processed by the first subtask, next
 * the results are processed by the second subtask and so on.
 * The intermediate results are saved in the output root files and
 * the subtasks are reading the events from those files.
 *
 * This class only overrides the "run" method of its base JPetTaskIO.
 */
class JPetTaskIOLoopPerSubTask : public JPetTaskIO
{
public:
  JPetTaskIOLoopPerSubTask(const char* name = "", const char* in_file_type = "", const char* out_file_type = "");
  virtual bool run(const JPetDataInterface& inData) override;
  virtual ~JPetTaskIOLoopPerSubTask();
};
#endif /*  !JPETTASKIOLOOPPERSUBTASK_H */
