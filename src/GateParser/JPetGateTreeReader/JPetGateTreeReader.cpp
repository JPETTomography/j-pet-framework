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
 *  @file JPetGateTreeReader.cpp
 */

#include "JPetLoggerInclude.h"
#include <JPetGateTreeReader/JPetGateTreeReader.h>

#include <iostream>

JPetGateTreeReader::JPetGateTreeReader(const std::string& inFile, JPetGateTreeReader::DetectorGeometry geom, int nMaxEntries)
    : fInputFileName(inFile), fDetectorGeometry(geom), fNMaxEntries(nMaxEntries)
{
  fFile = new TFile(fInputFileName.c_str(), "READ");
  fTree = dynamic_cast<TTree*>(fFile->Get("Hits"));
  fEntries = fTree->GetEntries();
  if ((fNMaxEntries == -1) || (fNMaxEntries > fEntries))
  {
    fNMaxEntries = fEntries;
  }
  fTree->SetBranchAddress("PDGEncoding", &pdg, &b_pdg);
  fTree->SetBranchAddress("trackID", &track_id, &b_track_id);
  fTree->SetBranchAddress("parentID", &parent_id, &b_parent_id);
  fTree->SetBranchAddress("time", &time, &b_time);
  fTree->SetBranchAddress("eventID", &event_id, &b_event_id);
  fTree->SetBranchAddress("posX", &posx, &b_posx);
  fTree->SetBranchAddress("posY", &posy, &b_posy);
  fTree->SetBranchAddress("posZ", &posz, &b_posz);
  fTree->SetBranchAddress("edep", &edep, &b_edep);
  fTree->SetBranchAddress("processName", process_name, &b_process_name);
  fTree->SetBranchAddress("sourcePosX", &sourcex, &b_sourcex);
  fTree->SetBranchAddress("sourcePosY", &sourcey, &b_sourcey);
  fTree->SetBranchAddress("sourcePosZ", &sourcez, &b_sourcez);
  fTree->SetBranchAddress("volumeID", &volID, &b_volID);
}

JPetGateTreeReader::~JPetGateTreeReader()
{
  if (fFile)
  {
    fFile->Close();
    delete fFile;
  }
  INFO("Number of entries in input GATE tree : " + std::to_string(fEntries));
  INFO("Number of gate hits processed: " + std::to_string(fProcessedEntries));
}

bool JPetGateTreeReader::read()
{
  if (entry_index >= fNMaxEntries)
    return false;
  fTree->GetEntry(entry_index);
  ++entry_index;
  return true;
}

GateHit* JPetGateTreeReader::get()
{
  bool is_ok = parent_id == 0;
  is_ok = is_ok && pdg == 22;
  is_ok = is_ok && std::string(process_name) == "compt";
  if (!is_ok)
    return nullptr;
  ++fProcessedEntries;
  gate_hit.track_id = track_id;
  gate_hit.event_id = event_id;
  gate_hit.edep = edep;
  gate_hit.time = time;
  gate_hit.posx = posx / 10.0; // mm --> cm
  gate_hit.posy = posy / 10.0;
  gate_hit.posz = posz / 10.0;
  gate_hit.sourcex = sourcex;
  gate_hit.sourcey = sourcey;
  gate_hit.sourcez = sourcez;
  gate_hit.sci_id = getScintillatorId(volID[1], volID[2]);
  return &gate_hit;
}

int JPetGateTreeReader::getScintillatorId(int volID1, int volID2) const
{
  switch (fDetectorGeometry)
  {
  case DetectorGeometry::ThreeLayers:
    return 1 + volID1;
  case DetectorGeometry::TwentyFourModules:
    return 201 + volID1 * 13 + volID2;
  default:
    return 0;
  };
}
