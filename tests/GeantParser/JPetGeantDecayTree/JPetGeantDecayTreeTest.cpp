/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
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

BOOST_AUTO_TEST_CASE(branch_default_constructor)
{
  int testID = -1;

  Branch branch;

  BOOST_REQUIRE_EQUAL(branch.getTrackID(), testID);
  BOOST_REQUIRE_EQUAL(branch.getPrimaryBranchID(), testID);
}

BOOST_AUTO_TEST_CASE(branch_nonstandard_constructor)
{
  int primaryBranchID = 1;
  int trackID = 2;

  Branch branch(trackID, primaryBranchID);

  BOOST_REQUIRE_EQUAL(branch.getTrackID(), trackID);
  BOOST_REQUIRE_EQUAL(branch.getPrimaryBranchID(), primaryBranchID);
}

BOOST_AUTO_TEST_CASE(check_branch_setting_one_element)
{
  int primaryBranchID = 1;
  int trackID = 2;
  int nodeID = 3;
  InteractionType interactionType = InteractionType::kPrimaryGamma;

  Branch branch(trackID, primaryBranchID);
  branch.addNodeID(nodeID, interactionType);

  BOOST_REQUIRE_EQUAL(branch.getPrimaryNodeID(), nodeID);
  BOOST_REQUIRE_EQUAL(branch.getLastNodeID(), nodeID);
  BOOST_REQUIRE_EQUAL(branch.getPreviousNodeID(nodeID), nodeID);
  BOOST_REQUIRE_EQUAL(branch.getInteractionType(nodeID), interactionType);
}

BOOST_AUTO_TEST_CASE(check_branch_setting_more_elements)
{
  int primaryBranchID = 1;
  int trackID = 2;
  int firstNodeID = 3;
  int secondNodeID = 13;
  int thirdNodeID = 113;
  InteractionType firstInteractionType = InteractionType::kPrimaryGamma;
  InteractionType secondInteractionType = InteractionType::kScattNonActivePart;
  InteractionType thirdInteractionType = InteractionType::kScattActivePart;

  Branch branch(trackID, primaryBranchID);
  branch.addNodeID(firstNodeID, firstInteractionType);
  branch.addNodeID(secondNodeID, secondInteractionType);
  branch.addNodeID(thirdNodeID, thirdInteractionType);

  BOOST_REQUIRE_EQUAL(branch.getPrimaryNodeID(), firstNodeID);
  BOOST_REQUIRE_EQUAL(branch.getLastNodeID(), thirdNodeID);
  BOOST_REQUIRE_EQUAL(branch.getPreviousNodeID(thirdNodeID), secondNodeID);
  BOOST_REQUIRE_EQUAL(branch.getPreviousNodeID(secondNodeID), firstNodeID);
  BOOST_REQUIRE_EQUAL(branch.getInteractionType(firstNodeID), firstInteractionType);
  BOOST_REQUIRE_EQUAL(branch.getInteractionType(secondNodeID), secondInteractionType);
  BOOST_REQUIRE_EQUAL(branch.getInteractionType(thirdNodeID), thirdInteractionType);
}

BOOST_AUTO_TEST_CASE(check_decayTree_creation_and_getting_branch)
{
  JPetGeantDecayTree decayTree;
  int primaryBranchID = -1;
  int firstTrackID = 2;
  int firstNodeID = 3;
  int secondNodeID = 13;
  int thirdNodeID = 113;
  int secondTrackID = 3;
  int secondBranchID = 1;
  int fourthNodeID = 3;
  int thirdTrackID = 5;
  int fifthNodeID = 30;

  InteractionType firstInteractionType = InteractionType::kPrimaryGamma;
  InteractionType secondInteractionType = InteractionType::kScattNonActivePart;
  InteractionType thirdInteractionType = InteractionType::kScattActivePart;
  InteractionType fourthInteractionType = InteractionType::kPrimaryGamma;
  InteractionType fifthInteractionType = InteractionType::kSecondaryPart;

  decayTree.addNodeToBranch(firstNodeID, firstTrackID, firstInteractionType);
  decayTree.addNodeToBranch(secondNodeID, firstTrackID, secondInteractionType);
  decayTree.addNodeToBranch(thirdNodeID, firstTrackID, thirdInteractionType);
  decayTree.addNodeToBranch(fourthNodeID, secondTrackID, fourthInteractionType);
  decayTree.addNodeToBranch(fifthNodeID, thirdTrackID, fifthInteractionType);

  Branch firstBranch = decayTree.getBranch(firstTrackID);
  Branch secondBranch = decayTree.getBranch(secondTrackID);
  Branch thirdBranch = decayTree.getBranch(thirdTrackID);

  BOOST_REQUIRE_EQUAL(firstBranch.getPrimaryBranchID(), primaryBranchID);
  BOOST_REQUIRE_EQUAL(firstBranch.getTrackID(), firstTrackID);
  BOOST_REQUIRE_EQUAL(firstBranch.getPrimaryNodeID(), firstNodeID);
  BOOST_REQUIRE_EQUAL(firstBranch.getLastNodeID(), thirdNodeID);
  BOOST_REQUIRE_EQUAL(firstBranch.getPreviousNodeID(thirdNodeID), secondNodeID);
  BOOST_REQUIRE_EQUAL(firstBranch.getPreviousNodeID(secondNodeID), firstNodeID);
  BOOST_REQUIRE_EQUAL(firstBranch.getInteractionType(firstNodeID), firstInteractionType);
  BOOST_REQUIRE_EQUAL(firstBranch.getInteractionType(secondNodeID), secondInteractionType);
  BOOST_REQUIRE_EQUAL(firstBranch.getInteractionType(thirdNodeID), thirdInteractionType);

  BOOST_REQUIRE_EQUAL(secondBranch.getPrimaryBranchID(), primaryBranchID);
  BOOST_REQUIRE_EQUAL(secondBranch.getTrackID(), secondTrackID);
  BOOST_REQUIRE_EQUAL(secondBranch.getPrimaryNodeID(), fourthNodeID);
  BOOST_REQUIRE_EQUAL(secondBranch.getLastNodeID(), fourthNodeID);
  BOOST_REQUIRE_EQUAL(secondBranch.getPreviousNodeID(fourthNodeID), fourthNodeID);
  BOOST_REQUIRE_EQUAL(secondBranch.getInteractionType(fourthNodeID), fourthInteractionType);

  BOOST_REQUIRE_EQUAL(thirdBranch.getPrimaryBranchID(), secondBranchID);
  BOOST_REQUIRE_EQUAL(thirdBranch.getTrackID(), thirdTrackID);
  BOOST_REQUIRE_EQUAL(thirdBranch.getPrimaryNodeID(), fifthNodeID);
  BOOST_REQUIRE_EQUAL(thirdBranch.getLastNodeID(), fifthNodeID);
  BOOST_REQUIRE_EQUAL(thirdBranch.getPreviousNodeID(fifthNodeID), fifthNodeID);
  BOOST_REQUIRE_EQUAL(thirdBranch.getInteractionType(fifthNodeID), fifthInteractionType);
}

BOOST_AUTO_TEST_SUITE_END()
