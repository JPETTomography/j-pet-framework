#include "JPetTOMBChannel.h"


ClassImp(JPetTOMBChannel);

JPetTOMBChannel::JPetTOMBChannel(): fChannel(0), fThreshold(-1), fFEB(NULL), fTRB(NULL), fPM(NULL)	
{
  SetName("JPetTOMBChannel");
}

JPetTOMBChannel::JPetTOMBChannel(unsigned int p_channel): fChannel(p_channel), fThreshold(-1), fFEB(NULL), fTRB(NULL), fPM(NULL)	
{
  SetName("JPetTOMBChannel");
}

JPetTOMBChannel::~JPetTOMBChannel()
{
}

