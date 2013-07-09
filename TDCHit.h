#ifndef TDCHit_h
#define TDCHit_h

#include <TObject.h>

#define MAX_HITS 100

class TDCHit : public TObject {
  
private:
  Int_t channel;
  float leadTime1;
  float trailTime1;
  float leadTimes[MAX_HITS];
  float trailTimes[MAX_HITS];
  Int_t leadsNum;
  Int_t trailsNum;
  Int_t tot;
  
public:

  TDCHit();
  ~TDCHit();
  
  void SetChannel(Int_t channel) { this->channel = channel; }
  
  void AddLeadTime(Int_t time);
  void AddTrailTime(Int_t time);
  void AddTot(Int_t time);
  
  Int_t GetChannel() { return channel; }
  float GetLeadTime1() { return leadTime1; }
  float GetTrailTime1() { return trailTime1; }
  Int_t GetLeadsNum() { return leadsNum; }
  Int_t GetTrailsNum() { return trailsNum; }
  float GetLeadTime(int mult) { return leadTimes[mult]; }
  float GetTrailTime(int mult) { return trailTimes[mult]; }
  Int_t GetTot() { return tot; }
  
  ClassDef(TDCHit,1);
};

#endif
