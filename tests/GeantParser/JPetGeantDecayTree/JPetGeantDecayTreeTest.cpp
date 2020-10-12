/**
 *  @copyright Copyright 2020 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file JPetGeantParserDecayTreeTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetGeantParserDecayTreeTest
#include <boost/test/unit_test.hpp>

#include "JPetGeantDecayTree/JPetGeantDecayTree.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(firstTreeTest)
{
  Branch root(6, -1);
  BOOST_REQUIRE_EQUAL(root.GetTrackID(), 6);
  // BOOST_REQUIRE_EQUAL(root.GetPrimaryNodeID(),-1);
  // BOOST_REQUIRE_EQUAL(root.GetLastNodeID(), -1);
  // BOOST_REQUIRE_EQUAL(root.GetPreviousNodeID(-1), -1);
  BOOST_REQUIRE_EQUAL(root.GetPrimaryBranchID(), -1);
  BOOST_REQUIRE_EQUAL(root.GetInteractionType(-1), kUnknownInteractionType);
}

BOOST_AUTO_TEST_CASE(addNodeIdTreeTest)
{
  Branch root(6, -1);
  root.AddNodeID(2, kScattActivePart);
  BOOST_REQUIRE_EQUAL(root.GetTrackID(), 6);
  BOOST_REQUIRE_EQUAL(root.GetPrimaryNodeID(), 2);
  BOOST_REQUIRE_EQUAL(root.GetLastNodeID(), 2);
  /// ? BOOST_REQUIRE_EQUAL(root.GetPreviousNodeID(-1), -1);
  // BOOST_REQUIRE_EQUAL(root.GetPreviousNodeID(2), -1);
  // BOOST_REQUIRE_EQUAL(root.GetPreviousNodeID(123), -1);
  BOOST_REQUIRE_EQUAL(root.GetPrimaryBranchID(), -1);
  BOOST_REQUIRE_EQUAL(root.GetInteractionType(-1), kUnknownInteractionType);
  BOOST_REQUIRE_EQUAL(root.GetInteractionType(2), kScattActivePart);
  BOOST_REQUIRE_EQUAL(root.GetInteractionType(123), kUnknownInteractionType);
}

BOOST_AUTO_TEST_SUITE_END()
