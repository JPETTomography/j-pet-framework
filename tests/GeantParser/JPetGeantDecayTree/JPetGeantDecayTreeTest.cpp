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

BOOST_AUTO_TEST_CASE(branch_default_constructor)
{
  int testID = -1;
  
  Branch branch;
  
  BOOST_REQUIRE_EQUAL(branch.GetTrackID(), testID);
  BOOST_REQUIRE_EQUAL(branch.GetPrimaryBranchID(), testID);
}

BOOST_AUTO_TEST_CASE(branch_nonstandard_constructor)
{
  int primaryBranchID = 1;
  int trackID = 2;
  
  Branch branch(trackID, primaryBranchID);
  
  BOOST_REQUIRE_EQUAL(branch.GetTrackID(), trackID);
  BOOST_REQUIRE_EQUAL(branch.GetPrimaryBranchID(), primaryBranchID);
}

BOOST_AUTO_TEST_CASE(check_branch_setting_one_element)
{
  int primaryBranchID = 1;
  int trackID = 2;
  int nodeID = 3;
  InteractionType interactionType = InteractionType::kPrimaryGamma;
  
  Branch branch(trackID, primaryBranchID);
  branch.AddNodeID(nodeID, interactionType);
  
  BOOST_REQUIRE_EQUAL(branch.GetPrimaryNodeID(), nodeID);
  BOOST_REQUIRE_EQUAL(branch.GetLastNodeID(), nodeID);
  BOOST_REQUIRE_EQUAL(branch.GetPreviousNodeID(nodeID), nodeID);
  BOOST_REQUIRE_EQUAL(branch.GetInteractionType(nodeID), interactionType);
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
  branch.AddNodeID(firstNodeID, firstInteractionType);
  branch.AddNodeID(secondNodeID, secondInteractionType);
  branch.AddNodeID(thirdNodeID, thirdInteractionType);
  
  BOOST_REQUIRE_EQUAL(branch.GetPrimaryNodeID(), firstNodeID);
  BOOST_REQUIRE_EQUAL(branch.GetLastNodeID(), thirdNodeID);
  BOOST_REQUIRE_EQUAL(branch.GetPreviousNodeID(thirdNodeID), secondNodeID);
  BOOST_REQUIRE_EQUAL(branch.GetPreviousNodeID(secondNodeID), firstNodeID);
  BOOST_REQUIRE_EQUAL(branch.GetInteractionType(firstNodeID), firstInteractionType);
  BOOST_REQUIRE_EQUAL(branch.GetInteractionType(secondNodeID), secondInteractionType);
  BOOST_REQUIRE_EQUAL(branch.GetInteractionType(thirdNodeID), thirdInteractionType);
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

  decayTree.AddNodeToBranch(firstNodeID, firstTrackID, firstInteractionType);
  decayTree.AddNodeToBranch(secondNodeID, firstTrackID, secondInteractionType);
  decayTree.AddNodeToBranch(thirdNodeID, firstTrackID, thirdInteractionType);
  decayTree.AddNodeToBranch(fourthNodeID, secondTrackID, fourthInteractionType);
  decayTree.AddNodeToBranch(fifthNodeID, thirdTrackID, fifthInteractionType);
  
  Branch firstBranch = decayTree.GetBranch(firstTrackID);
  Branch secondBranch = decayTree.GetBranch(secondTrackID);
  Branch thirdBranch = decayTree.GetBranch(thirdTrackID);
  
  BOOST_REQUIRE_EQUAL(firstBranch.GetPrimaryBranchID(), primaryBranchID);
  BOOST_REQUIRE_EQUAL(firstBranch.GetTrackID(), firstTrackID);
  BOOST_REQUIRE_EQUAL(firstBranch.GetPrimaryNodeID(), firstNodeID);
  BOOST_REQUIRE_EQUAL(firstBranch.GetLastNodeID(), thirdNodeID);
  BOOST_REQUIRE_EQUAL(firstBranch.GetPreviousNodeID(thirdNodeID), secondNodeID);
  BOOST_REQUIRE_EQUAL(firstBranch.GetPreviousNodeID(secondNodeID), firstNodeID);
  BOOST_REQUIRE_EQUAL(firstBranch.GetInteractionType(firstNodeID), firstInteractionType);
  BOOST_REQUIRE_EQUAL(firstBranch.GetInteractionType(secondNodeID), secondInteractionType);
  BOOST_REQUIRE_EQUAL(firstBranch.GetInteractionType(thirdNodeID), thirdInteractionType);

  BOOST_REQUIRE_EQUAL(secondBranch.GetPrimaryBranchID(), primaryBranchID);
  BOOST_REQUIRE_EQUAL(secondBranch.GetTrackID(), secondTrackID);
  BOOST_REQUIRE_EQUAL(secondBranch.GetPrimaryNodeID(), fourthNodeID);
  BOOST_REQUIRE_EQUAL(secondBranch.GetLastNodeID(), fourthNodeID);
  BOOST_REQUIRE_EQUAL(secondBranch.GetPreviousNodeID(fourthNodeID), fourthNodeID);
  BOOST_REQUIRE_EQUAL(secondBranch.GetInteractionType(fourthNodeID), fourthInteractionType);
  
  BOOST_REQUIRE_EQUAL(thirdBranch.GetPrimaryBranchID(), secondBranchID);
  BOOST_REQUIRE_EQUAL(thirdBranch.GetTrackID(), thirdTrackID);
  BOOST_REQUIRE_EQUAL(thirdBranch.GetPrimaryNodeID(), fifthNodeID);
  BOOST_REQUIRE_EQUAL(thirdBranch.GetLastNodeID(), fifthNodeID);
  BOOST_REQUIRE_EQUAL(thirdBranch.GetPreviousNodeID(fifthNodeID), fifthNodeID);
  BOOST_REQUIRE_EQUAL(thirdBranch.GetInteractionType(fifthNodeID), fifthInteractionType);
}

BOOST_AUTO_TEST_SUITE_END()
