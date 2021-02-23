#include "Writer.h"

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
