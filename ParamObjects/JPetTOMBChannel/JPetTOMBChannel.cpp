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
 *  @file JPetTOMBChannel.cpp
 */

#include "JPetTOMBChannel.h"

ClassImp(JPetTOMBChannel);

JPetTOMBChannel::JPetTOMBChannel()
{
  SetName("JPetTOMBChannel");
}

JPetTOMBChannel::JPetTOMBChannel(unsigned int p_channel): fChannel(p_channel)
{
  SetName("JPetTOMBChannel");
}

JPetTOMBChannel::JPetTOMBChannel(int p_channel): fChannel(p_channel)
{
  if (p_channel < 0) {
    ERROR("p_channel cannot be negative");
  }
  SetName("JPetTOMBChannel");
}

JPetTOMBChannel::JPetTOMBChannel(bool isNull): fIsNullObject(isNull)
{
  SetName("JPetTOMBChannel");
}

JPetTOMBChannel::~JPetTOMBChannel(){}

void JPetTOMBChannel::setFEB(JPetFEB& p_FEB)
{
  fFEB = &p_FEB;
}

void JPetTOMBChannel::setTRB(JPetTRB& p_TRB)
{
  fTRB = &p_TRB;
}

void JPetTOMBChannel::setPM(JPetPM& p_PM)
{
  fPM = &p_PM;
}

void JPetTOMBChannel::setThreshold(float p_threshold)
{
  fThreshold = p_threshold;
}

const JPetFEB& JPetTOMBChannel::getFEB()const
{
  if (fFEB.GetObject()) return (JPetFEB&) * fFEB.GetObject();
  else {
    ERROR("No JPetFEB slot set, Null object will be returned");
    return JPetFEB::getDummyResult();
  }
}

const JPetTRB& JPetTOMBChannel::getTRB()const
{
  if (fTRB.GetObject()) return (JPetTRB&) * fTRB.GetObject();
  else {
    ERROR("No JPetTRB slot set, Null object will be returned");
    return JPetTRB::getDummyResult();
  }
}

const JPetPM& JPetTOMBChannel::getPM()const
{
  if (fPM.GetObject()) return (JPetPM&) * fPM.GetObject();
  else {
    ERROR("No JPetPM slot set, Null object will be returned");
    return JPetPM::getDummyResult();
  }
}

float JPetTOMBChannel::getThreshold()const
{
  return fThreshold;
}

int JPetTOMBChannel::getChannel()const
{
  return fChannel;
}

std::string JPetTOMBChannel::getDescription()const
{
  return m_description;
}

bool JPetTOMBChannel::operator==(const JPetTOMBChannel& channel)
{
  return getChannel() == channel.getChannel();
}

bool JPetTOMBChannel::operator!=(const JPetTOMBChannel& channel)
{
  return getChannel() != channel.getChannel();
}

/**
 * @brief Get the local channel number
 *
 * All thresholds (together on leading and trailing edge) applied to a single PM
 * signal can be ordered starting from 1, with an order corresponding to
 * the ascending order of DAQ channels assigned to the thresholds.
 * Therefore, if there are 4 thresholds applied to each signal edge,
 * the local channel number should be between 1 and 8.
 */
unsigned int JPetTOMBChannel::getLocalChannelNumber() const
{
  return fLocalChannelNumber;
}

void JPetTOMBChannel::setLocalChannelNumber(unsigned int lcn)
{
  fLocalChannelNumber = lcn;
}

/**
 * @brief Get the number of input channel (Numbering starts from 1) of the FEB
 * which corresponds to this TOMB channel.
 */
unsigned int JPetTOMBChannel::getFEBInputNumber() const
{
  return fFEBInputNumber;
}

/**
 * @brief Set the number of input channel (Numbering starts from 1) of the FEB
 * which corresponds to this TOMB channel
 */
void JPetTOMBChannel::setFEBInputNumber(unsigned int fin)
{
  fFEBInputNumber = fin;
}

bool JPetTOMBChannel::isNullObject() const
{
  return fIsNullObject;
}

JPetTOMBChannel& JPetTOMBChannel::getDummyResult()
{
  static JPetTOMBChannel DummyResult(true);
  return DummyResult;
}
