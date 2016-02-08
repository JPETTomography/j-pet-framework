#include "TDCChannel.h"

using namespace std;

ClassImp(TDCChannel);

TDCChannel::TDCChannel() {
	hitsNum = 0;
	channel = -1;

	leadTime1 = -100000;
	trailTime1 = -100000;
	tot1 = -100000;
	referenceDiff1 = -100000;

	for (int i = 0; i < MAX_FULL_HITS; i++) {
		leadTimes[i] = -100000;
		trailTimes[i] = -100000;
		tots[i] = -100000;
		referenceDiffs[i] = -100000;
	}
}

TDCChannel::~TDCChannel() {}

void TDCChannel::AddHit(double lead, double trail, double ref) {
	if (hitsNum < MAX_FULL_HITS - 1) {
		if (hitsNum == 0) {
			leadTime1 = lead;
			trailTime1 = trail;
			tot1 = trail - lead;
			referenceDiff1 = ref - lead;
		}

		leadTimes[hitsNum] = lead;
		trailTimes[hitsNum] = trail;
		tots[hitsNum] = trail - lead;
		referenceDiffs[hitsNum] = ref - lead;


//cerr<<channel<<" "<<lead<<" "<<trail<<" "<<hitsNum<<endl;

		hitsNum++;
//		printf("Adding a hit on channel %d with lead %f and trail %f and tot %f\n", channel, lead, trail, trail - lead);
	}
}

void TDCChannel::AddHit(double lead, double trail) {
	if (hitsNum < MAX_FULL_HITS - 1) {
		if (hitsNum == 0) {
			leadTime1 = lead;
			trailTime1 = trail;
			tot1 = trail - lead;
		}

		leadTimes[hitsNum] = lead;
		trailTimes[hitsNum] = trail;
		tots[hitsNum] = trail - lead;

//cerr<<channel<<" "<<lead<<" "<<trail<<" "<<hitsNum<<endl;
		hitsNum++;

//		printf("Adding a hit on channel %d with lead %f and trail %f and tot %f\n", channel, lead, trail, trail - lead);
	}
}
