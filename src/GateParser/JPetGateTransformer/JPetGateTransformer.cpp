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
 *  @file JPetGateTransformer.cpp
 */

#include "JPetOptionsTools/JPetOptionsTools.h"
#include <JPetGateTransformer/JPetGateTransformer.h>
using namespace jpet_options_tools;

JPetGateTransformer::JPetGateTransformer(const char* name) : JPetTask(name) {}

bool JPetGateTransformer::init(const JPetParams& inParams)
{
  INFO("GateTransformer started.");
  fOptions = inParams.getOptions();

  // p_file = new TFile(input_file_path.c_str(), "READ");
  // p_tree = dynamic_cast<TTree*>(p_file->Get("Hits"));
  // entries = p_tree->GetEntries();

  // p_tree->SetBranchAddress("PDGEncoding", &pdg, &b_pdg);
  // p_tree->SetBranchAddress("trackID", &track_id, &b_track_id);
  // p_tree->SetBranchAddress("parentID", &parent_id, &b_parent_id);
  // p_tree->SetBranchAddress("time", &time, &b_time);
  // p_tree->SetBranchAddress("eventID", &event_id, &b_event_id);
  // p_tree->SetBranchAddress("posX", &posx, &b_posx);
  // p_tree->SetBranchAddress("posY", &posy, &b_posy);
  // p_tree->SetBranchAddress("posZ", &posz, &b_posz);
  // p_tree->SetBranchAddress("edep", &edep, &b_edep);
  // p_tree->SetBranchAddress("processName", process_name, &b_process_name);
  // p_tree->SetBranchAddress("sourcePosX", &sourcex, &b_sourcex);
  // p_tree->SetBranchAddress("sourcePosY", &sourcey, &b_sourcey);
  // p_tree->SetBranchAddress("sourcePosZ", &sourcez, &b_sourcez);
  // p_tree->SetBranchAddress("volumeID", &volID, &b_volID);

  return true;
}

bool JPetGateTransformer::run(const JPetDataInterface&)
{
  std::string g_output_file_name = "test.out";
  std::string g_input_file_name = "test.root";
  Reader::DetectorGeometry g_detector_geometry = Reader::DetectorGeometry::ThreeLayers;

  Writer w;
  w.set_output_file_path(g_output_file_name);
  w.init();
  Reader r;
  r.set_geometry(g_detector_geometry);
  r.set_input_file_path(g_input_file_name);
  r.init();
  while (r.read())
  {
    GateHit* p_gh = r.get();
    if (p_gh != nullptr)
      w.write(*p_gh);
  }
  r.close();
  w.close();
  // auto inputFileWithPath = getInputFile(fOptions);
  // auto outputPath = getOutputPath(fOptions);
  // if(outputPath == "") { outputPath = "./"; }
  // INFO(Form("Unzipping file: %s into %s", inputFileWithPath.c_str(), outputPath.c_str()));
  // if (!unzipFile(inputFileWithPath, outputPath)) {
  // ERROR(Form("Problem with unzipping file: %s", inputFileWithPath.c_str()));
  // return false;
  //}
  return true;
}

bool JPetGateTransformer::terminate(JPetParams& outParams)
{
  OptsStrAny new_opts;
  // setOutputFileType(new_opts, "hld");
  // auto outputFile =
  // getOutputPath(fOptions)
  //+ JPetCommonTools::stripFileNameSuffix(getInputFile(fOptions));
  // setOutputFile(new_opts, outputFile);

  // if (isOptionSet(fOptions, "firstEvent_int") && isOptionSet(fOptions, "lastEvent_int")) {
  // if (getOptionAsInt(fOptions, "firstEvent_int") != -1 && getOptionAsInt(fOptions, "lastEvent_int") != -1) {
  // setResetEventRangeOption(new_opts, true);
  //}
  //}

  // outParams = JPetParams(new_opts, outParams.getParamManagerAsShared());
  // INFO(Form(
  //"GateTransformer finished, unzipped file name: %s", outputFile.c_str()
  //));
  return true;
}

// bool JPetGateTransformer::read()
//{
// if (entry_index < entries)
// p_tree->GetEntry(entry_index);
// else
// return false;
//++entry_index;
// return true;
//}

