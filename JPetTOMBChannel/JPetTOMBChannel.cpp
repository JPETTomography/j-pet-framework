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
 *  @file JPetTOMBChannel.cpp
 */


#include "JPetTOMBChannel.h"

ClassImp(JPetTOMBChannel);

JPetTOMBChannel::JPetTOMBChannel(): fChannel(0), fFEB(NULL), fTRB(NULL), fPM(NULL), fThreshold(-1), fLocalChannelNumber(0), fFEBInputNumber(0)
{
  SetName("JPetTOMBChannel");
}

JPetTOMBChannel::JPetTOMBChannel(unsigned int p_channel): fChannel(p_channel), fFEB(NULL), fTRB(NULL), fPM(NULL), fThreshold(-1), fLocalChannelNumber(0), fFEBInputNumber(0)
{
  SetName("JPetTOMBChannel");
}

JPetTOMBChannel::JPetTOMBChannel(int p_channel): fChannel(p_channel), fFEB(NULL), fTRB(NULL), fPM(NULL), fThreshold(-1), fLocalChannelNumber(0), fFEBInputNumber(0)
{
  if(p_channel < 0) {
    ERROR("p_channel cannot be negative"); //
  }
  SetName("JPetTOMBChannel");
}

JPetTOMBChannel::JPetTOMBChannel(bool isNull): fChannel(0), fFEB(NULL), fTRB(NULL), fPM(NULL), fThreshold(-1), fLocalChannelNumber(0), fFEBInputNumber(0), fIsNullObject(isNull)
{
  SetName("JPetTOMBChannel");
}

JPetTOMBChannel::~JPetTOMBChannel()
{
}

