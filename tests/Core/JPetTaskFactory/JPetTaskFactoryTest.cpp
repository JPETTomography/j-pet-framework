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
 *  @file JPetTaskFactoryTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTaskFactoryTest

#include "JPetTaskFactory/JPetTaskFactory.h"
#include <boost/test/unit_test.hpp>
#include "JPetTaskIO/JPetTaskIO.h"
#include "JPetTask/JPetTask.h"
#include <boost/any.hpp>
#include <cstdio>

using namespace jpet_task_factory;

class TestClass: public JPetTask
{
  public:
  explicit TestClass(const char* name):JPetTask(name) {;}
  virtual bool init(const JPetParams&) override {return true;}
  virtual bool run(const JPetDataInterface&)  override {return true;}
  virtual bool terminate(JPetParams&)  override {return true;}
};

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(factory_default)
{
  JPetTaskFactory factory;
  BOOST_REQUIRE(factory.getTasksDictionary().empty());
  BOOST_REQUIRE(factory.getTasksToUse().empty());

  std::map<std::string, boost::any> opts = {{"inputFileType_std::string", std::string("root")}};
  auto chain = factory.createTaskGeneratorChain(opts);
  BOOST_REQUIRE_EQUAL(chain.size(), 1); // ParamBankHandler
  BOOST_REQUIRE(factory.getTasksDictionary().empty());
  BOOST_REQUIRE(factory.getTasksToUse().empty());
}

BOOST_AUTO_TEST_CASE(factory_scope)
{
  JPetTaskFactory factory;
  std::map<std::string, boost::any> opts = {{"inputFileType_std::string", std::string("scope")}};
  auto chain = factory.createTaskGeneratorChain(opts);
  BOOST_REQUIRE_EQUAL(chain.size(), 2); // ScopeLoader + ParamBankHandler
}

BOOST_AUTO_TEST_CASE(factory_hld)
{
  JPetTaskFactory factory;
  std::map<std::string, boost::any> opts = {{"inputFileType_std::string", std::string("hld")}};
  auto chain = factory.createTaskGeneratorChain(opts);
  BOOST_REQUIRE_EQUAL(chain.size(), 2); // UnpackTask + ParamBankHandler
}

BOOST_AUTO_TEST_CASE(factory_zip)
{
  JPetTaskFactory factory;
  std::map<std::string, boost::any> opts = {{"inputFileType_std::string", std::string("zip")}};
  auto chain = factory.createTaskGeneratorChain(opts);
  BOOST_REQUIRE_EQUAL(chain.size(), 3); // UnzipTask + UnpackTask + ParamBankHandler
}

BOOST_AUTO_TEST_CASE(factory_mcGeant)
{
  JPetTaskFactory factory;
  std::map<std::string, boost::any> opts = {{"inputFileType_std::string", std::string("mcGeant")}};
  auto chain = factory.createTaskGeneratorChain(opts);
  BOOST_REQUIRE_EQUAL(chain.size(), 1); // ParamBankHandler, GeantParser is added in another way
}

BOOST_AUTO_TEST_CASE(factory_registerTask)
{
  JPetTaskFactory factory;
  factory.registerTask<TestClass>("TestClass");
  factory.registerTask<TestClass>("task2");
  BOOST_REQUIRE_EQUAL(factory.getTasksDictionary().size(), 2);
  BOOST_REQUIRE(factory.getTasksToUse().empty());  // Task was registered but not added to be used

  std::map<std::string, boost::any> opts = {{"inputFileType_std::string", std::string("root")}};
  auto chain = factory.createTaskGeneratorChain(opts);
  BOOST_REQUIRE_EQUAL(chain.size(), 1); // ParamBankHandler
}

BOOST_AUTO_TEST_CASE( factory_addTaskInfo_wrong )
{
  JPetTaskFactory factory;
  std::map<std::string, boost::any> opts = {{"inputFileType_std::string", std::string("root")}};
  BOOST_REQUIRE(!factory.addTaskInfo("fakeName","raw","calib", 1)); ///Because fakeName task is not registered!
  BOOST_REQUIRE_EQUAL(factory.getTasksToUse().size(), 0);
  BOOST_REQUIRE(factory.getTasksDictionary().empty());  /// Task was not registered.
  auto chain = factory.createTaskGeneratorChain(opts); /// Because task was not registered, so it will return chain with just default task generators.
  BOOST_REQUIRE_EQUAL(chain.size(), 1); /// ParamBankHandler
}

