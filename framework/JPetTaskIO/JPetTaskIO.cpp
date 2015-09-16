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
fHeader(0)
{
  fTask = new JPetTask();
  assert(fTask);
}

void JPetTaskIO::init(const JPetTaskInterface::Options& opts)
{
  //here we should call some function to parse options
  auto inputFilename = opts.at("inputFile");
  auto outputFilename= opts.at("outputFile");
  createInputObjects(inputFilename.c_str());
  createOutputObjects(outputFilename.c_str());
}
  
void JPetTaskIO::exec() 
{
 JPetTaskInterface::Options emptyOpts;
 fTask->init(emptyOpts); //prepare current task for file
 const auto kEventNum = fReader->getNbOfAllEvents();
// while
 for (auto i = 0; i < kEventNum; i++) {
  fTask->setEvent(&(static_cast<TNamed&>(fReader->getCurrentEvent())));
  fTask->exec();
  fReader->nextEvent();
 }
 //
 //setEvent Bounds
 //processEventsInRange
 fTask->terminate();
}
void JPetTaskIO::terminate()
{
   fWriter->writeHeader( fHeader ); 
   //fWriter->writeObject( getStatsObjects(), "Stats" );

   // rewrite the parametric objects from input file to output file
   //getParamManager().saveParametersToFile(fWriter);
   //getParamManager().clearParameters();
   //   fParamManager.saveParametersToFile( fWriter );
   //   fParamManager.clearParameters();  
   fWriter->closeFile();
   fReader->closeFile();
}

void JPetTaskIO::createInputObjects(const char* inputFilename)
{
  //fInFileName = inputFilename;
  //fInFileName += ".";
  //fInFileName += fInFileSuffix;
  
  // create the JPetReader and load the tree
  fReader = new JPetReader;
  if ( fReader->openFileAndLoadData( inputFilename )) {
    // read the header from the previous analysis stage
    fHeader = fReader->getHeaderClone();
    //fParamManager.readParametersFromFile( fReader );
    //fParamManager->readParametersFromFile(fReader);
    //INFO( Form("Starting %s.", GetName() ) );
  
  } else { 
    ERROR(inputFilename +std::string(": Unable to open the input file"));
    exit(-1);
  }
}
void JPetTaskIO::createOutputObjects(const char* outputFilename)
{
   //fOutFileName = outputFilename;
   //fOutFileName += ".";
   //fOutFileName += fOutFileSuffix;

   fEvent = 0;
   //fWriter = new JPetWriter( fOutFileName.c_str() );
   fWriter = new JPetWriter( outputFilename );

   // call user function before starting processing
   //begin();
}

JPetTaskIO::~JPetTaskIO()
{
  if (fTask) delete fTask;
  if (fWriter) delete fWriter;
  if (fReader) delete fReader;
  if (fHeader) delete fHeader;
}
