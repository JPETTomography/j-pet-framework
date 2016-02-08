#ifndef TDCHitExtended_h
#define TDCHitExtended_h

#include "TDCHit.h"

#define MAX_HITS 50

class TDCHitExtended : public TDCHit {
  
protected:

	int timeLineSize;

	int fineTimeLine[MAX_HITS*2];
	int coarseTimeLine[MAX_HITS*2];
	int epochTimeLine[MAX_HITS*2];
	double shortTimeLine[MAX_HITS*2];
	double absoluteTimeLine[MAX_HITS*2];
	bool riseTimeLine[MAX_HITS*2];
  
public:

	TDCHitExtended();
	~TDCHitExtended();

	void SetFineTimeLine(int fine, int index) { fineTimeLine[index] = fine; }
	void SetCoarseTimeLine(int coarse, int index) { coarseTimeLine[index] = coarse; }
	void SetEpochTimeLine(int epoch, int index) { epochTimeLine[index] = epoch; }
	void SetShortTimeLine(double time, int index) { shortTimeLine[index] = time; }
	void SetAbsoluteTimeLine(double time, int index) {absoluteTimeLine[index] = time; }
	void SetRisingEdge(bool edge, int index) { riseTimeLine[index] = edge; }

	double GetShortTimeLine(int mult) { return shortTimeLine[mult]; }
	double GetAbsoluteTimeLine(int mult) { return absoluteTimeLine[mult]; }
	bool GetRisingEdge(int mult) { return riseTimeLine[mult]; }

	void ShiftEverythingUpByOne(int start);

	void SetTimeLineSize(int size) { timeLineSize = size; }
	int GetTimeLineSize() { return timeLineSize; }

	void PrintOut();

  ClassDef(TDCHitExtended,1);
};

#endif
