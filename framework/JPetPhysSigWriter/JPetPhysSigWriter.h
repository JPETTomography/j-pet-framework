#ifndef _JPETPHYSSIGWRITER_H_
#define _JPETPHYSDIGWRITER_H_

#include "../JPetWriter/JPetWriter.h"
#include "../JPetSignal/JPetSignal.h"

#include "TFile.h"
#include "TTree.h"

#include <cstddef>
#include <vector>

class JPetPhysSigWriter: public JPetWriter{
  
  public:
 
  bool Write (const TNamed& data){}
  bool Write (const JPetSignal& obj, const char* filename);
  bool Write (const vector<JPetSignal>& obj, const char* filename);

};

#endif
