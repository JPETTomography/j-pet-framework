#ifndef Sig_h
#define Sig_h

#include <TObject.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <TObject.h>

#define MaxSignals 10
#define MaxChannels  10
#define MaxChannelHits 20 
using namespace std;

class Sig : public TObject{
 public:
  int nSig;
  int nChannel;
  int channel[MaxChannels];
  float LTimes[MaxChannels][MaxChannelHits];
  float TTimes[MaxChannels][MaxChannelHits];

  Sig();//konstruktor
  ~Sig();//{Clear();}
  void Clear(void);
  ClassDef(Sig,1);  
};
#endif
