#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTaskFactoryTest

#include <boost/test/unit_test.hpp>
#include <boost/any.hpp>
#include "./JPetTaskFactory/JPetTaskFactory.h"
#include "./JPetTask/JPetTask.h"
#include "./JPetTaskIO/JPetTaskIO.h"
#include <cstdio> //for std::remove

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

BOOST_AUTO_TEST_CASE( factory )
{
  JPetTaskFactory factory;
  BOOST_REQUIRE(factory.getTasksDictionary().empty());
  BOOST_REQUIRE(factory.getTasksToUse().empty());

  std::map<std::string, boost::any> opts = {{"inputFileType_std::string", std::string("root")}};
  auto chain = factory.createTaskGeneratorChain(opts);
  BOOST_REQUIRE_EQUAL(chain.size(), 2); /// ParamBankHandler + UnpackerAndUnzipper are added by default
  BOOST_REQUIRE(factory.getTasksDictionary().empty());
  BOOST_REQUIRE(factory.getTasksToUse().empty());
}

BOOST_AUTO_TEST_CASE( factory2 )
{
  JPetTaskFactory factory;
  std::map<std::string, boost::any> opts = {{"inputFileType_std::string", std::string("scope")}};
  auto chain = factory.createTaskGeneratorChain(opts);
  BOOST_REQUIRE_EQUAL(chain.size(), 3); /// ScopeLoader + ParamBankHandler + UnpackerAndUnzipper are added
}

BOOST_AUTO_TEST_CASE( factory_registerTask )
{
  JPetTaskFactory factory;
  factory.registerTask<TestClass>("TestClass");
  factory.registerTask<TestClass>("task2");
  BOOST_REQUIRE_EQUAL(factory.getTasksDictionary().size(), 2);
  BOOST_REQUIRE(factory.getTasksToUse().empty());  /// Task was registered but not added to be used

  std::map<std::string, boost::any> opts = {{"inputFileType_std::string", std::string("root")}};
  auto chain = factory.createTaskGeneratorChain(opts);
  BOOST_REQUIRE_EQUAL(chain.size(), 2); /// ParamBankHandler + UnpackerAndUnzipper are added by default, no other task were present
}

BOOST_AUTO_TEST_CASE( factory_addTaskInfo_wrong )
{
  JPetTaskFactory factory;
  std::map<std::string, boost::any> opts = {{"inputFileType_std::string", std::string("root")}};
  BOOST_REQUIRE(!factory.addTaskInfo("fakeName","raw","calib", 1)); ///Because fakeName task is not registered!
  BOOST_REQUIRE_EQUAL(factory.getTasksToUse().size(), 0);
  BOOST_REQUIRE(factory.getTasksDictionary().empty());  /// Task was not registered.
  auto chain = factory.createTaskGeneratorChain(opts); /// Because task was not registered, so it will return chain with just default task generators.
  BOOST_REQUIRE_EQUAL(chain.size(), 2); /// ParamBankHandler + UnpackerAndUnzipper are added by default.
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
  BOOST_REQUIRE_EQUAL(chain.size(), 4); /// UnpackerAndUnzipper ->ParamBankHandler -> TestClass->task2 
  auto task3 = chain[2]();
  BOOST_REQUIRE_EQUAL(task3->getName(), std::string("task1"));
  auto task4 = chain[3]();
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
  BOOST_REQUIRE_EQUAL(chain.size(), 4); /// UnpackerAndUnzipper ->ParamBankHandler -> TestClass->task2 
  auto task3 = chain[2]();
  BOOST_REQUIRE_EQUAL(task3->getName(), std::string("task1"));
  auto task4 = chain[3]();
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
  BOOST_REQUIRE_EQUAL(chain.size(), 4); /// UnpackerAndUnzipper ->ParamBankHandler -> TestClass->task2 
  auto task3 = chain[2]();
  BOOST_REQUIRE_EQUAL(task3->getName(), std::string("task1"));
  auto task4 = chain[3]();
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
