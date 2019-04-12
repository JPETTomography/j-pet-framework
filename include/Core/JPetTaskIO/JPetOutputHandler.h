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
 *  @file JPetOutputHandler.h
 */

#ifndef JPETOUTPUTHANDLER_H
#define JPETOUTPUTHANDLER_H

#include "./JPetStatistics/JPetStatistics.h"
#include "./JPetParamManager/JPetParamManager.h"
#include "./JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include <map>
#include <string>
#include <memory>


class JPetTreeHeader;
class JPetTaskInterface;

/**
 * @brief Helper class handles the output operation performed by JPetWriter
 * It is a helper method for the JPetTaskIO class.
 */
class JPetOutputHandler
{
public:
  JPetOutputHandler(); 
  explicit JPetOutputHandler(const char* outputFilename);

  void saveOutput(JPetParamManager& manager, JPetTreeHeader* header, JPetStatistics* statistics, std::map<std::string, std::unique_ptr<JPetStatistics>>& fSubTasksStatistics);
  void saveAndCloseOutput(JPetParamManager& manager, JPetTreeHeader* header, JPetStatistics* statistics, std::map<std::string, std::unique_ptr<JPetStatistics>>& fSubTasksStatistics);
  bool writeEventToFile(JPetTaskInterface* task);

protected:
  JPetWriter fWriter;

private:
  JPetOutputHandler(const JPetOutputHandler&);
  void operator=(const JPetOutputHandler&);

};
#endif /*  !JPETOUTPUTHANDLER_H */
