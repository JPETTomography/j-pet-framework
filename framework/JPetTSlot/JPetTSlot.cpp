#include "JPetTSlot.h"

void JPetTSlot::addCh(JPetSigCh& new_ch)
{
  new (fSigChannels[fSize++]) JPetSigCh(new_ch);
}

ClassImp(JPetTSlot);
