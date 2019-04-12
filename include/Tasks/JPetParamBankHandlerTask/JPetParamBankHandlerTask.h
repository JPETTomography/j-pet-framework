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
 *  @file JPetParamBankHandlerTask.h
 */

#ifndef JPETPARAMBANKHANDLERTASK_H
#define JPETPARAMBANKHANDLERTASK_H

#include "./JPetParamGetterAscii/JPetParamSaverAscii.h"
#include "./JPetParams/JPetParams.h"
#include "./JPetTask/JPetTask.h"

/**
 * @brief Reading params and filling ParamBank
 *
 * Extension of JPetTask (with init(), run() and terminate() methods) for
 * reading the parameters from options and filling the Paramere Bank.
 * Init() method returns false if readout is successful. It is possible
 * to save parameters to ASCII file.
 */
class JPetParamBankHandlerTask : public JPetTask
{
public:
  explicit JPetParamBankHandlerTask(const char* name = "");
  bool init(const JPetParams& inOptions) override;
  bool run(const JPetDataInterface&) override;
  bool terminate(JPetParams&) override;

private:
  bool generateParamBankFromConfig(const JPetParams& params);
  bool generateParamBankFromRootFile(const JPetParams& params);
};

#endif /* !JPETPARAMBANKHANDLERTASK_H */
