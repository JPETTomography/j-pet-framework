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
 *  @file JPetTaskChainExecutorUtilsTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTaskChainExecutorUtilsTest
#include <boost/test/unit_test.hpp>
#include "../JPetTaskChainExecutor/JPetTaskChainExecutorUtils.h"

BOOST_AUTO_TEST_SUITE(JPetTaskChainExecutorTestSuite)

BOOST_AUTO_TEST_CASE(tryToUnzipSomethingNotExistingFile)
{
  BOOST_REQUIRE(JPetTaskChainExecutorUtils::unzipFile("unitTestData/JPetTaskChainExecutorUtilsTest/goodZip.gz"));
  std::string initialPath = boost::filesystem::path(boost::filesystem::current_path()).string();
  initialPath = initialPath.substr(0, initialPath.find("build") );
  std::string wrongZipPath = initialPath + "wrongZip.gz";
  BOOST_REQUIRE(!JPetTaskChainExecutorUtils::unzipFile( wrongZipPath.c_str() ));
  BOOST_REQUIRE(!JPetTaskChainExecutorUtils::unzipFile( "unitTestData/JPetTaskChainExecutorUtilsTest/wrongZip.gz" ));
  BOOST_REQUIRE(boost::filesystem::exists("unitTestData/JPetTaskChainExecutorUtilsTest/goodZip"));
  system("rm unitTestData/JPetTaskChainExecutorUtilsTest/goodZip");
}

BOOST_AUTO_TEST_CASE(tryToUnzipSomethingNotExistingFileWithXz)
{
  BOOST_REQUIRE(JPetTaskChainExecutorUtils::unzipFile("unitTestData/JPetTaskChainExecutorUtilsTest/goodXZ.xz"));
  std::string initialPath = boost::filesystem::path(boost::filesystem::current_path()).string();
  initialPath = initialPath.substr(0, initialPath.find("build") );
  std::string wrongZipPath = initialPath + "unitTestData/JPetTaskChainExecutorUtilsTest/wrongZip.Xz";
  BOOST_REQUIRE(!JPetTaskChainExecutorUtils::unzipFile( wrongZipPath.c_str() ));
  BOOST_REQUIRE(!JPetTaskChainExecutorUtils::unzipFile( "unitTestData/JPetTaskChainExecutorUtilsTest/wrongXZ.xz" ));
  BOOST_REQUIRE(boost::filesystem::exists("unitTestData/JPetTaskChainExecutorUtilsTest/goodXZ"));
  system("rm unitTestData/JPetTaskChainExecutorUtilsTest/goodXZ");
}

BOOST_AUTO_TEST_SUITE_END()
