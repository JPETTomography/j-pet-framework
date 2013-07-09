#include <iostream>
#include "Sig.h"
using namespace std;

ClassImp(Sig);

Sig::Sig() {   
  nSig =0 ;
  nChannel = 0;
  for(int i=0;i<MaxChannels;i++)
    {
      channel[i] = 0;
      for(int j=0;j<MaxChannelHits;j++)
	{
	  LTimes[i][j] = 0.;
	  TTimes[i][j] = 0.;
	}
    }
}
Sig::~Sig() {
}

void Sig::Clear(void){
  nSig =0 ;
  nChannel = 0;
  for(int i=0;i<MaxChannels;i++)
    {
      channel[i] = 0;
      for(int j=0;j<MaxChannelHits;j++)
        {
          LTimes[i][j] = 0.;
          TTimes[i][j] = 0.;
        }
    }

}
