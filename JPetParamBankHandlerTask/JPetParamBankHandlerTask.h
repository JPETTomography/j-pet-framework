/**
 *  @copyright Copyright 2017 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetParamBankHandlerTask.h
 */

#ifndef JPETPARAMBANKHANDLERTASK_H
#define JPETPARAMBANKHANDLERTASK_H

#include "../JPetTask/JPetTask.h"
#include "../JPetParams/JPetParams.h"
#include "../JPetParamGetterAscii/JPetParamSaverAscii.h"

/**
 * @brief class that reads param manager and fill param bank, also if needed saves param bank to ascii file
 * methods:
 * init: inOptions - options with param manager, returns true if param bank readed correctly, false otherwise
 * run: always return true
 * terminate: always return true
 */

class JPetParamBankHandlerTask : public JPetTask
{
public:
  explicit JPetParamBankHandlerTask(const char* name = "");
  bool init(const JPetParamsInterface& inOptions) override;
  bool run(const JPetDataInterface&) override;
  bool terminate(JPetParamsInterface&) override;
};

#endif /*  !JPETPARAMBANKHANDLERTASK_H */
