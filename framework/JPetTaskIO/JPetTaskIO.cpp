/**
  *  @copyright Copyright (c) 2014, Wojciech Krzemien
  *  @file JPetTaskIO.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */

#include "JPetTaskIO.h"
#include <cassert>
#include "../JPetReader/JPetReader.h"
#include "../JPetTreeHeader/JPetTreeHeader.h"
#include "../JPetTask/JPetTask.h"
#include "../../framework/JPetHLDReader/JPetHLDReader.h"
#include "../../framework/CommonTools/CommonTools.h"

#include "../../JPetLoggerInclude.h"


JPetTaskIO::JPetTaskIO():
  fTask(0),
  fEventNb(-1),
  fWriter(0),
  fReader(0),
  fHeader(0),
  fStatistics(0),
  fParamManager(0)
{
}

void JPetTaskIO::init(const JPetOptions::Options& opts)
{
  setOptions(JPetOptions(opts));
  auto inputFilename = fOptions.getInputFile();
  auto outputFilename = fOptions.getOutputFile();
  createInputObjects(inputFilename);
  createOutputObjects(outputFilename);
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
    totalEvents - 1;
  }
  auto firstEvent = 0ll;
  auto lastEvent = 0ll;
  setUserLimits(fOptions, totalEvents,  firstEvent, lastEvent);
  assert(lastEvent >= 0);
  for (auto i = firstEvent; i <= lastEvent; i++) {
    fTask->setEvent(&(static_cast<TNamed&>(fReader->getCurrentEvent())));
    if (fOptions.isProgressBar()) {
      manageProgressBar(i, lastEvent);
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

  fWriter->writeHeader(fHeader);

  fWriter->writeObject(fStatistics->getHistogramsTable(), "Stats");

  // store the parametric objects in the ouptut ROOT file
  getParamManager().saveParametersToFile(
    fWriter);
  getParamManager().clearParameters();

  fWriter->closeFile();
  fReader->closeFile();

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
    
    // add info about this module to the processing stages' history in Tree header
    fHeader->addStageInfo(fTask->GetName(), fTask->GetTitle(), 0,
			  CommonTools::getTimeString());
    
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
    fTask->setStatistics(fStatistics);
  } else {
    WARNING("the subTask does not exist, so Write was not passed to it");
  }
}

void JPetTaskIO::manageProgressBar(long long done, long long end)
{
  printf("\r[%6.4f%% %%]", setProgressBar(done, end));
}

float JPetTaskIO::setProgressBar(int currentEventNumber, int numberOfEvents)
{
  return ( ((float)currentEventNumber) / numberOfEvents ) * 100;
}


const JPetParamBank& JPetTaskIO::getParamBank()
{
  return fParamManager->getParamBank();
}

JPetTaskIO::~JPetTaskIO()
{
  if (fTask) delete fTask;
  if (fWriter) delete fWriter;
  if (fReader) delete fReader;
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
