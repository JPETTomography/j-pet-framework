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
 *  @file JPetGateTreeReader.h
 */

#ifndef JPETGATETREEREADER_H
#define JPETGATETREEREADER_H

#include <GateHit/GateHit.h>
#include <TFile.h>
#include <TTree.h>
#include <string>

/**
 * @brief  Class responsible for reading the content of GATE root file.
 *
 */
class JPetGateTreeReader
{
public:
  enum class DetectorGeometry
  {
    Unknown = 0,
    ThreeLayers = 1,
    TwentyFourModules = 2
  };

  JPetGateTreeReader(const std::string& inFile, DetectorGeometry geom);

  bool read();
  GateHit* get();
  void close();

  int getScintillatorId(int volID1, int volID2) const;

  std::string fInputFileName;
  TFile* fFile = nullptr;
  TTree* fTree = nullptr;

  int entries = 0;
  int entry_index = 0;
  DetectorGeometry fDetectorGeometry = DetectorGeometry::Unknown;

  GateHit gate_hit;
  int event_id = -1;
  int track_id = -1;
  int parent_id = -1;
  int pdg = 0;
  int volID[10];

  float edep = 0.0;
  double time = 0.0;
  float posx = 0.0;
  float posy = 0.0;
  float posz = 0.0;
  float sourcex = 0.0;
  float sourcey = 0.0;
  float sourcez = 0.0;

  Char_t process_name[20];

  int level1ID = 0;
  int baseID = 0;

  unsigned int counter = 0;

  TBranch* b_event_id = nullptr;
  TBranch* b_track_id = nullptr;
  TBranch* b_parent_id = nullptr;
  TBranch* b_pdg = nullptr;

  TBranch* b_edep = nullptr;
  TBranch* b_time = nullptr;
  TBranch* b_posx = nullptr;
  TBranch* b_posy = nullptr;
  TBranch* b_posz = nullptr;
  TBranch* b_sourcex = nullptr;
  TBranch* b_sourcey = nullptr;
  TBranch* b_sourcez = nullptr;
  TBranch* b_process_name = nullptr;
  TBranch* b_volID = nullptr;
};

#endif /*  !JPETGATETREEREADER_H */
