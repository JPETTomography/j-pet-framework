#include "JPetTSlot.h"

void JPetTSlot::addCh(JPetSigCh& new_ch)
{
  fSigChannels.push_back( new JPetSigCh(new_ch) );
}

ClassImp(JPetTSlot);
