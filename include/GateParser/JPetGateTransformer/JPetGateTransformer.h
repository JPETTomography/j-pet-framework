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
 *  @file JPetGateTransformer.h
 */

#ifndef JPETGATETRANSFORMER_H
#define JPETGATETRANSFORMER_H

#include "JPetTask/JPetTask.h"
#include <GateHit/GateHit.h>

class Writer
{
public:
  Writer() {}
  void init();
  void write(GateHit gh);
  void close();
  void test();
  void set_output_file_path(std::string path);

  std::string output_file_path = "";
  TFile* p_file = nullptr;
  TTree* p_tree = nullptr;
  GateHit* p_gate_hit = nullptr;
};

class Reader
{
public:
  enum class DetectorGeometry
  {
    Unknown = 0,
    ThreeLayers = 1,
    TwentyFourModules = 2
  };

  Reader() {}
  void init();
  bool read();
  GateHit* get();
  void close();

  void set_geometry(DetectorGeometry dg);
  int get_scintillator_id();
  void set_input_file_path(std::string path);

  std::string input_file_path = "";
  TFile* p_file = nullptr;
  TTree* p_tree = nullptr;
  int entries = 0;
  int entry_index = 0;
  DetectorGeometry detector_geometry = DetectorGeometry::Unknown;

  GateHit gate_hit;
  // Zmienne branchów
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

  // Branche
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

class JPetGateTransformer : public JPetTask
{
public:
  enum class DetectorGeometry
  {
    kUnknown = 0,
    kThreeLayers = 1,
    kTwentyFourModules = 2
  };
  using OptsStrAny = std::map<std::string, boost::any>;
  explicit JPetGateTransformer(const char* name = "");
  bool init(const JPetParams& inOptions) override;
  bool run(const JPetDataInterface& inData) override;
  bool terminate(JPetParams& outOptions) override;

private:
  ////void init();
  // bool read();
  // GateHit* get();
  // void close();

  // void set_geometry(DetectorGeometry dg);
  // int get_scintillator_id();
  // void set_input_file_path(std::string path);

  // std::string input_file_path = "";
  // TFile* p_file = nullptr;
  // TTree* p_tree = nullptr;
  // int entries = 0;
  // int entry_index = 0;
  // DetectorGeometry detector_geometry = DetectorGeometry::kUnknown;

  // GateHit gate_hit;

  //// Zmienne branchów
  // int event_id = -1;
  // int track_id = -1;
  // int parent_id = -1;
  // int pdg = 0;
  // int volID[10];

  // float edep = 0.0;
  // double time = 0.0;
  // float posx = 0.0;
  // float posy = 0.0;
  // float posz = 0.0;
  // float sourcex = 0.0;
  // float sourcey = 0.0;
  // float sourcez = 0.0;

  // Char_t process_name[20];

  // int level1ID = 0;
  // int baseID = 0;

  // unsigned int counter = 0;

  //// Branche
  // TBranch* b_event_id = nullptr;
  // TBranch* b_track_id = nullptr;
  // TBranch* b_parent_id = nullptr;
  // TBranch* b_pdg = nullptr;

  // TBranch* b_edep = nullptr;
  // TBranch* b_time = nullptr;
  // TBranch* b_posx = nullptr;
  // TBranch* b_posy = nullptr;
  // TBranch* b_posz = nullptr;
  // TBranch* b_sourcex = nullptr;
  // TBranch* b_sourcey = nullptr;
  // TBranch* b_sourcez = nullptr;
  // TBranch* b_process_name = nullptr;
  // TBranch* b_volID = nullptr;

protected:
  OptsStrAny fOptions;
};

#endif /*  !JPETGATETRANSFORMER_H */
