#include "JPetTSlot.h"

void JPetTSlot::AddCh(JPetSigCh& new_ch)
{
  new (fSigChannels[fSize++]) JPetSigCh(new_ch);
}

ClassImp(JPetTSlot);
