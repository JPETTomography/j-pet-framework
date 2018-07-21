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
 *  @file JPetUnzipAndUnpackTask.h
 */

#ifndef JPETUNZIPANDUNPACKTASK_H
#define JPETUNZIPANDUNPACKTASK_H

#include "./JPetTask/JPetTask.h"
#include <boost/any.hpp>
#include <map>

class JPetUnzipAndUnpackTask: public JPetTask
{
public:
  using OptsStrAny = std::map<std::string, boost::any>;
  explicit JPetUnzipAndUnpackTask(const char* name = "");
  bool init(const JPetParams& inOptions) override;
  bool run(const JPetDataInterface& inData) override;
  bool terminate(JPetParams& outOptions) override;
  static void unpackFile(const std::string& filename, long long nevents,
    const std::string& configfile, const std::string& calibfile);
  static bool unzipFile(const std::string& filename);

protected:
  OptsStrAny fOptions;
  bool fUnpackHappened = false;
};

#endif /* !JPETUNZIPANDUNPACKTASK_H */
