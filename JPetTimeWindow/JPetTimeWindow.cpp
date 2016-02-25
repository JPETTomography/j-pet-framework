#include "JPetTimeWindow.h"

void JPetTimeWindow::addCh(JPetSigCh& new_ch)
{
  fSigChannels.push_back( JPetSigCh(new_ch) );
}

ClassImp(JPetTimeWindow);
