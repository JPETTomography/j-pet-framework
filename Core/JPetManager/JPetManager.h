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
 *  @file JPetManager.h
 *  @brief Main manager of the analysis performed with the J-PET Framework.
 */

#ifndef JPETMANAGER_H
#define JPETMANAGER_H

#include "./JPetTaskChainExecutor/JPetTaskChainExecutor.h"
#include "./JPetOptionsTools/JPetOptionsTools.h"
#include <memory>
#include <map>

/**
 * @brief Main manager of the analysis performed with the J-PET Framework.
 *
 * Each analysis program needs an instance of the JPetManager which is responsible for parsing the command line arguments
 * registering processing tasks, and
 * sending it to JPetExecutor which executes the chain of registered tasks in threads.
 */

class JPetManager
{
public:
  using Options = std::map<std::string, jpet_options_tools::OptsStrAny>;
  using TaskGenerator = std::function< JPetTaskInterface* () >;
  using TaskGeneratorChain = std::vector<TaskGenerator>;

  static JPetManager& getManager();
  ~JPetManager();

  bool run(int argc, const char** argv);

  template<typename T> void registerTask(const char * name){
    fTasksDictionary[name] = [name]() {
      return new T(name);
    };
  }
  /// Function parses command line arguments and generates options for tasks.
  /// The fOptions is filled with the generated options.
  bool parseCmdLine(int argc, const char** argv);
  Options getOptions() const;
  bool areThreadsEnabled() const;
  void setThreadsEnabled(bool enable);
  void useTask(const char * name, const char * inputFileType="", const char * outputFileType="");
  void clearRegisteredTasks();

private:
  JPetManager(const JPetManager&);
  void operator=(const JPetManager&);

  JPetManager();
  /// Number of elements in the fOptions container corresponds to the number of independent input files.
  Options fOptions;
  TaskGeneratorChain* fTaskGeneratorChain = nullptr; /// fTaskGeneratorChain is a sequences of registered computing tasks.
  bool fThreadsEnabled = false;
  std::map<const char *, TaskGenerator> fTasksDictionary;
};
#endif /*  !JPETMANAGER_H */
