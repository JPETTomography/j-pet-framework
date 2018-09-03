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

#include "./JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "./JPetCommonTools/JPetCommonTools.h"
#include "./JPetTreeHeader/JPetTreeHeader.h"
#include "./JPetUserTask/JPetUserTask.h"
#include "./JPetTask/JPetTask.h"
#include "./JPetData/JPetData.h"
#include "./JPetLoggerInclude.h"
#include "JPetTaskIOTools.h"
#include "JPetTaskIO.h"
#include "./version.h"
#include <cassert>
#include <memory>

JPetTaskIO::JPetTaskIO(const char* name, const char* in_file_type, const char* out_file_type):
  JPetTask(name), fTaskInfo(in_file_type, out_file_type, "", false)
{
  if (std::string(out_file_type).empty()) {
    fIsOutput = false;
  }
  if (std::string(in_file_type).empty()) {
    fIsInput = false;
  }
}

JPetTaskIO::~JPetTaskIO() {}

bool JPetTaskIO::init(const JPetParams& params)
{
  using namespace jpet_options_tools;
  setParams(params);
  auto opts = fParams.getOptions();

  bool isOK = false;
  std::string inputFilename;
  std::string outFileFullPath;
  bool resetOutputPath = false;
  std::tie(isOK, inputFilename, outFileFullPath, resetOutputPath) = setInputAndOutputFile(opts);
  fTaskInfo.fOutFileFullPath = outFileFullPath;
  fTaskInfo.fResetOutputPath = resetOutputPath;

  auto subTaskName = getFirstSubTaskName();
  if (!isOK) {
    ERROR("Some error occured in setInputAndOutputFile, subtask name:" + subTaskName);
    return false;
  }

  if (isInput()) {
    if (!createInputObjects(inputFilename.c_str())) {
      ERROR("createInputObjects with the input file:" + inputFilename);
      ERROR("Subtask name:" + subTaskName);
      return false;
    }
  }
  if (isOutput()) {
    if (!createOutputObjects(outFileFullPath.c_str())) {
      ERROR("createOutputObjects with the output file:" + outFileFullPath);
      ERROR("Subtask name:" + subTaskName);
      return false;
    }
  }
  return true;
}

std::tuple<bool, std::string, std::string, bool> JPetTaskIO::setInputAndOutputFile(const OptsStrAny opts) const
{
  /// We cannot remove this method completely and leave the one from JPetTaskIOTools, because it  is overloaded in JPetScopeLoader class.
  return JPetTaskIOTools::setInputAndOutputFile(opts, fTaskInfo.fResetOutputPath, fTaskInfo.fInFileType, fTaskInfo.fOutFileType);
}

bool JPetTaskIO::run(const JPetDataInterface& data)
{
  return runDirect(data);
  
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
  for (const auto& pTask : fSubTasks) {
    auto subTaskName = pTask->getName();
    bool isOK = false;

    isOK = pTask->init(fParams);
    if (!isOK) {
      WARNING("In init() of:" + subTaskName + ". run()  and terminate() of this task will be skipped.");
      continue;
    }

    if (isInput()) {
      assert(fInputHandler);
      bool isProgressBarOn = isProgressBar(fParams.getOptions());
      isOK = fInputHandler->setEntryRange(fParams.getOptions());
      if (!isOK) {
        ERROR("Some error occured in setEntryRange");
        return false;
      }
      auto lastEvent = fInputHandler->getLastEntryNumber();
      assert(lastEvent >= 0);
      do {
        if (isProgressBarOn) {
          displayProgressBar(subTaskName, fInputHandler->getCurrentEntryNumber(), lastEvent);
        }
        JPetData event(fInputHandler->getEntry());
        isOK = pTask->run(event);
        if (!isOK) {
          ERROR("In run() of:" + subTaskName + ". ");
          return false;
        }
        if (isOutput()) {
          if (!fOutputHandler->writeEventToFile(pTask.get())) {
            ERROR("Some problems occured, while writing the event to file.");
            return false;
          }
        }
      } while (fInputHandler->nextEntry());
    } else {
      JPetDataInterface dummyEvent;
      pTask->run(dummyEvent);
    }

    JPetParams subTaskParams;
    isOK = pTask->terminate(subTaskParams);
    if (!isOK) {
      ERROR("In terminate() of:" + subTaskName + ". ");
      return false;
    }
    fParams = mergeWithExtraParams(fParams, subTaskParams);
  }
  return true;
}


