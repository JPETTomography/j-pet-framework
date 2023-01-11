/**
 *  @copyright Copyright 2022 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetTaskTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTaskTest
#include "JPetTask/JPetTask.h"

#include <boost/test/unit_test.hpp>

class TestTask : public JPetTask
{
public:
  explicit TestTask(const char* name = "") : JPetTask(name) {}
  bool init(const JPetParams&) override { return true; }
  bool run(const JPetDataInterface&) override { return true; }
  bool terminate(JPetParams&) override { return true; }
};

BOOST_AUTO_TEST_SUITE(JPetTaskTestSuite)

BOOST_AUTO_TEST_CASE(constructor_test)
{
  TestTask task;
  BOOST_REQUIRE_EQUAL(task.getName(), "");
  BOOST_REQUIRE_EQUAL(task.getSubTasks().size(), 0);
}

BOOST_AUTO_TEST_CASE(task_name_test)
{
  TestTask task("the_task");
  BOOST_REQUIRE_EQUAL(task.getName(), "the_task");
  task.setName("same_task");
  BOOST_REQUIRE_EQUAL(task.getName(), "same_task");
}

BOOST_AUTO_TEST_CASE(subtask_test)
{
  TestTask task("task");

  std::unique_ptr<JPetTaskInterface> pTask1;
  std::unique_ptr<JPetTaskInterface> pTask2;
  std::unique_ptr<JPetTaskInterface> pTask3;
  task.addSubTask(std::move(pTask1));
  task.addSubTask(std::move(pTask2));
  task.addSubTask(std::move(pTask3));

  BOOST_REQUIRE_EQUAL(task.getSubTasks().size(), 3);
}

BOOST_AUTO_TEST_SUITE_END()
