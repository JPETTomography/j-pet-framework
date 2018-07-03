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
  if (!createOutputObjects(fOutFileFullPath.c_str())) {
    ERROR("createOutputObjects");
    return false;
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
    (*fSubTask)->init(fParams); //prepare current task for file

    /// setting range of events to loop
    auto totalEntrys = 0ll;
    if (fReader) {
      totalEntrys = fReader->getNbOfAllEntries();
    } else {
      WARNING("no JPETReader set totalEntrys set to -1");
      totalEntrys = -1;
    }
    auto firstEvent = 0ll;
    auto lastEvent = 0ll;
    if (!JPetTaskIOTools::setUserLimits(fParams.getOptions(), totalEntrys,  firstEvent, lastEvent)) {
      ERROR("in setUserLimits");
      return false;
    }
    assert(lastEvent >= 0);

    //for (auto i = firstEvent; i <= lastEvent; i++) {

      /////just distraction
      //if (isProgressBar(fParams.getOptions())) {
        //displayProgressBar(i, lastEvent);
      //}
      //auto pUserTask= (dynamic_cast<JPetUserTask*>(fSubTask->get()));

      //auto pOutputEntry = pUserTask->getOutputEvents();
      //if (pOutputEntry != nullptr) {
        //pOutputEntry->Clear();
      //} else {
        //WARNING("No proper timeWindow object returned to clear events");
      //}

      //JPetData event(fReader->getCurrentEntry());

      //fSubTask->get()->run(event);
      //TASK::Event->Clean();
      //TASK::RUN(event)
      //WRITE(EVENT)
      //}

      //fReader->nextEntry();
    //}

    /// loop over events
    for (auto i = firstEvent; i <= lastEvent; i++) {

      ///just distraction
      if (isProgressBar(fParams.getOptions())) {
        displayProgressBar(i, lastEvent);
      }

      JPetData event(fReader->getCurrentEntry());

      fSubTask->get()->run(event);

      auto pUserTask= (dynamic_cast<JPetUserTask*>(fSubTask->get()));
      auto pOutputEntry = pUserTask->getOutputEvents();
      if (pOutputEntry != nullptr) {
        fWriter->write(*pOutputEntry);
      } else {
        ERROR("No proper timeWindow object returned to save to file, returning from subtask " + fSubTask->get()->getName());
        return false;
      }

      fReader->nextEntry();
    }
    
    JPetParamsInterface fake_params;
    (*fSubTask)->terminate(fake_params);
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
  if (!fWriter) {
    ERROR("fWriter set to null");
    return false;
  }
  if (!fHeader) {
    ERROR("fHeader set to null");
    return false;
  }
  if (!fStatistics.get()) {
    ERROR("fStatistics set to null");
    return false;
  }

  saveOutput(fWriter);

  fWriter->closeFile();
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
  fReader = new JPetReader;
  if (fReader->openFileAndLoadData(inputFilename, JPetReader::kRootTreeName.c_str())) {
    /// For all types of files which has not hld format we assume
    /// that we can read paramBank from the file.
    if (FileTypeChecker::getInputFileType(options) != FileTypeChecker::kHldRoot ) {
      auto paramManager = fParams.getParamManager();
      assert(paramManager);
      if (!paramManager->readParametersFromFile(dynamic_cast<JPetReader*> (fReader))) {
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
  fWriter = new JPetWriter( outputFilename );
  assert(fWriter);
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
    fHeader = dynamic_cast<JPetReader*>(fReader)->getHeaderClone();
  }

  // create an object for storing histograms and counters during processing
  // make_unique is not available in c++11 :(
  std::unique_ptr<JPetStatistics> tmpUnique(new JPetStatistics);
  fStatistics = std::move(tmpUnique);
  //fStatistics = std::make_unique<JPetStatistics>();

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
  if (fWriter) {
    delete fWriter;
    fWriter = 0;
  }
  if (fReader) {
    delete fReader;
    fReader = 0;
  }
}

void JPetTaskIO::saveOutput(JPetWriter* writer)
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
  getParamManager().saveParametersToFile(
    writer);
  getParamManager().clearParameters();
}
