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
 *  @file JPetTaskIO.cpp
 */

#include "JPetTaskIO.h"
#include "JPetTaskIOTools.h"
#include <memory>
#include <cassert>
#include "./JPetReader/JPetReader.h"
#include "./JPetTreeHeader/JPetTreeHeader.h"
#include "./JPetTask/JPetTask.h"
#include "./JPetUserTask/JPetUserTask.h"
#include "./JPetCommonTools/JPetCommonTools.h"
#include "./JPetData/JPetData.h"
#include "./JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "./JPetLoggerInclude.h"
#include "./version.h"

using namespace jpet_options_tools;

JPetTaskIO::JPetTaskIO(const char* name,
                       const char* in_file_type,
                       const char* out_file_type):
  JPetTask(name),
  fInFileType(in_file_type),
  fOutFileType(out_file_type),
  fOutFileFullPath(""),
  fResetOutputPath(false)
{
  if (std::string(out_file_type).empty()) {
    fIsOutput = false;
  }
}

void JPetTaskIO::addSubTask(std::unique_ptr<JPetTaskInterface> subTask)
{
  if (dynamic_cast<JPetUserTask*>(subTask.get()) == nullptr) {
    ERROR("JPetTaskIO currently only allows JPetUserTask as subtask");
  }
  fSubTasks.push_back(std::move(subTask));
}


bool JPetTaskIO::init(const JPetParamsInterface& paramsI)
{
  using namespace jpet_options_tools;
  auto params = dynamic_cast<const JPetParams&>(paramsI);
  setOptions(params);
  auto opts = fParams.getOptions();

  bool isOK = false;
  std::string inputFilename;
  std::tie(isOK, inputFilename, fOutFileFullPath, fResetOutputPath) = setInputAndOutputFile(opts);
  if (!isOK) {
    ERROR("Some error occured in setInputAndOutputFile");
    return false;
  }
  if (!createInputObjects(inputFilename.c_str())) {
    ERROR("createInputObjects");
    return false;
  }
  if (isOutput()) {
    if (!createOutputObjects(fOutFileFullPath.c_str())) {
      ERROR("createOutputObjects");
      return false;
    }
  }
  return true;
}

std::tuple<bool, std::string, std::string, bool> JPetTaskIO::setInputAndOutputFile(const OptsStrAny opts) const
{
  /// We cannot remove this method completely and leave the one from JPetTaskIOTools, because it  is overloaded in JPetScopeLoader class.
  return JPetTaskIOTools::setInputAndOutputFile(opts, fResetOutputPath, fInFileType, fOutFileType);
}

bool JPetTaskIO::run(const JPetDataInterface&)
{
  if (fSubTasks.empty()) {
    ERROR("No subTask set");
    return false;
  }
  if (!fReader) {
    ERROR("No reader set");
    return false;
  }
  for (auto fSubTask = fSubTasks.begin(); fSubTask != fSubTasks.end(); fSubTask++) {
    auto pTask = fSubTask->get();
    pTask->init(fParams); //prepare current task for file

    /// setting range of events to loop
    auto totalEntrys = 0ll;
    auto firstEvent = 0ll;
    auto lastEvent = 0ll;
    bool isOK = false;
    std::tie(isOK, totalEntrys, firstEvent, lastEvent) = getEventRange(fParams.getOptions(), fReader.get());
    if (!isOK) {
      ERROR("Some error occured in getEventRange");
      return false;
    }
    assert(lastEvent >= 0);

    /// loop over events
    for (auto i = firstEvent; i <= lastEvent; i++) {

      ///just distraction
      if (isProgressBar(fParams.getOptions())) {
        displayProgressBar(i, lastEvent);
      }

      JPetData event(fReader->getCurrentEntry());
      pTask->run(event);
      if (isOutput()) {
        if (!fOutputHandler->writeEventToFile(pTask)) {
          return false;
        }
      }
      fReader->nextEntry();
    }
    JPetParamsInterface fake_params;
    pTask->terminate(fake_params);
  }
  return true;
}


bool JPetTaskIO::terminate(JPetParamsInterface& output_params)
{
  auto& params = dynamic_cast<JPetParams&>(output_params);
  auto newOpts = JPetTaskIOTools::setOutputOptions(fParams, fResetOutputPath, fOutFileFullPath);
  params = JPetParams(newOpts, params.getParamManagerAsShared());

  if (!fReader) {
    ERROR("fReader set to null");
    return false;
  }
  if (isOutput()) {
    if (!fHeader) {
      ERROR("fHeader set to null");
      return false;
    }
    if (!fStatistics.get()) {
      ERROR("fStatistics set to null");
      return false;
    }
    fOutputHandler->saveAndCloseOutput(getParamManager(), fHeader, fStatistics.get(), fSubTasksStatistics);
  }
  fReader->closeFile();
  return true;
}

void JPetTaskIO::setOptions(const JPetParams& opts)
{
  fParams = opts;
}

