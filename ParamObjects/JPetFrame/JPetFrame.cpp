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
 *  @file JPetFrame.cpp
 */

#include "JPetFrame.h"

JPetFrame::JPetFrame() { SetName("JPetFrame"); }

JPetFrame::JPetFrame(int id, bool isActive, std::string status,
  std::string description, int version, int creator_id): fId(id),
  fIsActive(isActive), fStatus(status), fDescription(description),
  fVersion(version), fCreator_id(creator_id)
{
  SetName("JPetFrame");
}

JPetFrame::JPetFrame(bool isNull):
  fIsNullObject(isNull)
{
  SetName("JPetFrame");
}

bool JPetFrame::operator==(const JPetFrame& frame)
{
  return getID() == frame.getID();
}

bool JPetFrame::operator!=(const JPetFrame& frame)
{
  return getID() != frame.getID();
}

int JPetFrame::getID() const
{
  return fId;
}

bool JPetFrame::getIsActive() const
{
  return fIsActive;
}

std::string JPetFrame::getStatus() const
{
  return fStatus;
}

std::string JPetFrame::getDescription() const
{
  return fDescription;
}

int JPetFrame::getVersion() const
{
  return fVersion;
}

int JPetFrame::getCreator() const
{
  return fCreator_id;
}

bool JPetFrame::isNullObject() const
{
  return fIsNullObject;
}

JPetFrame& JPetFrame::getDummyResult()
{
  static JPetFrame DummyResult(true);
  return DummyResult;
}

ClassImp(JPetFrame);
