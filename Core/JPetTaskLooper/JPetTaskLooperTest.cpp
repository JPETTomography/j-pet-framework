#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTaskLooperTest
#include <boost/test/unit_test.hpp>
#include "JPetTaskLooper/JPetTaskLooper.h"
#include "JPetUserTask/JPetUserTask.h"
#include "JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "JPetParamsInterface/JPetParamsInterface.h"

/// Special test task that allows to check how many times its run method
/// was called. It can be done by checking fRunCounter value.
class TestTask: public JPetTask
{
public:
  TestTask(const char* name = ""): JPetTask(name) {}
  bool init(const JPetParamsInterface&) override
  {
    return true;
  }
  bool run(const JPetDataInterface&) override
  {
    fRunCounter++;
    return true;
  }
  bool terminate(JPetParamsInterface&) override
  {
    return true;
  }
  int fRunCounter = 0;

};

BOOST_AUTO_TEST_SUITE(JPetTaskTestSuite)

/// By default if we don't define any condition
/// the false condition will be used, that means,
/// We should not run even a single time.
BOOST_AUTO_TEST_CASE( my_test_false_predicate)
{
  using namespace jpet_options_generator_tools;
  std::vector<jpet_options_tools::OptsStrAny> opts;
  auto opt = getDefaultOptions();
  opts.push_back(opt);
  JPetTaskLooper looper("testTaskLooper", std::unique_ptr<JPetTask>(new TestTask ));
  JPetDataInterface nullDataObject;
  JPetParams inputParams;
  JPetParams outputParams;
  auto result = looper.init(inputParams);
  BOOST_REQUIRE(result);
  result = looper.run(nullDataObject);
  BOOST_REQUIRE(result);
  result = looper.terminate(outputParams);
  BOOST_REQUIRE(result);
  auto subTask = dynamic_cast<TestTask*>(looper.getSubTasks()[0]);
  /// Since we didnt give any condition we expect that the subtask was never called.
  BOOST_REQUIRE_EQUAL(subTask ->fRunCounter, 0);
}

/// This example show how to define a predicate function in
/// such a way that the subtask(s) will be called n-th times
/// In this example the inputParams given by subtask are ignored.
BOOST_AUTO_TEST_CASE( my_test_10_iterations)
{
  using namespace jpet_options_generator_tools;
  std::vector<jpet_options_tools::OptsStrAny> opts;
  auto opt = getDefaultOptions();
  opts.push_back(opt);

  /// those two variables are defined outside but are captured by condFunc.
  /// This means that they are bounded to the function definition
  /// and that
  const int maxIter = 10; /// we define some number of iteration
  int counter = 0;
  auto condFunc = [maxIter, &counter](const JPetParamsInterface&)->bool {
    if (counter < maxIter)
    {
      counter++;
      return true;
    } else {
      return false;
    }
  };
  JPetTaskLooper looper("testTaskLooper", std::unique_ptr<JPetTask>(new TestTask ), condFunc);
  JPetDataInterface nullDataObject;
  JPetParams inputParams;
  JPetParams outputParams;
  auto result = looper.init(inputParams);
  BOOST_REQUIRE(result);
  result = looper.run(nullDataObject);
  BOOST_REQUIRE(result);
  result = looper.terminate(outputParams);
  BOOST_REQUIRE(result);
  auto subTask = dynamic_cast<TestTask*>(looper.getSubTasks()[0]);
  BOOST_REQUIRE_EQUAL(subTask ->fRunCounter, maxIter);
}

///// Dummy param class just to show how to set conditions
//class JPetParamsTest: public JPetParamsInterface
//{
//public:
//bool fStopIteration = false;
//};

///// Special test task that allows to check how many times its run method
///// was called. It can be done by checking fRunCounter value.
///// The condition is set to 12
//class TestTask2: public JPetTask
//{
//public:
//TestTask2(const char* name = ""): JPetTask(name) {}

//bool init(const JPetParamsInterface&) override
//{
//return true;
//}

//bool run(const JPetDataInterface&) override
//{
//fRunCounter++;
//return true;
//}

//bool terminate(JPetParamsInterface& paramsI) override
//{
///// Some conditions here can be calculated.
///// We will just use the stupid condition  if fRunCounter > 12
///// but in principle it can be cuts on histograms or other things.
//auto params = dynamic_cast<JPetParamsTest&>(paramsI);
//if (fRunCounter > 12) {
//params.fStopIteration = true;
//}
//}

//int fRunCounter = 0;
//};

///// This example uses inputParams set by terminate() of subtask to stop iterations.
///// Here the role of the subtask is played by TestTask2 class.
///// Iteration should finish after 12, cause it is condition used in TestTask2.
//BOOST_AUTO_TEST_CASE(my_test_subtask)
//{
//using namespace jpet_options_generator_tools;
//std::vector<jpet_options_tools::OptsStrAny> opts;
//auto opt = getDefaultOptions();
//opts.push_back(opt);

//auto condFunc = [](const JPetParamsInterface& paramsI)->bool {
//auto params = dynamic_cast<const JPetParamsTest&>(paramsI);
//return params.fStopIteration;
//};

//JPetTaskLooper looper("testTaskLooper", std::unique_ptr<JPetTask>(new TestTask2), condFunc);
//JPetDataInterface nullDataObject;
//JPetParams inputParams;
//JPetParams outputParams;
//auto result = looper.init(inputParams);
//BOOST_REQUIRE(result);
//result = looper.run(nullDataObject);
//BOOST_REQUIRE(result);
//result = looper.terminate(outputParams);
//BOOST_REQUIRE(result);
//auto subTask =dynamic_cast<TestTask*>(looper.getSubTasks()[0]);
//BOOST_REQUIRE_EQUAL(subTask ->fRunCounter, 12);
//}

BOOST_AUTO_TEST_SUITE_END()