JPetParamManager& JPetTaskIO::getParamManager()
{
  DEBUG("JPetTaskIO");
  auto paramManager = fParams.getParamManager();
  static JPetParamManager NullManager(true);
  if (paramManager) {
    DEBUG("JPetParamManger returning normal parammanager");
    return *paramManager;
  } else {
    DEBUG("JPetParamManger returning NullManager ");
    return NullManager;
  }
}

bool JPetTaskIO::createInputObjects(const char* inputFilename)
{
  using namespace jpet_options_tools;
  auto options = fParams.getOptions();
  assert(!fReader);
  fReader = jpet_common_tools::make_unique<JPetReader>() ;
  if (fReader->openFileAndLoadData(inputFilename, JPetReader::kRootTreeName.c_str())) {
    /// For all types of files which has not hld format we assume
    /// that we can read paramBank from the file.
    if (FileTypeChecker::getInputFileType(options) != FileTypeChecker::kHldRoot ) {
      auto paramManager = fParams.getParamManager();
      assert(paramManager);
      if (!paramManager->readParametersFromFile(dynamic_cast<JPetReader*> (fReader.get()))) {
        ERROR("Failed to read paramBank from input file.");
        return false;
      }
      assert(paramManager->getParamBank().getPMsSize() > 0);
    }
  } else {
    ERROR(inputFilename + std::string(": Unable to open the input file or load the tree"));
    return false;
  }
  return true;
}

bool JPetTaskIO::createOutputObjects(const char* outputFilename)
{
  if (!isOutput()) {
    ERROR("isOutput set to false and you are trying to createOutputObjects");
    return false;
  }
  fOutputHandler = jpet_common_tools::make_unique<JPetOutputHandler>(outputFilename);
  using namespace jpet_options_tools;
  auto options = fParams.getOptions();
  if (FileTypeChecker::getInputFileType(options) == FileTypeChecker::kHldRoot ) {
    // create a header to be stored along with the output tree
    fHeader = new JPetTreeHeader(getRunNumber(options));
    fHeader->setFrameworkVersion(FRAMEWORK_VERSION);
    fHeader->setFrameworkRevision(FRAMEWORK_REVISION);

    // add general info to the Tree header
    fHeader->setBaseFileName(getInputFile(options).c_str());
  } else {
    // read the header from the previous analysis stage
    fHeader = dynamic_cast<JPetReader*>(fReader.get())->getHeaderClone();
  }

  fStatistics = jpet_common_tools::make_unique<JPetStatistics>();

  // add info about this module to the processing stages' history in Tree header
  //auto task = std::dynamic_pointer_cast<JPetTask>(fTask);
  for (auto fSubTask = fSubTasks.begin(); fSubTask != fSubTasks.end(); fSubTask++) {
    auto task = dynamic_cast<JPetUserTask*>((*fSubTask).get());
    fHeader->addStageInfo(task->getName(), "", 0,
                          JPetCommonTools::getTimeString());
  }

  if (!fSubTasks.empty()) {
    int i = 0;
    for (auto fSubTask = fSubTasks.begin(); fSubTask != fSubTasks.end(); fSubTask++) {
      auto task = dynamic_cast<JPetUserTask*>(fSubTask->get());
      std::string subtaskStatisticsName = task->getName()
                                          + std::string(" subtask ")
                                          + std::to_string(i)
                                          + std::string(" stats");
      fSubTasksStatistics[subtaskStatisticsName] = std::move(std::unique_ptr<JPetStatistics>(new JPetStatistics(*fStatistics)));
      task->setStatistics(fSubTasksStatistics[subtaskStatisticsName].get());
      i++;
    }
  } else {
    WARNING("the subTask does not exist, so JPetStatistics not passed to it");
    //return false;
  }
  return true;
}

void JPetTaskIO::displayProgressBar(int currentEventNumber, int numberOfEvents) const
{
  return fProgressBar.display(currentEventNumber, numberOfEvents);
}

const JPetParamBank& JPetTaskIO::getParamBank()
{
  DEBUG("from JPetTaskIO");
  auto paramManager = fParams.getParamManager();
  assert(paramManager);
  return paramManager->getParamBank();
}

JPetTaskIO::~JPetTaskIO()
{
}

std::tuple<bool, long long, long long, long long> JPetTaskIO::getEventRange(const jpet_options_tools::OptsStrAny& options, JPetReaderInterface* reader)
{
  auto totalEntrys = 0ll;
  auto firstEvent = 0ll;
  auto lastEvent = 0ll;
  if (fReader) {
    totalEntrys = fReader->getNbOfAllEntries();
  } else {
    WARNING("no JPETReader set totalEntrys set to -1");
    totalEntrys = -1;
  }
  if (!JPetTaskIOTools::setUserLimits(options, totalEntrys,  firstEvent, lastEvent)) {
    ERROR("in setUserLimits");
    return std::make_tuple(false, -1, -1, -1);
  }
  return std::make_tuple(true, totalEntrys, firstEvent, lastEvent);
}

bool JPetTaskIO::isOutput() const
{
  return fIsOutput;
}
