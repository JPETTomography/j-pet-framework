#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTaskLooperTest
#include <boost/test/unit_test.hpp>
#include "JPetTaskLooper/JPetTaskLooper.h"
#include "JPetUserTask/JPetUserTask.h"
#include "JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include "JPetParamsInterface/JPetParamsInterface.h"
#include "JPetTaskIO/JPetTaskIO.h"
#include "JPetCommonTools/JPetCommonTools.h"

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

class TestTaskRun20Times: public JPetTask
{
public:
  TestTaskRun20Times(const char* name = ""): JPetTask(name) {}
  bool init(const JPetParamsInterface& paramsI) override
  {
    fParams = static_cast<const JPetParams&>(paramsI);
    return true;
  }
  bool run(const JPetDataInterface&) override
  {
    fRunCounter++;
    return true;
  }
  bool terminate(JPetParamsInterface& paramsO) override
  {
    auto& params = static_cast<JPetParams&>(paramsO);
    params = fParams;
    /// Here I set the condition that it should stop after 20th iteration, but it can be some other condition.
    if (fRunCounter == 20) {
      auto newOpts = params.getOptions();
      newOpts["stopIteration_bool"] = true;
      params = JPetParams(newOpts, params.getParamManagerAsShared());
    }
    return true;
  }
  int fRunCounter = 0;
  JPetParams fParams;
};
BOOST_AUTO_TEST_SUITE(JPetTaskTestSuite)

BOOST_AUTO_TEST_CASE( my_test_false_predicate)
{
  using namespace jpet_options_generator_tools;
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
  BOOST_REQUIRE_EQUAL(subTask ->fRunCounter, 0);
}

BOOST_AUTO_TEST_CASE( my_test_10_iterations)
{
  using namespace jpet_options_generator_tools;
  const int maxIter = 10;
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

BOOST_AUTO_TEST_CASE( my_test_10_iterations_with_predefined_function)
{
  const int maxIter = 10;
  auto condFunc =  JPetTaskLooper::getMaxIterationPredicate(maxIter);

  using namespace jpet_options_generator_tools;
  std::vector<jpet_options_tools::OptsStrAny> opts;
  auto opt = getDefaultOptions();
  opts.push_back(opt);
  JPetTaskLooper looper("testTaskLooper", std::unique_ptr<JPetTask>(new TestTask), condFunc);
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

BOOST_AUTO_TEST_CASE( my_test_withSettingOptions)
{
  std::string optName = "stopIteration_bool";
  auto condFunc =  JPetTaskLooper::getStopOnOptionPredicate(optName);

  using namespace jpet_options_generator_tools;
  auto opt = getDefaultOptions();
  opt[optName] = false;
  JPetParams inputParams = JPetParams(opt, inputParams.getParamManagerAsShared());

  JPetTaskLooper looper("testTaskLooper", std::unique_ptr<JPetTask>(new TestTaskRun20Times), condFunc);
  JPetDataInterface nullDataObject;
  auto result = looper.init(inputParams);
  BOOST_REQUIRE(result);
  result = looper.run(nullDataObject);
  BOOST_REQUIRE(result);
  JPetParams outputParams;
  result = looper.terminate(outputParams);
  BOOST_REQUIRE(result);
  auto subTask = dynamic_cast<TestTaskRun20Times*>(looper.getSubTasks()[0]);
  BOOST_REQUIRE_EQUAL(subTask->fRunCounter, 20);
}

BOOST_AUTO_TEST_CASE(my_test_JPetTaskIO)
{
  std::string optName = "stopIteration_bool";
  auto condFunc =  JPetTaskLooper::getStopOnOptionPredicate(optName);

  using namespace jpet_options_generator_tools;

  auto task = jpet_common_tools::make_unique<JPetTaskIO>("bla","" ,"" );
  task->addSubTask(std::unique_ptr<JPetTask>(new TestTaskRun20Times));
  JPetTaskLooper looper("bla", std::move(task), condFunc);

  auto opt = getDefaultOptions();
  opt[optName] = false;
  JPetParams inputParams;
  inputParams = JPetParams(opt, inputParams.getParamManagerAsShared());

  auto result = looper.init(inputParams);
  BOOST_REQUIRE(result);
  JPetDataInterface nullDataObject;
  result = looper.run(nullDataObject);
  BOOST_REQUIRE(result);

  JPetParams outputParams;
  result = looper.terminate(outputParams);
  BOOST_REQUIRE(result);

  auto subTaskIO = dynamic_cast<JPetTaskIO*>(looper.getSubTasks()[0]);
  auto subSubTask = dynamic_cast<TestTaskRun20Times*>(subTaskIO->getSubTasks()[0]);
  BOOST_REQUIRE_EQUAL(subSubTask->fRunCounter, 20);
}
BOOST_AUTO_TEST_SUITE_END()