BOOST_AUTO_TEST_CASE( factory_addAndRegisterTask )
{
  JPetTaskFactory factory;
  factory.registerTask<TestClass>("task1");
  factory.registerTask<TestClass>("task2");
  BOOST_REQUIRE_EQUAL(factory.getTasksDictionary().size(), 2);
  BOOST_REQUIRE(factory.addTaskInfo("task1","raw","calib", 1));
  BOOST_REQUIRE(factory.addTaskInfo("task2","calib","sig", 1));
  BOOST_REQUIRE_EQUAL(factory.getTasksToUse().size(), 2);

  std::map<std::string, boost::any> opts = {{"inputFileType_std::string", std::string("root")}};
  auto chain = factory.createTaskGeneratorChain(opts);
  BOOST_REQUIRE_EQUAL(chain.size(), 3); // ParamBankHandler -> TestClass -> task2
  auto task3 = chain[1]();
  BOOST_REQUIRE_EQUAL(task3->getName(), std::string("task1"));
  auto task4 = chain[2]();
  BOOST_REQUIRE_EQUAL(task4->getName(), std::string("task2"));
}

BOOST_AUTO_TEST_CASE( factory_addAndRegisterTaskWithIteration )
{
  JPetTaskFactory factory;
  factory.registerTask<TestClass>("task1");
  factory.registerTask<TestClass>("task2");
  BOOST_REQUIRE_EQUAL(factory.getTasksDictionary().size(), 2);
  BOOST_REQUIRE(factory.addTaskInfo("task1","raw","calib", 1));
  BOOST_REQUIRE(factory.addTaskInfo("task2","calib","sig", 2));  /// iterative, the task will be packed in the Looper Class
  BOOST_REQUIRE_EQUAL(factory.getTasksToUse().size(), 2);

  std::map<std::string, boost::any> opts = {{"inputFileType_std::string", std::string("root")}};
  auto chain = factory.createTaskGeneratorChain(opts);
  BOOST_REQUIRE_EQUAL(chain.size(), 3); /// ParamBankHandler -> TestClass -> task2
  auto task3 = chain[1]();
  BOOST_REQUIRE_EQUAL(task3->getName(), std::string("task1"));
  auto task4 = chain[2]();
  BOOST_REQUIRE_EQUAL(task4->getName(), std::string("task2"));
  auto subTask = dynamic_cast<JPetTaskIO*>(task4->getSubTasks()[0]);
  BOOST_REQUIRE(subTask);
}

BOOST_AUTO_TEST_CASE( factory_addAndRegisterTaskWithStop )
{
  JPetTaskFactory factory;
  factory.registerTask<TestClass>("task1");
  factory.registerTask<TestClass>("task2");
  BOOST_REQUIRE_EQUAL(factory.getTasksDictionary().size(), 2);
  BOOST_REQUIRE(factory.addTaskInfo("task1","raw","calib", 1));
  BOOST_REQUIRE(factory.addTaskInfo("task2","calib","sig", -1));  /// iterative with stop condition the task will be packed in the Looper Class
  BOOST_REQUIRE_EQUAL(factory.getTasksToUse().size(), 2);

  std::map<std::string, boost::any> opts = {{"inputFileType_std::string", std::string("root")}};
  auto chain = factory.createTaskGeneratorChain(opts);
  BOOST_REQUIRE_EQUAL(chain.size(), 3); /// ParamBankHandler -> TestClass -> task2
  auto task3 = chain[1]();
  BOOST_REQUIRE_EQUAL(task3->getName(), std::string("task1"));
  auto task4 = chain[2]();
  BOOST_REQUIRE_EQUAL(task4->getName(), std::string("task2"));
  auto subTask = dynamic_cast<JPetTaskIO*>(task4->getSubTasks()[0]);
  BOOST_REQUIRE(subTask);
}

BOOST_AUTO_TEST_CASE( factory_clear )
{
  JPetTaskFactory factory;
  factory.registerTask<TestClass>("task1");
  factory.registerTask<TestClass>("task2");
  factory.addTaskInfo("task1","raw","calib", 1);
  factory.addTaskInfo("task2","calib","sig", 1);

  factory.clear();
  BOOST_REQUIRE(factory.getTasksDictionary().empty());
  BOOST_REQUIRE(factory.getTasksToUse().empty());
}

BOOST_AUTO_TEST_SUITE_END()
