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

#include "../../JPetLoggerInclude.h"

JPetTaskIO::JPetTaskIO():
  fWriter(0),
  fReader(0),
  fHeader(0),
  fTask(0)
{
}

void JPetTaskIO::init(const JPetTaskInterface::Options& opts)
{
  //here we should call some function to parse options
  auto inputFilename = opts.at("inputFile");
  auto outputFilename = opts.at("outputFile");
  createInputObjects(inputFilename.c_str());
  createOutputObjects(outputFilename.c_str());
}

void JPetTaskIO::exec()
{
  assert(fTask);
  assert(fReader);
  JPetTaskInterface::Options emptyOpts;
  fTask->init(emptyOpts); //prepare current task for file
  const auto kEventNum = fReader->getNbOfAllEvents();
  for (auto i = 0; i < kEventNum; i++) {
    fTask->setEvent(&(static_cast<TNamed&>(fReader->getCurrentEvent())));
    manageProgressBar(i, kEventNum);
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
  fWriter->writeHeader( fHeader );

  // rewrite the parametric objects from input file to output file
  //getParamManager().saveParametersToFile(fWriter);
  //getParamManager().clearParameters();
  //   fParamManager.saveParametersToFile( fWriter );
  //   fParamManager.clearParameters();
  fWriter->closeFile();
  fReader->closeFile();
  std::cout <<"or there?" <<std::endl;
}

void JPetTaskIO::createInputObjects(const char* inputFilename)
{
  fReader = new JPetReader;
  if ( fReader->openFileAndLoadData( inputFilename )) {
    // read the header from the previous analysis stage
    fHeader = fReader->getHeaderClone();
    //fParamManager.readParametersFromFile( fReader );
    //fParamManager->readParametersFromFile(fReader);
  } else {
    ERROR(inputFilename + std::string(": Unable to open the input file"));
    exit(-1);
  }
}
void JPetTaskIO::createOutputObjects(const char* outputFilename)
{
  fWriter = new JPetWriter( outputFilename );
}

void JPetTaskIO::manageProgressBar(long long done, long long end)
{
    printf("\r[%6.4f%% %%]", setProgressBar(done, end));
}

float JPetTaskIO::setProgressBar(int currentEventNumber, int numberOfEvents)
{
  return ( ((float)currentEventNumber) / numberOfEvents ) * 100;
}

JPetTaskIO::~JPetTaskIO()
{
  if (fTask) delete fTask;
  if (fWriter) delete fWriter;
  if (fReader) delete fReader;
}
