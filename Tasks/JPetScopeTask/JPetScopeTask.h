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
 *  @file JPetScopeTask.h
 *  @brief Module for oscilloscope data
 */

#ifndef JPETSCOPETASK_H
#define JPETSCOPETASK_H

#include "JPetUserTask/JPetUserTask.h"
#include <string>
#include <map>

class JPetScopeTask: public JPetUserTask
{
public:
  JPetScopeTask(const char* name);
  virtual ~JPetScopeTask() {};

  bool run(const JPetDataInterface& inData) override;

  /// getting oscilloscope data full file names to process

protected:
  bool init() override;
  bool exec() override;
  bool terminate() override;

  std::pair<int, std::map<std::string, int>> fInputFilesInCurrentWindow;
};

#endif /*  !JPETSCOPETASK_H */
