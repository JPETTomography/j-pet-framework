#include "./JPetPhysSigWriter.h"

bool JPetPhysSigWriter::Write (const vector<JPetSignal>& obj, const char* filename) {
  
  if(!OpenFile(filename)) {
    ERROR("Could not write to file.");
    return false;
  }

  TTree tree("PhysSig","PhysSig");

  JPetSignal* filler = new JPetSignal;

  tree.Branch ("JPetSignal", "JPetSignal", &filler);
  
  for (int i=0; i<obj.size(); i++) {
    *filler = obj[i];
    tree.Fill();
  }

  tree.Write();

  tree.Print();
  CloseFile();

  return true;
}
