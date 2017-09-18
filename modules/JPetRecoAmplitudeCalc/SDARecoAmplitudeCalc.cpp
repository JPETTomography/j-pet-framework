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
 *  @file SDARecoAmplitudeCalc.cpp
 */

#include "../../tools/JPetRecoSignalTools/JPetRecoSignalTools.h"
#include "SDARecoAmplitudeCalc.h"

SDARecoAmplitudeCalc::SDARecoAmplitudeCalc(const char* name)
  : JPetUserTask(name),
    fBadSignals(0),
    fCurrentEventNumber(0)
{}

SDARecoAmplitudeCalc::~SDARecoAmplitudeCalc() {}

bool SDARecoAmplitudeCalc::init()
{
  INFO(Form("Starting amplitude calculation"));
  fBadSignals = 0;
  return true;
}

bool SDARecoAmplitudeCalc::exec()
{
  if (auto signal = dynamic_cast<const JPetRecoSignal* const>(fEvent)) {
    double amplitude = JPetRecoSignalTools::calculateAmplitude(*signal);
    if (amplitude == JPetRecoSignalTools::ERRORS::badAmplitude) {
      WARNING( Form("Something went wrong when calculating charge for event: %d", fCurrentEventNumber) );
      JPetRecoSignalTools::saveBadSignalIntoRootFile(*signal, fBadSignals, "badAmplitudes.root");
      fBadSignals++;
    } else {
      auto signalWithAmplitude = *signal;
      signalWithAmplitude.setAmplitude(amplitude);
      // @todo: replace by fOutputEvents
      //      fWriter->write(signalWithAmplitude);
    }
    fCurrentEventNumber++;
  }
  return true;
}

bool SDARecoAmplitudeCalc::terminate()
{
  int fEventNb = fCurrentEventNumber;
  double goodPercent = (fEventNb - fBadSignals) * 100.0 / fEventNb;
  INFO(Form("Amplitude calculation complete \nAmount of bad signals: %d \n %f %% of data is good" , fBadSignals, goodPercent) );
  return true;
}