// GateHit* JPetGateTransformer::get()
//{
// bool is_ok = parent_id == 0;
// is_ok = is_ok && pdg == 22;
// is_ok = is_ok && std::string(process_name) == "compt";
// if (!is_ok)
// return nullptr;
//++counter;
// gate_hit.track_id = track_id;
// gate_hit.event_id = event_id;
// gate_hit.edep = edep;
// gate_hit.time = time;
// gate_hit.posx = posx / 10.0; // mm --> cm
// gate_hit.posy = posy / 10.0;
// gate_hit.posz = posz / 10.0;
// gate_hit.sourcex = sourcex;
// gate_hit.sourcey = sourcey;
// gate_hit.sourcez = sourcez;
// gate_hit.sci_id = get_scintillator_id();
// return &gate_hit;
//}

// void JPetGateTransformer::close()
//{
// p_file->Close();
// delete p_file;
// std::cout << counter << std::endl;
//}

// void JPetGateTransformer::set_geometry(DetectorGeometry dg) { detector_geometry = dg; }

// int JPetGateTransformer::get_scintillator_id()
//{
// switch (detector_geometry)
//{
// case DetectorGeometry::kThreeLayers:
// return 1 + volID[1];
// case DetectorGeometry::kTwentyFourModules:
// return 201 + volID[1] * 13 + volID[2];
// default:
// return 0;
//};
//}

// void JPetGateTransformer::set_input_file_path(std::string path) { input_file_path = path; }

void Writer::init()
{
  p_file = new TFile(output_file_path.c_str() /*"data.mcGate.root"*/, "RECREATE");
  p_tree = new TTree("T", "T");
  p_gate_hit = new GateHit();
  p_tree->Branch("GHit", &p_gate_hit);
}

void Writer::write(GateHit gh)
{
  p_gate_hit->copy(gh);
  p_tree->Fill();
}

void Writer::close()
{
  p_file->Write();
  p_file->Close();
}

void Writer::test()
{
  init();
  for (int i = 1; i < 4; ++i)
  {
    GateHit gh;
    gh.event_id = i;
    write(gh);
  }
  close();
}

void Writer::set_output_file_path(std::string path) { output_file_path = path; }

void Reader::init()
{

  p_file = new TFile(input_file_path.c_str(), "READ");
  p_tree = dynamic_cast<TTree*>(p_file->Get("Hits"));
  entries = p_tree->GetEntries();

  p_tree->SetBranchAddress("PDGEncoding", &pdg, &b_pdg);
  p_tree->SetBranchAddress("trackID", &track_id, &b_track_id);
  p_tree->SetBranchAddress("parentID", &parent_id, &b_parent_id);
  p_tree->SetBranchAddress("time", &time, &b_time);
  p_tree->SetBranchAddress("eventID", &event_id, &b_event_id);
  p_tree->SetBranchAddress("posX", &posx, &b_posx);
  p_tree->SetBranchAddress("posY", &posy, &b_posy);
  p_tree->SetBranchAddress("posZ", &posz, &b_posz);
  p_tree->SetBranchAddress("edep", &edep, &b_edep);
  p_tree->SetBranchAddress("processName", process_name, &b_process_name);
  p_tree->SetBranchAddress("sourcePosX", &sourcex, &b_sourcex);
  p_tree->SetBranchAddress("sourcePosY", &sourcey, &b_sourcey);
  p_tree->SetBranchAddress("sourcePosZ", &sourcez, &b_sourcez);
  p_tree->SetBranchAddress("volumeID", &volID, &b_volID);
}

bool Reader::read()
{
  if (entry_index < entries)
    p_tree->GetEntry(entry_index);
  else
    return false;
  ++entry_index;
  return true;
}

GateHit* Reader::get()
{
  bool is_ok = parent_id == 0;
  is_ok = is_ok && pdg == 22;
  is_ok = is_ok && std::string(process_name) == "compt";
  if (!is_ok)
    return nullptr;
  ++counter;
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
  gate_hit.sci_id = get_scintillator_id();
  return &gate_hit;
}

void Reader::close()
{
  p_file->Close();
  delete p_file;
  std::cout << counter << std::endl;
}

void Reader::set_geometry(DetectorGeometry dg) { detector_geometry = dg; }

int Reader::get_scintillator_id()
{
  switch (detector_geometry)
  {
  case DetectorGeometry::ThreeLayers:
    return 1 + volID[1];
  case DetectorGeometry::TwentyFourModules:
    return 201 + volID[1] * 13 + volID[2];
  default:
    return 0;
  };
}

void Reader::set_input_file_path(std::string path) { input_file_path = path; }
