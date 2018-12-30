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
 *  @file JPetMCDecayTree.h
 */

#ifndef _JPETMCHIT_H_
#define _JPETMCHIT_H_

#include "./JPetHit/JPetHit.h"

/**
 * @brief Data class representing a hit of a photon in the scintillator strip based on Monte Carlo simulation.
 *
 */
class JPetMCDecayTree : public TObject 
{

public:
  JPetMCDecayTree();

private:

  UInt_t fMCMCDecayTreeIndex = 0u;
  UInt_t fMCVtxIndex = 0u;

  UInt_t fnVertices = 0u;
  UInt_t fnTracks = 0u;
  // add also track and vertices structures  

  ClassDef(JPetMCDecayTree, 1);
};

#endif
