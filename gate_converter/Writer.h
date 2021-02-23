#ifndef Writer_h
#define Writer_h

#include "GateHit.h"
#include "TFile.h"
#include "TTree.h"

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

#endif
