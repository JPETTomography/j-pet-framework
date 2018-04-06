/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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
  if (dynamic_cast<JPetUserTask*>(subTask.get()) == nullptr)
    ERROR("JPetTaskIO currently only allows JPetUserTask as subtask");
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
  bool resetOutputPath = fResetOutputPath;
  // handle input file path
  std::string inputFilename = getInputFile(opts);
  if ( JPetCommonTools::extractDataTypeFromFileName(inputFilename) != fInFileType ) {
    WARNING(Form("Input file type %s does not match the one provided by the previous module (%s).",
                 fInFileType.c_str(), JPetCommonTools::extractDataTypeFromFileName(inputFilename).c_str()));
  }
  inputFilename = JPetCommonTools::replaceDataTypeInFileName(inputFilename, fInFileType);

  // handle output file path
  auto outFileFullPath = inputFilename;
  if (isOptionSet(opts, "outputPath_std::string")) {
    std::string outputPath(getOutputPath(opts));
    if (!outputPath.empty()) {
      outFileFullPath = outputPath + JPetCommonTools::extractFileNameFromFullPath(getInputFile(opts));
      resetOutputPath = true;
    }
  }
  outFileFullPath = JPetCommonTools::replaceDataTypeInFileName(outFileFullPath, fOutFileType);
  return std::make_tuple(true, inputFilename, outFileFullPath, resetOutputPath);
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

    auto totalEntrys = 0ll;
    if (fReader) {
      totalEntrys = fReader->getNbOfAllEntries();
    } else {
      WARNING("no JPETReader set totalEntrys set to -1");
      totalEntrys = -1;
    }
    auto firstEvent = 0ll;
    auto lastEvent = 0ll;
    if (!setUserLimits(fParams.getOptions(), totalEntrys,  firstEvent, lastEvent)) {
      ERROR("in setUserLimits");
      return false;
    }
    assert(lastEvent >= 0);
    for (auto i = firstEvent; i <= lastEvent; i++) {

      if (isProgressBar(fParams.getOptions())) {
        displayProgressBar(i, lastEvent);
      }
      auto pOutputEntry = (dynamic_cast<JPetUserTask*>(fSubTask->get()))->getOutputEvents();
      if (pOutputEntry != nullptr) {
        pOutputEntry->Clear();
      } else {
        WARNING("No proper timeWindow object returned to clear events");
        //return false;
      }
      JPetData event(fReader->getCurrentEntry());
      fSubTask->get()->run(event);
      pOutputEntry = (dynamic_cast<JPetUserTask*>(fSubTask->get()))->getOutputEvents();
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
  OptsStrAny new_opts;
  if (FileTypeChecker::getInputFileType(fParams.getOptions()) == FileTypeChecker::kHldRoot) {
    jpet_options_generator_tools::setOutputFileType(new_opts, "root");
  }

  if (FileTypeChecker::getInputFileType(fParams.getOptions()) == FileTypeChecker::kMCGeant) {
    jpet_options_generator_tools::setOutputFileType(new_opts, "root");
  }


  if ( jpet_options_tools::getOptionAsInt(fParams.getOptions(), "firstEvent_int") != -1 &&
       jpet_options_tools::getOptionAsInt(fParams.getOptions(), "lastEvent_int") != -1 ) {
    jpet_options_generator_tools::setResetEventRangeOption(new_opts, true);
  }

  if (fResetOutputPath) {
    jpet_options_generator_tools::setOutputPath(new_opts, "");
  }

  jpet_options_generator_tools::setOutputFile(new_opts, fOutFileFullPath);

  params = JPetParams(new_opts, params.getParamManagerAsShared());

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

  assert(fReader);
  assert(fWriter);
  assert(fHeader);
  assert(fStatistics.get());

  fWriter->writeHeader(fHeader);
  fWriter->writeCollection(fStatistics->getStatsTable(), "Main Task Stats");
  for (auto it = fSubTasksStatistics.begin(); it != fSubTasksStatistics.end(); it++) {
    if (it->second)
      fWriter->writeCollection(it->second->getStatsTable(), it->first.c_str());
  }


  //store the parametric objects in the ouptut ROOT file
  getParamManager().saveParametersToFile(
    fWriter);
  getParamManager().clearParameters();

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


  if ( fReader->openFileAndLoadData(inputFilename, JPetReader::kRootTreeName.c_str())) {
    if (FileTypeChecker::getInputFileType(options) == FileTypeChecker::kHldRoot || 
    FileTypeChecker::getInputFileType(options) == FileTypeChecker::kMCGeant ) {
      // create a header to be stored along with the output tree
      fHeader = new JPetTreeHeader(getRunNumber(options));
      fHeader->setFrameworkVersion(FRAMEWORK_VERSION);
      fHeader->setFrameworkRevision(FRAMEWORK_REVISION);

      // add general info to the Tree header
      fHeader->setBaseFileName(getInputFile(options));

    } else {
      auto paramManager = fParams.getParamManager();
      assert(paramManager);
      if (!paramManager->readParametersFromFile(dynamic_cast<JPetReader*> (fReader))) {
        ERROR("Failed to read paramBank from input file.");
        return false;
      }
      assert(paramManager->getParamBank().getPMsSize() > 0);
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

/// Sets values of firstEvent and lastEvent based on user options opts and total number of events from JPetReader
// if the totEventsFromReader is less than 0, than first and last are set to -1.
bool JPetTaskIO::setUserLimits(const OptsStrAny& opts, const long long kTotEventsFromReader, long long& first, long long& last) const
{
  const auto kLastEvent = getLastEvent(opts);
  const auto kFirstEvent = getFirstEvent(opts);
  if ( kTotEventsFromReader < 1) {
    WARNING("kTotEvetnsFromReader < 1, first and last set to -1");
    first = last = -1;
  } else {
    if ( kFirstEvent < 0) {
      first = 0;
    } else {
      first = kFirstEvent < kTotEventsFromReader ? kFirstEvent : kTotEventsFromReader - 1;
    }
    if (kLastEvent < 0)  {
      last = kTotEventsFromReader - 1;
    } else {
      last = kLastEvent < kTotEventsFromReader ? kLastEvent : kTotEventsFromReader - 1;
    }
  }
  if (first < 0) {
    ERROR("first <0");
    return false;
  }
  if (last < 0) {
    ERROR("last < 0");
    return false;
  }
  if (first > last) {
    ERROR("first > last");
    return false;
  }
  assert(first >= 0);
  assert(last >= 0);
  assert(first <= last);
  return true;
}
