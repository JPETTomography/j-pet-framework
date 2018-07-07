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
#include <type_traits>
#include <memory>
#include <map>
#include <string>
#include <boost/any.hpp>
#include "./JPetTaskInterface/JPetTaskInterface.h"

class JPetTaskFactory
{
public:

  JPetTaskFactory();
  //using TaskGenerator = std::function< std::unique_ptr<JPetTaskInterface>() >;
  using TaskGenerator = std::function< JPetTaskInterface*() >;
  using TaskGeneratorChain = std::vector<TaskGenerator>;

  TaskGeneratorChain* getTaskGeneratorChain()
  {
    return fTaskGeneratorChain;
  }

  void addDefaultTasksFromOptions(const std::map<std::string, boost::any>& options);

  template<typename TDerived>
  void registerTask(const char* name)
  {
    static_assert(std::is_base_of<JPetTaskInterface, TDerived>::value, "registerType doesn't accept this type because doesn't derive from base class");
    fTasksDictionary[name] = [name]() {
      return std::unique_ptr<TDerived>(new TDerived{name});
    };
  }
  void useTask(const char* name, const char* inputFileType, const char* outputFileType);
private:
  JPetTaskFactory(const JPetTaskFactory&);
  void operator=(const JPetTaskFactory&);

  std::map<std::string, TaskGenerator> fTasksDictionary;
  TaskGeneratorChain* fTaskGeneratorChain{nullptr}; /// fTaskGeneratorChain is a sequences of registered computing tasks.

};
#endif /*  !JPETTASKFACTORY_H */
