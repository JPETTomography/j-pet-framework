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
  finesNum = 0;
  coarsesNum = 0;
  tot = -100000;
  fineTime1 = -100000.;
  coarseTime1 = -100000.;
    
  for (int i = 0; i < MAX_HITS; i++) {
    leadTimes[i] = -100000;
    trailTimes[i] = -100000;
    fineTimes[i] = -100000.;
    coarseTimes[i] = -100000.;
  }
}

TDCHit::~TDCHit() {
}

void TDCHit::AddLeadTime(float time) {
  leadTimes[leadsNum] = time;
  
  if (leadsNum == 0)
    leadTime1 = time;
  
  leadsNum++;
}

void TDCHit::AddTrailTime(float time) {
  trailTimes[trailsNum] = time;
  
  if (trailsNum == 0)
    trailTime1 = time;
  
  trailsNum++;
}

void TDCHit::AddTot(float time) {
  tot = time;
}


void TDCHit::AddFineTime(float Ftime) {
    fineTimes[finesNum] = Ftime;

  if (finesNum == 0)
    fineTime1 = Ftime;

  finesNum++;
}

void TDCHit::AddCoarseTime(float Ctime) {
  coarseTimes[finesNum] = Ctime;

  if (coarsesNum == 0)
    coarseTime1 = Ctime;

  coarsesNum++;
}
