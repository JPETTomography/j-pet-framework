#ifndef EventIII_h
#define EventIII_h

#include <fstream>
#include <TObject.h>
#include <TClonesArray.h>
#include "TDCChannel.h"
#include <iostream>
#include <TTree.h>


class TDCChannel;

class EventIII : public TObject {
  
private:
  Int_t totalNTDCChannels;
  
public:
  TClonesArray* TDCChannels;
  
  EventIII();
  virtual ~EventIII() { Clear(); }
  
  TDCChannel* AddTDCChannel(int channel);
  
  Int_t GetTotalNTDCChannels() { return totalNTDCChannels; }
  
  TClonesArray* GetTDCChannelsArray() { return TDCChannels; }
  
  void Clear(void);
  
  ClassDef(EventIII,1);
  
};


#endif
