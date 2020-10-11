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
 *  @file JPetGeantDecayTree.cpp
 */

#include "JPetGeantDecayTree/JPetGeantDecayTree.h"

ClassImp(JPetGeantDecayTree)

Branch::Branch(int trackID, int primaryBranch)
{
  fTrackID = trackID;
  fPrimaryBranchID = primaryBranch;
}

void Branch::AddNodeID(int nodeID, InteractionType interactionType)
{
  fNodeIDs.push_back(nodeID);
  fInteractionType.push_back(interactionType);
}

int Branch::GetPreviousNodeID(int nodeID) const
{
  if (fNodeIDs.size() > 1) {
    for (unsigned i=fNodeIDs.size(); i>1; i--) {
      if (fNodeIDs[i-1] == nodeID)
        return fNodeIDs[i-2];
    }
  }
  return fNodeIDs[0];
}

InteractionType Branch::GetInteractionType(int nodeID) const
{
  for (unsigned i = fNodeIDs.size(); i > 0; i--)
  {
    if (fNodeIDs[i - 1] == nodeID)
      return fInteractionType[i - 1];
  }
  return kUnknownInteractionType;
}

JPetGeantDecayTree::JPetGeantDecayTree() {}

JPetGeantDecayTree::~JPetGeantDecayTree() 
{
  fBranches.clear();
  fTrackBranchConnection.clear();
}

void JPetGeantDecayTree::Clean()
{
  this->ClearVectors();
}

void JPetGeantDecayTree::ClearVectors() 
{
  fBranches.clear();
  fTrackBranchConnection.clear();
}

int JPetGeantDecayTree::FindPrimaryPhoton(int nodeID)
{
  for (unsigned i=fBranches.size(); i>0; i--) {
    if (fBranches[i-1].GetLastNodeID() == nodeID)
      return i-1;
  }
  return -1;
}

void JPetGeantDecayTree::AddNodeToBranch(int nodeID, int trackID, InteractionType interactionType)
{
  auto search = fTrackBranchConnection.find(trackID);
  if (search == fTrackBranchConnection.end()) {
    int branchSize = fBranches.size();
    int primaryBranchID = -1;
    if (interactionType == kSecondaryPart)
      primaryBranchID = FindPrimaryPhoton(nodeID/10);
    Branch newBranch(trackID, primaryBranchID);
    newBranch.AddNodeID(nodeID, interactionType);
    fBranches.push_back(newBranch);
    fTrackBranchConnection.insert(std::make_pair(trackID, branchSize));
  } else {
    int branchID = fTrackBranchConnection.at(trackID);
    fBranches[branchID].AddNodeID(nodeID, interactionType);
  }
}