bool JPetTaskIO::runDirect(const JPetDataInterface&)
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
    auto ok = pTask->init(fParams);
    if (!ok) {
      /// @todo: skipping makes no sense in this case, terminate everything
      ERROR("In init() of:" + subTaskName + ". run()  and terminate() of this task will be skipped.");
      continue;
    }
  }

  auto& firstTask = fSubTasks.front();

  auto firstEvent = 0ll;
  auto lastEvent = 0ll;
  bool isOK = false;
  assert(fInputHandler);
  std::tie(isOK, firstEvent, lastEvent) = fInputHandler->getEventRange(fParams.getOptions());
  if (!isOK) {
    ERROR("Some error occured in getEventRange");
        return false;
  }
  assert(lastEvent >= 0);

  for (auto i = firstEvent; i <= lastEvent; i++) {

    // @todo: make progressbar work with the direct chain
    // if (isProgressBar(fParams.getOptions())) {
    //   displayProgressBar(i, lastEvent);
    // }

    // subsequently run all subtasks on the same event

    TObject * output_event = &(fInputHandler->getNextEntry());

    // iterator
    auto subtask_it = fSubTasks.begin();

    bool ok;
    while(subtask_it != fSubTasks.end()){

      auto& current_task = *subtask_it;

      std::cout << static_cast<JPetTimeWindow* const>(output_event)->getNumberOfEvents() <<std::endl;
      
      ok = current_task->run(JPetData(*output_event));

      if (!ok) {
	ERROR("In run() of:" + current_task->getName() + ". ");
      }

      output_event = dynamic_cast<JPetUserTask*>(current_task.get())->getOutputEvents();

      subtask_it++;
    }

    auto& lastTask = fSubTasks.back();
    
    if (isOutput()) {
      if (!fOutputHandler->writeEventToFile(lastTask.get())) {
	WARNING("Some problems occured, while writing the event to file.");
	return false;
      }
    }
    
  }

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

bool JPetTaskIO::terminate(JPetParams& output_params)
{
  auto subTaskName = getFirstSubTaskName();
  if (isOutput()) {
    auto newOpts = JPetTaskIOTools::setOutputOptions(fParams, fTaskInfo.fResetOutputPath, fTaskInfo.fOutFileFullPath);
    output_params = JPetParams(newOpts, fParams.getParamManagerAsShared());
  } else {
    output_params = fParams;
  }

  if (isOutput()) {
    if (!fHeader) {
      ERROR("Tree header is not set,");
      ERROR("Subtask name:" + subTaskName);
      return false;
    }
    if (!fStatistics.get()) {
      ERROR("Statistics container with histograms is not set.");
      ERROR("Subtask name:" + subTaskName);
      return false;
    }
    fOutputHandler->saveAndCloseOutput(getParamManager(), fHeader, fStatistics.get(), fSubTasksStatistics);
  }
  if (isInput()) {
    if (!fInputHandler) {
      ERROR("fInputHandler set to null.");
      ERROR("Subtask name:" + subTaskName);
      return false;
    }
    fInputHandler->closeInput();
  }
  return true;
}

void JPetTaskIO::addSubTask(std::unique_ptr<JPetTaskInterface> subTask)
{
  if (dynamic_cast<JPetUserTask*>(subTask.get()) == nullptr) {
    ERROR("JPetTaskIO currently only allows JPetUserTask as subtask");
  }
  fSubTasks.push_back(std::move(subTask));
}

void JPetTaskIO::displayProgressBar(std::string taskName, int currentEventNumber, int numberOfEvents) const
{
  return fProgressBar.display(taskName, currentEventNumber, numberOfEvents);
}

/**
 * @brief Currently this method passes "stopIteration_bool" option from subTask to fParams if present.
 */
JPetParams JPetTaskIO::mergeWithExtraParams(const JPetParams& oldParams, const JPetParams& extraParams) const
{
  using namespace jpet_options_tools;
  using namespace jpet_options_generator_tools;
  auto oldOpts = oldParams.getOptions();
  auto extraOpts = extraParams.getOptions();
  // @todo this is hardcoded and should be moved somewhere.
  const std::string stopIterationOptName = "stopIteration_bool";
  if (isOptionSet(extraOpts, stopIterationOptName)) {
    oldOpts[stopIterationOptName] = getOptionValue(extraOpts, stopIterationOptName);
  }
  return JPetParams(oldOpts, oldParams.getParamManagerAsShared());
}

