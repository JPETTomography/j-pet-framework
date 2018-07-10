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
 *  @file JPetManager.h
 */

#ifndef JPETMANAGER_H
#define JPETMANAGER_H

#include "./JPetTaskFactory/JPetTaskFactory.h"
#include <map>
#include <string>
#include <boost/any.hpp>

/**
 * @brief Main Manager of the analyses performed with the J-PET Framework.
 *
 * Each analysis program needs an instance of the JPetManager,
 * which is responsible for parsing the command line arguments,
 * registering processing tasks, and sending it to JPetExecutor,
 * which executes the chain of registered tasks in threads.
 * Private fields include Options container, in which the number of elements
 * corresponds to the number of independent input files.
 */
class JPetManager
{
public:
  static JPetManager& getManager();
  
  /// @throws exceptions in case of errors.
  void run(int argc, const char** argv); 

  /// @brief Method parses command line arguments and returns the set of validated option generated based on it.
  /// @return pair of boolean status and the map of validated options. In case of errors the status is set to false.
  std::pair<bool, std::map<std::string, boost::any> > parseCmdLine(int argc, const char** argv);

  /// @brief Method to register tasks that can form the a chain of tasks to be executed.
  /// The registration of the task gives the opportunity to use it later by calling useTask method.
  /// The task must inherit from JPeTaskInterface.
  /// @param name c-string that identifies given registered task. Also, this string is passed to the construct as argument.
  template<typename T>
  void registerTask(const char* name)
  {
    fTaskFactory.registerTask<T>(name);
  }

  /// @brief Method to add the task to the chain of tasks that will be executed later by JPetTaskExecutor.
  /// The task must be registered before (e.g. using registerTask) using the same name label.
  /// The input and output file type arguments correspond to labels that form a part of the input/output file extension.
  /// The following format is used: fileNameRoot.fileType.root  e.g. if inputFileType is "raw" and file name is "bla", then
  /// the input file name is expected to be "bla.raw.root". There are some labels that are treated separately e.g.
  /// "zip" or "hld". If the outputFileType is the empty string then the task is assumed to have no output tree.
  /// @param name c-string that identifies registered task. Also, this string is passed to the construct as argument.
  /// @param inputFileType c-string corresponding to the input file extension.
  /// @param outputFileType c-string corresponding to the output file extension. If empty, the task with no typical output is assumed.
  /// @throws exception in case of errors.
  void useTask(const char* name, const char* inputFileType = "", const char* outputFileType = "");

  bool areThreadsEnabled() const;
  void setThreadsEnabled(bool enable);

private:
  JPetManager(const JPetManager&);
  void operator=(const JPetManager&);

  JPetManager();
  bool fThreadsEnabled = false;
  jpet_task_factory::JPetTaskFactory fTaskFactory;
};
#endif /* !JPETMANAGER_H */
