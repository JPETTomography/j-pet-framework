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
#include <JPetGeomMapping/JPetGeomMapping.h>
#include <JPetSmearingFunctions/JPetSmearingFunctions.h>

class JPetGateTreeWriter
{
public:
  JPetGateTreeWriter(const std::string& outFileName);
  void write(GateHit gh);
  void close();

  std::string fOutputFileName;
  TFile* fFile = nullptr;
  TTree* fTree = nullptr;
  GateHit* fGateHit = nullptr;
};

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

/**
 * @brief Transforming the Gate root file into a file with hits.
 *
 */
class JPetGateTransformer : public JPetTask
{
public:
  using OptsStrAny = std::map<std::string, boost::any>;
  enum class DetectorGeometry
  {
    kUnknown = 0,
    kThreeLayers = 1,
    kTwentyFourModules = 2
  };
  static bool transformTree(const std::string& inFile, const std::string& outFile, JPetGateTreeReader::DetectorGeometry geom);
  bool transformTree2(const std::string& inFile, const std::string& outFile, JPetGateTreeReader::DetectorGeometry geom);
  explicit JPetGateTransformer(const char* name = "");
  bool init(const JPetParams& inOptions) override;
  bool run(const JPetDataInterface& inData) override;
  bool terminate(JPetParams& outOptions) override;

  unsigned long getOriginalSeed() const;

protected:
  OptsStrAny fOptions;
  JPetParams fParams;

  std::vector<JPetHit> fStoredHits; ///< save RECONSTRUCTED MC hits into single time window when it contains enough hits

  int fLastEventID = -1;
  JPetGeomMapping* fDetectorMap = nullptr;
  double fMaxTime = 0.;
  double fMinTime = -50.e6;           // electronic time window 50 micro seconds - true for run 3
  double fSimulatedActivity = 4.7;    // 4.7; //< in MBq; value for run3
  double fExperimentalThreshold = 10; //< in keV
  JPetHitExperimentalParametrizer fExperimentalParametrizer;
  double fTimeShift = fMinTime;
  unsigned long fSeed = 0.;

  const JPetParamBank& getParamBank(); // from JPetUserTask
  void processGateHit(GateHit* gate_hit);
  void saveHits();
  void saveReconstructedHit(JPetHit recHit);
  unsigned int getNumberOfDecaysInWindow() const;
  float getNextTimeShift();
  void clearTimeDistoOfDecays();
  bool isTimeWindowFull() const;
  JPetTimeWindow* fOutputEvents = 0; // from JPetUserTask
  std::vector<float> fTimeDistroOfDecays = {};
  std::vector<float> fTimeDiffDistro = {};
  unsigned int fCurrentIndexTimeShift = 0;
};
#endif /*  !JPETGATETRANSFORMER_H */
