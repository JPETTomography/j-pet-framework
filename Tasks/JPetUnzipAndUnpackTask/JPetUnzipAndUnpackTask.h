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
 *  @file JPetUnzipAndUnpackTask.h
 */

#ifndef JPETUNZIPANDUNPACKTASK_H 
#define JPETUNZIPANDUNPACKTASK_H 

#include <map>
#include "./JPetTask/JPetTask.h"
#include <boost/any.hpp>

class JPetUnzipAndUnpackTask: public JPetTask {
public:
  using OptsStrAny = std::map<std::string, boost::any>;
  explicit JPetUnzipAndUnpackTask(const char* name= "");
  bool init(const JPetParamsInterface& inOptions) override;
  bool run(const JPetDataInterface& inData) override;
  bool terminate(JPetParamsInterface& outOptions) override;

  static void unpackFile(const char* filename, long long nevents, const char* configfile, const char* calibfile);
  /// system(...) is returning integer, 0 when everything went smoothly and error code when not.
  /// Here I just convert return value into boolean type - Sz.N.
  static bool unzipFile(const char* filename);
protected:
  OptsStrAny fOptions;
  bool fUnpackHappened = false;
  
};
#endif /*  !JPETUNZIPANDUNPACKTASK_H */