void JPetTaskIO::setParams(const JPetParams& opts)
{
  fParams = opts;
}

JPetParams JPetTaskIO::getParams() const
{
  return fParams;
}

bool JPetTaskIO::isOutput() const
{
  return fIsOutput;
}

bool JPetTaskIO::isInput() const
{
  return fIsInput;
}

/**
 * @return (isOK, inputFile, outputFileFullPath, isResetOutputPath) based on provided options.
 * If isOK is set to false, that means that an error has occured.
 */
std::tuple<bool, std::string, std::string, bool> JPetTaskIO::setInputAndOutputFile(const OptsStrAny opts) const
{
  // We cannot remove this method completely and leave the one from JPetTaskIOTools, because it is overloaded in JPetScopeLoader class.
  return JPetTaskIOTools::setInputAndOutputFile(opts, fTaskInfo.fResetOutputPath, fTaskInfo.fInFileType, fTaskInfo.fOutFileType);
}

bool JPetTaskIO::createInputObjects(const char* inputFilename)
{
  fInputHandler = jpet_common_tools::make_unique<JPetInputHandler>();
  return fInputHandler->openInput(inputFilename, fParams);
}

bool JPetTaskIO::createOutputObjects(const char* outputFilename)
{
  if (!isOutput()) {
    ERROR("isOutput set to false and you are trying to createOutputObjects");
    return false;
  }
  fOutputHandler = jpet_common_tools::make_unique<JPetOutputHandler>(outputFilename);
  if (!fOutputHandler) {
    ERROR("OutputHandler is not set, cannot creat output file.");
    return false;
  }
  using namespace jpet_options_tools;
  auto options = fParams.getOptions();

  if (FileTypeChecker::getInputFileType(options) == FileTypeChecker::kHldRoot ||
      FileTypeChecker::getInputFileType(options) == FileTypeChecker::kMCGeant ) {

    fHeader = new JPetTreeHeader(getRunNumber(options));
    fHeader->setFrameworkVersion(FRAMEWORK_VERSION);
    fHeader->setFrameworkRevision(FRAMEWORK_REVISION);

    // add general info to the Tree header
    fHeader->setBaseFileName(getInputFile(options).c_str());
  } else {
    if (isInput()) {
      // read the header from the previous analysis stage
      fHeader = fInputHandler->getHeaderClone();
    } else {
      ERROR("We are trying to load Tree Header from the input file, and no input is set.");
      return false;
    }
  }

  fStatistics = jpet_common_tools::make_unique<JPetStatistics>();

  // add info about this module to the processing stages' history in Tree header
  for (auto fSubTask = fSubTasks.begin(); fSubTask != fSubTasks.end(); fSubTask++) {
    auto task = dynamic_cast<JPetUserTask*>((*fSubTask).get());
    fHeader->addStageInfo(task->getName(), "", 0,
                          JPetCommonTools::getTimeString());
  }

  if (!fSubTasks.empty()) {
    int i = 0;
    for (auto fSubTask = fSubTasks.begin(); fSubTask != fSubTasks.end(); fSubTask++) {
      auto task = dynamic_cast<JPetUserTask*>(fSubTask->get());
      std::string subtaskStatisticsName =
        task->getName() + std::string(" subtask ") + std::to_string(i) + std::string(" stats");
      fSubTasksStatistics[subtaskStatisticsName] = std::move(jpet_common_tools::make_unique<JPetStatistics>(*fStatistics));
      task->setStatistics(fSubTasksStatistics[subtaskStatisticsName].get());
      i++;
    }
  } else {
    WARNING("the subTask does not exist, so JPetStatistics not passed to it");
  }
  return true;
}

const JPetParamBank& JPetTaskIO::getParamBank()
{
  DEBUG("from JPetTaskIO");
  auto paramManager = fParams.getParamManager();
  assert(paramManager);
  return paramManager->getParamBank();
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

std::string JPetTaskIO::getFirstSubTaskName() const
{
  std::string subTaskName;
  auto subtasks = getSubTasks();
  if (subtasks.size() > 0) {
    auto subTask = subtasks[0];
    if (subTask) {
      subTaskName = subTask->getName();
    }
  }
  return subTaskName;
}
