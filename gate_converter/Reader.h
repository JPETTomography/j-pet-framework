#ifndef Reader_h
#define Reader_h

#include "GateHit.h"
#include "TBranch.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include <string>

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
  TH1D* h_volID_1 = nullptr;
  TH1D* h_volID_2 = nullptr;
  TH1D* h_sci_id = nullptr;
  TH2D* h_x_y = nullptr;

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

#endif
