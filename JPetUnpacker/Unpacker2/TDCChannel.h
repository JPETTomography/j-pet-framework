#ifndef TDCChannel_h
#define TDCChannel_h

#include <fstream>
#include <TObject.h>
#include <TClonesArray.h>
#include <iostream>

#define MAX_FULL_HITS 100

class TDCChannel : public TObject {

protected:
  Int_t channel;

	double leadTime1;
	double trailTime1;
	double tot1;
	double referenceDiff1;

	double leadTimes[MAX_FULL_HITS];
	double trailTimes[MAX_FULL_HITS];
	double tots[MAX_FULL_HITS];
	double referenceDiffs[MAX_FULL_HITS];
	int hitsNum;

  
public:

  TDCChannel();
  ~TDCChannel();
  
  void SetChannel(Int_t channel) { this->channel = channel; }
	int GetChannel() { return channel; }

	int GetHitsNum() { return hitsNum; }

	void AddHit(double lead, double trail, double ref);
	void AddHit(double lead, double trail);
	double GetLeadTime1() { return leadTime1; }
	double GetLeadTime(int mult) { return leadTimes[mult]; }
	double GetTrailTime1() { return trailTime1; }
	double GetTrailTime(int mult) { return trailTimes[mult]; }
	double GetTOT1() { return tot1; }
	int GetMult() { return hitsNum; }
	double GetTOT(int mult) { return tots[mult]; }



  ClassDef(TDCChannel,1);
};

#endif
