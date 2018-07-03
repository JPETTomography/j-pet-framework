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


void JPetOutputHandler::saveOutput(JPetWriter* writer, JPetParamManager& manager)
{
  assert(writer);
  assert(fHeader);
  assert(fStatistics.get());

  writer->writeHeader(fHeader);
  writer->writeCollection(fStatistics->getStatsTable(), "Main Task Stats");
  for (auto it = fSubTasksStatistics.begin(); it != fSubTasksStatistics.end(); it++) {
    if (it->second)
      writer->writeCollection(it->second->getStatsTable(), it->first.c_str());
  }

  //store the parametric objects in the ouptut ROOT file
  manager.saveParametersToFile(
    writer);
  manager.clearParameters();
}

bool JPetOutputHandler::writeEventToFile(JPetWriter* writer, JPetTaskInterface* task)
{
  auto pUserTask = (dynamic_cast<JPetUserTask*>(task));
  auto pOutputEntry = pUserTask->getOutputEvents();
  if (pOutputEntry != nullptr) {
    fWriter->write(*pOutputEntry);
  } else {
    ERROR("No proper timeWindow object returned to save to file, returning from subtask " + task->getName());
    return false;
  }
  return true;
}

bool JPetOutputHandler::createOutputObjects(const char* outputFilename, const jpet_options_tools::OptsStrAny& options, JPetReaderInterface* reader)
{
  fWriter = new JPetWriter( outputFilename );
  assert(fWriter);
  using namespace jpet_options_tools;
  if (FileTypeChecker::getInputFileType(options) == FileTypeChecker::kHldRoot ) {
    // create a header to be stored along with the output tree
    fHeader = new JPetTreeHeader(getRunNumber(options));
    fHeader->setFrameworkVersion(FRAMEWORK_VERSION);
    fHeader->setFrameworkRevision(FRAMEWORK_REVISION);

    // add general info to the Tree header
    fHeader->setBaseFileName(getInputFile(options).c_str());
  } else {
    // read the header from the previous analysis stage
    fHeader = dynamic_cast<JPetReader*>(reader)->getHeaderClone();
  }

  // create an object for storing histograms and counters during processing
  // make_unique is not available in c++11 :(
  std::unique_ptr<JPetStatistics> tmpUnique(new JPetStatistics);
  fStatistics = std::move(tmpUnique);
  //fStatistics = std::make_unique<JPetStatistics>();

  //// add info about this module to the processing stages' history in Tree header
  ////auto task = std::dynamic_pointer_cast<JPetTask>(fTask);
  //for (auto fSubTask = fSubTasks.begin(); fSubTask != fSubTasks.end(); fSubTask++) {
    //auto task = dynamic_cast<JPetUserTask*>((*fSubTask).get());
    //fHeader->addStageInfo(task->getName(), "", 0,
                          //JPetCommonTools::getTimeString());
  //}

  //if (!fSubTasks.empty()) {
    //int i = 0;
    //for (auto fSubTask = fSubTasks.begin(); fSubTask != fSubTasks.end(); fSubTask++) {
      //auto task = dynamic_cast<JPetUserTask*>(fSubTask->get());
      //std::string subtaskStatisticsName = task->getName()
                                          //+ std::string(" subtask ")
                                          //+ std::to_string(i)
                                          //+ std::string(" stats");
      //fSubTasksStatistics[subtaskStatisticsName] = std::move(std::unique_ptr<JPetStatistics>(new JPetStatistics(*fStatistics)));
      //task->setStatistics(fSubTasksStatistics[subtaskStatisticsName].get());
      //i++;
    //}
  //} else {
    //WARNING("the subTask does not exist, so JPetStatistics not passed to it");
    ////return false;
  //}
  return true;
}
