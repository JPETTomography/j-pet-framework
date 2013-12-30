#include "TDCHit.h"
#include <iostream>

using namespace std;

ClassImp(TDCHit);

TDCHit::TDCHit() {
  channel = -1;
  leadTime1 = -100000;
  trailTime1 = -100000;
  leadsNum = 0;
  trailsNum = 0;
  tot = -100000;
  for (int i = 0; i < MAX_HITS; i++) {
    leadTimes[i] = -100000;
    trailTimes[i] = -100000;
  }
}

TDCHit::~TDCHit() {
}

void TDCHit::AddLeadTime(Int_t time) {
  leadTimes[leadsNum] = time;
  
  if (leadsNum == 0)
    leadTime1 = time;
  
  leadsNum++;
}

void TDCHit::AddTrailTime(Int_t time) {
  trailTimes[trailsNum] = time;
  
  if (trailsNum == 0)
    trailTime1 = time;
  
  trailsNum++;
}

void TDCHit::AddTot(Int_t time) {
  tot = time;
}