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
#include <cassert>
#include "../JPetReader/JPetReader.h"
#include "../JPetTreeHeader/JPetTreeHeader.h"
#include "../JPetTask/JPetTask.h"
#include "../JPetHLDReader/JPetHLDReader.h"
#include "../JPetCommonTools/JPetCommonTools.h"

#include "../JPetLoggerInclude.h"


JPetTaskIO::JPetTaskIO():
  fTask(0),
  fEventNb(-1),
  fWriter(0),
  fReader(0),
  fHeader(0),
  fStatistics(0),
  fAuxilliaryData(0),
  fParamManager(0)
{
}

void JPetTaskIO::init(const JPetOptions::Options& opts)
{
  setOptions(JPetOptions(opts));
  std::string inputFilename(fOptions.getInputFile());
  std::string outputPath(fOptions.getOutputPath());
  auto outputFilename = outputPath + std::string(fOptions.getOutputFile());
  createInputObjects(inputFilename.c_str());
  createOutputObjects(outputFilename.c_str());
}


void JPetTaskIO::exec()
{
  assert(fTask);
  assert(fReader);
  assert(fParamManager);
  fTask->setParamManager(fParamManager);
  JPetTaskInterface::Options emptyOpts;
  fTask->init(emptyOpts); //prepare current task for file
  auto totalEvents = 0ll;
  if (fReader) {
    totalEvents = fReader->getNbOfAllEvents();
  } else {
    WARNING("no JPETReader set totalEvents set to -1");
    totalEvents = -1;
  }
  auto firstEvent = 0ll;
  auto lastEvent = 0ll;
  setUserLimits(fOptions, totalEvents,  firstEvent, lastEvent);
  assert(lastEvent >= 0);
  for (auto i = firstEvent; i <= lastEvent; i++) {
    fTask->setEvent(&(static_cast<TNamed&>(fReader->getCurrentEvent())));
    if (fOptions.isProgressBar()) {
      displayProgressBar(i, lastEvent);
    }
    fTask->exec();
    fReader->nextEvent();
  }
  fTask->terminate();
}

void JPetTaskIO::terminate()
{
  assert(fReader);
  assert(fWriter);
  assert(fHeader);
  assert(fStatistics);
  assert(fAuxilliaryData);

  fWriter->writeHeader(fHeader);

  fWriter->writeObject(fStatistics->getHistogramsTable(), "Stats");

  fWriter->writeObject(fAuxilliaryData, "Auxilliary Data");

  // store the parametric objects in the ouptut ROOT file
  getParamManager().saveParametersToFile(
    fWriter);
  getParamManager().clearParameters();

  fWriter->closeFile();
  fReader->closeFile();

}
void JPetTaskIO::addSubTask(JPetTaskInterface* subtask)
{
  fTask = dynamic_cast<JPetTask*>(subtask);
}
JPetTask* JPetTaskIO::getSubTask() const
{
  return fTask;
}

void JPetTaskIO::setOptions(const JPetOptions& opts)
{
  fOptions = opts;
}
void JPetTaskIO::setParamManager(JPetParamManager* paramManager)
{
  DEBUG("JPetTaskIO");
  fParamManager = paramManager;
}

JPetParamManager& JPetTaskIO::getParamManager()
{
  DEBUG("JPetTaskIO");
  static JPetParamManager NullManager(true);
  if (fParamManager) {
    DEBUG("JPetParamManger returning normal parammanager");
    return *fParamManager;
  } else {
    DEBUG("JPetParamManger returning NullManager ");
    return NullManager;
  }
}

void JPetTaskIO::createInputObjects(const char* inputFilename)
{
  auto treeName = "";
  if (fOptions.getInputFileType() == JPetOptions::kHld ) {
    fReader = new JPetHLDReader;
    treeName = "T";
  } else {
    fReader = new JPetReader;
    treeName = "tree";
  }
  if ( fReader->openFileAndLoadData( inputFilename, treeName )) {
    if (fOptions.getInputFileType() == JPetOptions::kHld ) {
      // create a header to be stored along with the output tree
      fHeader = new JPetTreeHeader(fOptions.getRunNumber());

      // add general info to the Tree header
      fHeader->setBaseFileName(fOptions.getInputFile());

    } else {
      assert(fParamManager);
      fParamManager->readParametersFromFile(dynamic_cast<JPetReader*> (fReader));
      // read the header from the previous analysis stage
      //
      fHeader = dynamic_cast<JPetReader*>(fReader)->getHeaderClone();
      //fParamManager.readParametersFromFile( fReader );
    }
    // create an object for storing histograms and counters during processing
    fStatistics = new JPetStatistics();

    // read the Auxilliary data from input file
    // or create it if it was non-existent
    fAuxilliaryData = dynamic_cast<JPetAuxilliaryData*>(fReader->getObjectFromFile("Auxilliary Data"));

    // add info about this module to the processing stages' history in Tree header
    fHeader->addStageInfo(fTask->GetName(), fTask->GetTitle(), 0,
                          JPetCommonTools::getTimeString());

  } else {
    ERROR(inputFilename + std::string(": Unable to open the input file or load the tree"));
    exit(-1);
  }
}

void JPetTaskIO::createOutputObjects(const char* outputFilename)
{
  fWriter = new JPetWriter( outputFilename );
  assert(fWriter);
  if (fTask) {
    fTask->setWriter(fWriter);
    if (!fAuxilliaryData) {
      fAuxilliaryData = new JPetAuxilliaryData();
    }
    fTask->setStatistics(fStatistics);
    fTask->setAuxilliaryData(fAuxilliaryData);
  } else {
    WARNING("the subTask does not exist, so Write was not passed to it");
  }
}


void JPetTaskIO::displayProgressBar(int currentEventNumber, int numberOfEvents) const
{
  return fProgressBar.display(currentEventNumber, numberOfEvents);
}


const JPetParamBank& JPetTaskIO::getParamBank()
{
  DEBUG("from JPetTaskIO");
  assert(fParamManager);
  return fParamManager->getParamBank();
}

JPetTaskIO::~JPetTaskIO()
{
  if (fTask) {
    delete fTask;
    fTask = 0;
  }
  if (fWriter) {
    delete fWriter;
    fWriter = 0;
  }
  if (fReader) {
    delete fReader;
    fReader = 0;
  }
  if (fStatistics) {
    delete fStatistics;
    fStatistics = 0;
  }
  if (fAuxilliaryData) {
    delete fAuxilliaryData;
    fAuxilliaryData = 0;
  }

}


/// Sets values of firstEvent and lastEvent based on user options opts and total number of events from JPetReader
// if the totEventsFromReader is less than 0, than first and last are set to -1.
void JPetTaskIO::setUserLimits(const JPetOptions& opts, const long long kTotEventsFromReader, long long& first, long long& last) const
{
  const auto kLastEvent = opts.getLastEvent();
  const auto kFirstEvent = opts.getFirstEvent();
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
  assert(first >= 0);
  assert(last >= 0);
  assert(first <= last);
}
