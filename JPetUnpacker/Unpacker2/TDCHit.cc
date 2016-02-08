#include "TDCHit.h"
#include <iostream>

using namespace std;

ClassImp(TDCHit);

TDCHit::TDCHit() {
  channel = -1;

  leadsNum = 0;
  trailsNum = 0;
    
  for (int i = 0; i < MAX_HITS; i++) {
    leadFineTimes[i] = -100000;
    leadCoarseTimes[i] = -100000;
    leadEpochs[i] = -100000;

    trailFineTimes[i] = -100000;
    trailCoarseTimes[i] = -100000;
    trailEpochs[i] = -100000;
  }
}

TDCHit::~TDCHit() {
}

void TDCHit::AddLeadTime(int fine, int coarse, int epoch) {
	leadFineTimes[leadsNum] = fine;
	leadCoarseTimes[leadsNum] = coarse;
	leadEpochs[leadsNum] = epoch;

	leadsNum++;
}

void TDCHit::AddTrailTime(int fine, int coarse, int epoch) {
	trailFineTimes[trailsNum] = fine;
	trailCoarseTimes[trailsNum] = coarse;
	trailEpochs[trailsNum] = epoch;

	trailsNum++;
}
