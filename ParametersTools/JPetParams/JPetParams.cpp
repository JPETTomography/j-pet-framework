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
 *  @file JPetParams.cpp
 */

#include "./JPetParams.h"

using namespace jpet_options_tools;

JPetParams::JPetParams(): fParamManager(0) {}

JPetParams::JPetParams(const OptsStrAny& opts,
                       std::shared_ptr<JPetParamManager> mgr): fOptions(opts), fParamManager(mgr) {}

OptsStrAny JPetParams::getOptions() const
{
  return fOptions;
}

JPetParamManager* JPetParams::getParamManager() const
{
  return fParamManager.get();
}

std::shared_ptr<JPetParamManager> JPetParams::getParamManagerAsShared() const
{
  return fParamManager;
}

void JPetParams::setParamManager(std::shared_ptr<JPetParamManager> mgr)
{
  fParamManager = mgr;
}
