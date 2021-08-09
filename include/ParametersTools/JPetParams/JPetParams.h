/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetParams.h
 */

#ifndef JPETPARAMS_H
#define JPETPARAMS_H

#include "JPetOptionsTools/JPetOptionsTools.h"
#include "JPetParamManager/JPetParamManager.h"
#include <boost/any.hpp>
#include <map>
#include <memory>
#include <string>

class JPetParams
{
public:
  JPetParams();
  JPetParams(const jpet_options_tools::OptsStrAny& opts, std::shared_ptr<JPetParamManager> mgr);
  jpet_options_tools::OptsStrAny getOptions() const;
  JPetParamManager* getParamManager() const;
  std::shared_ptr<JPetParamManager> getParamManagerAsShared() const;
  void setParamManager(std::shared_ptr<JPetParamManager> mgr);

protected:
  jpet_options_tools::OptsStrAny fOptions;
  std::shared_ptr<JPetParamManager> fParamManager;
};
#endif /* !JPETPARAMS_H */
