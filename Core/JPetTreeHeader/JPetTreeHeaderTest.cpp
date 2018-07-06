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
 *  @file JPetTreeHeaderTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetTreeHeaderTest

#include "./JPetTreeHeader/JPetTreeHeader.h"
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

BOOST_AUTO_TEST_SUITE(JPetTreeHeaderSuite)

BOOST_AUTO_TEST_CASE(emptyHeader)
{
	JPetTreeHeader treeHeader;
	BOOST_REQUIRE_EQUAL(treeHeader.getRunNumber(), -1);
	BOOST_REQUIRE_EQUAL(treeHeader.getBaseFileName(), "filename not set");
	BOOST_REQUIRE_EQUAL(treeHeader.getSourcePosition(), -1);
	BOOST_REQUIRE_EQUAL(treeHeader.getStagesNb(), 0);
	BOOST_REQUIRE_EQUAL(treeHeader.getProcessingStageInfo(0).fModuleName, "module not set");
	BOOST_REQUIRE_EQUAL(treeHeader.getProcessingStageInfo(10).fModuleDescription, "description not set");
	BOOST_REQUIRE_EQUAL(treeHeader.getProcessingStageInfo(12).fModuleVersion, -1);
	BOOST_REQUIRE_EQUAL(treeHeader.getProcessingStageInfo(12).fCreationTime, "-1");
	BOOST_REQUIRE_EQUAL(treeHeader.getVariable( "" ), "");
}

BOOST_AUTO_TEST_CASE(checkingEmptyStage)
{
	JPetTreeHeader treeHeader;
	BOOST_REQUIRE_EQUAL(treeHeader.emptyProcessingStageInfo().fModuleName,
		treeHeader.getProcessingStageInfo(0).fModuleName);
	BOOST_REQUIRE_EQUAL(treeHeader.emptyProcessingStageInfo().fModuleDescription,
		treeHeader.getProcessingStageInfo(0).fModuleDescription);
	BOOST_REQUIRE_EQUAL(treeHeader.emptyProcessingStageInfo().fModuleVersion,
		treeHeader.getProcessingStageInfo(0).fModuleVersion);
	BOOST_REQUIRE_EQUAL(treeHeader.emptyProcessingStageInfo().fCreationTime,
		treeHeader.getProcessingStageInfo(0).fCreationTime);
}

BOOST_AUTO_TEST_CASE(headerWithNumber)
{
	JPetTreeHeader treeHeader(345);
	BOOST_REQUIRE_EQUAL(treeHeader.getRunNumber(), 345);
}

BOOST_AUTO_TEST_CASE(headerWithStageInfo)
{
	JPetTreeHeader treeHeader;
	treeHeader.addStageInfo("name", "myDescription", 3, "time_stamp");
	BOOST_REQUIRE_EQUAL(treeHeader.getStagesNb(), 1);
	BOOST_REQUIRE_EQUAL(treeHeader.getRunNumber(), -1 );
	BOOST_REQUIRE_EQUAL(treeHeader.getBaseFileName(), "filename not set" );
	BOOST_REQUIRE_EQUAL(treeHeader.getSourcePosition(), -1 );
	BOOST_REQUIRE_EQUAL(treeHeader.getProcessingStageInfo(0).fModuleName, "name");
	BOOST_REQUIRE_EQUAL(treeHeader.getProcessingStageInfo(0).fModuleDescription, "myDescription");
}

BOOST_AUTO_TEST_CASE(simpleTest)
{
	JPetTreeHeader treeHeader;
	treeHeader.setBaseFileName("baseFileName");
	BOOST_REQUIRE_EQUAL(treeHeader.getBaseFileName(), "baseFileName");
	treeHeader.setSourcePosition(2);
	BOOST_REQUIRE_EQUAL(treeHeader.getSourcePosition(), 2);
}

BOOST_AUTO_TEST_CASE(headerWithVariable)
{
	JPetTreeHeader treeHeader;
	treeHeader.setVariable("name", "value");
	BOOST_REQUIRE_EQUAL(treeHeader.getVariable("name"), "value");
	BOOST_REQUIRE_EQUAL(treeHeader.getVariable("blank name"), "");
}

BOOST_AUTO_TEST_SUITE_END()
