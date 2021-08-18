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
 *  @file JPetGeantDecayTree.h
 */

#ifndef JPETGEANTDECAYTREE_H
#define JPETGEANTDECAYTREE_H

#include "TObject.h"
#include "TVector3.h"
#include <map>
#include <vector>

/**
 * @class JPetGeantDecayTree
 * @brief Class stores decay tree structures (in form of vertices and tracks)
 * Class is not yet fully implemented
 */

enum InteractionType
{
  kPrimaryGamma,
  kScattActivePart,
  kScattNonActivePart,
  kSecondaryPart,
  kUnknownInteractionType
};

struct Branch
{
  Branch(){};
  Branch(int trackID, int primaryBranch);
  int fTrackID = -1;         // ID of the track corresponding to this branch
  std::vector<int> fNodeIDs; // container for all of the nodes
  std::vector<InteractionType> fInteractionType;
  int fPrimaryBranchID = -1; //-1 for branch coming from primary photon, primary branchId otherwise

  void addNodeID(int nodeID, InteractionType interactionType);
  int getTrackID() const { return fTrackID; };
  int getPrimaryNodeID() const { return fNodeIDs[0]; };
  int getLastNodeID() const { return fNodeIDs[fNodeIDs.size() - 1]; };
  int getPrimaryBranchID() const { return fPrimaryBranchID; };
  int getPreviousNodeID(int nodeID) const;
  InteractionType getInteractionType(int nodeID) const;
};

class JPetGeantDecayTree : public TObject
{

public:
  JPetGeantDecayTree();
  ~JPetGeantDecayTree();

  void Clean();
  void ClearVectors();

  int FindPrimaryPhoton(int nodeID);
  void addNodeToBranch(int nodeID, int trackID, InteractionType interactionType);
  Branch getBranch(unsigned trackID) const;

private:
  std::vector<Branch> fBranches;
  std::map<int, int> fTrackBranchConnection;

  ClassDef(JPetGeantDecayTree, 4)
};

#endif /* !JPETGEANTDECAYTREE_H */
