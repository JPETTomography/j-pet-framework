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
 *  @file JPetOutputHandler.cpp
 */

#include "./JPetOutputHandler.h"
#include "./JPetWriter/JPetWriter.h"
#include "./JPetTreeHeader/JPetTreeHeader.h"
#include "./JPetUserTask/JPetUserTask.h"
#include "./version.h"
#include <cassert>

JPetOutputHandler::JPetOutputHandler():fWriter("defaultOutput.root")
{
} 

JPetOutputHandler::JPetOutputHandler(const char* outputFilename): fWriter(outputFilename)
{
}

void JPetOutputHandler::saveOutput(JPetParamManager& manager, JPetTreeHeader* fHeader, JPetStatistics* fStatistics, std::map<std::string, std::unique_ptr<JPetStatistics>>& fSubTasksStatistics)
{
  assert(fHeader);
  assert(fStatistics);

  fWriter.writeHeader(fHeader);
  fWriter.writeCollection(fStatistics->getStatsTable(), "Main Task Stats");
  for (auto it = fSubTasksStatistics.begin(); it != fSubTasksStatistics.end(); it++) {
    if (it->second)
      fWriter.writeCollection(it->second->getStatsTable(), it->first.c_str());
  }
  //store the parametric objects in the ouptut ROOT file
  manager.saveParametersToFile(
    &fWriter);
  manager.clearParameters();
}

bool JPetOutputHandler::writeEventToFile(JPetTaskInterface* task)
{
  assert(task);
  auto pUserTask = (dynamic_cast<JPetUserTask*>(task));
  auto pOutputEntry = pUserTask->getOutputEvents();
  if (pOutputEntry != nullptr) {
    fWriter.write(*pOutputEntry);
  } else {
    ERROR("No proper timeWindow object returned to save to file, returning from subtask " + task->getName());
    return false;
  }
  return true;
}


/// @todo change it!!!
void JPetOutputHandler::saveAndCloseOutput(JPetParamManager& manager, JPetTreeHeader* fHeader, JPetStatistics* fStatistics, std::map<std::string, std::unique_ptr<JPetStatistics>>& fSubTasksStatistics)
{
    saveOutput(manager, fHeader, fStatistics, fSubTasksStatistics);
    fWriter.closeFile();
}
