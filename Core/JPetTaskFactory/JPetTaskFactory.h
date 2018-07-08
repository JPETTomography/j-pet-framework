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
#include "./JPetCommonTools/JPetCommonTools.h"
#include "./JPetTaskInterface/JPetTaskInterface.h"

/**
 * @brief Factory functions and factory class to produce chain of tasks.
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

namespace jpet_task_factory
{

//using TaskGenerator = std::function< std::unique_ptr<JPetTaskInterface>() >;
using TaskGenerator = std::function< std::unique_ptr<JPetTaskInterface>() >;
using TaskGeneratorChain = std::vector<TaskGenerator>;

/// @brief helper struct contains the information attached to given task
struct TaskInfo {
  TaskInfo(const std::string& n, const std::string& inType, const std::string& outType, int numIter):
    name(n),
    inputFileType(inType),
    outputFileType(outType),
    numOfIterations(numIter) {}

  std::string name; /// task identifier
  std::string inputFileType; 
  std::string outputFileType;
  int numOfIterations{1};
};


/// @brief Factory class provides the interface to create a chain of tasks generators 
/// A Chain correspond to a set of task generators that can be executated.  
/// Generator is the special function which called will return a task object.  
class JPetTaskFactory
{

public:
  JPetTaskFactory();
  /// @brief Method creates the generator chain based on the added tasks and set of default tasks.
  /// The tasks previously via addTaskInfo are used to form a chain of generators.
  /// In addition some default tasks are added based on the information from options argument.
  /// Warning(!): the added tasks are wrapped in the special tasks that handle the I/O operations, so effectively
  /// they become subtasks of the I/O tasks. 
  /// @param options set of options that are passed to decide which default tasks will be added at the beginning of the chain.
  /// of the  chain e.g. unzipping task or unpacking task. 
  /// @return chain of task generators
  TaskGeneratorChain createTaskGeneratorChain(const std::map<std::string, boost::any>& options) const;

  /// @brief Method to register the task generator. TDerived corresponds to the task type.
  ///  The name string is also passed as c-string parameter to the class constructor.
  /// @param name string that plays a role of the unique identifier of the task. If the previously used name is given the task generator will overwrite the previous one.
  template<typename TDerived>
  void registerTask(const std::string& name)
  {
    static_assert(std::is_base_of<JPetTaskInterface, TDerived>::value, "the class does not inherit from JPetTaskInterface");
    fTasksDictionary[name] = [name]()->std::unique_ptr<TDerived> {
      return jpet_common_tools::make_unique<TDerived>(name.c_str());
    };
  }

  /// @brief Method adds task information to the collection of tasks to be used while creating the task chain.
  /// @return false if the task with the name has not been registered. true otherwise.
  bool addTaskInfo(const char* name, const char* inputFileType, const char* outputFileType);

  std::vector<TaskInfo> getTasksToUse() const;
  std::map<std::string, TaskGenerator> getTasksDictionary() const;

private:
  JPetTaskFactory(const JPetTaskFactory&);
  void operator=(const JPetTaskFactory&);

  std::map<std::string, TaskGenerator> fTasksDictionary; /// Map containint the registered task types.
  std::vector<TaskInfo> fTasksToUse; /// The collection of task information (name, input and output file type) corresponding to task chain to be created.
};

/// Set of helper factory functions used by the JPetTaskFactory methods

/// @brief Function generates the chain of task generators
/// @param taskInfoVect vector of task information which will be transform into the chain of the corresponding generators
/// @param generatorMap map of registered tasks. Only those task can be used to produce the task generators
/// @param options set of options that are passed to decide which default tasks will be added at the beginning of the chain.
/// @return chain of task generators. Generator is the special function which called will return a task object.
TaskGeneratorChain generateTaskGeneratorChain(const std::vector<TaskInfo>& taskInfoVect, const std::map<std::string, TaskGenerator>& generatorsMap, const std::map<std::string, boost::any>& options);

/// @brief Function adds the set of predefined task generators to the beginning of outChain  based on the provided options.
/// @param options set of options that are passed to decide which default tasks will be added at the beginning of the chain.
/// @param outChain chain of task  generators that will be modified.
void addDefaultTasksFromOptions(const std::map<std::string, boost::any>& options, TaskGeneratorChain& outChain);

/// @brief generates the chain of task generators.
/// @param generatorMap map of registered tasks. Only those task can be used to produce the task generators.
/// @param info about the task to be added. The task type and name must be present in the generatorsMap.
/// @param outChain chain of task  generators that will be modified. 
void addTaskToChain(const std::map<std::string, TaskGenerator>& generatorsMap, const TaskInfo& info, TaskGeneratorChain& outChain);

}
#endif /*  !JPETTASKFACTORY_H */
