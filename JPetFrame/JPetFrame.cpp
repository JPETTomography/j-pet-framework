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
 *  @file JPetFrame.cpp
 */

#include "JPetFrame.h"


JPetFrame::JPetFrame() :
  fId(-1),
  fIsActive(false),
  fStatus(std::string("")),
  fDescription(std::string("")),
  fVersion(-1),
  fCreator_id(-1)
{
  SetName("JPetFrame");
}
  
JPetFrame::JPetFrame(int id, bool isActive, std::string status, std::string description, int version, int creator_id) :
  fId(id),
  fIsActive(isActive),
  fStatus(status),
  fDescription(description),
  fVersion(version),
  fCreator_id(creator_id)
{
  SetName("JPetFrame");
}

JPetFrame::JPetFrame(bool isNull) :
  fId(-1),
  fIsActive(false),
  fStatus(std::string("")),
  fDescription(std::string("")),
  fVersion(-1),
  fCreator_id(-1),
  fIsNullObject(isNull)
{
  SetName("JPetFrame");
}

ClassImp(JPetFrame);
