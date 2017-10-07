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
#include "../JPetReader/JPetReader.h"
#include "../JPetTreeHeader/JPetTreeHeader.h"
#include "../JPetTask/JPetTask.h"
#include "../JPetUserTask/JPetUserTask.h"
#include "../JPetCommonTools/JPetCommonTools.h"
#include "../JPetData/JPetData.h"

#include "../JPetLoggerInclude.h"
#include "../version.h"

using namespace jpet_options_tools;

JPetTaskIO::JPetTaskIO(const char* name): JPetTask(name)
{
}

bool JPetTaskIO::init(const JPetParamsInterface& paramsI)
{
  using namespace jpet_options_tools;
  auto params = dynamic_cast<const JPetParams&>(paramsI);
  setOptions(params);
  auto opts = fParams.getOptions();
  std::string inputFilename(getInputFile(opts));
  std::string outputPath(getOutputPath(opts));
  auto outputFilename = outputPath + std::string(getOutputFile(opts));
  if (!createInputObjects(inputFilename.c_str())) {
    ERROR("createInputObjects");
    return false;
  }
  if (!createOutputObjects(outputFilename.c_str())) {
    ERROR("createOutputObjects");
    return false;
 }
  return true;
}


bool JPetTaskIO::run(const JPetDataInterface& inData)
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

    auto totalEvents = 0ll;
    if (fReader) {
      totalEvents = fReader->getNbOfAllEvents();
    } else {
      WARNING("no JPETReader set totalEvents set to -1");
      totalEvents = -1;
    }
    auto firstEvent = 0ll;
    auto lastEvent = 0ll;
    if (!setUserLimits(fParams.getOptions(), totalEvents,  firstEvent, lastEvent)) {
      ERROR("in setUserLimits");
      return false;
    }
    assert(lastEvent >= 0);
    for (auto i = firstEvent; i <= lastEvent; i++) {

    if (isProgressBar(fParams.getOptions())) {
      displayProgressBar(i, lastEvent);
    }
    (*fSubTask)->terminate(fParams);
  }
  return true;
}


bool JPetTaskIO::terminate(JPetParamsInterface&)
{
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
  if (!fStatistics) {
    ERROR("fStatistics set to null");
    return false;
  }

  assert(fReader);
  assert(fWriter);
  assert(fHeader);
  assert(fStatistics);

  fWriter->writeHeader(fHeader);

  fWriter->writeCollection(fStatistics->getStatsTable(), "Stats");

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
    if (FileTypeChecker::getInputFileType(options) == FileTypeChecker::kHld ) {
      // create a header to be stored along with the output tree
      fHeader = new JPetTreeHeader(getRunNumber(options));
      fHeader->setFrameworkVersion(FRAMEWORK_VERSION);
      fHeader->setFrameworkRevision(FRAMEWORK_REVISION);

      // add general info to the Tree header
      fHeader->setBaseFileName(getInputFile(options));

    } else {
      auto paramManager = fParams.getParamManager();
      assert(paramManager);
      paramManager->readParametersFromFile(dynamic_cast<JPetReader*> (fReader));
      // read the header from the previous analysis stage
      //
      fHeader = dynamic_cast<JPetReader*>(fReader)->getHeaderClone();
      //fParamManager.readParametersFromFile( fReader );
    }
    // create an object for storing histograms and counters during processing
    // make_unique is not available in c++11 :(
    // std::shared_ptr<JPetStatistics> tmpUnique(new JPetStatistics);
    fStatistics = std::make_shared<JPetStatistics>();

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
  if (fSubTask) {
    auto task = dynamic_cast<JPetUserTask*>(fSubTask.get());
    task->setStatistics(fStatistics.get());
  } else {
    WARNING("the subTask does not exist, so JPetStatistics not passed to it");
    return false;
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
