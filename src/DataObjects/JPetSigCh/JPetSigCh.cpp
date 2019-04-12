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
 *  @file JPetSigCh.cpp
 */

#include "JPetSigCh/JPetSigCh.h"

#include <limits>

ClassImp(JPetSigCh);

const float JPetSigCh::kUnset = std::numeric_limits<float>::infinity();

/**
 * Default constructor
 */
JPetSigCh::JPetSigCh()
    : TObject(), fFlag(JPetSigCh::Unknown), fType(JPetSigCh::Leading), fValue(kUnset), fThreshold(kUnset), fThresholdNumber(0), fDAQch(-1)
{
}

/**
 * Constructor
 */
JPetSigCh::JPetSigCh(EdgeType edge, float time)
    : TObject(), fFlag(JPetSigCh::Unknown), fType(edge), fValue(time), fThreshold(kUnset), fThresholdNumber(0), fDAQch(-1)
{
}

/**
 * Destructor
 */
JPetSigCh::~JPetSigCh() {}

/**
 * Get the reconstruction flag
 */
JPetSigCh::RecoFlag JPetSigCh::getRecoFlag() const { return fFlag; }

/**
 * Get the edge type
 */
JPetSigCh::EdgeType JPetSigCh::getType() const { return fType; }

/**
 * Get the value of time in [ps]
 */
float JPetSigCh::getValue() const { return fValue; }

/**
 * Get the value of threshold setting in [mV]
 */
float JPetSigCh::getThreshold() const { return fThreshold; }

/**
 * Get the number of threshold of this Signal Channel.
 * The thresholds are numbered starting from 1 according to ascending order
 * of their corresponding DAQ channels.
 */
unsigned int JPetSigCh::getThresholdNumber() const { return fThresholdNumber; }

/**
 * Get the data acquisition channel
 */
int JPetSigCh::getDAQch() const { return fDAQch; }

/**
 * Get the PM associated with this Signal Channel
 */
const JPetPM& JPetSigCh::getPM() const
{
  if (fPM.GetObject())
  {
    return (JPetPM&)*fPM.GetObject();
  }
  else
  {
    ERROR("No JPetPM slot set, Null object will be returned");
    return JPetPM::getDummyResult();
  }
}

/**
 * Get the FEB associated with this Signal Channel
 */
const JPetFEB& JPetSigCh::getFEB() const
{
  if (fFEB.GetObject())
  {
    return (JPetFEB&)*fFEB.GetObject();
  }
  else
  {
    ERROR("No JPetFEB slot set, Null object will be returned");
    return JPetFEB::getDummyResult();
  }
}

/**
 * Get the TRB associated with this Signal Channel
 */
const JPetTRB& JPetSigCh::getTRB() const
{
  if (fTRB.GetObject())
  {
    return (JPetTRB&)*fTRB.GetObject();
  }
  else
  {
    ERROR("No JPetTRB slot set, Null object will be returned");
    return JPetTRB::getDummyResult();
  }
}

/**
 * Get the TOMBCHannel associated with this Signal Channel
 */
const JPetTOMBChannel& JPetSigCh::getTOMBChannel() const
{
  if (fTOMBChannel.GetObject())
  {
    return (JPetTOMBChannel&)*fTOMBChannel.GetObject();
  }
  else
  {
    ERROR("No JPetTOMBChannel slot set, Null object will be returned");
    return JPetTOMBChannel::getDummyResult();
  }
}

/**
 * A proxy method for quick access to DAQ channel number ignorantly of what a TOMBCHannel is
 */
int JPetSigCh::getChannel() const { return getTOMBChannel().getChannel(); }

/**
 * Set the reconstruction flag with enum
 */
void JPetSigCh::setRecoFlag(JPetSigCh::RecoFlag flag) { fFlag = flag; }

/**
 * Set the edge type for this Signal Channel
 */
void JPetSigCh::setType(JPetSigCh::EdgeType type) { fType = type; }

/**
 * Set the time value for this Signal Channel
 */
void JPetSigCh::setValue(float value) { fValue = value; }

/**
 * Set the threshold setting value [mV] for this Signal Channel
 */
void JPetSigCh::setThreshold(float thrValue) { fThreshold = thrValue; }

/**
 * Set the threshold number (starting form 1) for this Signal Channel
 */
void JPetSigCh::setThresholdNumber(unsigned int thrNumber) { fThresholdNumber = thrNumber; }

/**
 * Set the data acquisition channel number
 */
void JPetSigCh::setDAQch(int daq) { fDAQch = daq; }

/**
 * Set the PM associated with this Signal Channel
 */
void JPetSigCh::setPM(const JPetPM& pm) { fPM = const_cast<JPetPM*>(&pm); }

/**
 * Set the FEB associated with this Signal Channel
 */
void JPetSigCh::setFEB(const JPetFEB& feb) { fFEB = const_cast<JPetFEB*>(&feb); }

/**
 * Set the TRB associated with this Signal Channel
 */
void JPetSigCh::setTRB(const JPetTRB& trb) { fTRB = const_cast<JPetTRB*>(&trb); }

/**
 * Set the TOMBChannel associated with this Signal Channel
 */
void JPetSigCh::setTOMBChannel(const JPetTOMBChannel& channel) { fTOMBChannel = const_cast<JPetTOMBChannel*>(&channel); }

/**
 * Compares two SigChs by their threshold value
 */
bool JPetSigCh::compareByThresholdValue(const JPetSigCh& sigA, const JPetSigCh& sigB) { return sigA.getThreshold() < sigB.getThreshold(); }

/**
 * Compares two SigChs by their threshold numbers
 */
bool JPetSigCh::compareByThresholdNumber(const JPetSigCh& sigA, const JPetSigCh& sigB)
{
  return sigA.getThresholdNumber() < sigB.getThresholdNumber();
}

void JPetSigCh::Clear(Option_t*)
{
  fType = JPetSigCh::Leading;
  fFlag = JPetSigCh::Unknown;
  fValue = 0.0f;
  fThreshold = 0.0f;
  fThresholdNumber = 0;
  fDAQch = -1;
  fPM = NULL;
  fFEB = NULL;
  fTRB = NULL;
  fTOMBChannel = NULL;
}
