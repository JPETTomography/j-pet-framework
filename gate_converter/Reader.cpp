#include "Reader.h"
#include "TCanvas.h"
#include <iostream>

void Reader::init()
{
  h_volID_1 = new TH1D("h_vol_id1", "", 601, -0.5, 600.5);
  h_volID_2 = new TH1D("h_vol_id2", "", 601, -0.5, 600.5);
  h_sci_id = new TH1D("h_sci_id", "", 601, -0.5, 600.5);
  h_x_y = new TH2D("h_x_y", "", 1000, -50, 50, 1000, -50, 50);

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
  h_volID_1->Fill(volID[1]);
  h_volID_2->Fill(volID[2]);
  gate_hit.sci_id = get_scintillator_id();
  h_sci_id->Fill(gate_hit.sci_id);
  h_x_y->Fill(posx, posy);
  return &gate_hit;
}

void Reader::close()
{
  p_file->Close();
  delete p_file;
  std::cout << counter << std::endl;
  TCanvas c("c");
  h_volID_1->Draw("hist");
  c.Print("h_volID_1.png");
  h_volID_2->Draw("hist");
  c.Print("h_volID_2.png");
  h_sci_id->Draw("hist");
  c.Print("h_sci_id.png");
  h_x_y->Draw("colz");
  c.Print("h_x_y.png");

  delete h_volID_1;
  delete h_volID_2;
  delete h_sci_id;
  delete h_x_y;
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
