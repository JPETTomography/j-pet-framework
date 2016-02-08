#include "TDCHitExtended.h"
#include <iostream>

using namespace std;

ClassImp(TDCHitExtended);

TDCHitExtended::TDCHitExtended() {
  channel = -1;

  leadsNum = 0;
  trailsNum = 0;

  timeLineSize = 0;
    
  for (int i = 0; i < MAX_HITS * 2; i++) {
    leadFineTimes[i] = -100000;
    leadCoarseTimes[i] = -100000;
    leadEpochs[i] = -100000;

    trailFineTimes[i] = -100000;
    trailCoarseTimes[i] = -100000;
    trailEpochs[i] = -100000;

    fineTimeLine[i] = -100000;
    coarseTimeLine[i] = -100000;
    epochTimeLine[i] = -100000;
    shortTimeLine[i] = -100000;
    absoluteTimeLine[i] = -100000;
    riseTimeLine[i] = -100000;
  }
}

TDCHitExtended::~TDCHitExtended() {
}

void TDCHitExtended::ShiftEverythingUpByOne(int start) {
	for (int i = timeLineSize; i >= start; i--) {
		fineTimeLine[i+1] = fineTimeLine[i];
		coarseTimeLine[i+1] = coarseTimeLine[i];
		epochTimeLine[i+1] = epochTimeLine[i];
		shortTimeLine[i+1] = shortTimeLine[i];
		absoluteTimeLine[i+1] = absoluteTimeLine[i];
		riseTimeLine[i+1] = riseTimeLine[i];
	}
}

void TDCHitExtended::PrintOut() {
	cerr<<"Event on channel "<<channel<<": "<<endl;
	for(int i = 0; i < timeLineSize; i++) {
		cerr<<i<<": "<<shortTimeLine[i]<<" "<<riseTimeLine[i]<<" ";
		printf("%f\n", absoluteTimeLine[i]);
	}
}
