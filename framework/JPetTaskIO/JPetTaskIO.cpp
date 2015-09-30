/**
  *  @copyright Copyright (c) 2014, Wojciech Krzemien
  *  @file JPetTaskIO.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */

#include "JPetTaskIO.h"
#include <cassert>
#include "../JPetWriter/JPetWriter.h"
#include "../JPetReader/JPetReader.h"
#include "../JPetTreeHeader/JPetTreeHeader.h"
#include "../JPetTask/JPetTask.h"
#include "../../framework/JPetHLDReader/JPetHLDReader.h"

#include "../../JPetLoggerInclude.h"



JPetTaskIO::JPetTaskIO():
  fWriter(0),
  fReader(0),
  fHeader(0)
{
}

void JPetTaskIO::init(const JPetTaskOptions::Options& opts)
{
  setOptions(JPetTaskOptions(opts));
  //here we should call some function to parse options
  auto inputFilename = fOptions.getInputFile();
  auto outputFilename = fOptions.getOutputFile();
  createInputObjects(inputFilename);
  createOutputObjects(outputFilename);
}


void JPetTaskIO::exec()
{
  assert(fTask);
  assert(fReader);
  JPetTaskInterface::Options emptyOpts;
  fTask->init(emptyOpts); //prepare current task for file
  auto firstEvent = 0ll;
  auto lastEvent = 0ll;
  setUserLimits(fOptions, firstEvent, lastEvent);
  assert(lastEvent > 0);
  for (auto i = firstEvent; i < lastEvent; i++) {
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

  INFO(Form("Finished processing %s.", "A"));
  fWriter->writeHeader(fHeader);

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
  if (fOptions.getInputFileType() == JPetTaskOptions::kHld ) {
    fReader = new JPetHLDReader;
    treeName = "T";
  } else {
    fReader = new JPetReader;
    treeName = "tree";
  }
  if ( fReader->openFileAndLoadData( inputFilename, treeName )) {
    if (fOptions.getInputFileType() == JPetTaskOptions::kHld ) {
      // create a header to be stored along with the output tree
      fHeader = new JPetTreeHeader(26);

      // add general info to the Tree header
      //fHeader->setBaseFileName(
      //JPetManager::GetManager().getInputFileNames()[0].c_str());

      //// add info about this module to the processing stages' history in Tree header
      //fHeader->addStageInfo(this->GetName(), this->GetTitle(), MODULE_VERSION,
      //JPetManager::GetManager().GetTimeString());

    } else {
      assert(fParamManager);
      fParamManager->readParametersFromFile(dynamic_cast<JPetReader*> (fReader));
      // read the header from the previous analysis stage
      //
      fHeader = dynamic_cast<JPetReader*>(fReader)->getHeaderClone();
      //fParamManager.readParametersFromFile( fReader );
    }
  } else {
    ERROR(inputFilename + std::string(": Unable to open the input file"));
    exit(-1);
  }
}

void JPetTaskIO::createOutputObjects(const char* outputFilename)
{
  fWriter = new JPetWriter( outputFilename );
  fTask->setWriter(fWriter);
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
void JPetTaskIO::setUserLimits(const JPetTaskOptions& opts, long long& firstEvent, long long& lastEvent) const
{
  assert(fReader);
  const auto kLastEvent = opts.getLastEvent();
  const auto kFirstEvent = opts.getFirstEvent();  // not used for a moment
  const auto kEventNum = fReader->getNbOfAllEvents();
  lastEvent = kLastEvent < kEventNum ? kLastEvent : kEventNum;
  firstEvent = kFirstEvent;
  assert(firstEvent <= lastEvent);
}
