/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetUnpackTaskTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetUnpackTaskTest

#include "JPetUnpackTask/JPetUnpackTask.h"
#include "JPetOptionsGenerator/JPetOptionsGeneratorTools.h"
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(UnpackTaskSuite)

BOOST_AUTO_TEST_CASE(wrong_init_test)
{
  std::string fileNameWithPath = "bla.hld";
  std::string xmlConfig = "bli.xml";
  std::string totCalib = "blu.root";
  std::string tdcCalib = "blo.root";

  BOOST_REQUIRE(!JPetUnpackTask::validateFiles(fileNameWithPath, xmlConfig, totCalib, true, tdcCalib, true));
}

BOOST_AUTO_TEST_CASE(no_calib_init_test)
{
  std::string fileNameWithPath = "unitTestData/JPetUnpackerTest/xx14099113231.hld";
  std::string xmlConfig = "unitTestData/JPetUnpackerTest/conf_trb3.xml";
  std::string totCalib = "blu.root";
  std::string tdcCalib = "blo.root";

  BOOST_REQUIRE(JPetUnpackTask::validateFiles(fileNameWithPath, xmlConfig, totCalib, false, tdcCalib, false));
}

BOOST_AUTO_TEST_CASE(good_init_test)
{
  std::string fileNameWithPath = "unitTestData/JPetUnpackerTest/xx14099113231.hld";
  std::string xmlConfig = "unitTestData/JPetUnpackerTest/conf_trb3.xml";
  std::string totCalib = "unitTestData/JPetUnpackerTest/calib.root";
  std::string tdcCalib = "unitTestData/JPetUnpackerTest/tdccalib.root";

  BOOST_REQUIRE(JPetUnpackTask::validateFiles(fileNameWithPath, xmlConfig, totCalib, true, tdcCalib, true));
}

BOOST_AUTO_TEST_SUITE_END()
