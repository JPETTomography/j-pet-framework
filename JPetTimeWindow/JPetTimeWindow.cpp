#include "JPetTimeWindow.h"

void JPetTimeWindow::addCh(JPetSigCh& new_ch)
{
  fSigChannels.push_back( new JPetSigCh(new_ch) );
}

ClassImp(JPetTimeWindow);
