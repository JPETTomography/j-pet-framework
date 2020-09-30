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
 *  @file JPetGeantDecayTree.h
 */

#ifndef JPETGEANTDECAYTREE_H
#define JPETGEANTDECAYTREE_H

#include "TVector3.h" 
#include "TObject.h"
#include <vector>
#include <tuple>
#include <map>

/**
 * @class JPetGeantDecayTree
 * @brief Class stores decay tree structures (in form of vertices and tracks)
 * Class is not yet fully implemented
 */

enum InteractionType {
  primaryGamma, scattActivePart, scattNonActivePart, secondaryPart, unknown
};

struct Branch {
  Branch() {};
  Branch(int trackID, int primaryBranch);
  int fTrackID = -1;             //ID of the track corresponding to this branch
  std::vector<int> fNodeIDs;    //container for all of the nodes
  std::vector<InteractionType> fInteractionType;
  int fPrimaryBranchID = -1;       //-1 for branch coming from primary photon, primary branchId otherwise
  
  void AddNodeID(int nodeID, InteractionType interactionType);
  // cppcheck-suppress unusedFunction
  int GetTrackID() const { return fTrackID; };
  // cppcheck-suppress unusedFunction
  int GetPrimaryNodeID() const { return fNodeIDs[0]; };
  // cppcheck-suppress unusedFunction
  int GetLastNodeID() const { return fNodeIDs[fNodeIDs.size()-1]; };
  // cppcheck-suppress unusedFunction
  int GetPrimaryBranchID() const { return fPrimaryBranchID; };
  int GetPreviousNodeID(int nodeID) const;
  InteractionType GetInteractionType(int nodeID);
};

class JPetGeantDecayTree : public TObject
{

public:
  JPetGeantDecayTree();
  ~JPetGeantDecayTree();
  
  void Clean();
  void ClearVectors();
  
  int FindPrimaryPhoton(int nodeID);
  void AddNodeToBranch(int nodeID, int trackID, InteractionType interactionType);

private:
  std::vector<Branch> fBranches;
  std::map<int, int> fTrackBranchConnection;
     
  ClassDef(JPetGeantDecayTree,3)

};

#endif
