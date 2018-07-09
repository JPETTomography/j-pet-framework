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
 *  @file JPetTask.cpp
 */

#include "./JPetParamManager/JPetParamManager.h"
#include "./JPetTask.h"

JPetTask::JPetTask(const char* name): fName(name){}

void JPetTask::setName(const std::string& name)
{
  fName = name;
}

std::string JPetTask::getName() const
{
  return fName;
}

void JPetTask::addSubTask(std::unique_ptr<JPetTaskInterface> subTask)
{
  fSubTasks.push_back(std::move(subTask));
}

const std::vector<JPetTaskInterface*> JPetTask::getSubTasks() const
{
  std::vector<JPetTaskInterface*> tmp;
  for (auto subtask = fSubTasks.begin(); subtask != fSubTasks.end(); subtask++) {
    tmp.push_back(subtask->get());
  }
  return tmp;
}
