/**
 * @file SDAMatchLORs.h
 * @author Szymon Niedzwiecki, szymon.niedzwiecki@googlemail.com
 * @copyright Copyright (c) 2015, Szymon Niedzwiecki
 * @brief Producer of JPetLOR 
 * Reads a TTree of JPetHit and transforms them into JPetLOR objects
 */

#ifndef _JPETANALYSISMODULE_SDAMATCHLORS_H_
#define _JPETANALYSISMODULE_SDAMATCHLORS_H_

#include "../../JPetTask/JPetTask.h"
#include "../../JPetLOR/JPetLOR.h"
#include "../../JPetHit/JPetHit.h"
#include "TCanvas.h"

class SDAMatchLORs: public JPetTask
{

public:

  SDAMatchLORs(const char* name, const char* description);
  virtual ~SDAMatchLORs();
  virtual void exec();
  virtual void init(const JPetTaskInterface::Options& /* opts */);
  virtual void terminate();

private:
  std::vector<JPetLOR> createLORs(std::vector<JPetHit>& hits);
  void saveLORs(std::vector<JPetLOR> lors);

  std::vector<JPetHit> fHitsArray;
  int fTSlot;
  int fMatched;
  int fCurrentEventNumber;
};

#endif
