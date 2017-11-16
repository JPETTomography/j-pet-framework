/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetUnzipAndUnpackTaskTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetUnzipAndUnpackTaskTest
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "../JPetUnzipAndUnpackTask/JPetUnzipAndUnpackTask.h"


BOOST_AUTO_TEST_SUITE(JPetUnzipAndUnpackTaskTestSuite)

BOOST_AUTO_TEST_CASE(sucessZip)
{
  boost::filesystem::remove("unitTestData/JPetTaskChainExecutorUtilsTest/goodZip");
  BOOST_REQUIRE(JPetUnzipAndUnpackTask::unzipFile("unitTestData/JPetTaskChainExecutorUtilsTest/goodZip.gz"));
}

BOOST_AUTO_TEST_CASE(tryToUnzipSomethingNotExistingFile)
{
  std::string initialPath = boost::filesystem::path(boost::filesystem::current_path()).string();
  initialPath = initialPath.substr(0, initialPath.find("build") );
  std::string wrongZipPath = initialPath + "wrongZip.gz";
  BOOST_REQUIRE(!JPetUnzipAndUnpackTask::unzipFile( wrongZipPath.c_str() ));
  BOOST_REQUIRE(!JPetUnzipAndUnpackTask::unzipFile( "unitTestData/JPetTaskChainExecutorUtilsTest/wrongZip.gz" ));
}

BOOST_AUTO_TEST_CASE(sucessXz)
{
  boost::filesystem::remove("unitTestData/JPetTaskChainExecutorUtilsTest/goodXZ");
  BOOST_REQUIRE(JPetUnzipAndUnpackTask::unzipFile("unitTestData/JPetTaskChainExecutorUtilsTest/goodXZ.xz"));
}

BOOST_AUTO_TEST_CASE(tryToUnzipSomethingNotExistingFileWithXz)
{
  std::string initialPath = boost::filesystem::path(boost::filesystem::current_path()).string();
  initialPath = initialPath.substr(0, initialPath.find("build") );
  std::string wrongZipPath = initialPath + "unitTestData/JPetTaskChainExecutorUtilsTest/wrongZip.Xz";
  BOOST_REQUIRE(!JPetUnzipAndUnpackTask::unzipFile( wrongZipPath.c_str() ));
  BOOST_REQUIRE(!JPetUnzipAndUnpackTask::unzipFile( "unitTestData/JPetTaskChainExecutorUtilsTest/wrongXZ.xz" ));
}

BOOST_AUTO_TEST_SUITE_END()
