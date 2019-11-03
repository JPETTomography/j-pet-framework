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

#include "JPetLogger/JPetTMessageHandler.h"
#include "JPetLoggerInclude.h"
#include <TBufferFile.h>
#include <TSystem.h>
#include <iostream>

JPetTMessageHandler::JPetTMessageHandler() : TMessageHandler("TObject", true) {}

JPetTMessageHandler::~JPetTMessageHandler() {}
/// TODO: exit execution of the analysis when unrecoverable error occurs.
Bool_t JPetTMessageHandler::Notify()
{
  switch (fMessId)
  {
  case 1001:
    WARNING("ROOT warning: " + std::string(gSystem->GetError()));
    break;
  case 1002:
    ERROR("ROOT error: " + std::string(gSystem->GetError()));
    break;
  case 1003:
    ERROR("ROOT sysError: " + std::string(gSystem->GetError()));
    break;
  case 1004:
    ERROR("ROOT fatalError: " + std::string(gSystem->GetError()));
    break;
  default:
    ERROR("UNKNOWN ROOT message id: " + std::to_string(fMessId) + ", message: " + std::string(gSystem->GetError()));
    break;
  }
  return true;
}
