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
 *  @file JPetUnzipAndUnpackTaskTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetUnzipAndUnpackTaskTest

#include "./JPetUnzipAndUnpackTask/JPetUnzipAndUnpackTask.h"
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

BOOST_AUTO_TEST_SUITE(JPetUnzipAndUnpackTaskTestSuite)

BOOST_AUTO_TEST_CASE(sucessGz)
{
  boost::filesystem::remove("unitTestData/JPetTaskChainExecutorUtilsTest/goodGZ");
  BOOST_REQUIRE(JPetUnzipAndUnpackTask::unzipFile("unitTestData/JPetTaskChainExecutorUtilsTest/goodGZ.gz"));
}

BOOST_AUTO_TEST_CASE(tryToUnzipSomethingNotExistingFileWithGz)
{
  std::string initialPath = boost::filesystem::path(boost::filesystem::current_path()).string();
  initialPath = initialPath.substr(0, initialPath.find("build") );
  std::string wrongZipPath = initialPath + "wrongGZ.gz";
  BOOST_REQUIRE(!JPetUnzipAndUnpackTask::unzipFile( wrongZipPath.c_str() ));
  BOOST_REQUIRE(!JPetUnzipAndUnpackTask::unzipFile( "unitTestData/JPetTaskChainExecutorUtilsTest/wrongGZ.gz" ));
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
  std::string wrongZipPath = initialPath + "unitTestData/JPetTaskChainExecutorUtilsTest/wrongXZ.Xz";
  BOOST_REQUIRE(!JPetUnzipAndUnpackTask::unzipFile( wrongZipPath.c_str() ));
  BOOST_REQUIRE(!JPetUnzipAndUnpackTask::unzipFile( "unitTestData/JPetTaskChainExecutorUtilsTest/wrongXZ.xz" ));
}

BOOST_AUTO_TEST_CASE(sucessBz2)
{
  boost::filesystem::remove("unitTestData/JPetTaskChainExecutorUtilsTest/goodBZ2");
  BOOST_REQUIRE(JPetUnzipAndUnpackTask::unzipFile("unitTestData/JPetTaskChainExecutorUtilsTest/goodBZ2.bz2"));
}

BOOST_AUTO_TEST_CASE(tryToUnzipSomethingNotExistingFileWithBz2)
{
  std::string initialPath = boost::filesystem::path(boost::filesystem::current_path()).string();
  initialPath = initialPath.substr(0, initialPath.find("build") );
  std::string wrongZipPath = initialPath + "unitTestData/JPetTaskChainExecutorUtilsTest/wrongBZ2.bz2";
  BOOST_REQUIRE(!JPetUnzipAndUnpackTask::unzipFile( wrongZipPath.c_str() ));
  BOOST_REQUIRE(!JPetUnzipAndUnpackTask::unzipFile( "unitTestData/JPetTaskChainExecutorUtilsTest/wrongBZ2.bz2" ));
}

BOOST_AUTO_TEST_CASE(sucessZip)
{
  boost::filesystem::remove("unitTestData/JPetTaskChainExecutorUtilsTest/goodZIP");
  BOOST_REQUIRE(JPetUnzipAndUnpackTask::unzipFile("unitTestData/JPetTaskChainExecutorUtilsTest/goodZIP.zip"));
}

BOOST_AUTO_TEST_CASE(tryToUnzipSomethingNotExistingFileWithZip)
{
  std::string initialPath = boost::filesystem::path(boost::filesystem::current_path()).string();
  initialPath = initialPath.substr(0, initialPath.find("build") );
  std::string wrongZipPath = initialPath + "unitTestData/JPetTaskChainExecutorUtilsTest/wrongZIP.zip";
  BOOST_REQUIRE(!JPetUnzipAndUnpackTask::unzipFile( wrongZipPath.c_str() ));
  BOOST_REQUIRE(!JPetUnzipAndUnpackTask::unzipFile( "unitTestData/JPetTaskChainExecutorUtilsTest/wrongZIP.zip" ));
}

BOOST_AUTO_TEST_SUITE_END()
