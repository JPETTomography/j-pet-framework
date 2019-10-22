/**
 *  @copyright Copyright 2019 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetTMessageHandler.cpp
 */

#include "./JPetTMessageHandler.h"
#include "JPetLoggerInclude.h"
#include <TBufferFile.h>
#include <TSystem.h>
#include <iostream>

JPetTMessageHandler::JPetTMessageHandler() : TMessageHandler("TObject", true) { std::cout << "Handler added" << std::endl; }

JPetTMessageHandler::~JPetTMessageHandler() { std::cout << "Handler removed" << std::endl; }

Bool_t JPetTMessageHandler::Notify()
{
  switch (fMessId)
  {
  case 1001:
    WARNING(gSystem->GetError());
  case 1002:
    ERROR(gSystem->GetError());
    break;
  case 1003:
    ERROR(gSystem->GetError());
    break;
  case 1004:
    ERROR(gSystem->GetError());
    break;
  default:
    ERROR("UNKNOWN ROOT error: " + std::to_string(fMessId));
    break;
  }
  return true;
}
