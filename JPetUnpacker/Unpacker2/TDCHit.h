#ifndef TDCHit_h
#define TDCHit_h

#include <TObject.h>

#define MAX_HITS 50

class TDCHit : public TObject {
  
protected:
  Int_t channel;

  Int_t leadsNum;
  int leadFineTimes[MAX_HITS];
  int leadCoarseTimes[MAX_HITS];
  int leadEpochs[MAX_HITS];

  Int_t trailsNum;
  int trailFineTimes[MAX_HITS];
  int trailCoarseTimes[MAX_HITS];
  int trailEpochs[MAX_HITS];
  
public:

  TDCHit();
  ~TDCHit();
  
  void SetChannel(Int_t channel) { this->channel = channel; }
  
	void AddLeadTime(int fine, int coarse, int epoch);
	void AddTrailTime(int fine, int coarse, int epoch);

	int GetChannel() { return channel; }

	int GetLeadsNum() { return leadsNum; }
	int GetLeadFine(int mult) { return leadFineTimes[mult]; }
	int GetLeadCoarse(int mult) { return leadCoarseTimes[mult]; }
	int GetLeadEpoch(int mult) { return leadEpochs[mult]; }

	int GetTrailsNum() { return trailsNum; }
	int GetTrailFine(int mult) { return trailFineTimes[mult]; }
	int GetTrailCoarse(int mult) { return trailCoarseTimes[mult]; }
	int GetTrailEpoch(int mult) { return trailEpochs[mult]; }


  ClassDef(TDCHit,1);
};

#endif
