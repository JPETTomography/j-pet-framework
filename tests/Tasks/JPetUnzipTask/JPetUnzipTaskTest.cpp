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
 *  @file JPetUnzipTaskTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetUnzipTask

#include "./JPetUnzipTask/JPetUnzipTask.h"
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

BOOST_AUTO_TEST_SUITE(JPetUnzipTaskSuite)

BOOST_AUTO_TEST_CASE(sucessGz)
{
  boost::filesystem::remove("unitTestData/JPetTaskChainExecutorUtilsTest/goodGZ");
  BOOST_REQUIRE(JPetUnzipTask::unzipFile(
    "unitTestData/JPetTaskChainExecutorUtilsTest/goodGZ.gz",
    "./"
  ));

  boost::filesystem::remove("unitTestData/JPetTaskChainExecutorUtilsTest/goodGZ");
  BOOST_REQUIRE(JPetUnzipTask::unzipFile(
    "unitTestData/JPetTaskChainExecutorUtilsTest/goodGZ.gz",
    "unitTestData/JPetTaskChainExecutorUtilsTest/"
  ));

  boost::filesystem::remove("unitTestData/goodGZ");
  boost::filesystem::remove("unitTestData/JPetTaskChainExecutorUtilsTest/goodGZ");
  BOOST_REQUIRE(JPetUnzipTask::unzipFile(
    "unitTestData/JPetTaskChainExecutorUtilsTest/goodGZ.gz",
    "unitTestData/"
  ));
}

BOOST_AUTO_TEST_CASE(wrongGz)
{
  BOOST_REQUIRE(!JPetUnzipTask::unzipFile(
    "unitTestData/JPetTaskChainExecutorUtilsTest/wrongGZ.gz", "./"
  ));
}

BOOST_AUTO_TEST_CASE(sucessXz)
{
  boost::filesystem::remove("unitTestData/JPetTaskChainExecutorUtilsTest/goodXZ");
  BOOST_REQUIRE(JPetUnzipTask::unzipFile(
    "unitTestData/JPetTaskChainExecutorUtilsTest/goodXZ.xz",
    "./"
  ));

  boost::filesystem::remove("unitTestData/JPetTaskChainExecutorUtilsTest/goodXZ");
  BOOST_REQUIRE(JPetUnzipTask::unzipFile(
    "unitTestData/JPetTaskChainExecutorUtilsTest/goodXZ.xz",
    "unitTestData/JPetTaskChainExecutorUtilsTest/"
  ));

  boost::filesystem::remove("unitTestData/goodXZ");
  boost::filesystem::remove("unitTestData/JPetTaskChainExecutorUtilsTest/goodXZ");
  BOOST_REQUIRE(JPetUnzipTask::unzipFile(
    "unitTestData/JPetTaskChainExecutorUtilsTest/goodXZ.xz",
    "unitTestData/"
  ));
}

BOOST_AUTO_TEST_CASE(wrongXz)
{
  BOOST_REQUIRE(!JPetUnzipTask::unzipFile(
    "unitTestData/JPetTaskChainExecutorUtilsTest/wrongXZ.xz", "./"
  ));
}

BOOST_AUTO_TEST_CASE(sucessBz2)
{
  boost::filesystem::remove("unitTestData/JPetTaskChainExecutorUtilsTest/goodBZ2");
  BOOST_REQUIRE(JPetUnzipTask::unzipFile(
    "unitTestData/JPetTaskChainExecutorUtilsTest/goodBZ2.bz2",
    "./"
  ));

  boost::filesystem::remove("unitTestData/JPetTaskChainExecutorUtilsTest/goodBZ2");
  BOOST_REQUIRE(JPetUnzipTask::unzipFile(
    "unitTestData/JPetTaskChainExecutorUtilsTest/goodBZ2.bz2",
    "unitTestData/JPetTaskChainExecutorUtilsTest/"
  ));

  boost::filesystem::remove("unitTestData/goodBZ2");
  boost::filesystem::remove("unitTestData/JPetTaskChainExecutorUtilsTest/goodBZ2");
  BOOST_REQUIRE(JPetUnzipTask::unzipFile(
    "unitTestData/JPetTaskChainExecutorUtilsTest/goodBZ2.bz2",
    "unitTestData/"
  ));
}

BOOST_AUTO_TEST_CASE(wrongBz2)
{
  BOOST_REQUIRE(!JPetUnzipTask::unzipFile(
    "unitTestData/JPetTaskChainExecutorUtilsTest/wrongBZ2.bz2", "./"
  ));
}

BOOST_AUTO_TEST_CASE(sucessZip)
{
  boost::filesystem::remove("goodZIP");
  BOOST_REQUIRE(JPetUnzipTask::unzipFile(
    "unitTestData/JPetTaskChainExecutorUtilsTest/goodZIP.zip", "./"
  ));

  boost::filesystem::remove("goodZIP");
  BOOST_REQUIRE(JPetUnzipTask::unzipFile(
    "unitTestData/JPetTaskChainExecutorUtilsTest/goodZIP.zip",
    "unitTestData/JPetTaskChainExecutorUtilsTest/"
  ));

  boost::filesystem::remove("goodZIP");
  BOOST_REQUIRE(JPetUnzipTask::unzipFile(
    "unitTestData/JPetTaskChainExecutorUtilsTest/goodZIP.zip",
    "unitTestData/"
  ));
}

BOOST_AUTO_TEST_CASE(wrongZip)
{
  BOOST_REQUIRE(
    !JPetUnzipTask::unzipFile("unitTestData/JPetTaskChainExecutorUtilsTest/wrongZIP.zip", "./"
  ));
}

BOOST_AUTO_TEST_SUITE_END()
