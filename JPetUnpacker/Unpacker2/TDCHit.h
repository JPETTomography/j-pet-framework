#ifndef TDCHit_h
#define TDCHit_h

#include <TObject.h>

#define MAX_HITS 100

class TDCHit : public TObject {
  
private:
  Int_t channel;
  float fineTime1;
  float coarseTime1;
  float fineTimes[MAX_HITS];
  float coarseTimes[MAX_HITS];
  float leadTime1;
  float trailTime1;
  float leadTimes[MAX_HITS];
  float trailTimes[MAX_HITS];
  Int_t leadsNum;
  Int_t trailsNum;
  Int_t finesNum;
  Int_t coarsesNum;
  float tot;
  
public:

  TDCHit();
  ~TDCHit();
  
  void SetChannel(Int_t channel) { this->channel = channel; }
  
  void AddLeadTime(float time);
  void AddTrailTime(float time);
  void AddTot(float time);
  void AddFineTime(float Ftime);
  void AddCoarseTime(float Ctime);
  
  Int_t GetChannel() { return channel; }
  float GetLeadTime1() { return leadTime1; }
  float GetTrailTime1() { return trailTime1; }
  float GetFineTime1() { return fineTime1; }
  float GetCoarseTime1() { return coarseTime1; }
  Int_t GetLeadsNum() { return leadsNum; }
  Int_t GetTrailsNum() { return trailsNum; }
  float GetLeadTime(int mult) { return leadTimes[mult]; }
  float GetTrailTime(int mult) { return trailTimes[mult]; }
  float GetFineTime(int mult) { return fineTimes[mult]; }
  float GetCoarseTime(int mult) { return coarseTimes[mult]; }
  float GetTot() { return tot; }
  
  ClassDef(TDCHit,1);
};

#endif
