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
 *  @file JPetTaskFactory.h
 */

#ifndef JPETTASKFACTORY_H
#define JPETTASKFACTORY_H
#include <vector>
#include <memory>
#include <map>
#include <string>
#include <type_traits>
#include <boost/any.hpp>
#include "./JPetTaskInterface/JPetTaskInterface.h"

/**
 * @brief Factory to produce objects of classes with inherit from JPetTaskInterface.
 *
 * The factory provides the possiblility to register a task and based on registered task
 * to create chains of generators which are special functions that can be used
 * to produce the corresponding objects later. One chain of generators corresponds to the chain
 * of task objects that together form a stream of processing units: TaskA ->TaskB->TaskC.
 * The factor provides also the method to add predifined tass generators at the beginning
 * of the formed chain. They correspond to e.g. unzipping operations.
 * The registered JPetUserTask  are not actually added directly to the stream, but are first
 * encapsulated (as subTasks) into the JPetTaskIO objects which provide the input/output
 * operations e.g. handle the reading/writing events.
 *
 */

struct TaskInfo {
  TaskInfo(const std::string& n, const std::string& inType, const std::string& outType, int numIter):
    name(n),
    inputFileType(inType),
    outputFileType(outType),
    numOfIterations(numIter) {}

  std::string name;
  std::string inputFileType;
  std::string outputFileType;
  int numOfIterations{1};
};


class JPetTaskFactory
{

public:
  JPetTaskFactory() {};

  //using TaskGenerator = std::function< std::unique_ptr<JPetTaskInterface>() >;
  using TaskGenerator = std::function< JPetTaskInterface*() >;
  using TaskGeneratorChain = std::vector<TaskGenerator>;

  std::vector<TaskGenerator> createTaskGeneratorChain(const std::map<std::string, boost::any>& options) const;

  void addTaskToChain(const std::map<std::string, TaskGenerator>& generatorsMap, const TaskInfo& info, TaskGeneratorChain& outChain) const;
  
  TaskGeneratorChain generateTaskGeneratorChain(const std::vector<TaskInfo>& taskInfoVect, const std::map<std::string, TaskGenerator>& generatorsMap, const std::map<std::string, boost::any>& options) const;
  //TaskGeneratorChain* generateTaskGeneratorChain(const std::vector<TaskInfo>& taskInfoVect, const std::map<std::string, TaskGenerator>& generatorsMap, const std::map<std::string, boost::any>& options);

  /// \brief Method to register the task generator. TDerived corresponds to the task type.
  ///  The name string is also passed as parameter to the class constructor.
  /// \param name string that plays a role of the unique identifier of the task. If the previously used name is given the task generator will overwrite the previous one.
  template<typename TDerived>
  void registerTask(const std::string& name)
  {
    static_assert(std::is_base_of<JPetTaskInterface, TDerived>::value, "the class does not inherit from JPetTaskInterface");
    fTasksDictionary[name] = [name]() {
      return std::unique_ptr<TDerived>(new TDerived{name});
    };
  }

  void addDefaultTasksFromOptions(const std::map<std::string, boost::any>& options, TaskGeneratorChain& outChain) const;

  //void addDefaultTasksFromOptions(const std::map<std::string, boost::any>& options);


  //void useTask(const char* name, const char* inputFileType, const char* outputFileType);

  /// Method adds task information to the collection of tasks to be used while creating the task chain.
  void addTaskInfo(const char* name, const char* inputFileType, const char* outputFileType);

private:
  JPetTaskFactory(const JPetTaskFactory&);
  void operator=(const JPetTaskFactory&);

  std::map<std::string, TaskGenerator> fTasksDictionary;
  std::vector<TaskInfo> fTasksToUse; /// The collection of task information (name, input and output file type) corresponding to task chain to be created.
};
#endif /*  !JPETTASKFACTORY_H */
