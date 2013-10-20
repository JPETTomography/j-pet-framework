/*
 *  JPetTslotRawWriter.h
 *  
 *
 *  Created by Karol Stola on 13-09-14.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include <TFile.h>
#include <TTree.h>
#include <cstdlib>
#include "../../Event.h"
#include "../../JPetLoggerInclude.h"
#include "../JPetTSlot/JPetTSlot.h"
#include "../JPetSigCh/JPetSigCh.h"
#include "../JPetWriter/JPetWriter.h"


class JPetTSlotRawWriter: public JPetWriter{
    //bool Write(const TNamed& data){}
public:
	static bool Write(const vector<JPetTSlot>& obj, const char* file_name);
};
