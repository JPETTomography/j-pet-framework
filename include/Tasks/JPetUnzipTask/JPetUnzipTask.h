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
 *  @file JPetUnzipTask.h
 */

#ifndef JPETUNZIPTASK_H
#define JPETUNZIPTASK_H

#include "JPetTask/JPetTask.h"
#include <boost/any.hpp>
#include <map>

class JPetUnzipTask : public JPetTask
{
public:
  using OptsStrAny = std::map<std::string, boost::any>;
  explicit JPetUnzipTask(const char* name = "");
  bool init(const JPetParams& inOptions) override;
  bool run(const JPetDataInterface& inData) override;
  bool terminate(JPetParams& outOptions) override;
  static bool unzipFile(std::string fileNameWithPath, std::string outputPath);

protected:
  OptsStrAny fOptions;
};

#endif /* !JPETUNZIPTASK_H */
