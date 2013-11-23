#include "JPetTRB.h"

ClassImp(JPetTRB);

void JPetTRB::init(){
    SetNameTitle("JPetTRB", "Trigger Readout Board");
}

JPetTRB::JPetTRB(){
    init();
}

JPetTRB::JPetTRB(int id, int type, int channel)
: fID(id)
, fType(type)
, fChan(channel)
{
    init();
}