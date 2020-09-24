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



class JPetGeantDecayTree : public TObject 
{
 
    public:
        JPetGeantDecayTree();
        ~JPetGeantDecayTree();
        
        void Clean();
        void ClearVectors();
        InteractionType GetInteractionType(int nodeID, int trackID);
        int GetPreviousNodeID(int nodeID, int trackID);
        int GetPrimaryNodeID(int nodeID, int trackID);
        void AddNode(int nodeID, int previousNodeID, int trackID, InteractionType interactionType);

    private:
        int fMinSecondaryMultiplicity = 10;
// fNodeTrackConnections is constructed as {nodeID, previous NodeID, connecting trackID}
// previous node for primary gamma = -1
        std::vector<std::tuple<int, int, int>> fNodeConnections;
// fNodeInteractionType connects nodeID with the type of interaction and trackID
// types of interaction: 100 - scattering in active part, 10 scattering in non-active part
// 0 - secondary particle generation
        std::vector<std::tuple<int, InteractionType, int>> fNodeInteractionType;

     ClassDef(JPetGeantDecayTree,3)

};

#endif
