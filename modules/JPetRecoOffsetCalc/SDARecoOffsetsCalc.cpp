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
 *  @file SDARecoOffsetsCalc.cpp
 */

#include "SDARecoOffsetsCalc.h"
#include "../../tools/JPetRecoSignalTools/JPetRecoSignalTools.h"
#include "sstream"
#include <stdlib.h>

//standard constructor from AnalysisModule
SDARecoOffsetsCalc::SDARecoOffsetsCalc(const char* name, const char* description) 
  : JPetTask(name, description),
    fCurrentEventNumber(0)
{
}

//no specific destructor needed
SDARecoOffsetsCalc::~SDARecoOffsetsCalc()
{
}

//Checking how many signals are stored in file and writing it on screen
void SDARecoOffsetsCalc::init(const JPetTaskInterface::Options& /* opts */)
{
  fBadSignals = 0;
}

//used for taking RecoSignals from file, calculating fOffset and saving new
//RecoSignals with fOffset values into new file
void SDARecoOffsetsCalc::exec()
{

  // Cast data from the entry into JPetRecoSignal
  const JPetRecoSignal& signal = (JPetRecoSignal&)(*getEvent());

  //fOffset calculation
  fOffset = JPetRecoSignalTools::calculateOffset(signal);
  
  // if something went wrong with calculating fOffset its value will be equal to badOffset value
  // and save bad signal plot into root file
  if ( fOffset == JPetRecoSignalTools::ERRORS::badOffset ) {
	WARNING( Form("Problem with calculating fOffset for event: %d", fCurrentEventNumber) );
	JPetRecoSignalTools::saveBadSignalIntoRootFile(signal, fBadSignals, "badOffsets.root");
	fBadSignals++;
	fCurrentEventNumber++;
	return;
  }

  //to save Reco signal one needs to copy it to non const variable
  JPetRecoSignal signalWithOffset = signal;

  //setting fOffset of signal
  signalWithOffset.setOffset(fOffset);

  //saving singal into output root file
  fWriter->write(signalWithOffset);

  fCurrentEventNumber++;
}

void SDARecoOffsetsCalc::terminate()
{
  int fEventNb = fCurrentEventNumber;
  double goodPercent = (fEventNb-fBadSignals) * 100.0/fEventNb;
  INFO(
       Form("Amount of signals in input file: %d", fEventNb ) );
  INFO(
       Form("Offset calculation complete \nAmount of bad signals: %d \n %f %% of data is good" , fBadSignals, goodPercent) );
}
