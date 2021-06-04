/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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

#include "JPetTaskIO/JPetTaskIO.h"
#include "JPetCommonTools/JPetCommonTools.h"
#include "JPetData/JPetData.h"
#include "JPetLoggerInclude.h"
#include "JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "JPetTask/JPetTask.h"
#include "JPetTaskIO/JPetTaskIOTools.h"
#include "JPetTaskIO/version.h"
#include "JPetTreeHeader/JPetTreeHeader.h"
#include "JPetUserTask/JPetUserTask.h"

#include <cassert>
#include <memory>

JPetTaskIO::JPetTaskIO(const char* name, const char* in_file_type, const char* out_file_type)
    : JPetTask(name), fTaskInfo(in_file_type, out_file_type, "", false)
{
  if (std::string(out_file_type).empty())
  {
    fIsOutput = false;
  }
  if (std::string(in_file_type).empty())
  {
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
  if (!isOK)
  {
    ERROR("Some error occured in setInputAndOutputFile, subtask name:" + subTaskName);
    return false;
  }

  if (isInput())
  {
    if (!createInputObjects(inputFilename.c_str()))
    {
      ERROR("createInputObjects with the input file:" + inputFilename);
      ERROR("Subtask name:" + subTaskName);
      return false;
    }
  }
  if (isOutput())
  {
    if (!createOutputObjects(outFileFullPath.c_str()))
    {
      ERROR("createOutputObjects with the output file:" + outFileFullPath);
      ERROR("Subtask name:" + subTaskName);
      return false;
    }
  }
  return true;
}

bool JPetTaskIO::terminate(JPetParams& output_params)
{
  auto subTaskName = getFirstSubTaskName();
  if (isOutput())
  {
    auto newOpts = JPetTaskIOTools::setOutputOptions(fParams, fTaskInfo.fResetOutputPath, fTaskInfo.fOutFileFullPath);
    output_params = JPetParams(newOpts, fParams.getParamManagerAsShared());
  }
  else
  {
    output_params = fParams;
  }

  if (isOutput())
  {
    if (!fHeader)
    {
      ERROR("Tree header is not set,");
      ERROR("Subtask name:" + subTaskName);
      return false;
    }
    if (!fStatistics.get())
    {
      ERROR("Statistics container with histograms is not set.");
      ERROR("Subtask name:" + subTaskName);
      return false;
    }
    fOutputHandler->saveAndCloseOutput(getParamManager(), fHeader, fStatistics.get(), fSubTasksStatistics);
  }
  if (isInput())
  {
    if (!fInputHandler)
    {
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
  if (dynamic_cast<JPetUserTask*>(subTask.get()) == nullptr)
  {
    ERROR("JPetTaskIO currently only allows JPetUserTask as subtask");
  }
  fSubTasks.push_back(std::move(subTask));
}

void JPetTaskIO::displayProgressBar(std::string taskName, int currentEventNumber, int numberOfEvents) const
{
  return fProgressBar.display(taskName, currentEventNumber, numberOfEvents);
}

/**
 * @brief Currently this method passes "StopIteration_bool" option from subTask to fParams if present.
 */
JPetParams JPetTaskIO::mergeWithExtraParams(const JPetParams& oldParams, const JPetParams& extraParams) const
{
  using namespace jpet_options_tools;
  using namespace jpet_options_generator_tools;
  auto oldOpts = oldParams.getOptions();
  auto extraOpts = extraParams.getOptions();
  // @todo this is hardcoded and should be moved somewhere.
  const std::string stopIterationOptName = "StopIteration_bool";
  if (isOptionSet(extraOpts, stopIterationOptName))
  {
    oldOpts[stopIterationOptName] = getOptionValue(extraOpts, stopIterationOptName);
  }
  return JPetParams(oldOpts, oldParams.getParamManagerAsShared());
}

void JPetTaskIO::setParams(const JPetParams& opts) { fParams = opts; }

JPetParams JPetTaskIO::getParams() const { return fParams; }

bool JPetTaskIO::isOutput() const { return fIsOutput; }

bool JPetTaskIO::isInput() const { return fIsInput; }

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
  if (!isOutput())
  {
    ERROR("isOutput set to false and you are trying to createOutputObjects");
    return false;
  }
  fOutputHandler = jpet_common_tools::make_unique<JPetOutputHandler>(outputFilename);
  if (!fOutputHandler)
  {
    ERROR("OutputHandler is not set, cannot creat output file.");
    return false;
  }
  using namespace jpet_options_tools;
  auto options = fParams.getOptions();

  if (file_type_checker::getInputFileType(options) == file_type_checker::kHldRoot ||
      file_type_checker::getInputFileType(options) == file_type_checker::kMCGeant)
  {

    fHeader = new JPetTreeHeader(getRunNumber(options));
    fHeader->setFrameworkVersion(FRAMEWORK_VERSION);
    fHeader->setFrameworkRevision(FRAMEWORK_REVISION);

    // add general info to the Tree header
    fHeader->setBaseFileName(getInputFile(options).c_str());
  }
  else
  {
    if (isInput())
    {
      // read the header from the previous analysis stage
      fHeader = fInputHandler->getHeaderClone();
    }
    else
    {
      ERROR("We are trying to load Tree Header from the input file, and no input is set.");
      return false;
    }
  }

  fStatistics = jpet_common_tools::make_unique<JPetStatistics>();

  // add info about this module to the processing stages' history in Tree header
  for (auto fSubTask = fSubTasks.begin(); fSubTask != fSubTasks.end(); fSubTask++)
  {
    auto task = dynamic_cast<JPetUserTask*>((*fSubTask).get());
    fHeader->addStageInfo(task->getName(), "", 0, JPetCommonTools::getTimeString());
  }

  if (!fSubTasks.empty())
  {
    int i = 0;
    for (auto fSubTask = fSubTasks.begin(); fSubTask != fSubTasks.end(); fSubTask++)
    {
      auto task = dynamic_cast<JPetUserTask*>(fSubTask->get());
      std::string subtaskStatisticsName = task->getName() + std::string(" subtask ") + std::to_string(i) + std::string(" stats");
      fSubTasksStatistics[subtaskStatisticsName] = std::move(jpet_common_tools::make_unique<JPetStatistics>(*fStatistics));
      task->setStatistics(fSubTasksStatistics[subtaskStatisticsName].get());
      i++;
    }
  }
  else
  {
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
  if (paramManager)
  {
    DEBUG("JPetParamManger returning normal parammanager");
    return *paramManager;
  }
  else
  {
    DEBUG("JPetParamManger returning NullManager ");
    return NullManager;
  }
}

std::string JPetTaskIO::getFirstSubTaskName() const
{
  std::string subTaskName;
  auto subtasks = getSubTasks();
  if (subtasks.size() > 0)
  {
    auto subTask = subtasks[0];
    if (subTask)
    {
      subTaskName = subTask->getName();
    }
  }
  return subTaskName;
}
